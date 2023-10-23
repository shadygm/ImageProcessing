#include <iostream>
#include "images/myImage.h"
#include "commands/command.h"


const std::string astroPath = "image/input/astro.PNG";

using namespace Image;

int main () {
  myImage image = myImage(astroPath);

  image.convertToGrayScale();
  Command::execute("band", image);
  image.freeImage();   
}