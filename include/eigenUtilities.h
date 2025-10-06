#pragma once
#include "TwoFloat.h"


template <typename M1, typename M2>
TWOFLOAT_INLINE
void convertToDW(M1 const & src, M2 & dst) {
  using F = decltype(dst(0,0));
  for (unsigned int i = 0; i < src.rows(); ++i)
    for (unsigned int j = 0; j < src.cols(); ++j)
    if constexpr (std::is_floating_point_v<F>)
       dst(i,j) = double(src(i,j));
    else
       dst(i,j) = fromDouble(src(i,j));

//   auto dsti = std::begin(dst.reshaped());
//   for (auto x : src.reshaped()) *(dsti++) = fromDouble(x);
}

template <typename M1, typename M2>
TWOFLOAT_INLINE
void convertFromDW(M1 const & src, M2 & dst) {
  for (unsigned int i = 0; i < src.rows(); ++i)
    for (unsigned int j = 0; j < src.cols(); ++j)  dst(i,j) = toDouble(src(i,j));
}



  template<typename V>
  TWOFLOAT_INLINE
  auto squaredNorm(V const & v) {
#ifndef NO_TWOFLOAT_SN
     return squaredNorm(std::begin(v.reshaped()),std::end(v.reshaped()));
#else
    return v.squaredNorm();
#endif
  }


  template<typename V>
  TWOFLOAT_INLINE
  auto norm(V const & src) {
#ifndef NO_TWOFLOAT_SN
     return sqrt(squaredNorm(std::begin(v.reshaped()),std::end(v.reshaped())));
#else
    return v.norm();
#endif
  }
