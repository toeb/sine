#include "MatFile.h"
#include "MatElementFactory.h"

using namespace nspace;


bool MatFile::addElement(ElementHeader header, std::shared_ptr<char> rawData){  
  auto element = matElementFactory(header,rawData);
  if(!(bool)element)return false;
  Elements().push_back(element);
  return true;
}