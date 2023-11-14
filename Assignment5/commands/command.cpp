#include "command.h"
#include <iostream>

namespace Command {
  void execute(std::string command, myImage image) {
    if(!strcmp(command.c_str(), TOPHAT_COMMAND)) {
      tophat(image);
    } else {
      std::cout << "Command not found" << std::endl;
    }
  }
}