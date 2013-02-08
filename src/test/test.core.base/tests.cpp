/**
 * \file  src\test\core.base\tests.cpp
 *
 * \brief Contains basic tests that are written in pure c++ (because testing framework uses core).
 */
#include <core/Object.h>
#include <core/PropertyChangingObject.h>


#include <core.reflection.h>


bool objectInstanciation(){
  // test just checks object instanciation (this is rather a compile test)
 using namespace nspace;
  Object o;
  return true;
}

bool objectType(){
  // checks wether the correct typename is returned
  using namespace nspace;
  Object o;

  auto type = o.getType();
  if(!type)return false;
  
  auto name = type->getName();
  if(name!="Object")return false;

  return true;
}


#define DS_PROPERTY_MAKE_REFLECTABLE(NAME)                                                                             \
private:                           \
  typedef CurrentClassType NAME##OwningClassType;\
  class PROPERTYCLASS(NAME) : public virtual nspace::TypedProperty<NAME##OwningClassType,DS_PROPERTY_TYPE_NAME(NAME)>{ \
public:                                                                                                           \
    SINGLETON( PROPERTYCLASS(NAME) ){                                                                             \
      setPropertyType(typeof(DS_PROPERTY_TYPE_NAME(NAME)));                                                        \
      setName(# NAME);                                                                                            \
      setHasGetter(true);                                                                                         \
      setHasSetter(true);                                                                                         \
    }                                                                                                             \
    void setTypedValue(NAME##OwningClassType *  object, DS_PROPERTY_TYPE_NAME(NAME) value) const {                     \
      object->DS_PROPERTY_SETTER_NAME(NAME) (value);                                                               \
    }                                                                                                             \
    DS_PROPERTY_TYPE_NAME(NAME) getTypedValue(const NAME##OwningClassType *  object) const {                           \
      return object->DS_PROPERTY_GETTER_NAME(NAME) ();                                                            \
    }                                                                                                             \
  };                                                                                                              \
private:                                                                                                          \
  DS_INITIALIZER_STATIC(NAME ## Property)                                                                         \
  {                                                                                                               \
    auto type = const_cast<nspace::Type*>(static_cast<ConstTypePtr>(typeof(NAME##OwningClassType)));                                              \
    type->Members()|=PROPERTYCLASSINSTANCE(NAME);                                                                 \
  }







namespace nspace{
  struct ReflectionTest1;
  struct ReflectionTest1 :public Object{
    DS_CURRENT_CLASS(ReflectionTest1);
  //REFLECTABLE_OBJECT(ReflectionTest1);

    int basic_property(Value1);
    DS_PROPERTY_MAKE_REFLECTABLE(Value1);

  //PROPERTY(int , Value1){};

};
}
bool testReflection(){
  using namespace nspace;
  ReflectionTest1 t;
  auto type = typeof(ReflectionTest1);
  auto members = type->Members();
  auto prop = type->getProperty("Value1");
  t.setValue1(42);
  auto p =prop->get<int>(t);

  return true;
}




int main(){
  if(!objectInstanciation())return -1;
  if(!objectType())return -1;
  if(!testReflection())return -1;
  return 0;
}