#pragma once
#include <core.graph/DerivableDataNode.h>
namespace nspace{
  template<typename T>
  class DataNode : public DerivableDataNode<T,DataNode<T> >{
  public:
    DataNode(){}
    DataNode(T data):DerivableDataNode<T,DataNode<T> >(data){}
    DataNode<T> & operator = (T data){
      this->data()=data;
      return this->derived();
    }
  };
}
