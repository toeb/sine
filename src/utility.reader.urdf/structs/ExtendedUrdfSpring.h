#pragma once
#include <config.h>

namespace nspace{
  struct ExtendedUrdfSpring{
    ExtendedUrdfSpring():k(0),d(0),length(-1){}
    Real k;
    Real d;
    Real length;
    bool automaticLength(){
      return length<0;
    }
  };
}