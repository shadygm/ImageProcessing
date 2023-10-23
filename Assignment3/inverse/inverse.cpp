#include "inverse.h"
#include <iostream>

namespace inverse {
  
  void applyInverseTransformation(int maxLumi, myImage image) {
    uint8_t *inverseImage = new uint8_t[image.arrSize];
    for (size_t i = 0; i < image.arrSize; i++) {
      int pixelValue = (int)image.img[i];
      int invertedValue = maxLumi - 1 - pixelValue;
      invertedValue = std::min(255, std::max(0, invertedValue));
      inverseImage[i] = (uint8_t)invertedValue;
    }

    uint8_t *originalImg = image.img;
    image.img = inverseImage;
    // image.outputImage(INVERSE_PATH);
    image.img = originalImg;
    delete[] inverseImage;
  }

  
  void inverseTransformation(myImage image) {
    applyInverseTransformation(image.maxLuminosity, image);
  }

  
}