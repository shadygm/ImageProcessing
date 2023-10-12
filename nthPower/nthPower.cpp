#include "nthPower.h"
#include <iostream>
#include <algorithm>
namespace nthPower {
  void nthPowerTransformation(myImage image) {
    float gamma = 0.4;
    float c = 255/pow(image.maxLuminosity, gamma);
    applyNthPowerTransformation(c, gamma, image); 
  }

  void applyNthPowerTransformation(float c, float gamma, myImage image) {
    uint8_t *copy = new uint8_t[image.arrSize];
    for(size_t i = 0; i < image.arrSize; i++) {
      int value = image.img[i];
      value = pow(value, gamma) * c;
      value = (uint8_t)min(255, max(0, value));
      copy[i] = (uint8_t)value;
    }

    uint8_t *originalImage = image.img;
    image.img = copy;
    image.outputImage(NTH_POWER_PATH);
    image.img = originalImage;
    delete[] copy;
  }
}

