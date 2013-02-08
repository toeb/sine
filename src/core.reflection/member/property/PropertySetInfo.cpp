#include "PropertySetInfo.h"
using namespace nspace;


PropertySetInfo::PropertySetInfo():
  _ElementType(0),
  _CustomElementSerializer(0),
  _CustomElementDeserializer(0),
  _IsPointerCollection(false)//,
//  _ElementToObjectConverter([](void * ptr){return static_cast<Object*>(0);})
{}

/*
Object * PropertySetInfo::elementAsObjectPointer(Object * object, uint i)const{
  if(!getIsPointerCollection())return 0;
  void * value;
  if(!getElement(object,i,&value))return 0;
  return getElementToObjectConverter()(value);
}
*/