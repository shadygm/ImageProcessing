
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
    double *dct = new double[w * h];
    auto img = image.img;
    uint8_t *img1 = new uint8_t[w * h];



    image.outputImage(LOW_PASS_PATH);
    delete[] dct;
  }

}
