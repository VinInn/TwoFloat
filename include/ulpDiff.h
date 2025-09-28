#pragma once
#include "TwoFloat.h"
#include <cmath>


double ulpDiff(TwoFloat<float> a, TwoFloat<float> b) {
  double da = toDouble(a);
  double db = toDouble(b);
  da-=db; da = std::abs(da);
  int e;
  frexp(db, &e);
  return ldexp(da, 49 - e);
}

