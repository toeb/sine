#include <common/Config.h>

namespace nspace{
  union Pixel{
    struct{
      byte r;
      byte g;
      byte b;
      byte a;
    }color;
    byte value[4];
  };
}