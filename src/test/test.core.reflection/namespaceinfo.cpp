#include <core.testing.h>

#include <core.reflection/namespace/NamespaceInfo.h>
using namespace ds;
UNITTEST(NamespaceConstruction1){
  struct Derived : public NamespaceInfo {
    Derived():NamespaceInfo("testnamespace"){
    
    }
  }uut;
  CHECK_EQUAL("testnamespace",uut.getName());
  CHECK_EQUAL("::testnamespace::",uut.getFullyQualifiedName());
  CHECK_EQUAL(NamespaceInfo::Global(),uut.getParentNamespace());
  CHECK(NamespaceInfo::Global()->getNamespaces().contains(&uut));
}

UNITTEST(NamespaceConstruction2){
  struct Derived1 : public NamespaceInfo{
    Derived1():NamespaceInfo("test1",Global()){

    }
    
  };
  static Derived1 uut1;
  struct Derived2 : public NamespaceInfo{
    Derived2():NamespaceInfo("test2",&uut1){

    }
  }uut2;
  auto glob = NamespaceInfo::Global();
  CHECK_EQUAL("test2",uut2.getName());
  CHECK_EQUAL("::test1::test2::",uut2.getFullyQualifiedName());
  CHECK_EQUAL(&uut1,uut2.getParentNamespace());
  CHECK(uut1.getNamespaces().contains(&uut2));
  CHECK(!NamespaceInfo::Global()->getNamespaces().contains(&uut2));


}