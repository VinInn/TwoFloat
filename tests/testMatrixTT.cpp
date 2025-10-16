// c++ -std=c++20 -O3 -march=native testMatrixTT.cpp -DALL_T -I../include
// -DTWOFLOAT_PRECISE_MULT -DTWOFLOAT_PRECISE_DIV -DTWOFLOAT_PRECISE_SUM
// /c++ -O3 -std=c++20 -march=native tests/testMatrixTT.cpp -Iinclude -DALL_T -DDOPROB
#include<cmath>
#include<random>
#include <cassert>


#include "Matrix.h"
#include <TwoFloat.h>
#include<iostream>
#include<array>

// problematic matrices
constexpr int nProb =7;
using VA = std::array<float,15>; 
VA prob[nProb] = {
{0.00803683, -3.05983, 23791.8, -1.12256, -1559.84, 2071.61, -2.54266, -4669.75, -1514.62, 12813.8, -4.46718, -11275.8, -3345.82, -5650.64, 65502.2},
{0.0130532, -0.486671, 444.793, 2.95992, 666.121, 11544.2, 2.13826, 377.561, -1656.55, 4385.63, -3.84258, -1404.56, 6916.1, 4196.78, 55888.9},
{0.0326371, -7.51723, 22513.5, 3.3275, 3658.29, 7213.78, -3.23033, 3005.38, -0.000673902, 8213.12, -1.24941, -943.582, 12.7309, -67.2727, 587.217},
{0.0690571, -9.37057, 14150.2, 1.51091, 1315.86, 2676.18, -0.808169, -1119.88, 1665.85, 14809.3, 1.7771, 0.000215638, -276.727, 590.528, 768.092},
{0.282637, 19.9103, 23326.1, 1.55039, -374.328, 95.41, 30.466, -4788.99, -593.68, 41278.9, 14.2271, -2857.92, -217.75, -3429.35, 8032.11},
{0.300253, -6.73174, 2705.04, 7.32026, -665.777, 8496.9, 2.66633, -21.0154, 4.88386e-05, 505.332, -8.54343, 79.7429, 899.055, 203.445, 7681.97},
{0.365169, 3.90765e-06, 13478.1, -4.27523, -368.596, 3131.37, 7.47236, 751.991, 99.556, 4286.61, 1.24752, 2983.04, -2420.23, -83.2086, 20841.2},
};

#ifdef ALL_T
#define NOP_T
#define FLOAT_T
#define FLOAT2_T
#define DOUBLE_T
#define DOUBLE2_T
#define F128_T
#endif

#define VERIFY

template <typename M>
inline bool verify(std::string const & hi,M const& m, bool vv=true) {
  bool ret=true;
#ifdef VERIFY
#warning "Verify ON"
  int n = M::kRows;
  for (int i = 0; i < n; ++i) {
     auto d = toSingle(m(i,i));
     if (vv && d<0) std::cout << hi << "??? on " << i << ' ' << d << std::endl;
//     assert(d>-1.e-8);
     if (d<1.e-8) {ret=false; break;}
  }
  if (!ret)  {for (int i = 0; i < n; ++i) {std::cout << m(i,i) << ' ';} std::cout << std::endl;}
  if (!ret) return ret;
  //check minors
  for (int i = 0; i < n-1; ++i) {
    auto d = toSingle(m(i+0, i+0)*m(i+1,i+1)) - toSingle(m(i+0, i+1)*m(i+1,i+0));
    if (vv && d<0) std::cout << hi << "??? m2 " << i << ' ' << d << std::endl;
//    assert(d > -1.e-8);
    if (d<1.e-8) ret=false;
    if (i>0) continue;;
    auto d3 = toSingle(m(i+1, i+0)*m(i+2,i+1) - m(i+2, 0)*m(i+1,i+1));
    auto d2 = toSingle(m(i+1, i+0)*m(i+2,i+2) - m(i+2, 0)*m(i+1,i+2));
    auto d1 = toSingle(m(i+1, i+1)*m(i+2,i+2) - m(i+1, 2)*m(i+2,i+1));
    auto dd = toSingle(m(i+0,i+0)*d1-m(i+0,i+1)*d2+m(i+0,i+2)*d3);
    if (vv && dd<0) std::cout << "??? m3 " << i << ' ' << dd << std::endl;
//    assert(dd > -1.e-8);
    if (d<1.e-8) ret=false;
  }
#endif 
   return ret;
}

// generate matrices
template <typename M, typename Eng>
void genMatrix(M& m, Eng & eng) {
  // using T = typename std::remove_reference<decltype(m(0, 0))>::type;
  int n = M::kRows;
  std::uniform_real_distribution<float> rgen(0., 1.);
  do {
  // generate first diagonal elemets
  for (int i = 0; i < n; ++i) {
    float maxVal = i * 1.e5 / (n - 1) + 1;  // max condition is 10^5 as  min-generated is 10^-9
    m(i, i) = maxVal * (rgen(eng) + 1.e-10);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      float v = 0.3f * std::sqrt( toSingle(m(i, i)) * toSingle(m(j, j)) );  // this makes the matrix pos defined
      m(i, j) = v * (rgen(eng) + 1.e-10);
      if (rgen(eng)<0.5f) m(i, j) = -m(i, j);
      // m(j, i) = m(i, j);
    }
  }
  } while(!verify("gen",m,false));
}

#include <typeinfo>
#include<iostream>

template<typename T,typename TT=T>
void goProb() {
  std::cout << "testing " << typeid(TT).name() << std::endl;
  MatrixSym<TT,5> m2,m3, mon, moff;
  for (int k=0; k<nProb; ++k) {
    MatrixSym<TT,5> m1(prob[k]);
    for (int i=0; i<15; ++i) std::cout << toSingle(m1[i]) << ' ';std::cout << std::endl;
    invert55(m1,m2);
    for (int i=0; i<15; ++i) std::cout << toSingle(m2[i]) << ' ';std::cout << std::endl;
    invert55(m2,m3);
    for (int i=0; i<15; ++i) std::cout << toSingle(m3[i]) << ' ';std::cout << std::endl;
    for (int i=0; i<15; ++i) std::cout << toSingle(m3[i]-m1[i]) << ' ';std::cout << std::endl;
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

template<typename T,typename TT=T>
void go(int maxIter) {
  std::cout << "testing " << typeid(TT).name() << std::endl;
  T maxOn=0;
  T maxOff=0;
  T maxOnOld=0;
  T maxOffOld=0;
  MatrixSym<TT,5> m1,m2,m3, mon, moff;
  std::mt19937 eng;
  int n = 5; 
for (int kk=0; kk<maxIter; ++kk) {
  bool v = true;
  genMatrix(m1, eng);
  v &= verify("1",m1);
  invert55(m1,m2);
  v &= verify("2",m2);
  invert55(m2,m3);
  v &= verify("3",m3);
  invert55(m3,m2);
  invert55(m2,m3);
  v &= verify("4",m3);
  if (!v) continue;
  for (int i=0; i<n; ++i) {
    maxOn = std::max(maxOn,std::abs(toSingle(  (m3(i,i)-m1(i,i))/m1(i,i) )));
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      maxOff = std::max(maxOff,std::abs(toSingle( (m3(i,j)-m1(i,j))/m1(i,j) )));
    }
  }
  if (maxOn>maxOnOld) { maxOnOld=maxOn; mon=m1;}
  if (maxOff>maxOffOld) { maxOffOld=maxOff; moff=m1;}
}
  std::cout << "prec " << maxOn << ' ' << maxOff << std::endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) { std::cout << mon(i,j)<< ' ' ;}} std::cout << std::endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) { std::cout << moff(i,j)<< ' ' ;}} std::cout << std::endl;

}

int main() {

  int maxIter = 25000000;
  
  using FF = TwoFloat<float>;
  using DD = TwoFloat<double>;

#ifdef DOPROB

#ifdef FLOAT_T
  goProb<float>();
#endif

#ifdef DOUBLE_T
  goProb<double>();
#endif

#ifdef FLOAT2_T
  goProb<float,FF>();
#endif

#ifdef DOUBLE2_T
  goProb<double,DD>();
#endif

#else

#ifdef NOP_T
{
  std::cout << "testing NOP" << std::endl;
  float maxOn=0;
  float maxOff=0;
  MatrixSym<float,5> m1,m2,m3;
  std::mt19937 eng;

for (int kk=0; kk<maxIter; ++kk) {
  genMatrix(m1, eng);
  verify("gen",m1);
  m3 = m1;
  int n = 5;
  for (int i=0; i<n; ++i)
    maxOn = std::max(maxOn,std::abs(m3(i,i)-m1(i,i))/std::abs(m1(i,i)));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      maxOff = std::max(maxOff,std::abs(m3(i,j)-m1(i,j))/std::abs(m1(i,j)));
    }
  }
}
  std::cout << "prec " << maxOn << ' ' << maxOff << std::endl;
}
#endif

#ifdef FLOAT_T
  go<float>(maxIter);
#endif

#ifdef DOUBLE_T
  go<double>(maxIter);
#endif

#ifdef FLOAT2_T
  go<float,FF>(maxIter);
#endif

#ifdef DOUBLE2_T
  go<double,DD>(maxIter);
#endif

#ifdef F128_T
//  go<__float128,__float128>(maxIter);
#endif

#endif


  return 0;
}
