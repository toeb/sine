#pragma once

#include <simulation.model/reader/ModelReader.h>
#include <iostream>
namespace nspace{

class UrdfModelReader : public ModelReader{
private:
  static UrdfModelReader * _instance;
  UrdfModelReader();
public:
  static UrdfModelReader & instance(){
    if(!_instance)_instance = new UrdfModelReader();
    return *_instance;
  }
  bool parse(IModelBuilder & builder, std::istream  & input);
  
private:
};

}