#include "SeparatingAxes.h"

using namespace std;
using namespace IBDS;


bool SeparatingAxes::testCollision(Collision & col){
  if(!(a||b))return false;
  
  vector<Axis> axes;  
  for(int i = 0; i < a->faces().size(); i++){
    Axis axis;
    const Vector3D & n_ocs = a->face(i)->n_ocs;
    a->fromObjectCoordinates(n_ocs,axis.n);
    axes.push_back(axis);
  }

  for(int i = 0; i < b->faces().size(); i++){
    Axis axis;
    const Vector3D & n_ocs = b->face(i)->n_ocs;
    b->fromObjectCoordinates(n_ocs,axis.n);
    axes.push_back(axis);
  }

  for(int i= 0; i < a->edges().size(); i++){
    for(int j = 0; j < b->edges().size(); j++){
      Vector3D dirA,dirB;
      Edge * e1 = a->edge(i);
      Edge * e2 = b->edge(j);
      e1->getDirection(dirA);
      a->fromObjectCoordinates(dirA,dirA);
      b->fromObjectCoordinates(dirB,dirB);
      e2->getDirection(dirB);
      Axis axis;
      
      Vector3D::crossProduct(dirA,dirB,axis.n);
      axis.n.normalize();

    }
  }

  for(int i = 0; i < axes.size(); i++){
    Axis current = axes.at(i);
    Interval intervalA,intervalB;
    a->project(current,intervalA);
    b->project(current,intervalB);
    if(!intervalA.overlaps(intervalB)) return false;
  }
  return true;
}