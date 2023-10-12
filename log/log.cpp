#include "log.h"
#include <iostream>
#include <algorithm>
namespace logTrans {
  void logTransformation(myImage image) {
    float c = 255/log(image.maxLuminosity + 1);
    applyLogTransformation(c, image); 
  }

  void applyLogTransformation(float c, myImage image) {
    uint8_t *logImage = new uint8_t[image.arrSize];
    for(size_t i = 0; i < image.arrSize; i++) {
      int value = image.img[i];
      value = c * log(1.0 + value);
      value = (uint8_t)min(255, max(0, value));

      logImage[i] = (uint8_t)value;
    }

    uint8_t *originalImage = image.img;
    image.img = logImage;
    image.outputImage(LOG_PATH);
    image.img = originalImage;
    delete[] logImage;
  }
}

