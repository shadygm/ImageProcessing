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
  void lowPass(myImage image);
  
}

#endif
