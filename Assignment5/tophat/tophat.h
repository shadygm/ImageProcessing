#ifndef TOPHAT_H
#define TOPHAT_H

#include <cmath>
#include <cstdint>
#include <cstring>
#include <memory>

#include "../dilationErosion/dilationErosion.h"
#include "../images/myImage.h"
#define TOPHAT_PATH "image/output/tophat.png"
#define CLOSING_PATH "image/output/closing.png"
#define dilation true
#define erosion false
using namespace Image;
namespace imTophat {
void tophat(myImage input);
myImage computeClosing(myImage *input);
myImage subtractInputFromClosing(myImage *input, myImage *closing);
myImage medianFilter(myImage *input, int kernelDim);
}
#endif