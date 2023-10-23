
#include <cmath>
#include "lowPass.h"
#include <iostream>

namespace lowPass {
  void lowPassFun(myImage image) {
    uint8_t *temp = new uint8_t[image.arrSize];
    memcpy(temp, image.img, image.arrSize * sizeof(uint8_t));

    int w = image.width;
    int h = image.height;
    int ch = image.channels;
    auto img = image.img;



    image.outputImage(LOW_PASS_PATH);
  }

}
