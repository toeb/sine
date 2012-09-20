#include "SeparatingAxes.h"

using namespace std;
using namespace nspace;



bool SeparatingAxes::testCollision(const ISimulationObject & collidableA, const ISimulationObject & collidableB, Collision * collision)const{
  
  const Polygon & a = dynamic_cast<const Polygon &>(collidableA);
  const Polygon & b = dynamic_cast<const Polygon &>(collidableB);
  
  vector<Axis> axes;  
  for(int i = 0; i < a.faces().size(); i++){
    Axis axis;
    const Vector3D & n_ocs = a.face(i)->n_ocs;
    a.coordinates().fromObjectCoordinates(n_ocs,axis.n);
    axes.push_back(axis);
  }

  for(int i = 0; i < b.faces().size(); i++){
    Axis axis;
    const Vector3D & n_ocs = b.face(i)->n_ocs;
    b.coordinates().fromObjectCoordinates(n_ocs,axis.n);
    axes.push_back(axis);
  }

  for(int i= 0; i < a.edges().size(); i++){
    for(int j = 0; j < b.edges().size(); j++){
      Vector3D dirA,dirB;
      Edge * e1 = a.edge(i);
      Edge * e2 = b.edge(j);
      e1->getDirection(dirA);
      a.coordinates().fromObjectCoordinates(dirA,dirA);
      b.coordinates().fromObjectCoordinates(dirB,dirB);
      e2->getDirection(dirB);
      Axis axis;
      
      VectorOperations<Real>::crossProduct(axis.n,dirA,dirB);
      axis.n.normalize();

    }
  }

  for(int i = 0; i < axes.size(); i++){
    Axis current = axes.at(i);
    Interval intervalA,intervalB;
    a.project(current,intervalA);
    b.project(current,intervalB);
    if(!intervalA.overlaps(intervalB)) return false;
  }
  return true;
}