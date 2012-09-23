#pragma once
#include <config.h>

#include <tinyxml2/tinyxml2.h>

namespace nspace{
  //define mbslib::XMLElement
typedef tinyxml2::XMLElement XMLElement;

class ElementParser{
public:    
  //subclasses musst override and return true if parse of node was successfull
  virtual bool parse(XMLElement * node)=0;

  // parses all children of xml element passed
  bool parseChildrenOf(XMLElement * parent){
    return parseSiblingsOf(parent->FirstChildElement());
  }

  // node and all its sibling
  bool parseSiblingsOf(XMLElement * sibling){
    bool result = false;
    while(sibling){
      result |= parse(sibling);
      sibling = sibling->NextSiblingElement();
    }
    return result;
  }
};
}