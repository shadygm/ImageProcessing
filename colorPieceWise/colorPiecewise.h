#ifndef INTENSITYTRANSFORMATIONS_COLOR_PIECEWISE_H
#define INTENSITYTRANSFORMATIONS_COLOR_PIECEWISE_H

#include "../image/myImage.h"
#include <cstdint>
#include <cstring>
#include <cmath>
#define COLOR_PIECEWISE_PATH "images/output/piecewise.png"

using namespace Image;
using namespace std;
namespace colorPieceWise {
  void pieceWiseTransformation(myImage image);
  void applypieceWiseTransformation(uint8_t RLow, uint8_t RHigh, uint8_t GLow, uint8_t GHigh, uint8_t BLow, uint8_t BHigh , myImage image);
  uint8_t checkBoundaries (uint8_t low, uint8_t high, uint8_t value);
}

#endif