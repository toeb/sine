#include "HalfEdge.h"
#include "Edge.h"
#include "Face.h"

using namespace nspace;

bool HalfEdge::isForwardHalfEdge()const{
  if(edge->forward == this)return true;
  return false;
}

bool HalfEdge::isFirstHalfEdgeOfFace()const{
  if(face->first == this)return true;
  return false;
}
HalfEdge * HalfEdge::getPrevious()const{
  HalfEdge * current = next;
  while(true){
    if(!current)return 0;
    current = current->next;
    if(current->next==this)return current;
  }
}

Vertex * HalfEdge::getStartVertex()const{
  if(isForwardHalfEdge()){
    return edge->A;
  }else{
    return edge->B;
  }
}
Vertex * HalfEdge::getEndVertex()const{
  if(isForwardHalfEdge()){
    return edge->B;
  }else{
    return edge->A;
  }
}
HalfEdge * HalfEdge::getNextHalfEdgeOf(const Vertex * c)const{
  if(getStartVertex()==c)return edge->getHalfEdgeTo(c);
  if(!next)return 0;
  if(next->getStartVertex() == c)return next;
  return 0;
}

HalfEdge * HalfEdge::getReverseHalfEdge()const{
  if(edge->forward==this)return edge->backward;
  return edge->forward;
}