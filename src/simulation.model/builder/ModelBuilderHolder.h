#pragma once
#include <simulation.model/builder/IModelBuilder.h>

namespace nspace{
class ModelBuilderHolder{
private:
  IModelBuilder & _builder;
public:
  ModelBuilderHolder(IModelBuilder & builder):_builder(builder){

  }
  Model & model(){
    return *_builder.currentModel();
  }
  IModelBuilder &  builder(){
    return _builder;
  }
};
}