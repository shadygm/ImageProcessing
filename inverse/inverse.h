#ifndef INTENSITYTRANSFORMATIONS_INVERSE_H
#define INTENSITYTRANSFORMATIONS_INVERSE_H

#include "../image/myImage.h"
#include <cstdint>
#include <cstring>
#define INVERSE_PATH "images/output/inverse.png"

using namespace Image;
namespace inverse {
  void inverseTransformation(myImage image);
  void applyInverseTransformation(int maxLumi, myImage image);
}

#endif