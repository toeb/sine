#pragma once

#include <urdfreader/parsers/general/ElementParser.h>
#include <string>

namespace mbslib{

class NamedChildParser : public ElementParser{
private:
  std::string _name;
public:
  NamedChildParser(){

  }
  NamedChildParser(const std::string &name):_name(name){}
  std::string & name(){
    return _name;
  }
  bool parse(tinyxml2::XMLElement * node){
    tinyxml2::XMLElement * child = node->FirstChildElement(_name.c_str());
    if(!child)return false;
    return parseChild(child);
  }
protected:
  virtual bool parseChild(tinyxml2::XMLElement * child)=0;
};
}