#pragma once

#include <urdfreader/parsers/general/ElementParser.h>
#include <urdfreader/parsers/general/ChildElementParser.h>
#include <urdfreader/parsers/general/CompositeElementParser.h>

namespace mbslib{

class CompositeChildParser : public ElementParser{
private :
  ChildElementParser _childParser;
  CompositeElementParser _compositeParser;
public:
  CompositeElementParser & composite(){return _compositeParser;}
  CompositeChildParser():_childParser(_compositeParser){

  }
  virtual bool parse(tinyxml2::XMLElement * node){
    return _childParser.parse(node);
  }
};

}