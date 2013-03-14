#include "MatMatrixElement.h"


#include "MatFile.h"
using namespace nspace;

bool MatMatrixElement::doLoad(){
  bool swap = getHeader().getOwner()->getAreBytesSwapped();
  auto raw = getRawData().get();
  membuf buf(raw,raw+getHeader().byteSize);
  std::istream stream(&buf);
  stream.get();
  stream.get();
  char flags = stream.get();
  uint16 tmp;
  binaryRead(tmp,swap,stream);
  auto arrayClass = (Class)tmp;

  return false;
}
