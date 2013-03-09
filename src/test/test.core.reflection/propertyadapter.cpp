#include <core.testing.h>

#include <core.reflection.h>

#include <core.reflection/adapter/PropertyAdapter.h>

using namespace nspace;

TEST(1, PropertyAdapter){
  struct A{
    reflect_type(A);

    typedef int reflect_property(IntProperty);
  }a;

  PropertyAdapter adapter(a,"IntProperty");
  auto valueType = adapter.getValueType();
  CHECK_EQUAL(typeof(int),valueType);


}
