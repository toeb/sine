#pragma once

#include <core.reflection/type/Type.h>
namespace nspace{

  
  template<typename DerivedType> void Type::derivedToString(const void * pointer, std::ostream & stream){
    auto derived = static_cast<const DerivedType*>(pointer);
    auto obj = dynamic_cast<const Object*>(derived);

  }
  template<typename DerivedType> std::function<void (const void * , std::ostream &)> Type::derivedStringifier(){
    return [](const void * ptr, std::ostream  & stream){Type::derivedToString<DerivedType>(ptr,stream);};
  }

  template<typename T> std::shared_ptr<T> Type::createTypedInstance()const{
    return std::static_pointer_cast<T>(createInstance());
  }


  template<typename DerivedType>  Object * Type::rawCastToObject(void * pointer){
    auto derived = static_cast<DerivedType *>(pointer);
    auto object = dynamic_cast<Object*>(derived);
    return object;
  }
  template<typename DerivedType>  std::function<Object *(void * )> Type::rawToObjectCaster(){
    return [](void * ptr){return Type::rawCastToObject<DerivedType>(ptr);};
  }
  template<typename DerivedType>  std::shared_ptr<Object> Type::smartCastToObject(std::shared_ptr<void> pointer){
    auto derived = std::static_pointer_cast<DerivedType>(pointer);
    auto object = std::dynamic_pointer_cast<Object>(derived);
    return object;
  }
  template<typename DerivedType>  std::function<std::shared_ptr<Object> (std::shared_ptr<void>  )> Type::smartToObjectCaster(){
    return [](std::shared_ptr<void> ptr){return Type::smartCastToObject<DerivedType>(ptr);};
  }
  template<typename DerivedType>  std::shared_ptr<void> Type::smartCastToDerived(std::shared_ptr<Object> pointer){
    return std::static_pointer_cast<void>(std::dynamic_pointer_cast<DerivedType>(pointer));
  }
  template<typename DerivedType>  std::function<std::shared_ptr<void>(std::shared_ptr<Object>)> Type::smartToDerivedCaster(){
    return [](std::shared_ptr<Object> ptr){return Type::smartCastToDerived<DerivedType>(ptr);};
  }
  template<typename DerivedType>  void * Type::rawCastToDerived(Object * pointer){
    return static_cast<void*>( dynamic_cast<DerivedType*>(pointer));
  }
  template<typename DerivedType>  std::function<void*(Object *)> Type::rawToDerivedCaster(){
    return [](Object * ptr){return Type::rawCastToDerived<DerivedType>(ptr);};
  }

}