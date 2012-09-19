#pragma once
#include <urdfreader/ModelReader.h>

namespace mbslib{

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