#pragma once

#include <tinyxml2/tinyxml2.h>
#include <utility.xml/ElementParser.h>
#include <string>

namespace nspace{


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