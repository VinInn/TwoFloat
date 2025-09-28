#include "ulpDiff.h"
#include <cstdio>
#include <iostream>



int main() {
  using namespace detailsTwoFloat;
  using FF = TwoFloat<float>;
  double s = std::sqrt(3.);

  FF ref(s,fromDouble());
  std::cout << std::hexfloat << s << std::endl;
  std::cout << std::hexfloat << ref << std::endl;
  {
    FF t{ref.hi(),nextafterf(ref.lo(), 100000.f),fromMembers()};
    std::cout << std::hexfloat << t << std::endl;
    std::cout << std::hexfloat << toDouble(t) << std::endl;
    std::cout << std::fixed << ulpDiff(t,ref) << std::endl;
  }
 {
    FF t{ref.hi(),nextafterf(ref.lo(), -100000.f),fromMembers()};
    std::cout << std::hexfloat << t << std::endl;
    std::cout << std::hexfloat << toDouble(t) << std::endl;
    std::cout << std::fixed << ulpDiff(t,ref) << std::endl;
  }
 {
    FF t = ref;
    for (int i=0; i<16; ++i) {
      FF q{t.hi(),nextafterf(t.lo(), 100000.f),fromSum()};
      t = q;
    }
    std::cout << std::hexfloat << t << std::endl;
    std::cout << std::hexfloat << toDouble(t) << std::endl;
    std::cout << std::fixed << ulpDiff(t,ref) << std::endl;
  }
  return 0;
}
