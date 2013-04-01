#include <core.testing.h>

#include <core.reflection/namespace/NamespaceInfo.h>
using namespace ds;



UNITTEST(NamespaceConstruction1){
  struct Derived : public NamespaceInfo {
    Derived():NamespaceInfo("testnamespace"){
    
    }
  }uut;
  CHECK_EQUAL("testnamespace",uut.getName());

  CHECK_EQUAL("testnamespace",uut.getFullyQualifiedName());
  CHECK_EQUAL(0,uut.getParentNamespace());
  
  CHECK(!contains(NamespaceInfo::Global()->Namespaces(), &uut));
}

UNITTEST(NamespaceConstruction2){
  struct Derived : public NamespaceInfo {
    Derived():NamespaceInfo("testnamespace"){
      setScope(Global());
    }
  }uut;
  CHECK_EQUAL("testnamespace",uut.getName());

  CHECK_EQUAL("::testnamespace",uut.getFullyQualifiedName());
  CHECK_EQUAL(NamespaceInfo::Global(),uut.getParentNamespace());

  CHECK(contains(NamespaceInfo::Global()->Namespaces(), &uut));
}

UNITTEST(NamespaceConstruction3){
  struct Derived1 : public NamespaceInfo{
    Derived1():NamespaceInfo("test1"){
      setScope(Global());
    }
    
  };

  struct Derived2 : public NamespaceInfo{
    Derived2(NamespaceInfo * ns):NamespaceInfo("test2"){
      setScope(ns);
    }
  };
  Derived1 uut1;
  Derived2 uut2(&uut1);


  auto glob = NamespaceInfo::Global();
  CHECK_EQUAL("test2",uut2.getName());
  CHECK_EQUAL("::test1::test2",uut2.getFullyQualifiedName());
  CHECK_EQUAL(&uut1,uut2.getParentNamespace());
  CHECK(contains(uut1.Namespaces(),&uut2));
  CHECK(!contains(NamespaceInfo::Global()->Namespaces(), &uut2));


}

UNITTEST(getSpecificNamespace1){
  static auto global = NamespaceInfo::Global();

  struct Derived1: public NamespaceInfo{
    Derived1():NamespaceInfo("ns1"){setScope(NamespaceInfo::Global());}
    ~Derived1(){}
  }uut1;
  struct Derived2:public NamespaceInfo{
    Derived2(const NamespaceInfo & parent):NamespaceInfo("ns2"){setScope(&parent);}
    ~Derived2(){}    

  }uut2(uut1);

  auto found = global->getNamespace("ns1::ns2");
  CHECK_EQUAL(&uut2,found);
  found = global->getNamespace("ns1");
  CHECK_EQUAL(&uut1,found);
  auto notfound = global->getNamespace("somenamespacename::that::does::not::exist::really");
  CHECK_EQUAL(0,notfound);
}