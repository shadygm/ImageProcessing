#include "command.h"
#include <iostream>

namespace Command {
  void execute(std::string command, myImage image) {
    if(!strcmp(command.c_str(), SHARPENING_COMMAND)) {
      sharpenImage(image, 3);
    } else {
      std::cout << "Command not found" << std::endl;
    }
  }
}