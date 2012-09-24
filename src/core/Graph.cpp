#include "Graph.h"


using namespace nspace;

// returns all nodes of the graph
Set<Node*> & Graph::nodes(){
  return _nodes;
}
// readonly access to all nodes in the graph
const Set<Node*> & Graph::nodes()const{
  return _nodes;
}



// returns all nodes which have no predecessors
Set<Node*> Graph::leaves()const{
  return nodes().subset([](Node * n){
    return (bool)!n->predecessors();
  });
}
