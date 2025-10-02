#include "TwoFloat.h"
#include "ulpDiff.h"
#include <limits>
#include <cassert>
#include <cmath>

template<std::floating_point T>
void go(int k) {

  using namespace detailsTwoFloat;
  using DW = TwoFloat<T>;

  T eps = T(0.25)*std::numeric_limits<T>::epsilon();
  T a = std::sqrt(T(3.));

  if (k==0) {
    DW da = a;
    DW de = eps;
    assert(da.hi()==a);
    assert(da.lo()==0);
    DW d1(a,eps, fromMembers());    
    assert(d1.hi()==a);
    assert(d1.lo()==eps);
    DW d2(a,eps, fromSum());
    assert(d2.hi()==a);
    assert(d2.lo()==eps);
    DW d3(a,-eps, fromMembers());

    assert(0 == a+eps-a);
    assert(0 != da+de-da);

    assert(da==a);
    assert(a==da);
    assert(d1==d2);
    assert(da<d1);
    assert(de<da);
    assert(de<a);
    assert(a<d1);
    assert(d3<a);
    assert(eps<da);
  }



}



int main() {

  for (int k=0; k<8; ++k) {
    go<float>(k);
    go<double>(k);
  }

  return 0;

}
