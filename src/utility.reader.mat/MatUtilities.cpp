#include "MatUtilities.h"

using namespace nspace;
namespace nspace{
  bool isLittleEndian()
  {
    short int number = 0x1;
    char *numPtr = (char*)&number;
    return (numPtr[0] == 1);
  }
}