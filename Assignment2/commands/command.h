#ifndef INTENSITYTRANSFORMATIONS_COMMAND_H
#define INTENSITYTRANSFORMATIONS_COMMAND_H

#include <cstdint>
#include <string>
#include <cstring>
#include "../images/myImage.h"
#include "../histogramApply/histogram.h"
#include "../bandTransform/band.h"

#define HISTOGRAM_COMMAND "histogram"
#define BAND_COMMAND "band"
using namespace Image;
using namespace histo;
using namespace band;
namespace Command {
  void execute(std::string command, myImage image);
}

#endif