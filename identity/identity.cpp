#include "identity.h"
#include <iostream>

namespace identity {
  void identityTransformation(myImage image) {
    image.outputImage(IDENTITY_PATH);
  }
}