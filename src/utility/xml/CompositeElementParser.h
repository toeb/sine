#pragma once

#include <urdfreader/common/Set.h>
#include <urdfreader/parsers/general/ElementParser.h>

namespace mbslib{
class CompositeElementParser : public Set<ElementParser*>, public ElementParser{
public:
  virtual bool parse(tinyxml2::XMLElement * node){
    
    bool result = false;
    reduce<bool>(*&result,[node](bool & res, ElementParser* current){
      res |= current->parse(node);
    });

    return result;
  }
protected:
 

};
}