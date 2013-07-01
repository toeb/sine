#include "AttributeTarget.h"

#include <core.reflection/type/TypeInfo.h>
#include <core.reflection.builder.h>
using namespace nspace;

const Type* AttributeTarget::getType()const{
  return type_of<AttributeTarget>();
}
bool AttributeTarget::initializeType(){
  core::reflection::builder::reflect<AttributeTarget>()
    ->fullyQualifiedName(DS_INLINE_STRING("::"<<DS_STRINGIFY(nspace)<<"AttributeTarget"))
    ->publishHierarchy()
    ->end();
  return true;
}


const Attribute * AttributeTarget::getAttribute(const std::string & name)const{
  return getAttribute([&name](const Attribute * attribute){return attribute->getAttributeName()==name;});
}



void AttributeTarget::addAttribute(const Attribute * attribute){
  _Attributes.push_back(attribute);
}