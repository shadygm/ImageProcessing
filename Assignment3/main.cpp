#include <iostream>
#include "images/myImage.h"
#include "commands/command.h"


const std::string astroPath = "image/input/astro.PNG";
const std::string miniMoonPath = "image/input/moon.PNG";
const std::string saltPepperPath = "image/input/saltpepper.PNG";
const std::string moonPath = "image/input/half-moon-closeup.jpg";

using namespace Image;

int main () {
  myImage image = myImage(moonPath);
  image.outputImage("image/output/og.png");
  // for(int i = 0; i < 27; i++) {
  //   image.img[i] = 0;
  // }
  // image.img[12] = 255;
  // image.img[13] = 0;
  // image.img[14] = 0;


  // printf("original\n");
  // for(int i = 0; i < 27; i+= 3) {
  //   printf("%d ", image.img[i]);
  // }
  // printf("\n");

  // image.width = 3;
  // image.height = 3;
  // image.channels = 3;
  // image.arrSize = image.width * image.height * image.channels;
  image.convertToGrayScale();
  Command::execute("sharpening", image);
  image.freeImage();   
}