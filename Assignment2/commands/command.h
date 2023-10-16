#ifndef INTENSITYTRANSFORMATIONS_COMMAND_H
#define INTENSITYTRANSFORMATIONS_COMMAND_H

#include <cstdint>
#include <string>
#include <cstring>
#include "../images/myImage.h"
#include "../histogramApply/histogram.h"

#define HISTOGRAM_COMMAND "histogram"

using namespace Image;
using namespace histo;
namespace Command {
  void execute(std::string command, myImage image);
}

#endif