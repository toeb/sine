#include "Vertex.h"
#include "Edge.h"
#include "HalfEdge.h"
using namespace IBDS;

HalfEdge * Vertex::getHalfEdgeTo(const Vertex * b)const{
  HalfEdge * first = edge->getHalfEdgeTo(this);
  HalfEdge * current = first;
  while(true){
    if(current == 0)return 0;
    if(current->getEndVertex()==b)return current;
    current = current->getNextHalfEdgeOf(b);
    if(current==first)break;
  }
  return 0;
}