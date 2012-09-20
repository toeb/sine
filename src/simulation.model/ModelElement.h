#pragma once
#include <string>

#include <core/NamedObject.h>
#include <core/ValueLookup.h>
#include <core/Node.h>

namespace nspace{
  
  class NodeData{
    Node * _node;
  public:
    NodeData():_node(0){}
    void setNode(Node * node){
      _node = node;
    }
    Node * node(){return _node;}
    const Node * node()const{return _node;}
  };

  class ModelElement:
    public NodeData,
    public ValueLookup, 
    public NamedObject{
  



  };
}
