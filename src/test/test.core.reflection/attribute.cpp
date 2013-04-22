#include <core.testing.h>

#include <core.reflection.h>

namespace nspace{
  class DisplayAttribute : public Attribute{
    reflect_type(DisplayAttribute);

    propdef std::string reflect_property(Name);
    propdef std::string reflect_property(Description);
    propdef std::string reflect_property(GroupName);
  };
  class TableAttribute : public Attribute{
    reflect_type(TableAttribute);

    propdef std::string reflect_property(TableName);
  };
}


namespace testNamespace{
  class TestClass{
    reflect_type(TestClass);
    reflect_type_attribute(nspace::TableAttribute, setTableName("Some Table Name"));

    propdef int reflect_property(IntValue);
    reflect_member_attribute(IntValue, nspace::DisplayAttribute, setName("Int Value Display Name"));
        
    propdef std::string reflect_property(StringValue);
    reflect_member_attribute(StringValue,nspace::DisplayAttribute, setName("String Value Display Name"));   
    

  }a;
}



UNITTEST(MemberAttribute1){
  auto type = typeof(testNamespace::TestClass);
  auto prop1 = type->getMember("IntValue");
  auto attrs = prop1->getAttributes();
  CHECK_EQUAL(1,attrs.size());
  auto attr = dynamic_cast<const nspace::DisplayAttribute*>(attrs[0]);
  CHECK(attr);
  CHECK_EQUAL("Int Value Display Name", attr->getName());
}
UNITTEST(ClassAttribute1){
  auto type = typeof(testNamespace::TestClass);
  auto attr = type->getAttribute<nspace::TableAttribute>();
  CHECK(attr);
  CHECK_EQUAL("Some Table Name",attr->getTableName());

}

