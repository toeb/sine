#pragma once
#include <core/Object.h>
namespace nspace{
class Property : public virtual Object{
    TYPED_OBJECT(Property);
  private:
    std::string _propertyName;    
    bool _hasReadonlyReference;
    bool _hasMutableReference;
    bool _hasGetter;
    bool _hasSetter;
  protected:
    void setPropertyName(const std::string & propertyName){_propertyName = propertyName;}
    
  public:


    const std::string & propertyName()const{return _propertyName;}    
  

    virtual void setValue(void * object, const void * value)const=0;
    virtual void getValue(const void * object, void * value)const=0;  

    template<typename ObjectType, typename T>
    void get(T& value, const ObjectType & object)const{
      getValue(&object,&value);
    }
    template<typename ObjectType, typename T>
    void set(const T& value, ObjectType & object)const{
      setValue(&object,&value);
    }    
  };
}