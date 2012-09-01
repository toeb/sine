#pragma once

#include <common/Set.h>
#include <utility/xml/ElementParser.h>

namespace nspace{

class CompositeElementParser : public Set<ElementParser*>, public ElementParser{
public:
  virtual bool parse(XMLElement * node){
    
    bool result = false;
    reduce<bool>(*&result,[node](bool & res, ElementParser* current){
      res |= current->parse(node);
    });

    return result;
  }
protected:
 

};
}