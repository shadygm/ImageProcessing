#include "dilationErosion.h"
#include <cmath>
#include <iostream>
#include <memory>

#define dilation true
#define erosion false
namespace imDilationErosion {
  void dilateErode(myImage in, bool type) {
    int width = 31;
    int height = 31;
    uint8_t *structuringElem = createStructuringElement(width, height);
    myImage dilatedImage = applyStructuringElement(&in, structuringElem, width, height, type);
  }


/*
 * Can be modified to anything. It currently just uses a completely full
 * structuring element. 
 */
  uint8_t *createStructuringElement(int width, int height) {
    printf("Creating structuring elem\n");
    uint8_t *structuringElem = new uint8_t[width * height];
    memset(structuringElem, 1, width * height * sizeof(uint8_t));
    printf("Structuring elem created\n");
    return structuringElem;
  }



  uint8_t *createCircularStructuringElement(int diameter) {
    printf("Creating circular structuring elem\n");
    if (diameter % 2 == 0) {
      // Ensure odd diameter for a symmetric circle
      diameter++;
    }

    int radius = diameter / 2;
    uint8_t *structuringElem = new uint8_t[diameter * diameter];

    for (int y = 0; y < diameter; y++) {
      for (int x = 0; x < diameter; x++) {
        int xOffset = x - radius;
        int yOffset = y - radius;
        double distance = sqrt(xOffset * xOffset + yOffset * yOffset);

        if (distance <= radius) {
          structuringElem[y * diameter + x] = 1;
        } else {
          structuringElem[y * diameter + x] = 0;
        }
      }
    }

    printf("Circular structuring elem created\n");
    return structuringElem;
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
    int neededNum = countNeededNum(structuringElem, widthStruct*heightStruct);
    int center = widthStruct / 2;
    uint8_t *temp = new uint8_t[width * height * channels];
    uint8_t *tempPtr = new uint8_t[widthStruct * heightStruct];
    myImage out(temp, width, height, channels);
    memset(temp , 0, width * channels * height * sizeof(uint8_t));
    memset(tempPtr, 0, widthStruct * heightStruct * sizeof(uint8_t));
    
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        for (int c = 0; c < channels; c++) {
          int count = 0;
          int idx = (y * width + x) * channels + c;
          int resultIdx = 0;
          for (int structY = -center; structY <= center; structY++) {
            for (int structX = -center; structX <= center; structX++) {
              int imgX = x + structX;
              int imgY = y + structY;

              if (imgX >= 0 && imgX < width && imgY >= 0 && imgY < height) {
                int structIdx = (structY + center) * widthStruct + (structX + center);
                int imgIdx = (imgY * width + imgX) * channels + c;

                if (structuringElem[structIdx] == 1) {
                  tempPtr[resultIdx++] = in->img[imgIdx];
                }
              }
            }
          }

          if (type == dilation) {
            temp[idx] = findMax(tempPtr, widthStruct*heightStruct);
          } else if (type == erosion) {
            temp[idx] = findMin(tempPtr, widthStruct*heightStruct);
          }
        }
      }
    }
    return out;
  }

  int countNeededNum(uint8_t *structuringElem, int size) {
    int count = 0;
    for(int i = 0; i < size; i++) {
      if(structuringElem[i] == 1) {
        count++;
      }
    }
    return count;
  }

  uint8_t findMax(uint8_t *arr, int size) {
    uint8_t max = 0;
    for(int i = 0; i < size; i++) {
      if(arr[i] > max) {
        max = arr[i];
      }
      arr[i] = 0;
    }
    return max;
  }

  uint8_t findMin(uint8_t *arr, int size) {
    uint8_t min = 255;
    for(int i = 0; i < size; i++) {
      if(arr[i] < min) {
        min = arr[i];
      }
      arr[i] = 255;
    }
    return min;
  }
}