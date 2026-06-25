#include "ulpDiff.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <tuple>

// a + x*y
std::tuple<float,float> cfma(float a, float x, float y) {
  auto r = std::fma(x,y,a);
  auto t = r-a;
  auto e = std::fma(x,y,-t);
  return {r,e};
}

// a + y*xx
std::tuple<float,float> cfma(float a, float y, std::tuple<float,float> xx) {
  auto [x,ex] = xx;
  a = std::fma(ex,y,a);
  auto r = std::fma(x,y,a);
  auto t = r-a;
  auto e = std::fma(x,y,-t);
  return {r,e};
}


template< typename T>
inline T logf_P8(T y) {
   return  y * ( float(0x1.00000cp0) + y * (float(-0x8.0003p-4) + y * (float(0x5.55087p-4) + y * ( float(-0x3.fedcep-4) + y * (float(0x3.3a1dap-4) + y * (float(-0x2.cb55fp-4) + y * (float(0x2.38831p-4) + y * (float(-0xf.e87cap-8) )))))))) ;
}

template< typename T>
inline TwoFloat<T> logf_P8FF(T y) {
   using namespace detailsTwoFloat;
   return  y * ( float(0x1.00000cp0) + y * (float(-0x8.0003p-4) + y * (float(0x5.55087p-4) + y * ( float(-0x3.fedcep-4) + y * (float(0x3.3a1dap-4) + y * (float(-0x2.cb55fp-4) + y * (float(0x2.38831p-4) + TwoFloat<T>(y,float(-0xf.e87cap-8),fromProd())  ))))))) ;
}

inline float logf_P8C(float y) {
   auto [r,e] = cfma( float(0x1.00000cp0), y , cfma(float(-0x8.0003p-4),  y,  cfma(float(0x5.55087p-4), y,  cfma( float(-0x3.fedcep-4), y, cfma(float(0x3.3a1dap-4),  y, cfma(float(-0x2.cb55fp-4), y,cfma(float(0x2.38831p-4), y,(float(-0xf.e87cap-8) )))))))) ;
   auto c = y*r;
   return c + (std::fma(y,r,-c) +  y*e);
}


int main() {
  using namespace detailsTwoFloat;
  using FF = TwoFloat<float>;


  int nf=0; int n2f=0; int nc=0; double mf=0; double m2f=0; double mc=0;
  for (float x=0.75f; x<1.5f; x=std::nextafter(x,2.f)) {
    double d = logf_P8(double(x));
    float f = logf_P8(x);
    float fc = logf_P8C(x);
    FF ff = logf_P8FF(x);
    FF ref(d,fromDouble());
    auto a = ulpDiff(f,float(d));
    auto b = ulpDiff(ff,ref);
    auto c = ulpDiff(fc,float(d));
    mf = std::max(mf,std::abs(a));
    m2f = std::max(m2f,std::abs(b));
    mc = std::max(mc,std::abs(c));
    if (a>0.5) nf++;
    if (b>0.5f) n2f++;
    if (c>0.5) nc++;
//    std::cout << d << ' ' << f << ' ' << ff << std::endl;
  }

  std::cout << nf << ' ' << mf << ' ' << n2f << ' ' << m2f << ' ' << nc << ' ' << mc << std::endl;

  return 0;
}
