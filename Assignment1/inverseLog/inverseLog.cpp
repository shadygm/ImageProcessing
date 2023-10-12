#include "inverseLog.h"
#include <iostream>
#include <algorithm>
namespace logInvTrans {
  void inverseLogTransformation(myImage image) {
    float c = log10(image.maxLuminosity + 1) / 255;
    applyInverseLogTransformation(c, image); 
  }

  void applyInverseLogTransformation(float c, myImage image) {
    uint8_t *copy = new uint8_t[image.arrSize];
    for(size_t i = 0; i < image.arrSize; i++) {
      int value = image.img[i];
      value = pow(10, value*c) - 1;
      value = (uint8_t)min(255, max(0, value));

      copy[i] = (uint8_t)value;
    }

    uint8_t *originalImage = image.img;
    image.img = copy;
    image.outputImage(LOG_INVERSE_PATH);
    image.img = originalImage;
    delete[] copy;
  }
}

