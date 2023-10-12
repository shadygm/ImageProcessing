#ifndef INTENSITYTRANSFORMATIONS_COMMAND_H
#define INTENSITYTRANSFORMATIONS_COMMAND_H

#include <cstdint>
#include <string>
#include <cstring>
#include "../image/myImage.h"
#include "../inverse/inverse.h"
#include "../identity/identity.h"
#include "../inverseLog/inverseLog.h"
#include "../log/log.h"
#include "../nthPower/nthPower.h"
#include "../colorPiecewise/colorPiecewise.h"
#define IDENTITY_COMMAND "identity"
#define INVERSE_COMMAND  "inverse"
#define LOG_COMMAND      "log"
#define INVERSE_LOG_COMMAND "inverseLog"
#define NTH_POWER_COMMAND "nthPower"
#define COLOR_PIECEWISE_COMMAND "colorPiecewise"
using namespace Image;
using namespace inverse;
using namespace identity;
using namespace logTrans;
using namespace logInvTrans;
using namespace nthPower;
using namespace colorPieceWise;
namespace Command {
  void execute(std::string command, myImage image);
}

#endif