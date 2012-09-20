#pragma once

#include <config.h>
#include <ostream>
#include <string>
namespace nspace{

  
typedef const uint TypeId;
struct TypeData{
  TypeId id;
  
  inline operator const TypeId & ()const{return id;}
  TypeData();
  static unsigned int typeCount();
private:
  static unsigned int _typeCounter;
};
#define TYPED_OBJECT public: static inline const TypeData & ClassType(){static TypeData typeData; return typeData; }; virtual inline const TypeId getType()const {return ClassType().id;}

class Object{
TYPED_OBJECT;
private:
public:  
  virtual void toString(std::ostream & out)const;
  std::ostream & operator<<(std::ostream & out)const;
  std::string toString()const;
};



}