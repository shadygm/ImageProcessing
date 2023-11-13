#include "dilationErosion.h"
#include <iostream>
#include <memory>

#define dilation true
#define erosion false
namespace imDilationErosion {
  void dilateErode(myImage in, bool type) {
    int width = 31;
    int height = 31;
    uint8_t *structuringElem = createStructuringElement(width, height);
    std::cout << "num of channels == " << in.channels << "\n";
    myImage dilatedImage = applyStructuringElement(&in, structuringElem, width, height, type);
    // dilatedImage.convertFromSingleChannel();
    dilatedImage.outputImage(DILATE_PATH);
    delete[] dilatedImage.img;
  }


/*
 * Can be modified to anything. It currently just uses a completely full
 * structuring element. 
 */
  uint8_t *createStructuringElement(int width, int height) {
    unique_ptr<uint8_t[]> structuringElem(new uint8_t[width * height]);
    uint8_t *structuringElemPtr = structuringElem.get();
    memset(structuringElemPtr, 1, width * height * sizeof(uint8_t));
    return structuringElemPtr;
  }

  /*
   * Assumes that the structuring element is of odd dimensions and that the 
   * origin is at the center. 
   */
  myImage applyStructuringElement(myImage *in, uint8_t *structuringElem,
                                  int widthStruct, int heightStruct,
                                  bool type) {
    int width = in->width;
    int height = in->height;
    int channels = in->channels;
    int neededNum = countNeededNum(structuringElem, widthStruct, heightStruct);
    std::cout << "neededNum: " << neededNum << "\n";
    int center = widthStruct / 2;
    uint8_t *temp = new uint8_t[width * height * channels];
    myImage out(temp, width, height, channels);
    memset(temp, 0, width * channels * height * sizeof(uint8_t));

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        for (int c = 0; c < channels; c++) {
          int count = 0;
          int idx = (y * width + x) * channels + c;

          for (int structY = -center; structY <= center; structY++) {
            for (int structX = -center; structX <= center; structX++) {
              int imgX = x + structX;
              int imgY = y + structY;

              if (imgX >= 0 && imgX < width && imgY >= 0 && imgY < height) {
                int structIdx = (structY + center) * widthStruct + (structX + center);
                int imgIdx = (imgY * width + imgX) * channels + c;

                if (structuringElem[structIdx] == 1 && in->img[imgIdx] == 255) {
                  count++;
                }
              }
            }
          }

          if (type == dilation) {
            temp[idx] = (count >= 1) ? 255 : 0;
          } else if (type == erosion) {
            if(count == neededNum) {
              // printf("setting to 1");
            }
            temp[idx] = (count == neededNum) ? 255 : 0;
          }
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