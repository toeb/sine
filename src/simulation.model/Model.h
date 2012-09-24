#pragma once

#include <core/Set.h>
#include <core/Node.h>
#include <core/Graph.h>
#include <math/core.h>

#include <simulation.model/ModelElement.h>

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

