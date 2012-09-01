#pragma once

#include <utility/xml/ElementParser.h>
#include <utility/xml/ChildElementParser.h>
#include <utility/xml/CompositeElementParser.h>

namespace nspace{

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