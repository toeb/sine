#pragma once

#include <urdfreader/parsers/general/tinyxml2.h>
#include <urdfreader/parsers/general/ElementParser.h>
#include <string>

namespace mbslib{


class NamedElementParser : public ElementParser{
private:
  std::string _name;
public:
  const std::string & elementName()const{return _name;}
  NamedElementParser(const std::string  &name):_name(name){}
  bool parse(tinyxml2::XMLElement* node){
    const char * cstr = node->Name();
    if(!cstr)return false;
    std::string name = cstr;
    if(name!=_name)return false;
    return parseNamedElement(node);
  }
protected:
  virtual bool parseNamedElement(tinyxml2::XMLElement* node)=0;
};
}