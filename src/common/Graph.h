#pragma once


namespace mbslib{
    // 
  class Graph{
  private:
    Set<Node*> _nodes;
  public:
    
    Set<Node*> & nodes(){
      return _nodes;
    }
    const Set<Node*> & nodes()const{
      return _nodes;
    }
    template<typename T>
    Node * operator()(const T id)const{
      return _nodes(id);
    }


  protected:
   
  };
}