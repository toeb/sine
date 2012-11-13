#pragma once
#include <config.h>
#include <core/TypedNode.h>
#include <core/Set.h>
#include <core/Members.h>
#include <memory>
namespace nspace{
class MemberInfo;
class Property;
class Object;
typedef const uint TypeId;
typedef const uint ObjectId;

// struct representing a type. it is part of a inheritance graph
class TypeData : public Node<TypeData>{   
public:
  // the id of this type
  TypeId id;  
  // name of this type
  std::string name;
  PROPERTYSET(const MemberInfo*, Members,,)
  PROPERTYSET(const MemberInfo*, DirectMembers,,)
  PROPERTYSET(const Property*,Properties,,)
  PROPERTYSET(const Property*,DirectProperties,,)
private:  
  //declare copy constructor private.
  TypeData(const TypeData& original):id(original.id){
    convertToBase=[](void * p){return static_cast<Object*>(0);};
  }
  // also = operator?
public:
  bool isSuperClassOf(const TypeData & child)const{
    // TODO THIS DOES NOT WORK AND I KNOW WHY
    if(&child == this)return true;
    for(uint i=0; i < child.predecessors(); i++){
      auto current = child.predecessor(i);
      if(isSuperClassOf(*current))return true;
    }
    return false;
  }

  static const TypeData & UnknownType;
  // operator for converting this TypeData to its type id
  inline operator const TypeId & ()const{return id;}

  std::function<Object* (void * )> convertToBase;
  // default constructor
  TypeData();  
  // constructor accepting name
  TypeData(const std::string & name);
  // number of typedata structs created
  static unsigned int typeCount();
  //void * createInstance();
  const Property * getProperty(const std::string & name)const;
  const MemberInfo * getMember(const std::string & name)const;
protected:
  void onPredecessorAdded(TypeData* typedata);
  void onPredecessorRemoved(TypeData* typedata);

private:
  static unsigned int _typeCounter;
};


template<typename T>
class TypeDataProvider{
public:
static inline const TypeData & getTypeData(){
  return TypeData::UnknownType;
}
};

}



#define TYPEDATAPROVIDER(TYPE) \
  template<>\
  class TypeDataProvider<TYPE>{\
  public:\
    static inline const TypeData & getTypeData(){\
      return TYPE::ClassType();\
    }\
  };\
  template<>\
  class TypeDataProvider<TYPE*>{\
  public:\
    static inline const TypeData & getTypeData(){\
      return TYPE::ClassType();\
    }\
  };

// macro returns the TypeData of the specified typename
#define typeof(TYPE) (TypeDataProvider<TYPE>::getTypeData())


// Macro for making an object a typed object.  
// defines a static meta information structure (TypeData) and virtual access methods @TODO rename TYPED_OBJECT to TYPED_CLASS
#define TYPED_OBJECT(type)\
private:\
  typedef type CurrentClassType;\
public:\
  static inline const TypeData & ClassType(){static TypeData typeData(#type); return typeData; };\
  virtual inline const TypeId & getType()const {return ClassType().id;}\
  virtual inline const TypeData & getTypeData()const {return ClassType();}\
  inline bool isInstanceOf(const TypeData & other)const{return other.isSuperClassOf(ClassType());}\
  private:

// sets up inheritance hierarchy
#define SUBCLASSOF(TYPE)\
  private:\
  STATIC_INITIALIZER(TYPE##Subclass,{\
  TypeData * unconstCurrentType = const_cast<TypeData*>(&ClassType());\
  TypeData * unconstSuperType = const_cast<TypeData*>(&TYPE::ClassType());\
  unconstSuperType->successors()|=unconstCurrentType;\
})

