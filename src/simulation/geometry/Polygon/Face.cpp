#include "Face.h"
#include "Edge.h"
using namespace nspace;
using namespace std;

void Face::getVertices(vector<Vertex *> & vertices)const{
  HalfEdge * current=first;
  while(true){
    if(!current)return;
    if(current->isForwardHalfEdge()){
      vertices.push_back(current->edge->A);
    }else{  
      vertices.push_back(current->edge->B);
    }
    current = current->next;
    if(current == first)return;
  }
}
 void Face::getCenter(Vector3D & c_ocs)const{
    HalfEdge * current = first;
    int count = 0;
    while(true){
      count++;
      current = current->next;
      if(current->isForwardHalfEdge()){
        Vector3D::add(c_ocs,current->edge->A->p_ocs,c_ocs);
      }else{
        Vector3D::add(c_ocs,current->edge->B->p_ocs,c_ocs);
      
      }
      if(current == first)break;
    }
    Vector3D::multiplyScalar(1.0/count,c_ocs,c_ocs);
  }