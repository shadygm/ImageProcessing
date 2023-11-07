#ifndef INTENSITYTRANSFORMATIONS_MYIMAGE_H
#define INTENSITYTRANSFORMATIONS_MYIMAGE_H


#include <string>
#include <iostream>

#define INVERSE_PATH  "images/output/inverse.png"

namespace Image {

  class myImage {
  public:
    int width, height, channels, maxLuminosity;
    size_t arrSize;
    uint8_t *img;

    myImage(uint8_t *img, int width, int height, int channels);

    myImage(std::string path);

    void outputImage(std::string path) const;

    void convertToGrayScale();

    int findMaxLumi();

    void freeImage();
    void print();
    void convertToSingleChannel();
    void convertFromSingleChannel();
  };
}

#endif

