#pragma once


#include "ModelElement.h"
#include <urdfreader/common/Set.h>
#include <urdfreader/common/Node.h>
#include <urdfreader/common/Graph.h>
namespace mbslib{
  
  
class Model : public Graph,public ModelElement{


};
struct Body{
  Matrix3x3 inertia;
  Real mass;

};
}

