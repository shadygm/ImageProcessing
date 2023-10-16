#include "histogram.h"
#include <iostream>

using namespace std;
namespace histo {
  void histogramTransformation(myImage image) {

    cout << "Creating histogram" << endl;

    uint32_t *histogram = new uint32_t[256];
    memset(histogram, 0, 256 * sizeof(uint32_t));
    createHistogram(image, histogram);
    applyTransformation(image, histogram);

    delete[] histogram;
  }

  void createHistogram(myImage image, uint32_t *histogram) {
    for(size_t i = 0; i < image.arrSize; i += image.channels) {
      histogram[image.img[i]]++;
    }
  }

  void applyTransformation(myImage image, uint32_t *histogram) {
    uint32_t *cdf = new uint32_t[256];
    uint8_t *hisoModifiedImage = new uint8_t[image.arrSize];
    
    uint8_t *ogImage = image.img;
    image.img = hisoModifiedImage;

    cdf[0] = histogram[0];

    for(int i = 1; i < 256; i++) {
      cdf[i] = cdf[i - 1] + histogram[i];
    }
    size_t imgSize = image.width * image.height;
    for(int i = 0; i < 256; i++) {
      cdf[i] = (cdf[i]*255) / imgSize;
    } 

    for(size_t i = 0; i < image.arrSize; i++) {
      uint32_t cdfValue = cdf[image.img[i]];
      //round cdfValue
      cdfValue = (uint8_t)min(255, max(0, (int)cdfValue));
      for(int j = 0; j < image.channels; j++) {
        image.img[i + j] = cdfValue * image.maxLuminosity;
      }

    }
    
    image.outputImage(HISTOGRAM_PATH);
    image.img = ogImage;

    delete [] hisoModifiedImage;

    delete[] cdf;
  }
}