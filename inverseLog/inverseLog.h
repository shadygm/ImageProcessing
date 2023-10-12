#ifndef INTENSITYTRANSFORMATIONS_LOGINVERSE_H
#define INTENSITYTRANSFORMATIONS_LOGINVERSE_H

#include "../image/myImage.h"
#include <cstdint>
#include <cstring>
#include <cmath>
#define LOG_INVERSE_PATH "images/output/logInverse.png"

using namespace Image;
using namespace std;
namespace logInvTrans {
  void inverseLogTransformation(myImage image);
  void applyInverseLogTransformation(float c, myImage image);
}

#endif