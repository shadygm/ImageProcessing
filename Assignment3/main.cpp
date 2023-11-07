#include <iostream>
#include "images/myImage.h"
#include "commands/command.h"


const std::string astroPath = "image/input/astro.PNG";
const std::string miniMoonPath = "image/input/moon.PNG";
const std::string saltPepperPath = "image/input/HQ_saltpepper.png";
const std::string moonPath = "image/input/half-moon-closeup.jpg";
const std::string galaxyPath = "image/input/galaxy.png";

using namespace Image;

int main () {
  myImage image = myImage(saltPepperPath);

  // for(int i = 0; i < 9; i++) {
  //   image.img[i] = 0;
  // }
  // image.width = 3;
  // image.height = 3;
  // image.channels = 1;
  // image.arrSize = 9;
  image.outputImage("image/output/og.png");

  image.convertToGrayScale();
  image.outputImage("image/output/grayScale.png");
  // Command::execute("sharpening", image);
  Command::execute("lowpass", image);
  image.freeImage();   
}