#ifndef INTENSITYTRANSFORMATIONS_LOG_H
#define INTENSITYTRANSFORMATIONS_LOG_H

#include "../image/myImage.h"
#include <cstdint>
#include <cstring>
#include <cmath>
#define LOG_PATH "images/output/log.png"

using namespace Image;
using namespace std;
namespace logTrans {
  void logTransformation(myImage image);
  void applyLogTransformation(float c, myImage image);
}

#endif