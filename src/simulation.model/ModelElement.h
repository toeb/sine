#pragma once
#include <string>

#include <core/NamedObject.h>
#include <core/ValueLookup.h>
#include <core/Node.h>
#include <core/DataNode.h>
#include <core/TypedNode.h>

namespace nspace{

  class NodeDataClass : public ValueLookup, public NamedObject{

  };

  typedef TypedNode<NodeDataClass> ModelNode;
  
  class NodeData{
    ModelNode * _node;
  public:
    NodeData():_node(0){}
    void setNode(ModelNode * node){
      _node = node;
    }
    ModelNode * node(){return _node;}
    const ModelNode * node()const{return _node;}
  };

  class ModelElement: 
    public virtual ValueLookup, 
    public virtual NamedObject,
    public virtual NodeData
  {
    TYPED_OBJECT(ModelElement);
  public:
    ModelElement(){}
  };


}
