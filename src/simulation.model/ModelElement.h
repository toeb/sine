#pragma once
#include <string>
#include <common/NamedObject.h>
#include <common/ValueLookup.h>
#include <common/Node.h>

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
