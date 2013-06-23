#include <core.testing.h>

#include <core.reflection/namespace/NamespaceInfo.h>
using namespace ds;

class MyTestClass{
  reflect_type(::MyTestClass);
};


UNITTEST(GlobalNamespaceRegistration){
  auto resultType = type_of<MyTestClass>();
  auto result = Type::Global()->findChild("MyTestClass");
  CHECK(result);
  CHECK_EQUAL(resultType, result );
}

UNITTEST(findMyTestClass1){
  auto resultType = type_of<MyTestClass>();
  auto result = Type::Global()->findChild("::MyTestClass");
  CHECK(result);
  CHECK_EQUAL(resultType,result);
}
UNITTEST(NamespaceConstruction1){
  struct Derived : public NamespaceInfo {
    Derived():NamespaceInfo("testnamespace"){
    
    }
  }uut;
  CHECK_EQUAL("testnamespace",uut.getName());
  CHECK_EQUAL("::testnamespace::",uut.getFullyQualifiedName());
  CHECK_EQUAL(NamespaceInfo::Global(),uut.getParentNamespace());
  
  CHECK(contains(NamespaceInfo::Global()->Namespaces(),&uut));
}

UNITTEST(NamespaceConstruction2){  
  auto glob = NamespaceInfo::Global();


  struct Derived1 : public NamespaceInfo{
    Derived1():NamespaceInfo("::test1"){

    }
    
  };
  Derived1 uut1;
  struct Derived2 : public NamespaceInfo{
    Derived2(const NamespaceInfo * parent):NamespaceInfo("::test1::test2"){

    }
  }
  uut2(&uut1);
  CHECK_EQUAL("test2",uut2.getName());
  CHECK_EQUAL("::test1::test2::",uut2.getFullyQualifiedName());
  CHECK_EQUAL(&uut1,uut2.getParentNamespace());
  CHECK(contains(uut1.Namespaces(),&uut2));
  CHECK(!contains(NamespaceInfo::Global()->Namespaces(),&uut2));


}