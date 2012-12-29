#pragma once
#include <config.h>

namespace nspace{
  union Pixel{
    struct{
      byte r;
      byte g;
      byte b;
      byte a;
    }color;
    byte value[4];
    byte toGrayscale()const{
      return (byte) (0.2126 * color.r + 0.7152 * color.r + 0.0722 * color.b);
    }
    void fromGrayscale(byte grayscale){
      color.r = grayscale;
      color.g = grayscale;
      color.b = grayscale;
      color.a = 255;
    }
  };
}