
#include <cmath>

void forwardDCT(unsigned char** input, int width, int height, double** output) {
double cu, cv, dctSum;

  for (int u = 0; u < height; u += 8) {
    for (int v = 0; v < width; v += 8) {
      for (int i = u; i < u + 8; i++) {
        for (int j = v; j < v + 8; j++) {
          cu = (i == u) ? 1 / sqrt(2) : 1;
          cv = (j == v) ? 1 / sqrt(2) : 1;

          dctSum = 0;
          for (int x = u; x < u + 8; x++) {
            for (int y = v; y < v + 8; y++) {
              dctSum += (input[x][y]) * cos((2 * (x - u) + 1) * i * M_PI / (2 * height)) * cos((2 * (y - v) + 1) * j * M_PI / (2 * width));
            }
          }
          output[i][j] = 0.25 * cu * cv * dctSum;
        }
      }
    }
  }
}

void inverseDCT(double** input, int width, int height, unsigned char** output) {
  double cu, cv, idctSum;

  for (int u = 0; u < height; u += 8) {
    for (int v = 0; v < width; v += 8) {
      for (int x = u; x < u + 8; x++) {
        for (int y = v; y < v + 8; y++) {
          idctSum = 0;
          for (int i = u; i < u + 8; i++) {
            for (int j = v; j < v + 8; j++) {
              cu = (i == u) ? 1 / sqrt(2) : 1;
              cv = (j == v) ? 1 / sqrt(2) : 1;

              idctSum += cu * cv * input[i][j] * cos((2 * x + 1) * (i - u) * M_PI / (2 * height)) * cos((2 * y + 1) * (j - v) * M_PI / (2 * width));
            }
          }
          output[x][y] = (unsigned char)(idctSum + 0.5);
        }
      }
    }
  }
}