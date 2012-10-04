#pragma once

#include <core/Node.h>

namespace nspace{

  template<typename T, typename Derived>
  class DerivableDataNode: public Node<Derived>{
    T _data;
  public:
    DerivableDataNode(){}
    DerivableDataNode(T data):_data(data){}
    T & data(){return _data;}
    const T & data()const{return _data;}

    Derived & operator = (T data){
      this->data()=data;
      return derived();
    }
    operator T&() {
      return _data;
    }
    operator const T & ()const{
      return _data;
    }
  };

}