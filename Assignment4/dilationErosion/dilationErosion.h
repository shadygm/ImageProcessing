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
myImage applyStructuringElement(myImage *image, uint8_t *structuringElem,
                     int structuringElemHeight, int structuringElemWidth, bool type);
int countNeededNum(uint8_t *structuringElem, int widthStruct, int heightStruct);
}

#endif