#include "colorPiecewise.h"
#include <iostream>
#include <algorithm>
namespace colorPieceWise {
  void pieceWiseTransformation(myImage image) {
    applypieceWiseTransformation(150, 180, 150, 170, 0, 50, image); 
  }

  uint8_t checkBoundaries(uint8_t low, uint8_t high, uint8_t value) {
    if(value >= low && value <= high) {
      return value;
    } 
    return 0;
  }

  void applypieceWiseTransformation(uint8_t RLow, uint8_t RHigh, uint8_t GLow, uint8_t GHigh, uint8_t BLow, uint8_t BHigh , myImage image) {
    uint8_t *copy = new uint8_t[image.arrSize];
    int channels = image.channels;
    for(size_t i = 0; i < image.arrSize; i+= channels) {
      uint8_t red = image.img[i];
      uint8_t green = image.img[i+1];
      uint8_t blue = image.img[i+2];

      // red = checkBoundaries(RLow, RHigh, red);
      // green = checkBoundaries(GLow, GHigh, green);
      // blue = checkBoundaries(BLow, BHigh, blue);
      if(red >= RLow && red <= RHigh && green >= GLow && green <= GHigh && blue >= BLow && blue <= BHigh) {
        red = red;
        green = green;
        blue = blue;
      } else {
        red = 0;
        green = 0;
        blue = 0;
      }
      copy[i] = red;
      copy[i+1] = green;
      copy[i+2] = blue;
    }

    uint8_t *originalImage = image.img;
    image.img = copy;
    image.outputImage(COLOR_PIECEWISE_PATH);
    image.img = originalImage;
    delete[] copy;
  }
}

