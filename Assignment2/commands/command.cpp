#include "command.h"
#include <iostream>

namespace Command {
  void execute(std::string command, myImage image) {
    if(!strcmp(command.c_str(), HISTOGRAM_COMMAND)) {
      histogramTransformation(image);
    } else if (!strcmp(command.c_str(), BAND_COMMAND)) {
      bandTransform(image);
    }
  }
}