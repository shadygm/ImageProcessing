#include <iostream>
#include "images/myImage.h"
#include "commands/command.h"

const std::string doorPath = "image/input/door.jpg";
const std::string skiingPath = "image/input/skiing.jpg";
const std::string smogPath = "image/input/smog.jpg";
using namespace Image;
int main () {
  myImage image = myImage(doorPath);

  image.convertToGrayScale();
  image.outputImage("image/output/doorGrayScale.png");
  image.freeImage();   
}