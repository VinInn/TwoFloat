#include <algorithm>
#include <cassert>
#include <random>

#include "TwoFloat.h"
#include "trapTwoFloat.h"

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
void copyBack(M1 const & src, M2 & dst) {

  for (unsigned int i = 0; i < src.rows(); ++i)
    for (unsigned int j = 0; j < src.cols(); ++j)  dst(i,j) = toDouble(src(i,j));
}

#include "TwoFloat.h"
#include "ulpDiff.h"
#include <Eigen/Core>
#include <Eigen/Eigenvalues>
#include <Eigen/SVD>
#include <iostream>
#include <limits>
#include <complex>
#include <fenv.h>

using FF = TwoFloat<float>;

/*
FF real(FF const & a) { return a;}
FF imag(FF const & a) { return 0;}
FF conj(FF const & a) { return a;}
*/

FF abs2(FF const & a) { return square(a);}

int main() {

//  feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW);


  {
  FF a = fromDouble(std::sqrt(3.));
  auto q = Eigen::numext::abs2(a);
  std::cout << a << ' ' << q << std::endl;
  }



  Eigen::Matrix<double, 3, 3> md33;
  Eigen::Matrix<double, 5, 3> md53;
  Eigen::Matrix<double, 3, 5> md35;
  Eigen::Matrix<double, 5, 5> md55;

  Eigen::Matrix<FF, 3, 3> mf33;
  Eigen::Matrix<FF, 5, 3> mf53;
  Eigen::Matrix<FF, 3, 5> mf35;
  Eigen::Matrix<FF, 5, 5> mf55;

  using MfX = Eigen::Matrix<FF,-1,-1>;

  std::cout << std::numeric_limits<Eigen::Matrix<double, 3, 3>::Scalar>::min() << std::endl;
  std::cout << std::numeric_limits<Eigen::Matrix<FF, 3, 3>::Scalar>::min() << std::endl;
  std::cout << std::endl;

  {
  md33 << 1,-1,0, std::sqrt(2.), 3, 4, -4, -3, -2;
  mf33 << 1,-1,0, fromDouble(std::sqrt(2.)), 3, 4, -4, -3, -2;
  Eigen::Matrix<double, 3, 3> d;
  copyBack(mf33,d);
  std::cout << d-md33 << std::endl<< std::endl;

  std::cout << mf33 << std::endl;
  std::cout << std::endl;

  std::cout << mf33.transpose() << std::endl;
  std::cout << std::endl;

  std::cout << mf33.adjoint() << std::endl;
  std::cout << std::endl;

  MfX mx = mf33;

   std::cout << mx << std::endl;
   std::cout << std::endl;

   mx = mf33.block(0, 0, 2, 2).template triangularView<Eigen::Lower>().adjoint();
   std::cout << mx << std::endl;
   std::cout << std::endl;

   mx.setIdentity();
   std::cout << mx << std::endl;
   std::cout << std::endl;

   mx.setIdentity(2,3);
   std::cout << mx << std::endl;
   std::cout << std::endl;

  }

  fillMatrix(md33);
  fillMatrix(md53);
  fillMatrix(md35);
  fillMatrix(md55);
  Eigen::Matrix<double, 5, 5> resd = md53*md35 - md55;
  std::cout << resd << std::endl;

  copy(md53,mf53);
  copy(md35,mf35);
  copy(md55,mf55);
  Eigen::Matrix<FF, 5, 5> resf = mf53*mf35 - mf55;
  std::cout << resf << std::endl;

  Eigen::Matrix<double, 5, 5> diff;
  copyBack(resf,diff);
  std::cout << diff-resd << std::endl<< std::endl;

  resd = resd.inverse();
  resf = resf.inverse();
  copyBack(resf,diff);
  std::cout << diff-resd << std::endl<< std::endl;

  {
    auto a = resd.rowwise().sum().maxCoeff();
    auto b = resf.rowwise().sum().maxCoeff();
    std::cout << a <<' '<< b << ' ' <<toDouble(b)-a << std::endl;
  }

  std::cout << resd.squaredNorm() << ' ' << resf.squaredNorm() << std::endl;
  std::cout << resd.norm() << ' ' << resf.norm() << std::endl;
  std::cout << resd.row(0).dot(resd.row(1)) << ' ';
  std::cout << resf.row(0).dot(resf.row(1)) << ' ';
  std::cout << toDouble(resf.row(0).dot(resf.row(1)))-resd.row(0).dot(resd.row(1)) << std::endl;
  std::cout << std::endl;


  copy(md33,mf33);

   {
   Eigen::SelfAdjointEigenSolver<Eigen::Matrix<double, 3, 3>> es;
   auto const & sd = es.compute(md33);
   if (es.info() != Eigen::Success) std::cout << "falied" << std::endl;
   std::cout << sd.eigenvalues()  << std::endl;

   Eigen::SelfAdjointEigenSolver<Eigen::Matrix<FF, 3, 3>> es2;
   auto const & sf = es2.compute(mf33);
   if (sf.info() != Eigen::Success) std::cout << "falied" << std::endl;
   std::cout << sf.eigenvalues()  << std::endl;
   Eigen::Vector3d v;
   copyBack(sf.eigenvalues(),v);
   std::cout << v-sd.eigenvalues() << std::endl<< std::endl;
   }

   {
   Eigen::SelfAdjointEigenSolver<Eigen::Matrix<double, 3, 3>> es;
   auto const & sd = es.computeDirect(md33);
   std::cout << sd.eigenvalues()  << std::endl;

   Eigen::SelfAdjointEigenSolver<Eigen::Matrix<FF, 3, 3>> es2;
   auto const & sf = es2.computeDirect(mf33);
   std::cout << sf.eigenvalues()  << std::endl;
   Eigen::Vector3d v;
   copyBack(sf.eigenvalues(),v);
   std::cout << v-sd.eigenvalues() << std::endl<< std::endl;
   }

   {
    Eigen::JacobiSVD<Eigen::Matrix<double, 3, 5>, Eigen::ComputeThinU | Eigen::ComputeThinV> svd(md35);
    std::cout << svd.singularValues() << std::endl;
    Eigen::JacobiSVD<Eigen::Matrix<FF, 3, 5>, Eigen::ComputeThinU | Eigen::ComputeThinV> svf(mf35);
    std::cout << svf.singularValues() << std::endl << std::endl;
   }


   {
     Eigen::Vector3d vd; vd << -1., std::sqrt(3.),  4.;
     Eigen::Vector<FF,3> vf;
     copy(vd,vf); 
     md33.fullPivHouseholderQr().solve(vd);
     std::cout << vd << std::endl;
     mf33.fullPivHouseholderQr().solve(vf);
     std::cout << vf << std::endl;
     Eigen::Vector3d v;
     copyBack(vf,v);
     std::cout << v-vd << std::endl << std::endl;
   }

  return 0;
}
