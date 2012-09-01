#pragma once

#include <urdfreader/parsers/general/SiblingElementParser.h>

namespace mbslib{

class ChildElementParser : public SiblingElementParser{
private:
  ElementParser & _childParser;
public:
  ChildElementParser(ElementParser & parser):_childParser(parser),SiblingElementParser(parser){}
  virtual bool parse(tinyxml2::XMLElement * node){
    return SiblingElementParser::parse(node->FirstChildElement());
  }
};
}