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
    friend std::ostream &  operator << (std::ostream & out, const DerivableDataNode<T,Derived> &node ){
      out << "node{";
      node.toStream(out);
      out << "}";
      return out;
    }

    virtual void toStream(std::ostream & out)const{
      out << data();
    }

    void successorsToStream(std::ostream & out){
      this->dfsWithPath([](Derived* current, Set<Derived*> path){
        cout << spaces(path.size());
        cout << *current<<"\n";
      });
    }


  };

}