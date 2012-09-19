#pragma once


#include <simulation.model/ModelElement.h>
#include <common/Set.h>
#include <common/Node.h>
#include <common/Graph.h>
#include <math/definitions.h>

namespace nspace{
  
  
class Model : public Graph,public ModelElement{

  friend std::ostream & operator << (std::ostream & stream, const Model & model){
    model.leaves().foreachElement([&stream](Node * node){
      stream << *node;
    });
    return stream;
  }
};

struct Body{
  Matrix3x3 inertia;
  Real mass;

};
}

