#include "ulpDiff.h"
#include <cstdio>
#include <iostream>
#include <cmath>

template< typename T>
inline T logf_P8(T y) {
   return  y * ( T(0x1.00000cp0) + y * (T(-0x8.0003p-4) + y * (T(0x5.55087p-4) + y * ( T(-0x3.fedcep-4) + y * (T(0x3.3a1dap-4) + y * (T(-0x2.cb55fp-4) + y * (T(0x2.38831p-4) + y * (T(-0xf.e87cap-8) )))))))) ;
}


int main() {
  using namespace detailsTwoFloat;
  using FF = TwoFloat<float>;


  int nf=0; int n2f=0; double mf=0; double m2f=0;
  for (float x=0.75f; x<1.5f; x=std::nextafter(x,2.f)) {
    double d = logf_P8(double(x));
    float f = logf_P8(x);
    FF ff = logf_P8(FF(x));
    FF ref(d,fromDouble());
    auto a = ulpDiff(f,float(d));
    auto b = ulpDiff(ff,ref);
    mf = std::max(mf,std::abs(a));
    m2f = std::max(m2f,std::abs(b));
    if (a>0.5) nf++;
    if (b>0.5f) n2f++;
//    std::cout << d << ' ' << f << ' ' << ff << std::endl;
  }

  std::cout << nf << ' ' << n2f << ' ' << mf << ' ' << m2f << std::endl;

  return 0;
}
