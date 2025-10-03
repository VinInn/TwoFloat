#include "TwoFloat.h"
#include "ulpDiff.h"
#include <limits>
#include <cassert>
#include <cmath>
#include <iostream>

template<std::floating_point T>
void go(int k) {

  using namespace detailsTwoFloat;
  using DW = TwoFloat<T>;

  T zero  = 0;
  T eps = T(0.25)*std::numeric_limits<T>::epsilon();
  T a = std::sqrt(T(3.));
  DW da = a;
  DW de = eps;
  DW d1(a,eps, fromMembers());
  DW d2(a,eps, fromSum());
  DW d3(a,-eps, fromMembers());
  DW d4(-a,eps, fromMembers());

  if (k==0) {
    assert(da.hi()==a);
    assert(da.lo()==0);
    assert(d1.hi()==a);
    assert(d1.lo()==eps);
    DW d2(a,eps, fromSum());
    assert(d2.hi()==a);
    assert(d2.lo()==eps);
  }
  if (k==1) {
    assert(da==a);
    assert(da>=a);
    assert(da<=a);
    assert(a>=da);
    assert(a<=da);
    assert(a==da);
    assert(d1==d2);
    assert(d1<=d2);
    assert(d1>=d2);
    assert(da<d1);
    assert(d1>da);
    assert(da<=d1);
    assert(d1>=da);
    assert(de<da);
    assert(de<a);
    assert(de<=a);
    assert(a<d1);
    assert(a<=d1);
    assert(d3<=a);
    assert(a>=d3);
    assert(eps<da);

    assert(std::min(da,de)==de);
    assert(std::max(da,de)==da);
    assert(std::min(d1,d3)==d3);
    assert(std::max(d1,d3)==d1);

  }
  if (k==2) {
    assert(a == a+eps);
    assert(0 == a+eps-a);
    assert(0 != da+de-da);
    assert(a+d1 == d1+a);
    assert(d2+d1 == d1+d2);
    assert((d2+d3).lo() ==0);
    assert(d1-d2 ==0);
    assert(d1-d3 == eps+eps);
    assert(zero-d1 == -d1);
    assert(d3 == -d4);
  }
  if (k==3) {
    assert(a*eps == da*de);
    assert(a*de == a*eps);
    assert(de*a == a*eps);
    assert(a*d1 == d1*a);
    assert(d2*d1 == d1*d2);
  }
  if (k==4) {
    assert(a/eps == da/de);
    // assert(eps/a == de/da);
    assert(a/de == a/eps);
    // assert(e/da == eps/a);
    // std::cout << de/da << " vs " <<  eps/a << std::endl;
  }
  if (k==6) {
    assert(d1>0);
    assert(d3>0);
    assert(d4<0);
    assert(abs(d1)>0);
    assert(abs(d3)>0);
    assert(abs(d4)>0);

    assert(abs(d1) == d1);
    assert(abs(d3) == d3);
    assert(abs(d4) == d3);
    assert(abs(-d1) == d1);
    assert(abs(-d3) == d3);
    assert(abs(d4) == -d4);

  }

}



int main() {

  for (int k=0; k<8; ++k) {
    go<float>(k);
    go<double>(k);
  }

  return 0;

}
