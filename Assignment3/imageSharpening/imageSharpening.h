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
  void sharpenImage(myImage image);
  
}

#endif
