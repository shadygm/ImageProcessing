#include "myImage.h"
#include <iostream>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image/stb_image.h"
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image/stb_image_write.h"

namespace Image {

  myImage::myImage(uint8_t *img, int width, int height, int channels) {
    this->img = img;
    this->width = width;
    this->height = height;
    this->channels = channels;
    this->arrSize = width * height * channels;
    this->maxLuminosity = findMaxLumi();
  }
  myImage::myImage(std::string path) {
    this->img = stbi_load(path.c_str(), &this->width, &this->height, &this->channels, 0);
    if(this->img == nullptr) {
      std::cerr << "Failed to load image: " << stbi_failure_reason() << std::endl;
    }
    printf("channels loaded: %d\n", this->channels);
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
    size_t i = 0;
    for (size_t idx = 0; idx < (size_t)width*height; idx ++) {
      if(i + 2>= arrSize) {
        break;
      }

      size_t red = i;
      size_t green = i + 1;
      size_t blue = i + 2;
      double gray = ((double)img[red] + (double)img[green] + (double)img[blue]) / 3.0;
      gray = std::min(255.0, std::max(0.0, gray));
      img[red] = gray;
      img[green] = gray;
      img[blue] = gray;
      i += channels;
    }
    
    // uint8_t *ogStorage = img;
    // img = temp;
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
  
  void myImage::print() {
    for(size_t i = 0; i < arrSize; i++) {
      printf("%3d ", img[i]);
      if(i % width == 0) {
        printf("\n");
      }
    }
    printf("\n");
  }

  void myImage::convertToSingleChannel() {
    if(channels == 1) {
      printf("Cannot convert to single channel\n");
      return;
    }

    int idx = 0;
    for (size_t i = 0; i < arrSize; i += channels) {
      img[idx] = img[i];
      idx++;
    }
    this->channels = 1;
    this->arrSize = width * height;

  }

  void myImage::convertFromSingleChannel() {
    if(channels != 1) {
      printf("Cannot convert from single channel\n");
      return;
    }

    uint8_t *temp = new uint8_t[width * height * 3];
    int idx = 0;
    for (size_t i = 0; i < arrSize; i++) {
      temp[idx] = img[i];
      temp[idx + 1] = img[i];
      temp[idx + 2] = img[i];
      idx += 3;
    }
    uint8_t *ogStorage = img;
    this->channels = 3;
    this->arrSize = width * height * 3;
    this->img = temp;
    delete[] ogStorage;
  }

  void myImage::applyThreshold(int threshold) {
    for(int i = 0; i < arrSize; i++) {
      img[i] = (img[i] > threshold) ? 255 : 0;
    }
  }
}
#endif
#endif