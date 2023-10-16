#ifndef HISTOGRAM_BAND_H
#define HISTOGRAM_BAND_H

#include <cstdint>
#include <cstring>
#include <cmath>
#include <iostream>


#include "../images/myImage.h"
#define BAND_PATH "image/output/band.jpg"
using namespace Image;
namespace band {
  void bandTransform(myImage image);
  void forwardDCT(uint8_t* input, int width, int height, double* output);
  void inverseDCT(double* input, int width, int height, uint8_t* output);

}

#endif
