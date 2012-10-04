#pragma once
#include <core/DerivableDataNode.h>
namespace nspace{

  template<typename T>
  class DataNode : public DerivableDataNode<T,DataNode<T> >{
  public:
    DataNode(){}
    DataNode(T data):DerivableDataNode(data){}  
    DataNode<T> & operator = (T data){
      this->data()=data;
      return derived();
    }
  };
}