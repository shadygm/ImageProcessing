#ifndef INTENSITYTRANSFORMATIONS_COMMAND_H
#define INTENSITYTRANSFORMATIONS_COMMAND_H

#include <cstdint>
#include <string>
#include <cstring>
#include "../imageSharpening/imageSharpening.h"
#include "../lowPassFilter/lowPass.h"
#include "../images/myImage.h"

#define SHARPENING_COMMAND "sharpening"
#define LOWPASS_COMMAND "lowpass"

using namespace imageSharpening;
using namespace lowPass;
using namespace Image;
namespace Command {
  void execute(std::string command, myImage image);
}

#endif