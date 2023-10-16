#ifndef HISTOGRAM_HISTO_H
#define HISTOGRAM_HISTO_H

#include <cstdint>
#include <cstring>
#include <iostream>

#include "../images/myImage.h"
#define HISTOGRAM_PATH "image/output/histogram.png"

using namespace Image;
namespace histo {
  void createHistogram(myImage image, uint32_t *histogram);
  void applyTransformation(myImage image, uint32_t *histogram);
  void histogramTransformation(myImage image);
}

#endif