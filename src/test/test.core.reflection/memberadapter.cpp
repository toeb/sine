#include <core.testing.h>

#include <core.reflection/member/MemberInfo.h>

using namespace nspace;
UNITTEST(ConstructionString){
  struct Derived : public MemberInfo{
    Derived():MemberInfo("test"){
    
    }
  }uut;  
  CHECK_EQUAL("test",uut.getName());
}


UNITTEST(ConstructionDefault){
  struct Derived : public MemberInfo{
    Derived():MemberInfo(){
    
    }
  }uut;  
  CHECK_EQUAL("",uut.getName());
  CHECK_EQUAL(0,uut.getOwningType());
  
}