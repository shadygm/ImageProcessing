
#include <cmath>
#include "imageSharpening.h"
#include <iostream>


using namespace std;
namespace imageSharpening {
  void sharpenImage(myImage image, int kernelHeightWidth) {
    uint8_t *temp = new uint8_t[image.arrSize];
    memcpy(temp, image.img, image.arrSize * sizeof(uint8_t));

    int w = image.width;
    int h = image.height;
    int ch = image.channels;
    auto img = image.img;
    
    
    double **gaussianKernel = new double*[kernelHeightWidth];
    for(size_t i = 0; i < kernelHeightWidth; i++) {
      gaussianKernel[i] = new double[kernelHeightWidth];
    }

    buildGaussian(gaussianKernel, 1, kernelHeightWidth);
    applyGaussianKernel(gaussianKernel, image, kernelHeightWidth, "image/output/gaussian.png");

    double **laplacianOfGaussian = new double*[kernelHeightWidth];
    for(size_t i = 0; i < kernelHeightWidth; i++) {
      laplacianOfGaussian[i] = new double[kernelHeightWidth];
    }

    double laplacianWeights[] = {0, 1, 0, 1, -4, 1, 0, 1, 0};
    buildLaplacianKernel(laplacianOfGaussian, kernelHeightWidth, laplacianWeights);

    applyLaPlace(image, laplacianWeights, kernelHeightWidth);

    for(size_t i = 0; i < kernelHeightWidth; i++) {
      delete[]gaussianKernel[i];
      delete[]laplacianOfGaussian[i];
    }
    delete[]laplacianOfGaussian;
    delete[]gaussianKernel;

  }

  

  void applyGaussianKernel(double** gaussianKernel, myImage image, int kernelHeightWidth, std::string path) {
    int w = image.width;
    int h = image.height;
    int ch = image.channels;

    int center = kernelHeightWidth / 2;

    uint8_t *temp = new uint8_t[image.arrSize];
    memcpy(temp, image.img, image.arrSize * sizeof(uint8_t));

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            double r = 0.0, g = 0.0, b = 0.0;

            for (int ky = -center; ky <= center; ky++) {
                for (int kx = -center; kx <= center; kx++) {
                    int imgY = y + ky;
                    int imgX = x + kx;

                    if (imgY >= 0 && imgY < h && imgX >= 0 && imgX < w) {
                        double kernelValue = gaussianKernel[ky + center][kx + center];
                        r += (double)temp[imgY * w * ch + imgX * ch] * kernelValue;
                        g += (double)temp[imgY * w * ch + imgX * ch + 1] * kernelValue;
                        b += (double)temp[imgY * w * ch + imgX * ch + 2] * kernelValue;
                    }
                }
            }

            int baseIndex = y * w * ch + x * ch;
            temp[baseIndex] = (uint8_t)r;
            temp[baseIndex + 1] = (uint8_t)g;
            temp[baseIndex + 2] = (uint8_t)b;
        }
    }

    uint8_t *og = image.img;
    image.img = temp;
    image.outputImage(path); // You can save the blurred image to a file
    // image.img = og;
    // delete[] og;
  }


  void buildGaussian(double** gaussianKernel, double sigma, int kernelDimensions) {
    double sum = 0.0;
    double center = floor(kernelDimensions / 2.0);

    for (size_t y = 0; y < kernelDimensions; y++) {
      for (size_t x = 0; x < kernelDimensions; x++) {
        double xDistance = x - center;
        double yDistance = y - center;
        gaussianKernel[y][x] = exp(-(xDistance * xDistance + yDistance * yDistance) / (2.0 * sigma * sigma)) / (2.0 * M_PI * sigma * sigma);
        sum += gaussianKernel[y][x];
      }
    }

    for (size_t y = 0; y < kernelDimensions; y++) {
      for (size_t x = 0; x < kernelDimensions; x++) {
        gaussianKernel[y][x] /= sum;
      }
    }
  }

  
  void buildLaplacianKernel(double** laplacianKernel, int kernelDimensions, double* weights) {
      // Calculate the center position of the kernel
      int center = (kernelDimensions) / 2;
      int weightIndex = 0;

      for (int y = 0; y < kernelDimensions; y++) {
          for (int x = 0; x < kernelDimensions; x++) {
              laplacianKernel[y][x] = weights[weightIndex++];
          }
      }
  }


  void applyLaPlace(myImage image, double* window, int n) {
    int width = image.width;
    int height = image.height;
    int channels = image.channels;
    uint8_t* img = image.img;
    uint8_t* temp = new uint8_t[image.arrSize];
    memcpy(temp, image.img, image.arrSize * sizeof(uint8_t));
    int radius = n / 2;

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        float sum = 0;

        // Calculate bounds for the sliding window
        int yMin = max(0, y - radius);
        int yMax = min(height - 1, y + radius);
        int xMin = max(0, x - radius);
        int xMax = min(width - 1, x + radius);

        for (int ny = yMin; ny <= yMax; ny++) {
          for (int nx = xMin; nx <= xMax; nx++) {
            int index = (ny * width + nx) * channels;
            float weight = window[(ny - yMin) * n + (nx - xMin)];
            sum += temp[index] * weight;
          }
        }

        int currentIndex = (y * width + x) * channels;
      
        sum = (sum + 4 * 255)/8;
        sum = min(255.0f, max(0.0f, sum));
      
        temp[currentIndex]     = (uint8_t)(sum);
        temp[currentIndex + 1] = (uint8_t)(sum);
        temp[currentIndex + 2] = (uint8_t)(sum);
      }
    }

    // for(size_t i = 0; i < image.arrSize; i++) {
    //   float sum = (float)temp[i] + (float)img[i];
    //   sum = min(255.0f, max(0.0f, sum));
    //   temp[i] = (uint8_t)sum;
    // }

    uint8_t* og = image.img;
    image.img = temp;
    image.outputImage("image/output/laplace.png"); // You can save the blurred image to a file
    image.img = og;
    delete[] temp;
  }


}
