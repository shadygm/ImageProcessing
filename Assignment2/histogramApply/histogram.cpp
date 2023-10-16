#include "histogram.h"
#include <iostream>
#include <assert.h>
using namespace std;
namespace histo {
  void histogramTransformation(myImage image) {

    uint8_t *histoModifiedImage = new uint8_t[image.arrSize];
    uint8_t *temp = new uint8_t[image.arrSize];
    memcpy(temp, image.img, image.arrSize * sizeof(uint8_t));
    
    uint8_t *ogStorage = image.img;
    image.img = temp;
    
    image.convertToGrayScale();

    uint32_t *histogram = new uint32_t[256];
    memset(histogram, 0, 256 * sizeof(uint32_t));

    createHistogram(image, histogram, 0);
    image.img = ogStorage;
    applyTransformation(image, histogram, histoModifiedImage, 0);
    applyTransformation(image, histogram, histoModifiedImage, 1);
    applyTransformation(image, histogram, histoModifiedImage, 2);
    
    image.img = histoModifiedImage;
    image.outputImage(HISTOGRAM_PATH);
    image.img = ogStorage;
    delete[] histogram;
    delete[] temp;
    delete[] histoModifiedImage;
  }

  void createHistogram(myImage image, uint32_t *histogram, size_t startingVal) {
    for(; startingVal < image.arrSize; startingVal += image.channels) {
      histogram[image.img[startingVal]]++;
    }
    
  }

  void applyTransformation(myImage image, uint32_t *histogram, uint8_t *histoModifiedImage, size_t startingVal) {
    float *cdf = new float[256];

    cdf[0] = histogram[0];

    for(int i = 1; i < 256; i++) {
      cdf[i] = cdf[i - 1] + histogram[i];
    }

    size_t imgSize = image.width * image.height;
    
    for(int i = 0; i < 256; i++) {
      cdf[i] = 255 * cdf[i] / imgSize;
      printf("cdf[%d]: %f\n", i, cdf[i]);
    } 

    for(; startingVal < image.arrSize; startingVal+= image.channels) {
      float cdfValue = cdf[image.img[startingVal]];
      histoModifiedImage[startingVal] = (uint8_t) cdfValue;
    }

    delete[] cdf;
  }
}