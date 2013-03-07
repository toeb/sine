#pragma once
#include <core.reflection/member/property/PropertyInfo.h>
#include <core.reflection/value/IModifiableValue.h>
#include <core.serialization/ISerializable.h>
#include <core.reflection/adapter/MemberAdapter.h>

namespace nspace{
  class PropertyAdapter:
    public virtual IModifiableValue,
    public virtual ISerializeable,
    public virtual MemberAdapter,
    public virtual ObjectObserver
  {
    TYPED_OBJECT(PropertyAdapter);
    BASIC_PROPERTY(const PropertyInfo *, PropertyInfo,public,,onBeforePropertyInfoChanged();,onPropertyInfoChanged(););
  public:
    //TODO use factorymethods instead.  i hate constructors
    PropertyAdapter();
    PropertyAdapter(Argument object, const std::string & name);
    PropertyAdapter(Argument object, const PropertyInfo * info);
    ~PropertyAdapter();
    void setToDefault();
    // implementation of IModifiableValue
    bool retrieveValue(void * value)const;
    bool storeValue(const void * value);
    // implementation of ISerializable
    bool toStream(std::ostream & stream, Format format);
    bool fromStream(std::istream & stream, Format format);
  protected:
    void onChange(Observable * sender);
    void onOwnerChanged();
    void onBeforeOwnerChanged();
  private:
    void onBeforePropertyInfoChanged();
    void onPropertyInfoChanged();
  };
}