#pragma once
#include <urdfreader/parsers/general/ElementParser.h>

namespace mbslib{

class SiblingElementParser: public ElementParser{
  private:
  ElementParser & _siblingParser;
public:
  SiblingElementParser(ElementParser & parser):_siblingParser(parser){}
  virtual bool parse(tinyxml2::XMLElement * node){
    while(node){
      _siblingParser.parse(node);
      node = node->NextSiblingElement();
    }
    return true;
  }
};
}