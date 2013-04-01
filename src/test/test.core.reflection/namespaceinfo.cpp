#include <core.testing.h>

#include <core.reflection/namespace/NamespaceInfo.h>
using namespace ds;

template<typename TContainer, typename T>
bool contains(const TContainer & c, const T & val){
  return std::find(std::begin(c),std::end(c),val)!= std::end(c);
}
template<typename TContainer, typename T>
bool contains(const TContainer & c,const std::function<bool(const T &) > & pred){
  for(auto i : c){
    if(pred(i))return true;

  }
  return false;
}

UNITTEST(ScopeConstruction){


  struct MyScopeInfo: public ScopeInfo{
    MyScopeInfo():ScopeInfo("::testscope",Global()){}
  };
  MyScopeInfo * tmp;
  {

  MyScopeInfo   myScope;
  auto glob = ScopeInfo::Global();
  tmp = &myScope;
  CHECK_EQUAL("testscope",myScope.getName());
  CHECK_EQUAL("::testscope::",myScope.getFullyQualifiedName());
  CHECK_EQUAL(ScopeInfo::Global(), myScope.getScope());
  CHECK(contains(ScopeInfo::Global()->ChildScopes(),tmp));
  }
  CHECK(!contains(ScopeInfo::Global()->ChildScopes(),tmp));

}

UNITTEST(NamespaceConstruction1){
  struct Derived : public NamespaceInfo {
    Derived():NamespaceInfo("testnamespace"){
    
    }
  }uut;
  CHECK_EQUAL("testnamespace",uut.getName());

  CHECK_EQUAL("::default::testnamespace::",uut.getFullyQualifiedName());
  CHECK_EQUAL(NamespaceInfo::Default(),uut.getParentNamespace());
  
  CHECK(contains(NamespaceInfo::Global()->Namespaces(), &uut));
}

UNITTEST(NamespaceConstruction3){
  struct Derived : public NamespaceInfo {
    Derived():NamespaceInfo("::testnamespace"){

    }
  }uut;
  CHECK_EQUAL("testnamespace",uut.getName());

  CHECK_EQUAL("::testnamespace::",uut.getFullyQualifiedName());
  CHECK_EQUAL(NamespaceInfo::Global(),uut.getParentNamespace());

  CHECK(contains(NamespaceInfo::Global()->Namespaces(), &uut));
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
  CHECK(contains(uut1.Namespaces(),&uut2));
  CHECK(!contains(NamespaceInfo::Global()->Namespaces(), &uut2));


}

UNITTEST(getSpecificNamespace1){
  static auto global = NamespaceInfo::Global();

  struct Derived1: public NamespaceInfo{
    Derived1():NamespaceInfo("ns1", global){}
    ~Derived1(){}
  }uut1;
  struct Derived2:public NamespaceInfo{
    Derived2(const NamespaceInfo & parent):NamespaceInfo("ns2",&parent){}
    ~Derived2(){}    

  }uut2(uut1);

  auto found = global->getNamespace("ns1::ns2");
  CHECK_EQUAL(&uut2,found);
  found = global->getNamespace("ns1");
  CHECK_EQUAL(&uut1,found);
  auto notfound = global->getNamespace("somenamespacename::that::does::not::exist::really");
  CHECK_EQUAL(0,notfound);
}