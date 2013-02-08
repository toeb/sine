#include "CommandLineArgumentDefinition.h"

using namespace nspace;
using namespace nspace::commandline;


CommandLineArgumentDefinition::CommandLineArgumentDefinition(){}
CommandLineArgumentDefinition::CommandLineArgumentDefinition(const std::string & name,const std::string & description, const std::string & alias){
  setName(name);
  setDescription(description);
  if(alias!="") Aliases()|=alias;
}

bool CommandLineArgumentDefinition::isIdentifiedBy(const std::string & name) const {
  if(getName()==name) return true;
  if(Aliases().any([&name](std::string alias){return name==alias; })) return true;
  return false;
}