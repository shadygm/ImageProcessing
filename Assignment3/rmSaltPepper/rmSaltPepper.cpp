
#include <cmath>
#include "rmSaltPepper.h"
#include <iostream>

namespace saltPepper {
  void sweeten(myImage image) {
    uint8_t *temp = new uint8_t[image.arrSize];
    memcpy(temp, image.img, image.arrSize * sizeof(uint8_t));

    int w = image.width;
    int h = image.height;
    int ch = image.channels;
    auto img = image.img;



    image.outputImage(SALT_PEPPER_PATH);
  }

}
