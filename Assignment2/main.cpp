#include <iostream>
#include "images/myImage.h"
#include "commands/command.h"

const std::string doorPath = "image/input/door.jpg";
const std::string skiingPath = "image/input/skiing.jpg";
const std::string smogPath = "image/input/smog.jpg";
const std::string grayScale = "image/output/grayScale.jpg";

using namespace Image;

int main () {
  myImage image = myImage(smogPath);

  image.convertToGrayScale();
  image.outputImage(grayScale);
  Command::execute("histogram", image);
  image.freeImage();   
}