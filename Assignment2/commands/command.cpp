#include "command.h"
#include <iostream>

namespace Command {
  void execute(std::string command, myImage image) {
    if(!strcmp(command.c_str(), HISTOGRAM_COMMAND)) {
      histogramTransformation(image);
    } else {
      std::cout << "Command not found" << std::endl;
    }
  }
}