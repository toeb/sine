#include <core.testing.h>

using namespace nspace;
UNITTEST(normalizeScopeName1){
  auto result = ScopeInfo::normalizeName("::a::b::c");
  CHECK_EQUAL("c",result);
}

UNITTEST(normalizeScopeName2){
  auto result = ScopeInfo::normalizeName("a");
  CHECK_EQUAL("a",result);

}
UNITTEST(normalizeScopeName3){
  auto result = ScopeInfo::normalizeName("d::e::");
  CHECK_EQUAL("e",result);
}

UNITTEST(normalizeScopeFullyQualifiedName1){
  auto result = ScopeInfo::normalizeFullyQualifiedName("e");
  CHECK_EQUAL("::e",result);
}

UNITTEST(normalizeScopeFullyQualifiedName2){
  auto result = ScopeInfo::normalizeFullyQualifiedName("::e");
  CHECK_EQUAL("::e",result);
}

UNITTEST(normalizeScopeFullyQualifiedName3){
  auto result = ScopeInfo::normalizeFullyQualifiedName("::e::");
  CHECK_EQUAL("::e",result);
}

UNITTEST(normalizeScopeFullyQualifiedName4){
  auto result = ScopeInfo::normalizeFullyQualifiedName("e::f");
  CHECK_EQUAL("::e::f",result);
}

UNITTEST(normalizeScopeFullyQualifiedName5){
  auto result = ScopeInfo::normalizeFullyQualifiedName("::e::f");
  CHECK_EQUAL("::e::f",result);
}

UNITTEST(normalizeScopeFullyQualifiedName6){
  auto result = ScopeInfo::normalizeFullyQualifiedName("::e::f::");
  CHECK_EQUAL("::e::f",result);
}



UNITTEST(ScopeConstruction){


  struct MyScopeInfo: public ScopeInfo{
    MyScopeInfo():ScopeInfo("::testscope"){
      setScope(ScopeInfo::Global());
    }
  };
  MyScopeInfo * tmp;
  {

    MyScopeInfo   myScope;
    auto glob = ScopeInfo::Global();
    tmp = &myScope;
    CHECK_EQUAL("testscope",myScope.getName());
    CHECK_EQUAL("::testscope",myScope.getFullyQualifiedName());
    CHECK_EQUAL(ScopeInfo::Global(), myScope.getScope());
    CHECK(contains(ScopeInfo::Global()->ChildScopes(),tmp));
  }
  CHECK(!contains(ScopeInfo::Global()->ChildScopes(),tmp));

}

UNITTEST(AutoScopeConstruction1){
  auto scope = ScopeInfo::requireScope("::scopeA");
  CHECK_EQUAL("scopeA",scope->getName());
  CHECK_EQUAL(ScopeInfo::Global(), scope->getScope());
  CHECK(contains(ScopeInfo::Global()->ChildScopes(),scope));

}
UNITTEST(AutoScopeConstruction2){
  auto scope = ScopeInfo::requireScope("::scopeA::scopeB");
  auto scopeA = ScopeInfo::findScope("::scopeA");
  CHECK(scopeA!=0);
  CHECK(scope!=0);
  CHECK_EQUAL(scope->getScope(),scopeA);
  CHECK_EQUAL(scopeA->getScope(),ScopeInfo::Global());
}

UNITTEST(AutoConstructionWithClassInHierarchyClass1){
  struct A : public Type{
    A():Type("AType"){setScope(ScopeInfo::requireScope("::nsA::nsB"));}
  }a;
  auto scopeA = ScopeInfo::findScope("::nsA");
  auto scopeB = ScopeInfo::findScope("::nsA::nsB");
  auto type = ScopeInfo::findScope("::nsA::nsB::AType");
  CHECK(scopeA!=0);
  CHECK(scopeB!=0);
  CHECK(type!=0);
  CHECK(type->getScope()==scopeB);
  CHECK_EQUAL(&a,type);
}

