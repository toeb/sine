#pragma once

#include <config.h>
#include <ostream>
#include <string>

#define EXTENDED_PROPERTY(MODIFIER,TYPE, NAME,BEFORECHANGE, AFTERCHANGE) \
private:\
  TYPE _##NAME;\
  MODIFIER:\
    TYPE get##NAME()const{\
    return _##NAME;\
    }\
    void set##NAME(TYPE value){\
    BEFORECHANGE;\
      if(_##NAME==value)return;\
      bool cancel = false;\
        this->on##NAME##Changing(_##NAME,value,cancel);\
        if(cancel)return;\
      this->_##NAME = value;\
      AFTERCHANGE;\
    }\
  private:\
  void on##NAME##Changing(TYPE oldvalue, TYPE & newvalue, bool & cancel)

// This macro defines a Property in a class generating getter and setter methods
// as well as a field of the specified TYPE called _<Name> .  It also checks the value for equality 
// before changing it (if the oldvalue and new value are equal the set method just returns)
// The last statement generated is a method called on<NAME>Changing(<TYPE> oldvalue,<TYPE> newvalue, bool & cancel)
// which the client needs to implement (minimally by adding empty braces)
// IMPORTANT :  you can initialize the fields normally in the constructor by writing :_<Name>(...)
//  Example 1: 
//  PROPERTY(int, NumberOfOrders){}  will create:
//  - a private int field called _NumberOfOrders
//  - the getter and setter method int getNumberOfOrders()const, void setNumberOfOrders(int value)
//  - the onNumberOfOrdersChanging(...) method
//  Example 2: 
//  PROPERTY(int, NumberOfOrders){
//    if(newvalue < 3){ 
//      cancel = true;
//      return;
//    }
//    std::cout << "Number of Orders changed from " << oldvalue << " to " << newvalue <<std::endl;
//  }
//  this will create the same field and methods as example 1 however it will cancel the change if
//  the new value is smaller than 3.  if the value is higher than three a string will be printed
//  e.g: setNumberOfOrders(4) --> "Number of Orders changed from 0 to 4"
#define PROPERTY(TYPE, NAME) EXTENDED_PROPERTY(public,TYPE,NAME,{},{})


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

#define TYPED_OBJECT(type) public:\
  static inline const TypeData & ClassType(){static TypeData typeData(#type); return typeData; };\
  virtual inline const TypeId & getType()const {return ClassType().id;}\
  virtual inline const TypeData & getTypeData()const {return ClassType();}

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
  //std::ostream & operator<<(std::ostream & out)const;
  // tostring method which returns the string
  std::string toString()const;

  friend std::ostream & operator << (std::ostream & out, const Object * obj);  
  friend std::ostream & operator << (std::ostream & out, const Object & obj);
};







}