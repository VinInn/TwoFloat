// c++ -O3 -march=native tests/TwoFloat_t.cpp -Iinclude -std=c++20
#include "TwoFloat.h"
#include "ulpDiff.h"
#include <iostream>
#include <limits>
#include <complex>

template<std::floating_point T>
void trap(T h, T l){
  if (std::isnan(h) || std::isnan(l)) std::cout << "W nans: " << h << ","<< l << std::endl;
  auto eps = std::nextafter(std::abs(h),std::abs(h)+T(1)) - std::abs(h);
  if(l>eps) std::cout << "W DW not normalized: " << h << ","<< l <<" eps = " << eps << std::endl;
}

void trapTwoFloat(float h, float l) {
  trap(h,l);
}

void trapTwoFloat(double h, double l) {
  trap(h,l);
}

int main() {

  using namespace detailsTwoFloat;
  using FF = TwoFloat<float>;
  using DD = TwoFloat<double>;
  using nlFF = std::numeric_limits<FF>;
  using nlDD = std::numeric_limits<DD>;

  {
    std::cout << "limits" << std::endl;    
    std::cout << std::hexfloat << nlFF::min() << ' ' << nlFF::max() << ' ' << nlFF::epsilon() << ' ' << std::endl;
    std::cout << std::hexfloat << nlDD::min() << ' ' << nlDD::max() << ' ' << nlDD::epsilon() << ' ' << std::endl;
    std::cout << std::endl;

    std::cout << "trap" << std::endl;
    {
      FF k{0.5f,1.e-7f,fromMembers()};
      FF q{nlFF::quiet_NaN()}; 
    }
    std::cout << std::endl;
    float a = 4.f;
    float b = 1.e-7f;
    FF aa{a};
    FF bb{b};
    std::cout << std::hexfloat << a << ' ' << b << ' ' << -a << std::endl;
    std::cout << std::hexfloat << aa << ' ' << bb << ' ' << -aa << std::endl;
    std::cout << std::hexfloat << (a + b -a) << std::endl;
    std::cout << std::hexfloat << (aa + bb -aa) << std::endl;
    FF s{0};
    s+=a;
    s+=b;
    s-=a;
    std::cout << std::hexfloat << s << std::endl;
    std::cout << std::endl;
    std::cout << std::hexfloat << a << ' ' << b << ' ' << b << std::endl;
    std::cout << std::hexfloat << aa << ' ' << bb << ' ' << bb << std::endl;
    std::cout << std::hexfloat << (a + b + b) << std::endl;
    std::cout << std::hexfloat << (aa + bb + bb) << std::endl;
    s =a;
    s+=b;
    s+=b;
    std::cout << std::hexfloat << s << std::endl;
    std::cout << std::endl;

    std::cout <<"conversions ok"<< std::endl;
    FF q = sqrt(3.); std::cout << q << ' ' << toDouble(q)-sqrt(3.) << std::endl;
    FF qd(sqrt(3.),fromDouble()); std::cout << qd << ' ' << toDouble(qd)-sqrt(3.) << std::endl;
    q+= 1.e-8; std::cout << q << std::endl;;
    q+=1; std::cout << q << std::endl;
    q-=1; std::cout << q << std::endl;
    q*=2; std::cout << q << std::endl;
    q/=2; std::cout << q << std::endl;
    { auto w = q + 1.f; std::cout << w << std::endl;}
    {double ww = toDouble(q); std::cout << ww << std::endl;}
#ifdef TEST_INVALID
    std::cout <<"conversions problematic"<< std::endl;
    { auto w = q + 1.; std::cout << w << std::endl;}
    { auto w = 1 + q; std::cout << w << std::endl;}
    { auto w = q - 1.; std::cout << w << std::endl;}
    { auto w = 1 - q; std::cout << w << std::endl;}
    { auto w = q*2; std::cout << w << std::endl;}
    { auto w = 2*q; std::cout << w << std::endl;}
    { auto w = q/2; std::cout << w << std::endl;}
    { auto w = 2/q; std::cout << w << std::endl;}
    {double ww = q; std::cout << ww << std::endl;}
#endif

    std::cout << std::endl;
    std::cout <<"squared norm"<< std::endl;

    float v[4] = {2.f,1.e-4f,1.e-4f,2.f};
    FF vv[4];
    float sf=0;
    FF sff=0;
    for (int i=0; i<4; ++i) {
      vv[i]=v[i];
      sf+=v[i]*v[i];
      sff+=vv[i]*vv[i];
    }
    std::cout << std::hexfloat << sf << std::endl;
    std::cout << std::hexfloat << sff << std::endl;
    FF sn = squaredNorm2(v,4);
    std::cout << std::hexfloat << sn << std::endl;
    FF ssn = squaredNorm(vv,4);
    std::cout << std::hexfloat << ssn << std::endl;
    std::cout << std::endl;

    double vd[4] = {std::sqrt(2.),std::sqrt(1.e-4),-std::sqrt(1.e-4),-std::sqrt(2.)};
    FF vc[4];
    //std::transform(vd,vd+4,vc,fromDouble);
    auto dst = std::begin(vc);
    for (auto const & x : vd) *(dst++) = fromDouble(x);
    for (auto x : vd) std::cout << x << ' '; std::cout << std::endl;
    for (auto const & x : vc) std::cout << x << ' '; std::cout << std::endl;

  }

  float h = std::sqrt(2.f);
  float l = 1.e-4f*std::sqrt(3.f);
  TwoFloat<float> f(h,l, fromSum());
  TwoFloat<double> d(h,l, fromSum());
  std::cout << std::hexfloat << f.hi() << ',' << f.lo() << std::endl;
  std::cout << std::hexfloat << double(f.hi())+double(f.lo())<< std::endl;
  std::cout << std::hexfloat << d.hi() << ',' << d.lo() << std::endl;

  auto f1 = f;
  TwoFloat<float> f2(-1.e-3f*std::sqrt(3.f),1.e-6f*std::sqrt(2.f),  fromSum());
  TwoFloat<float> f2n(1.e-3f*std::sqrt(3.f),-1.e-6f*std::sqrt(2.f), fromSum());
  double d1 = double(f.hi())+double(f.lo());
  double d2 = double(f2.hi())+double(f2.lo());
  double d2n = double(f2n.hi())+double(f2n.lo());
  std::cout << std::hexfloat << f2.hi() << ',' << f2.lo() << std::endl;
  std::cout << std::hexfloat << d2 << std::endl;

  auto sf =  f1+f2;
  auto sd = d1 + d2;
  std::cout << std::hexfloat << sf.hi() << ',' << sf.lo() << std::endl;
  std::cout << std::hexfloat << double(sf.hi()) + double(sf.lo()) << std::endl;
  std::cout << std::hexfloat << sd << std::endl;
  auto sfn =  f1-f2n;
  auto sdn = d1 - d2n;
  std::cout << std::hexfloat << sfn.hi() << ',' << sfn.lo() << std::endl;
  std::cout << std::hexfloat << double(sfn.hi()) + double(sfn.lo()) << std::endl;
  std::cout << std::hexfloat << sdn << std::endl;

{
  std::cout << "mul" << std::endl;
  auto mf =  f1*f2.hi();
  auto md = d1 * f2.hi();
  std::cout << std::hexfloat << f1.hi()*f2.hi() << std::endl;
  std::cout << std::hexfloat << mf.hi() << ',' << mf.lo() << std::endl;
  std::cout << std::hexfloat << md << ' ' << std::fixed << ulpDiff(mf, FF{md,fromDouble()}) << std::endl;
}
{
  auto mf =  f1*f2;
  auto md = d1 * d2;
  std::cout << std::hexfloat << f1.hi()*f2.hi() << std::endl;
  std::cout << std::hexfloat << mf.hi() << ',' << mf.lo() << std::endl;
  std::cout << std::hexfloat << double(mf.hi()) + double(mf.lo()) << std::endl;
  std::cout << std::hexfloat << md << ' ' << std::fixed << ulpDiff(mf, FF{md,fromDouble()}) << std::endl;
}


{
  std::cout << "div" << std::endl;
  auto mf =  f1/f2.hi();
  double md = d1/f2.hi();
  std::cout << std::hexfloat << f1.hi()/f2.hi() << std::endl;
  std::cout << std::hexfloat << mf.hi() << ',' << mf.lo() << std::endl;
  std::cout << std::hexfloat << md << std::endl;
}
{
  auto mf =  f1/f2;
  auto md = d1/d2;
  std::cout << std::hexfloat << f1.hi()/f2.hi() << std::endl;
  std::cout << std::hexfloat << mf.hi() << ',' << mf.lo() << std::endl;
  std::cout << std::hexfloat << double(mf.hi()) + double(mf.lo()) << std::endl;
  std::cout << std::hexfloat << md << ' ' << std::fixed << ulpDiff(mf, FF{md,fromDouble()}) <<std::endl;
}

{
  std::cout << "square" << std::endl;
  auto mf =  square(f1);
  auto mf2 =  f1*f1;
  auto md = d1*d1;
  std::cout << std::hexfloat << f1.hi()*f1.hi() << std::endl;
  std::cout << std::hexfloat << mf.hi() << ',' << mf.lo() << std::endl;
  std::cout << std::hexfloat << mf2.hi() << ',' << mf2.lo() << std::endl;
  std::cout << std::hexfloat << double(mf.hi()) + double(mf.lo()) << std::endl;
  std::cout << std::hexfloat << md << ' ' << std::fixed << ulpDiff(mf, FF{md,fromDouble()}) << std::endl;
}

{
  std::cout << "sqrt" << std::endl;
  auto mf =  sqrt(f1);
  auto md =  sqrt(d1);
  std::cout << std::hexfloat << sqrt(f1.hi()) << std::endl;
  std::cout << std::hexfloat << mf.hi() << ',' << mf.lo() << std::endl;
  std::cout << std::hexfloat << double(mf.hi()) + double(mf.lo()) << std::endl;
  std::cout << std::hexfloat << md << ' ' << std::fixed << ulpDiff(mf, FF{md,fromDouble()}) << std::endl;

}


{
  std::cout << "rsqrt" << std::endl;
  auto mf =  rsqrt(f1);
  auto md =  rsqrt(d1);
  std::cout << std::hexfloat << rsqrt(f1.hi()) << std::endl;
  std::cout << std::hexfloat << mf.hi() << ',' << mf.lo() << std::endl;
  std::cout << std::hexfloat << double(mf.hi()) + double(mf.lo()) << std::endl;
  std::cout << std::hexfloat << md << ' ' << std::fixed << ulpDiff(mf, FF{md,fromDouble()}) << std::endl;

}


{
   std::cout << "complex" << std::endl;

   using CFF = std::complex<FF>;
   using CDD = std::complex<DD>;
   CFF cf1{f1,f2};
   CFF cf2{f1,-f2};
   CFF cf3{f2, f1};
   std::cout << std::hexfloat << cf1 << ' ' << cf2 << std::endl;
   CFF cd1{d1,d2};
   CFF cd2{d1,-d2};
   CFF cd3{d2, d1};
   std::cout << std::hexfloat << cd1 << ' ' << cd2 << std::endl;
   std::cout << std::hexfloat << abs(cd1) << ' ' << abs(cd2) << std::endl;

   std::cout << std::hexfloat << cf1*cf2 << ' ' << cd1*cd2 << std::endl;
   std::cout << std::hexfloat << cf1*cf3 << ' ' << cd1*cd3 << std::endl;
}


  return 0;
}
