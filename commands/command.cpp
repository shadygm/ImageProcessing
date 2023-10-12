#include "command.h"
#include <iostream>

namespace Command {
  void execute(std::string command, myImage image) {
    if(!strcmp(command.c_str(), IDENTITY_COMMAND)) {
      identityTransformation(image);
    } else if (!strcmp(command.c_str(), INVERSE_COMMAND)) {
      inverseTransformation(image);
    } else if (!strcmp(command.c_str(), LOG_COMMAND)) {
      logTransformation(image);
    } else if (!strcmp(command.c_str(), INVERSE_LOG_COMMAND)) {
      inverseLogTransformation(image);
    } else if (!strcmp(command.c_str(), NTH_POWER_COMMAND)){
      nthPowerTransformation(image);
    } else if (!strcmp(command.c_str(), COLOR_PIECEWISE_COMMAND)) {
      pieceWiseTransformation(image);
    }
  }
}