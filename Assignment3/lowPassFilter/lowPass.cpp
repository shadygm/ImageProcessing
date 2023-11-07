
#include <cmath>
#include "lowPass.h"
#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

namespace lowPass {
  void lowPassFun(myImage image) {
    uint8_t *temp = new uint8_t[image.arrSize];
    memcpy(temp, image.img, image.arrSize * sizeof(uint8_t));
    myImage copy = myImage(temp, image.width, image.height, image.channels);
    copy.convertToSingleChannel();

    int gaussianKernelSize = 3;
    int sigma = 6;
    int medianFilterSize = 7;
    double *gaussianKernel = buildGaussianKernel(sigma, gaussianKernelSize);
    myImage gaussianImage = applyKernel(&copy, gaussianKernel, gaussianKernelSize);
    gaussianImage.convertFromSingleChannel();
    gaussianImage.outputImage("image/output/gaussian.png");
    gaussianImage.convertToSingleChannel();
    
    // myImage threshHoldImage = thresholding(&gaussianImage);
    // copy.convertFromSingleChannel();
    // threshHoldImage.outputImage(LOW_PASS_PATH);

    myImage median = applyMedianFilter(&copy, medianFilterSize);
    median.convertFromSingleChannel();
    median.outputImage("image/output/median.png");

    delete[] gaussianKernel;
    delete[] gaussianImage.img;
    delete[] copy.img;
    // delete[] thresHoldImage.img;
    delete[] median.img;
  }

  double *buildGaussianKernel(double sigma, int kernelDimensions) {
    double *gaussianKernel = new double[kernelDimensions * kernelDimensions];
    double sum = 0.0;

    double center = floor(kernelDimensions / 2.0);
    for (size_t y = 0; y < kernelDimensions; y++) {
      for (size_t x = 0; x < kernelDimensions; x++) {
        double xDistance = x - center;
        double yDistance = y - center;
        gaussianKernel[y * kernelDimensions + x] =
            exp(-(xDistance * xDistance + yDistance * yDistance) /
                (2.0 * sigma * sigma)) /
            (2.0 * M_PI * sigma * sigma);
        sum += gaussianKernel[y * kernelDimensions + x];
      }
    }

    for (size_t i = 0; i < kernelDimensions * kernelDimensions; i++) {
      gaussianKernel[i] /= sum;
    }

    return gaussianKernel;
  }

  myImage applyKernel(myImage *in, double *kernel, int kernelHeightWidth) {
    int w = in->width;
    int h = in->height;
    int ch = in->channels;
    size_t imgSize = in->arrSize;
    int center = kernelHeightWidth / 2;

    std::unique_ptr<double[]> copyImage(new double[imgSize]);
    memset(copyImage.get(), 0, in->arrSize * sizeof(double));

    
    for (size_t i = 1; i < h - 1; i++) {
      for (size_t j = 1; j < w - 1; j++) {
        int idx = i * w + j * ch;
        int kernelIdx = 0;
        for (int yCenter = -center; yCenter <= center; yCenter++) {
          for (int xCenter = -center; xCenter <= center; xCenter++) {
            int imgY = i + yCenter;
            int imgX = j + xCenter;
            if (imgY >= 0 && imgY < h && imgX >= 0 && imgX < w) {
              if (imgY * w * ch + imgX * ch >= imgSize) {
                continue;
              }

              double kernelValue = kernel[kernelIdx];
              copyImage[idx] +=
                  (double)in->img[imgY * w * ch + imgX * ch] * kernelValue;
              kernelIdx++;
            }
          }
        }
      }
    }

    for (size_t i = 0; i < imgSize; i++) {
      copyImage[i] = std::min(255.0, std::max(0.0, copyImage[i]));
    }

    uint8_t *output = new uint8_t[imgSize];
    for (int i = 0; i < imgSize; i++) {
      output[i] = (uint8_t)copyImage[i];
    }

    return myImage(output, w, h, 1);
  }

  myImage thresholding(myImage *in) {
    int w = in->width;
    int h = in->height;
    int ch = in->channels;
    size_t imgSize = in->arrSize;
    int maxLumi = in->findMaxLumi();

    int threshold = 0.4*maxLumi;
    for (size_t i = 0; i < imgSize; i++) {
      if (in->img[i] > threshold) {
        in->img[i] = 255;
      } else {
        in->img[i] = 0;
      }
    }

    return *in;
  }

  myImage applyMedianFilter(myImage *in, int kernelSize) {
    int w = in->width;
    int h = in->height;
    int ch = in->channels;
    size_t imgSize = in->arrSize;
    int center = kernelSize / 2;

    uint8_t *output = new uint8_t[imgSize];
    memset(output, 0, imgSize * sizeof(uint8_t));
    for (size_t i = 1; i < h - 1; i++) {
      for (size_t j = 1; j < w - 1; j++) {
        int idx = i * w + j * ch;
        std::vector<uint8_t> pixelValues;

        for (int yCenter = -center; yCenter <= center; yCenter++) {
          for (int xCenter = -center; xCenter <= center; xCenter++) {
            int imgY = i + yCenter;
            int imgX = j + xCenter;

            if (imgY >= 0 && imgY < h && imgX >= 0 && imgX < w) {
              pixelValues.push_back(in->img[imgY * w * ch+ imgX * ch]);
            }
          }
        }
        if(pixelValues.empty()) {
          continue;
        }
        std::sort(pixelValues.begin(), pixelValues.end());
        output[idx] = pixelValues[pixelValues.size() / 2];
        pixelValues.clear();
      }
    }

    return myImage(output, w, h, 1);
  }
}
