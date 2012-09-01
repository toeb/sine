#pragma once

#include <urdfreader/IModelBuilder.h>
#include <iostream>
namespace mbslib{
class ModelReader{
private:
protected:
  std::string readToEnd(std::istream & input)const;
public:
  virtual bool parse(IModelBuilder & builder, std::istream & input)=0;
  virtual bool parseFile(IModelBuilder & bulder, const std::string & filename);
  virtual bool parseString(IModelBuilder & builder, const std::string & textData);
};
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