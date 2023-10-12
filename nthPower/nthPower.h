#ifndef INTENSITYTRANSFORMATIONS_NTHPOWER_H
#define INTENSITYTRANSFORMATIONS_NTHNPOWER_H

#include "../image/myImage.h"
#include <cstdint>
#include <cstring>
#include <cmath>
#define NTH_POWER_PATH "images/output/nthPower.png"

using namespace Image;
using namespace std;
namespace nthPower {
  void nthPowerTransformation(myImage image);
  void applyNthPowerTransformation(float c, float gamma, myImage image);
}

#endif