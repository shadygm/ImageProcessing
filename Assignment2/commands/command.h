#ifndef INTENSITYTRANSFORMATIONS_COMMAND_H
#define INTENSITYTRANSFORMATIONS_COMMAND_H

#include <cstdint>
#include <string>
#include <cstring>
#include "../images/myImage.h"
using namespace Image;
namespace Command {
  void execute(std::string command, myImage image);
}

#endif