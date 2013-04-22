#pragma once

#include <core.property.h>



namespace nspace{
  class Attribute{
    //DS_CLASS(Attribute);
    typedef std::string basic_property(AttributeName);
  public:
    virtual ~Attribute(){}
  };

  class AttributeTarget {
    //reflect_type(AttributeTarget);
  public:
    propdef std::vector<const Attribute*> basic_property(Attributes);
    property_reference(Attributes);


    const Attribute * getAttribute(const std::string & name)const{
      return getAttribute([&name](const Attribute * attribute){return attribute->getAttributeName()==name;});
    }
    template<typename TAttribute>
    const TAttribute * getAttribute()const{
      return static_cast<const TAttribute*>( getAttribute([](const Attribute * attribute){return dynamic_cast<const TAttribute*>(attribute);}));
    }

    template<typename Predicate>
    const Attribute * getAttribute(Predicate predicate)const{
      auto iterator = std::find_if(std::begin(Attributes()),std::end(Attributes()), predicate);
      if(iterator!=std::end(Attributes()))return *iterator;
      return 0;
    }



    void addAttribute(const Attribute * attribute){
      _Attributes.push_back(attribute);
    }

  };



}




#define DS_REFLECTION_ATTRIBUTE_CLASS_NAME(LINE) DS_CONCAT(Attribute,LINE)

#define _DS_REFLECTION_ATTRIBUTE(ATTRIBUTE_TYPE,TARGET_ACCESS, LINE,INITIALIZATION)             \
typedef CurrentClassType DS_CONCAT(DS_REFLECTION_ATTRIBUTE_CLASS_NAME(LINE),OwningType);        \
class DS_REFLECTION_ATTRIBUTE_CLASS_NAME(LINE):public ATTRIBUTE_TYPE{                           \
public:                                                                                         \
  DS_REFLECTION_ATTRIBUTE_CLASS_NAME(LINE)(){                                                   \
    {INITIALIZATION;}                                                                           \
    auto type = typeof(DS_CONCAT(DS_REFLECTION_ATTRIBUTE_CLASS_NAME(LINE),OwningType));         \
    auto target = TARGET_ACCESS;                                                                \
    target->addAttribute(this);                                                                 \
  }                                                                                             \
}DS_CONCAT(__instance,DS_REFLECTION_ATTRIBUTE_CLASS_NAME(LINE));

#define DS_REFLECTION_ATTRIBUTE(ATTRIBUTE,TARGET_ACCESS,...) _DS_REFLECTION_ATTRIBUTE(ATTRIBUTE,TARGET_ACCESS,__LINE__,DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__))

#define DS_REFLECTION_MEMBER_ATTRIBUTE(TARGET,ATTRIBUTE_TYPE,...) DS_REFLECTION_ATTRIBUTE(ATTRIBUTE_TYPE, const_cast<nspace::MemberInfo*>(type->getMember(#TARGET));,__VA_ARGS__)
#define DS_REFLECTION_TYPE_ATTRIBUTE(ATTRIBUTE_TYPE, ...) DS_REFLECTION_ATTRIBUTE(ATTRIBUTE_TYPE, const_cast<nspace::Type*>(type),__VA_ARGS__);

#define reflect_member_attribute(TARGET,ATTRIBUTE_TYPE,...) DS_REFLECTION_MEMBER_ATTRIBUTE(TARGET,ATTRIBUTE_TYPE,__VA_ARGS__)
#define reflect_type_attribute(ATTRIBUTE_TYPE, ...) DS_REFLECTION_TYPE_ATTRIBUTE(ATTRIBUTE_TYPE,__VA_ARGS__)