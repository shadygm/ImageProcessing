
#include <cmath>
#include "band.h"
#include <iostream>


namespace band {
  void bandTransform(myImage image) {
    uint8_t *temp = new uint8_t[image.arrSize];
    memcpy(temp, image.img, image.arrSize * sizeof(uint8_t));

    double *dct = new double[image.arrSize];

    forwardDCT(image.img, image.width, image.height, dct);

      // Process the DCT coefficients or apply any other operations as needed

    inverseDCT(dct, image.width, image.height, image.img);

    image.outputImage(BAND_PATH);
    delete[] dct;
  }

  void forwardDCT(uint8_t* input, int width, int height, double* output) {
    double cu, cv, dctSum;

    for (int u = 0; u < height; u++) {
      
    // std::cout << "Running here\n";
        for (int v = 0; v < width; v++) {
            cu = (u == 0) ? 1 / sqrt(2) : 1;
            cv = (v == 0) ? 1 / sqrt(2) : 1;

            dctSum = 0;
            for (int x = 0; x < height; x++) {
                for (int y = 0; y < width; y++) {
                    dctSum += input[x * width + y] *
                              cos((2 * x + 1) * u * M_PI / (2 * height)) *
                              cos((2 * y + 1) * v * M_PI / (2 * width));
                }
            }
            output[u * width + v] = 0.25 * cu * cv * dctSum;
            printf("%.3f ", (output[u * width + v]));
        }
        printf("\n\n");
    }
}

void inverseDCT(double* input, int width, int height, uint8_t* output) {
    double cu, cv, idctSum;
    std::cout << "Running here\n";
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            idctSum = 0;
            for (int u = 0; u < height; u++) {
                for (int v = 0; v < width; v++) {
                    cu = (u == 0) ? 1 / sqrt(2) : 1;
                    cv = (v == 0) ? 1 / sqrt(2) : 1;

                    idctSum += cu * cv * input[u * width + v] *
                              cos((2 * x + 1) * u * M_PI / (2 * height)) *
                              cos((2 * y + 1) * v * M_PI / (2 * width));
                }
            }
            output[x * width + y] = (unsigned char)(idctSum + 0.5);
        }
    }
}

}
