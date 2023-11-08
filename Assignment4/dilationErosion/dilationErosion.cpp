#include "dilationErosion.h"
#include <iostream>
#include <memory>

#define dilation 1

namespace imDilationErosion {
  void dilateErode(myImage in, bool type) {
    uint8_t *structuringElem = createStructuringElement(3, 3);
    int width = 3;
    int height = 3;
    in.convertToSingleChannel();
    myImage dilatedImage = applyStructuringElement(&in, structuringElem, width, height, type);
    dilatedImage.convertFromSingleChannel();
    dilatedImage.outputImage(DILATE_PATH);
    delete[] dilatedImage.img;
  }

  uint8_t *createStructuringElement(int width, int height) {
    unique_ptr<uint8_t[]> structuringElem(new uint8_t[width * height]);
    uint8_t *structuringElemPtr = structuringElem.get();
    structuringElemPtr[0] = 0;
    structuringElemPtr[1] = 1;
    structuringElemPtr[2] = 0;
    structuringElemPtr[3] = 1;
    structuringElemPtr[4] = 1;
    structuringElemPtr[5] = 1;
    structuringElemPtr[6] = 0;
    structuringElemPtr[7] = 1;
    structuringElemPtr[8] = 0;
    return structuringElemPtr;
  }

  myImage applyStructuringElement(myImage *in, uint8_t *structuringElem,
                                  int widthStruct, int heightStruct,
                                  bool type) {
    int width = in->width;
    int height = in->height;
    int neededNum = countNeededNum(structuringElem, widthStruct, heightStruct);
    int center = widthStruct/2;
    uint8_t *temp = new uint8_t[width * height];
    myImage out(temp, width, height, 1);
    memset(temp, 0, width * height * sizeof(uint8_t));

    for(int y = 0; y < height; y++) {
      for(int x = 0; x < width; x++) {
        int count = 0;
        int idx = y*width + x;

        for(int structY = -center; structY <= center; structY++) {
          for(int structX = -center; structX <= center; structX++) {
            int imgX = x + structX;
            int imgY = y + structY;

            if(imgX >= 0 && imgX < width && imgY >= 0 && imgY < height) {
              int structIdx = (structY + center) * widthStruct + (structX + center);
              int imgIdx = imgY * width + imgX;
              if(structuringElem[structIdx] == 1 && in->img[imgIdx] == 255) {
                count++;
              }
            }
          }
        }
        if(type == dilation) {
          temp[idx] = (count >= 1) ? 255 : 0;
        } else {
          temp[idx] = (count == neededNum) ? 255 : 0;
          printf("Count == %d\tneededCount == %d\n", count, neededNum);
        }
      }
    }
    return out;
  }

  int countNeededNum(uint8_t *structuringElem, int widthStruct, int heightStruct) {
    int count = 0;
    for(int i = 0; i < widthStruct * heightStruct; i++) {
      if(structuringElem[i] == 1) {
        count++;
      }
    }
    return count;
  }
}