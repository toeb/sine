#pragma once

#include <core/Node.h>

namespace nspace{
  // a class holding all nodes of a graph
  class Graph{
  private:
    // field of all nodes this graph contains
    Set<Node*> _nodes;
  public:
    // returns all nodes of the graph
    Set<Node*> & nodes();
    // readonly access to all nodes in the graph
    const Set<Node*> & nodes()const;
    // gets a single node by comparison with id
    template<typename T> Node * operator()(const T id)const;
    // returns all nodes which have no predecessors
    Set<Node*> leaves()const;   
  };



  //implementaion of templated methods
  // gets a single node by comparison with id
  template<typename T>
  Node * Graph::operator()(const T id)const{
    return _nodes(id);
  }
}