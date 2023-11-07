#ifndef IMAGE_SHARPENING_H
#define IMAGE_SHARPENING_H

#include <cstdint>
#include <cstring>
#include <cmath>
#include <iostream>


#include "../images/myImage.h"
#define IMAGE_SHARPENING_PATH "image/output/image_sharpening.png"
using namespace Image;
using namespace std;
namespace imageSharpening {
  void sharpenImage(myImage image, int kernelHeightWidth);
  double* buildGaussianKernel(double sigma, int kernelDimensions);
  double * buildLaplacianKernel();
  myImage applyKernel(myImage *in, double *kernel, int kernelDimension, string typeKernel);
  myImage sharpenImage(myImage *laplacianImage, myImage *originalImage);
}

#endif