#pragma once

#include <utility.xml/SiblingElementParser.h>

namespace nspace{

class ChildElementParser : public SiblingElementParser{
private:
  ElementParser & _childParser;
public:
  ChildElementParser(ElementParser & parser):SiblingElementParser(parser),_childParser(parser){}
  virtual bool parse(tinyxml2::XMLElement * node);
};
}
