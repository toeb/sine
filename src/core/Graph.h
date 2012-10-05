#pragma once

#include <core/Node.h>

namespace nspace{
  // a class holding all nodes of a graph
  template<typename NodeType>
  class Graph{
  private:
    // field of all nodes this graph contains
    Set<NodeType*> _nodes;
  public:
    // returns all nodes of the graph
    Set<NodeType*> & nodes();
    // readonly access to all nodes in the graph
    const Set<NodeType*> & nodes()const;
    // gets a single node by comparison with id
    template<typename T> NodeType * operator()(const T id)const;
    // returns all nodes which have no predecessors
    Set<NodeType*> leaves()const;
  };



  //implementation of templated methods

  // gets a single node by comparison with id
  template<typename NodeType>
  template<typename T>
  NodeType * Graph<NodeType>::operator()(const T id)const{
    return _nodes(id);
  }



  // returns all nodes of the graph
  template<typename NodeType>
  Set<NodeType*> & Graph<NodeType>::nodes(){
    return _nodes;
  }
  // readonly access to all nodes in the graph
  template<typename NodeType>
  const Set<NodeType*> & Graph<NodeType>::nodes()const{
    return _nodes;
  }

  // returns all nodes which have no predecessors
  template<typename NodeType>
  Set<NodeType*> Graph<NodeType>::leaves()const{
    return nodes().subset([](NodeType * n){
      return (bool)!n->predecessors();
    });
  }  

}