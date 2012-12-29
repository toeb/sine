#pragma once
#include <utility.xml/ElementParser.h>

namespace nspace{
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