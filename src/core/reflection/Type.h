#pragma once
#include <config.h>
#include <core/Node.h>
#include <core/Set.h>
#include <core/Members.h>
#include <core/patterns/Singleton.h>
#include <memory>
namespace nspace{
class MemberInfo;
class MethodInfo;
class PropertyInfo;
class Type;

typedef uint TypeId;
class Types{
private:
  SINGLETON(Types){}
  Set< const Type * > _types;
public:
  static const Set< const Type * > & allTypes();
  static const Type * getType(const std::string & name);
  static bool registerType(const Type * type);
};


class Type : public Node<Type>{
private:
  static TypeId _typeCounter;
protected:
  Type();
public:  
  friend bool operator==(const Type & a, const Type & b);
  friend inline bool operator!=(const Type & a, const Type & b){return !(a==b);}
  friend std::ostream & operator <<(std::ostream & out, const Type & type);
  friend std::ostream & operator <<(std::ostream & out, const Type * type);
  void * createInstance()const;
  BASIC_PROPERTY(std::function<void * ()> , CreateInstanceFunction, private,,,); 
  BASIC_PROPERTY(TypeId, Id,public,,,);
  BASIC_PROPERTY(std::string,Name,public,,,);
  PROPERTYSET(const MemberInfo *, Members,,);
public:
  Set<const PropertyInfo*> Properties()const;
  const MemberInfo * getMember(const std::string & name)const;
  const MethodInfo * getMethodInfo(const std::string & name)const;
  const PropertyInfo * getProperty(const std::string & name)const;
  // returns true if othe class is super class of this type
  bool isSuperClassOf(const Type & other)const;

protected:
  void onPredecessorAdded(Type* type);
  void onPredecessorRemoved(Type* type);
};

template<typename T>
class RemovePointer{
public:
  typedef T Type;
};
template<typename T>
class RemovePointer<T*>{
public:
  typedef T Type;
};

template<typename T>
struct IsPointer{
  bool operator()()const{
    return false;
  }
};
template<typename T>
struct IsPointer<T*>{
  bool operator()()const{
    return true;
  }
};

template<typename T>
struct IsConst{
  bool operator()()const{
    return false;
  }
};
template<typename T>
struct IsConst<const T>{
  bool operator()()const{
    return true;
  }
};



template<typename T>
class TypeInfo : public Type{
  TEMPLATEDSINGLETON(TypeInfo, <T>){
    setName(RemovePointer<T>::Type::getTypeName());
  }
};

// macro allows typeinfo to be declared for primitve types
#define META(TYPE)\
template<>\
class /*nspace::*/TypeInfo<TYPE>: public /*nspace::*/Type{\
  TEMPLATEDSINGLETON(TypeInfo, <TYPE>){\
    setName(#TYPE);\
  }\
};

META(int);
META(double);
META(bool);
META(float);
META(char);
META(short);
META(unsigned int);
META(long);
META(long long);
META(unsigned char);


META(std::string);
META(std::ostream);
META(std::istream);
META(std::iostream);
META(std::ifstream);
META(std::ofstream);

// this macro returns the Type * instance for TYPENAME
#define typeof(TYPENAME) nspace::TypeInfo<TYPENAME>::instance()



// Macro for making an object a typed object.  
// defines a static meta information structure (TypeData) and virtual access methods @TODO rename TYPED_OBJECT to TYPED_CLASS
#define TYPED_OBJECT(TYPE)\
private:\
  typedef TYPE CurrentClassType;\
public:\
  static std::string getTypeName(){return std::string(#TYPE);}\
  virtual inline const nspace::Type & getType()const {return *nspace::TypeInfo<TYPE>::instance();}\
  virtual inline bool isInstanceOf(const Type * type)const{ return type->isSuperClassOf(this->getType());}\
  private:


// sets up inheritance hierarchy
#define SUBCLASSOF(TYPE)\
  private:\
  STATIC_INITIALIZER(TYPE##Subclass,{\
  auto unconstCurrentType = const_cast<nspace::Type*>(dynamic_cast<const nspace::Type*>(typeof(CurrentClassType)));\
  auto unconstSuperType = const_cast<nspace::Type*>(dynamic_cast<const nspace::Type*>(typeof(TYPE)));\
  unconstSuperType->successors()|=unconstCurrentType;\
})

}