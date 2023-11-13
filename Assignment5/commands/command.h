#ifndef INTENSITYTRANSFORMATIONS_COMMAND_H
#define INTENSITYTRANSFORMATIONS_COMMAND_H

#include <cstdint>
#include <string>
#include <cstring>
#include "../dilationErosion/dilationErosion.h"
#include "../images/myImage.h"

#define DILATE_COMMAND "dilate"
#define ERODE_COMMAND "erode"


using namespace imDilationErosion;
using namespace Image;
namespace Command {
  void execute(std::string command, myImage image);
}

#endif