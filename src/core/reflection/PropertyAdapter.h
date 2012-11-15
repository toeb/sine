#pragma once
#include <core/reflection/PropertyInfo.h>
#include <core/reflection/IModifiableValue.h>
#include <core/reflection/ISerializable.h>
#include <core/reflection/MemberAdapter.h>

namespace nspace{
  class PropertyAdapter:
    public virtual IModifiableValue, 
    public virtual ISerializeable, 
    public virtual MemberAdapter
  {
    TYPED_OBJECT(PropertyAdapter);
    SIMPLE_PROPERTY(const PropertyInfo *, PropertyInfo);
  public:
    //TODO use factorymethod
    PropertyAdapter();
    PropertyAdapter(Object * object, const std::string & name);
    PropertyAdapter(Object * object, const PropertyInfo * info);
    void setToDefault();
    // implementation of IModifiableValue
    bool retrieveValue(void * value)const;
    bool storeValue(const void * value);
    // implementation of ISerializable
    bool toStream(std::ostream & stream, Format format);
    bool fromStream(std::istream & stream, Format format);
  };


}