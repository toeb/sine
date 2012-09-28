#pragma once

#include <config.h>
#include <ostream>
#include <string>
namespace nspace{

typedef const uint TypeId;

// struct representing a type. 
struct TypeData{
  // the id of this type
  TypeId id;  
  // operator for converting this TypeData to its type id
  inline operator const TypeId & ()const{return id;}

  // default constructor
  TypeData();
  // number of typedata structs created
  static unsigned int typeCount();
private:
  static unsigned int _typeCounter;
};

// Macro for making an object a typed object.  
#define TYPED_OBJECT public: static inline const TypeData & ClassType(){static TypeData typeData; return typeData; }; virtual inline const TypeId & getType()const {return ClassType().id;}


// base class including types
class Object{
TYPED_OBJECT;
private:
public:  
  // tostring method which converts this object to a string representation (should be overridden by subclasses)
  virtual void toString(std::ostream & out)const;
  // to string operator
  std::ostream & operator<<(std::ostream & out)const;
  // tostring method which returns the string
  std::string toString()const;
};



}