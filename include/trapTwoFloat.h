#pragma once
#include "TwoFloat.h"
#include<limits>
#include<iostream>

template<std::floating_point T>
void trap(T h, T l){
  if (std::isnan(h) || std::isnan(l)) std::cout << "W nans: " << h << ","<< l << std::endl;
  auto eps = std::nextafter(std::abs(h),std::numeric_limits<T>::max()) - std::abs(h);
  if(l>eps) std::cout << "W DW not normalized: " << h << ","<< l <<" eps = " << eps << std::endl;
}

void trapTwoFloat(float h, float l) {
  trap(h,l);
}

void trapTwoFloat(double h, double l) {
  trap(h,l);
}
