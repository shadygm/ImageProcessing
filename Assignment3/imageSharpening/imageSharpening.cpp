
#include <cmath>
#include "imageSharpening.h"
#include <iostream>
#include <memory>




using namespace std;
namespace imageSharpening {
  void sharpenImage(myImage originalImage, int kernelHeightWidth) {

    printf("OG arrSize == %d\n", originalImage.arrSize);
    uint8_t *copyImage = new uint8_t[originalImage.arrSize];
    memcpy(copyImage, originalImage.img, originalImage.arrSize * sizeof(uint8_t));
    myImage copy = myImage(copyImage, originalImage.width, originalImage.height, originalImage.channels);

    copy.convertToSingleChannel();
    printf("singleChannel ArrSize == %d\n", copy.arrSize);

    printf("IMAGE SHARPENING\n\n");
    double *gaussianKernel = buildGaussianKernel(1.0, 3);
    for(int i = 0; i < 9; i++) {
      printf("%f ", gaussianKernel[i]);
    }
    printf("\n");
    myImage gaussianImage = applyKernel(&copy, gaussianKernel, 3, "gaussian");

    gaussianImage.outputImage("image/output/gaussian.png");
    printf("Gaussian arrSize == %d\n", gaussianImage.arrSize);

    double *laplacianKernel = buildLaplacianKernel();
    myImage laplacianImage = applyKernel(&gaussianImage, laplacianKernel, 3, "laplacian");
    laplacianImage.outputImage("image/output/laplacian.png");

    myImage sharpenedImage = sharpenImage(&laplacianImage, &originalImage);
    sharpenedImage.outputImage("image/output/sharpened.png");

    delete[] gaussianKernel;
    delete[] laplacianKernel;
    delete[] copy.img;
    delete[] gaussianImage.img;
    delete[] laplacianImage.img;
    delete[] sharpenedImage.img;
  }

  double* buildGaussianKernel(double sigma, int kernelDimensions) {
    double *gaussianKernel = new double[kernelDimensions*kernelDimensions];
    double sum = 0.0;

    double center = floor(kernelDimensions / 2.0);
    for(size_t y = 0; y < kernelDimensions; y++) {
      for(size_t x = 0; x < kernelDimensions; x++) {
        double xDistance = x - center;
        double yDistance = y - center;
        gaussianKernel[y*kernelDimensions + x] = exp(-(xDistance * xDistance + yDistance * yDistance) 
        / (2.0 * sigma * sigma)) / (2.0 * M_PI * sigma * sigma);
        sum += gaussianKernel[y*kernelDimensions + x];
      }
    }

    for(size_t y = 0; y < kernelDimensions; y++) {
      for(size_t x = 0; x < kernelDimensions; x++) {
        gaussianKernel[y*kernelDimensions + x] /= sum;
      }
    }

    return gaussianKernel;
  }

  double* buildLaplacianKernel() {
    //im so sorry for this
    double *kernel = new double[9];
    kernel[0] = -1;
    kernel[1] = -1;
    kernel[2] = -1;
    kernel[3] = -1;
    kernel[4] = 8;
    kernel[5] = -1;
    kernel[6] = -1;
    kernel[7] = -1;
    kernel[8] = -1;
    return kernel;
  }

  myImage applyKernel(myImage *in, double *kernel, int kernelHeightWidth, string typeKernel) {
    double *copyImage = new double[in->arrSize];
    memset(copyImage, 0, in->arrSize * sizeof(double));

    int w = in->width;
    int h = in->height;
    int ch = in->channels;
    size_t imgSize = in->arrSize;
    int center = kernelHeightWidth / 2;

    for(size_t i = 1; i < h - 1; i ++) {
      for (size_t j = 1; j < w - 1; j++) {
        int idx = i * w + j * ch;
        int kernelIdx = 0;
        for(int yCenter = -center; yCenter <= center; yCenter++) {
          for(int xCenter = -center; xCenter <= center; xCenter++) {
            int imgY = i + yCenter;
            int imgX = j + xCenter;
            if(imgY >= 0 && imgY < h && imgX >= 0 && imgX < w) {
              if (imgY * w * ch + imgX * ch >= imgSize ) {
                continue;
              }

              double kernelValue = kernel[kernelIdx];
              copyImage[idx] += (double)in->img[imgY * w * ch + imgX * ch] * kernelValue;
              kernelIdx++;
            }
          }
        }
      }
    }


    if(!strcmp(typeKernel.c_str(), "laplacian")) {
      printf("laplacian\n");
      for(int i = 0; i < imgSize; i++) {
        copyImage[i] = 2*copyImage[i];
      }
    }

    for (size_t i = 0; i < imgSize; i++) {
      copyImage[i] = std::min(255.0, std::max(0.0, copyImage[i]));
    }

    uint8_t *output = new uint8_t[imgSize];
    for (int i = 0; i < imgSize; i++) {
      output[i] = (uint8_t)copyImage[i];
    }

    free(copyImage);
    return myImage(output, w, h, ch);
  }

  myImage sharpenImage(myImage *laplacian, myImage *original) {
    std::unique_ptr<double[]> copyImage(new double[laplacian->arrSize]);

    for(int i = 0; i < laplacian->arrSize; i++) {
      copyImage[i] = (double)laplacian->img[i] + (double)original->img[i];
    }

    uint8_t *output = new uint8_t[laplacian->arrSize];
    for (int i = 0; i < laplacian->arrSize; i++) {
      output[i] = std::min(255.0 , std::max(0.0, copyImage[i]));
    }
    return myImage(output, laplacian->width, laplacian->height, laplacian->channels);
  }
}