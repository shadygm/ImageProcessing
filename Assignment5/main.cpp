#include <iostream>

#include "commands/command.h"
#include "images/myImage.h"

#define DILATE_COMMAND "dilate"
#define ERODE_COMMAND "erode"
const std::string WRITING = "image/input/writing.jpg";
const std::string SMILE = "image/input/smallSmile.png";
const std::string ALTHOUGH = "image/input/although.png";
const std::string CLEAN = "image/input/cleanTest.jpg";
const std::string DIFF = "image/input/difficult.jpg";
const std::string TRIAL = "image/input/trial.jpg";
const std::string TOPHAT = "tophat";

using namespace Image;

int main() {
  myImage image = myImage(WRITING);
  printf("width = %d, height = %d\n", image.width, image.height);
  image.outputImage("image/output/og.png");

  image.convertToGrayScale();
  image.outputImage("image/output/grayScale.png");

  Command::execute(TOPHAT, image);
  image.freeImage();
}