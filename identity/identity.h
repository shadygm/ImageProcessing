#ifndef INTENSITYTRANSFORMATIONS_IDENTITY_H
#define INTENSITYTRANSFORMATIONS_IDENTITY_H

#include <cstdint>
#include <cstring>
#define IDENTITY_PATH "images/output/identity.png"
#include "../image/myImage.h"

using namespace Image;
namespace identity {
  void identityTransformation(myImage image);
}

#endif