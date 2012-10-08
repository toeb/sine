#pragma once

#include <config.h>
#include <ostream>
#include <string>


#define FIELDNAME(NAME) _##NAME
#define FIELD(MODIFIER, TYPE,NAME) MODIFIER: TYPE FIELDNAME(NAME);
#define GETTER(MODIFIER, TYPE,NAME) MODIFIER: inline TYPE get##NAME()const{return FIELDNAME(NAME);}
#define SETTER(MODIFIER,TYPE,NAME,BEFORESET,AFTERSET) MODIFIER:inline  void set##NAME(TYPE newvalue){BEFORESET; FIELDNAME(NAME) = newvalue; AFTERSET;} 
#define READONLY_REFERENCE(MODIFIER, TYPE,NAME) MODIFIER:inline  const TYPE & NAME()const{return FIELDNAME(NAME);}
#define REFERENCE(MODIFIER,TYPE,NAME) MODIFIER:inline TYPE & NAME(){return FIELDNAME(NAME);}

#define FIELD_REFERENCE(MODIFIER,TYPE,NAME) FIELD(private,TYPE,NAME) READONLY_REFERENCE(MODIFIER,TYPE,NAME); REFERENCE(MODIFIER, TYPE,NAME);
#define PUBLIC_FIELD_REFERENCE(TYPE,NAME) FIELD_REFERENCE(public,TYPE,NAME)

#define READONLY_SIMPLE_PROPERTY(TYPE,NAME)\
  FIELD(private, TYPE,NAME);\
  GETTER(public,TYPE,NAME);


#define READONLY_PROPERTY(TYPE,NAME) \
  READONLY_REFERENCE(public,TYPE,NAME)\
  READONLY_SIMPLE_PROPERTY(TYPE,NAME)


/*
#define READONLY_REFERENCE(TYPE,NAME,FIELDNAME)\
  const TYPE & NAME()const{return FIELDNAME;}

#define REFERENCE(TYPE,NAME,FIELDNAME) 

#define EXTENDED_REFERENCE(TYPE,NAME,EXTENSION)\
  

#define REFERENCE(TYPE,NAME, FIELD) 
  */

// the signature of the on changing method (w/o returntype, which is void)
#define ON_PROPERTY_CHANGING(TYPE,NAME) on##NAME##Changing(TYPE oldvalue, TYPE & newvalue, bool & cancel)
// a nicer to read alias of ON_PROPERTY_CHANGING
#define propertyChanging(TYPE,NAME) ON_PROPERTY_CHANGING(TYPE,NAME)

#define EXTENDED_PROPERTY(MODIFIER,TYPE, NAME,BEFORESET, AFTERSET) \
  FIELD(private,TYPE,NAME);\
  GETTER(public,TYPE,NAME);\
  SETTER(public,TYPE,NAME,BEFORESET; if(FIELDNAME(NAME)==newvalue)return; bool cancel=false;  this->on##NAME##Changing(FIELDNAME(NAME),newvalue,cancel); if(cancel)return;, AFTERSET; );\
  private:\
  void ON_PROPERTY_CHANGING(TYPE,NAME)

#define EXTENDED_REFERENCE_PROPERTY(MODIFIER,TYPE, NAME)\
  MODIFIER:\
  const TYPE & NAME()const{return _##NAME;} \
  TYPE & NAME(){return _##NAME;} \
  private:

#define REFERENCE_PROPERTY(TYPE, NAME) EXTENDED_REFERENCE_PROPERTY(public,TYPE, NAME)


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
#define SIMPLE_PROPERTY(TYPE, NAME) EXTENDED_PROPERTY(public,TYPE,NAME,{},{})


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

  friend bool operator == (const Object & a, const Object & b){
    return &a==&b;
  }
};







}