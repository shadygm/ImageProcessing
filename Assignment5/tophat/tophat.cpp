#include <iostream>
#include <vector>
#include <algorithm>
#include "tophat.h"

namespace imTophat {
  void tophat(myImage input) {
    myImage closing = computeClosing(&input);
    closing.outputImage(CLOSING_PATH);
    
    myImage dilatedClosing = imDilationErosion::applyStructuringElement(&closing, imDilationErosion::createCircularStructuringElement(11), 11, 11, dilation);
    dilatedClosing.outputImage("image/output/dilatedClosing.png");
    myImage tophatDilated = subtractInputFromClosing(&input, &dilatedClosing);
    
    tophatDilated.outputImage(TOPHAT_PATH);
    tophatDilated.applyThreshold(0.5);
    tophatDilated.outputImage("image/output/tophatDilatedThreshold.png");
    

    myImage tophat = subtractInputFromClosing(&input, &closing);
    tophat.applyThreshold(0 );
    tophat.outputImage("image/output/normalTophatThreshold.png");
    
    
    delete[] closing.img;
    delete[] dilatedClosing.img;
  }
  myImage computeClosing(myImage *input) {
    int width = 35;
    int height = 35;
    printf("Starting closing\n");
    uint8_t *structuringElem = imDilationErosion::createCircularStructuringElement(width);
    myImage dilated = imDilationErosion::applyStructuringElement(input, structuringElem, width, height, dilation);
    myImage eroded = imDilationErosion::applyStructuringElement(&dilated, structuringElem, width, height, erosion);
    eroded.outputImage("image/output/circularSE.png");
    printf("Closing done\n");
    delete[] structuringElem;
    delete [] dilated.img;
    return eroded;
  }
  myImage subtractInputFromClosing(myImage *input, myImage *closing) {
    unique_ptr<uint8_t[]> uniquePtr = unique_ptr<uint8_t[]>(new uint8_t[input->arrSize]);
    uint8_t *temp = uniquePtr.get();

    for(size_t i = 0; i < input->arrSize; i++) {
      uint8_t computed = closing->img[i] - input->img[i];
      temp[i] = std::min(255, std::max(0, (int)computed));
    }
    return myImage(temp, input->width, input->height, input->channels);
  }

  myImage medianFilter(myImage *input, int kernelDim) {
    printf("Starting median filter\n");
    uint8_t *temp = new uint8_t[input->arrSize];
    myImage out = myImage(temp, input->width, input->height, input->channels);
    int center = kernelDim / 2;

    for (size_t y = 0; y < input->height; y++) {
      for (size_t x = 0; x < input->width; x++) {
        for (size_t c = 0; c < input->channels; c++) {
          int idx = (y * input->width + x) * input->channels + c;
          std::vector<uint8_t> values;

          for (int yCenter = -center; yCenter <= center; yCenter++) {
            for (int xCenter = -center; xCenter <= center; xCenter++) {
              int imgY = y + yCenter;
              int imgX = x + xCenter;

              if (imgY >= 0 && imgY < input->height && imgX >= 0 &&
                  imgX < input->width) {
                values.push_back(
                    input->img[(imgY * input->width + imgX) * input->channels +
                               c]);
              }
            }
          }
          if (values.empty()) {
            continue;
          }
          std::sort(values.begin(), values.end());
          temp[idx] = values[values.size() / 2];
          values.clear();
        }
      }
    }
    printf("Median filter done\n");
    return out;
  }
}