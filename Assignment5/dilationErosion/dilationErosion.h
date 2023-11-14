#ifndef DILATION_H
#define DILATION_H

#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>

#include "../images/myImage.h"
#define DILATE_PATH "image/output/modified.png"
using namespace Image;
using namespace std;
namespace imDilationErosion {
  void dilateErode(myImage image, bool type);
  uint8_t *createStructuringElement(int height, int width);
  uint8_t *createCircularStructuringElement(int diameter);
  myImage applyStructuringElement(myImage *image, uint8_t *structuringElem,
                      int structuringElemHeight, int structuringElemWidth, bool type);
  int countNeededNum(uint8_t *structuringElem, int size);
  uint8_t findMin(uint8_t *arr, int size);
  uint8_t findMax(uint8_t *arr, int size);
}

#endif