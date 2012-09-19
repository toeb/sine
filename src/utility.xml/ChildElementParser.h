#pragma once

#include <utility.xml/SiblingElementParser.h>

namespace nspace{

class ChildElementParser : public SiblingElementParser{
private:
  ElementParser & _childParser;
public:
  ChildElementParser(ElementParser & parser):_childParser(parser),SiblingElementParser(parser){}
  virtual bool parse(tinyxml2::XMLElement * node);
};
}