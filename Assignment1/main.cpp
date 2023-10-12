#include <iostream>
#include "image/myImage.h"
#include "commands/command.h"

const std::string pepperPath = "images/input/peppers.png";
const std::string textbookPath = "images/input/textbook.png";
using namespace Image;
int main () {
  myImage image = myImage(pepperPath);
  Command::execute("colorPiecewise", image);
  image.convertToGrayScale();
  Command::execute("inverse", image); 
  Command::execute("identity", image);
  Command::execute("log", image);
  Command::execute("inverseLog", image);
  Command::execute("nthPower", image);
  image.freeImage();   
}