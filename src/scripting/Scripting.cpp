#include "Scripting.h"

#include <fstream>

using namespace std;
using namespace nspace;

bool VirtualScriptMachine::loadStream(std::istream & stream){
  logError("Not implemented");
  return false;
}
bool VirtualScriptMachine::loadString(const std::string & script){
  stringstream stream (script);
  return loadStream(stream);
}
bool VirtualScriptMachine::loadFile(const std::string & filename){
  ifstream stream(filename,fstream::in );

  if(!stream.good()){
    logError("could not load file " << filename);
    return false;
  }
  auto result = loadStream(stream);
  stream.close();
  return result;
}


bool VirtualScriptMachine::registerType(const Type * type){return false;}
bool VirtualScriptMachine::setVariable(const std::string & name, Argument argument){return false;}
Argument VirtualScriptMachine::getVariable(const std::string & name,const Type* type){return Argument();}


ScriptFunction VirtualScriptMachine::getFunction(const std::string & name){
  return getVariable<ScriptFunction>(name);
}
bool VirtualScriptMachine::setFunction(const std::string & name, ScriptFunction func ){
  return  setVariable(name,func);
}

