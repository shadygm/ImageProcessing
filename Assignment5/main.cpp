#include <iostream>

#include "commands/command.h"
#include "images/myImage.h"

#define DILATE_COMMAND "dilate"
#define ERODE_COMMAND "erode"
const std::string trianglePath = "image/input/triangle.jpg";
const std::string h = "image/input/H.jpg";
const std::string erode = "erode";
const std::string dilate = "dilate";

using namespace Image;

int main() {
  myImage image = myImage(trianglePath);

  image.outputImage("image/output/og.png");

  image.convertToGrayScale();
  image.applyThreshold(100);
  image.outputImage("image/output/grayScale.png");

  Command::execute(erode, image);
  image.freeImage();
}