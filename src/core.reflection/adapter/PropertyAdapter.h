#pragma once
#include <core.reflection/member/property/PropertyInfo.h>
#include <core.reflection/value/IModifiableValue.h>
#include <core.serialization/ISerializable.h>
#include <core.reflection/adapter/MemberAdapter.h>

namespace nspace{
  class PropertyAdapter:
    public IModifiableValue,
    public MemberAdapter
  {
    reflect_type(PropertyAdapter);

    typedef const PropertyInfo * extensible_property(PropertyInfo);
    auto before_set(PropertyInfo){
      onBeforePropertyInfoChanged();
      return true;
    }
    auto after_set(PropertyInfo){
      onPropertyInfoChanged();
    }

  public:
    //TODO use factorymethods instead.  i hate constructors
    PropertyAdapter();
    PropertyAdapter(Argument object, const std::string & name);
    PropertyAdapter(Argument object, const PropertyInfo * info);
    ~PropertyAdapter();
    // implementation of IModifiableValue
    Argument retrieveValue()const override final;
    bool storeValue(Argument value)override final;

    // implementation of ISerializable
    //bool toStream(std::ostream & stream, Format format);
    //bool fromStream(std::istream & stream, Format format);
  protected:
    void onChange(Observable * sender);
    void onOwnerChanged();
    void onBeforeOwnerChanged();
  private:
    void onBeforePropertyInfoChanged();
    void onPropertyInfoChanged();
  };
}