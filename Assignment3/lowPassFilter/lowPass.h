#ifndef LOW_PASS_H
#define LOW_PASS_H

#include <cstdint>
#include <cstring>
#include <cmath>
#include <iostream>

#include "../images/myImage.h"
#define LOW_PASS_PATH "image/output/low_pass.png"

using namespace Image;
namespace lowPass {
  void lowPassFun(myImage image);
  double *buildGaussianKernel(double sigma, int kernelDimensions);
  myImage applyKernel(myImage *in, double *kernel, int kernelDimension);
  myImage thresholding(myImage *in);
  myImage applyMedianFilter(myImage *in, int filterSize);
}

#endif
