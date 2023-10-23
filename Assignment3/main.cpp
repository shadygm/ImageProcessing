#include <iostream>
#include "images/myImage.h"
#include "commands/command.h"


const std::string astroPath = "image/input/astro.PNG";
const std::string moonPath = "image/input/moon.PNG";
const std::string saltPepperPath = "image/input/saltpepper.PNG";

using namespace Image;

int main () {
  myImage image = myImage(moonPath);

  image.convertToGrayScale();
  Command::execute("sharpening", image);
  image.freeImage();   
}