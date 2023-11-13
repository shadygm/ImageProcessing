#include "command.h"
#include <iostream>

namespace Command {
  void execute(std::string command, myImage image) {
    if(!strcmp(command.c_str(), DILATE_COMMAND)) {
      printf("number of rows: %d\tnumber of columns: %d\n", image.height, image.width);
      std::cout << "performing dilation" << std::endl;
      dilateErode(image, 1);
    } else if (!strcmp(command.c_str(), ERODE_COMMAND)) {
      std::cout << "performing erosion" << std::endl;
      dilateErode(image, 0);
    } else {
      std::cout << "Command not found" << std::endl;
    }
  }
}