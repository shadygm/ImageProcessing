#include "myImage.h"
#include <iostream>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image/stb_image_write.h"

namespace Image {

  myImage::myImage(std::string path) {
    this->img = stbi_load(path.c_str(), &this->width, &this->height, &this->channels, 0);
    if(this->img == nullptr) {
      std::cerr << "Failed to load image: " << stbi_failure_reason() << std::endl;
    }
    this->arrSize = width * height * channels;
    this->maxLuminosity = findMaxLumi();
  }


  void myImage::outputImage(std::string path) const {
    if (!stbi_write_jpg(path.c_str(), this->width, this->height, this->channels,
                        this->img, this->width * this->channels)) {
      std::cerr << "Failed to output image: " << stbi_failure_reason() << std::endl;
    }
  }

  void myImage::convertToGrayScale() {
    for (size_t i = 0; i < arrSize; i += channels) {

      // Adding 3 uint8_t can cause overflow!
      double gray = ((double)img[i] + (double)img[i + 1] + (double)img[i + 2]) / 3.0;
      gray = std::min(255.0, std::max(0.0, gray));
      img[i] = gray;
      img[i + 1] = gray;
      img[i + 2] = gray;
    }
    // uint8_t *ogStorage = img;
    // img = temp;
    outputImage("image/output/grayScale.png");
    // img = ogStorage;
    // delete[]temp;
  }

  int myImage::findMaxLumi() {
    int maxLumi = 0;
    for (size_t i = 0; i < arrSize; i += channels) {
      int pixelValue = (int)img[i];
      maxLumi = std::max(maxLumi, pixelValue);
    }
    return maxLumi;
  }
  void myImage::freeImage() {
    if(img != nullptr || img != NULL) {
      stbi_image_free(img);
    }
  }
}
#endif
#endif