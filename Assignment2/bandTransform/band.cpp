
#include <cmath>
#include "band.h"
#include <iostream>

namespace band {
  void bandTransform(myImage image) {
    uint8_t *temp = new uint8_t[image.arrSize];
    memcpy(temp, image.img, image.arrSize * sizeof(uint8_t));

    int w = image.width;
    int h = image.height;
    int ch = image.channels;
    double *dct = new double[w * h];
    auto img = image.img;
    uint8_t *img1 = new uint8_t[w * h];

    // You have 4 channels (ch = 4), 4th channel being K (probably) and shouldn't be changed (probably)

    // 3ch -> 1ch
    {
        int idx = 0;
        for (int i = 0;i < w * h;i++) {
            img1[i] = img[idx];
            idx += ch;
        }
    }

    // forwardDCT(image.img, image.width, image.height, dct);
    forwardDCT(img1, w, h, dct);

    dct[0] = 0; // freq. domain filter example - set mean to 0

    // Process the DCT coefficients or apply any other operations as needed

    // inverseDCT(dct, image.width, image.height, image.img);
    inverseDCT(dct, w, h, img1);

    // 1ch -> 3ch
    {
        int idx = 0;
        for (int i = 0;i < w * h;i++) {
            img[idx] =
            img[idx + 1] =
            img[idx + 2] = img1[i];
            idx += ch;
        }
    }

    image.outputImage(BAND_PATH);
    delete[] dct;
  }

  void forwardDCT(uint8_t* input, int width, int height, double* output) {
    double cu, cv, dctSum;

    for (int u = 0; u < height; u++) {
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
        }
    }
}

void inverseDCT(double* input, int width, int height, uint8_t* output) {
    double cu, cv, idctSum;
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
            double pval = (idctSum + 0.5) / ((float)width * (float)height / 16.0);
            output[x * width + y] = (unsigned char)(std::max(0.0, std::min(255.0, pval)));
        }
    }
}

}
