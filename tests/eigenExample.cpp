#include <algorithm>
#include <cassert>
#include <random>

#include "TwoFloat.h"

template <typename M>
void fillMatrix(M& m) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-2.0, 2.0);
  for (auto & x : m.reshaped()) x = dis(gen);
  return;
}

template <typename M1, typename M2>
void copy(M1 const & src, M2 & dst) {

  for (unsigned int i = 0; i < src.rows(); ++i) 
    for (unsigned int j = 0; j < src.cols(); ++j)  dst(i,j) = fromDouble(src(i,j));

//   auto dsti = std::begin(dst.reshaped());
//   for (auto x : src.reshaped()) *(dsti++) = fromDouble(x);
}

template <typename M1, typename M2>
void copyBack(M1 const & src, M2 & dst) {

  for (unsigned int i = 0; i < src.rows(); ++i)
    for (unsigned int j = 0; j < src.cols(); ++j)  dst(i,j) = toDouble(src(i,j));
}

#include "TwoFloat.h"
#include "ulpDiff.h"
#include <Eigen/Core>
#include <Eigen/Eigenvalues>
#include <iostream>

using FF = TwoFloat<float>;

int main() {

  Eigen::Matrix<double, 3, 3> md33;
  Eigen::Matrix<double, 5, 3> md53;
  Eigen::Matrix<double, 3, 5> md35;
  Eigen::Matrix<double, 5, 5> md55;

  Eigen::Matrix<FF, 3, 3> mf33;
  Eigen::Matrix<FF, 5, 3> mf53;
  Eigen::Matrix<FF, 3, 5> mf35;
  Eigen::Matrix<FF, 5, 5> mf55;

  fillMatrix(md33);
  fillMatrix(md53);
  fillMatrix(md35);
  fillMatrix(md55);
  Eigen::Matrix<double, 5, 5> resd = md53*md35 + md55;
  std::cout << resd << std::endl;

  copy(md53,mf53);
  copy(md35,mf35);
  copy(md55,mf55);
  Eigen::Matrix<FF, 5, 5> resf = mf53*mf35 + mf55;
  std::cout << resf << std::endl;

  Eigen::Matrix<double, 5, 5> diff;
  copyBack(resf,diff);
  std::cout << diff-resd << std::endl<< std::endl;

  resd = resd.inverse();
  resf = resf.inverse();
  copyBack(resf,diff);
  std::cout << diff-resd << std::endl<< std::endl;

  copy(md33,mf33);

   Eigen::SelfAdjointEigenSolver<Eigen::Matrix<double, 3, 3>> es;
   auto const & sd = es.compute/*Direct*/(md33);
   std::cout << sd.eigenvalues()  << std::endl;

   Eigen::SelfAdjointEigenSolver<Eigen::Matrix<FF, 3, 3>> es2;
   auto const & sf = es2.compute/*Direct*/(mf33);
   std::cout << sf.eigenvalues()  << std::endl;
   Eigen::Vector3d v;
   copyBack(sf.eigenvalues(),v);
   std::cout << v-sd.eigenvalues() << std::endl<< std::endl;

  return 0;
}
