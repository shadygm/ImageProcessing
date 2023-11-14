#ifndef INTENSITYTRANSFORMATIONS_COMMAND_H
#define INTENSITYTRANSFORMATIONS_COMMAND_H

#include <cstdint>
#include <string>
#include <cstring>
#include "../tophat/tophat.h"
#include "../images/myImage.h"

#define TOPHAT_COMMAND "tophat"


using namespace imTophat;
using namespace Image;
namespace Command {
  void execute(std::string command, myImage image);
}

#endif