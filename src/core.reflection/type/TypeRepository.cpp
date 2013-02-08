#include "TypeRepository.h"
#include <string>
using namespace std;
using namespace nspace;

const Set< const Type * > & TypeRepository::allTypes(){ return instance()->_types; }
bool TypeRepository::registerType(const Type * type){
  auto existingType = getType(type->getName());
  if(existingType)return false;
  instance()->_types.add(type);
  return true;
}

const Type * TypeRepository::getType(const std::string & name){
  auto type = instance()->_types.first([&name](const Type * type){ return type->getName()==name;  });
  return type;
}
