#include "MatElement.h"

using namespace nspace;

bool MatElement::load(ElementHeader header, std::shared_ptr<char> data){
  setHeader(header);
  setRawData(data);    
  return doLoad();
}
