#include "Edge.h"

using namespace IBDS;


void Edge::getDirection(Vector3D & dir){
  dir.assign(B->p_ocs - A->p_ocs);
}

bool Edge::isInFrontOf(const Edge * edge)const{
  if(A == edge->B)return true;
  return false;
}
bool Edge::isInBackOf(const Edge * edge)const{
  if(B == edge->A)return true;
  return false;
}
bool Edge::sharesVertex(const Edge * edge)const{
  if(A== edge->A)return true;
  if(B== edge->A)return true;
  if(A== edge->B)return true;
  if(B== edge->B)return true;
  return false;
}

HalfEdge * Edge::getHalfEdgeTo(const Vertex * v)const{
  if(forward->getEndVertex()==v)return forward;
  if(backward->getEndVertex()==v)return backward;
  return 0;
}