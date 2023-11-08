#include "command.h"
#include <iostream>

namespace Command {
  void execute(std::string command, myImage image) {
    if(!strcmp(command.c_str(), DILATE_COMMAND)) {
      dilateErode(image, 1);
    } else if (!strcmp(command.c_str(), ERODE_COMMAND)) {
      dilateErode(image, 0);
    } else {
      std::cout << "Command not found" << std::endl;
    }
  }
}