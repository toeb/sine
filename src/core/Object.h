#pragma once

#include <config.h>
#include <ostream>
#include <string>

namespace nspace{

typedef const uint TypeId;
typedef const uint ObjectId;
// struct representing a type. 
struct TypeData{
  // the id of this type
  TypeId id;  
  // name of this type
  std::string name;
  // operator for converting this TypeData to its type id
  inline operator const TypeId & ()const{return id;}

  // default constructor
  TypeData();  
  // default constructor
  TypeData(const std::string & name);
  // number of typedata structs created
  static unsigned int typeCount();
private:
  static unsigned int _typeCounter;
};

// Macro for making an object a typed object.  

#define TYPED_OBJECT(type) public: static inline const TypeData & ClassType(){static TypeData typeData(#type); return typeData; }; virtual inline const TypeId & getType()const {return ClassType().id;} virtual inline const TypeData & getTypeData()const {return ClassType();}

// base class including types
class Object{
TYPED_OBJECT(Object);
private:
  static uint _idCounter;
  ObjectId _id;

public:  
  Object();
  ~Object();
  inline const ObjectId & objectId()const{return _id;}
  // tostring method which converts this object to a string representation (should be overridden by subclasses)
  virtual void toString(std::ostream & out)const;
  
  // to string operator
  std::ostream & operator<<(std::ostream & out)const;
  // tostring method which returns the string
  std::string toString()const;

};



}