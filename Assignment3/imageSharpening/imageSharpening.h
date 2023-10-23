#ifndef IMAGE_SHARPENING_H
#define IMAGE_SHARPENING_H

#include <cstdint>
#include <cstring>
#include <cmath>
#include <iostream>


#include "../images/myImage.h"
#define IMAGE_SHARPENING_PATH "image/output/image_sharpening.png"
using namespace Image;
namespace imageSharpening {
  void sharpenImage(myImage image, int kernelHeightWidth);
  void buildGaussian(double** gaussianKernel, double sigma, int kernelDimensions);
  void applyGaussianKernel(double** gaussianKernel, myImage image, int kernelHeightWidth, std::string path);
  void buildLaplacianKernel(double** laplacianKernel, int kernelDimensions, double* weights);
  void applyLaPlace(myImage image, double window[3][3], int n);
}

#endif
