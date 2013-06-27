#include <core.testing.h>

UNITTEST(FluentChainerConstructionDestruction){
  class Subtype : public FluentChainer<Subtype>{
  public:
    Subtype():FluentChainer<Subtype>(*this){

    }
    ~Subtype(){
    }
  };
  {
    Subtype().derived()->derived()->derived();
  }
}




UNITTEST(BuilderValid){
  using namespace nspace::core::reflection;
  struct Uut : public Builder<Uut, int>{
    Uut():Builder(*this){}
  }uut;      
  CHECK(!uut.isValid());
}
UNITTEST(BuilderInstanciate){
  using namespace nspace::core::reflection;
  struct Uut : public Builder<Uut,int>{
    Uut():Builder(*this){}
  }uut;      
  uut.begin();
  CHECK(uut.isValid());
}
UNITTEST(BuilderExtensionPointOnBeforeEnd){
  using namespace nspace::core::reflection;
  static bool called = false;
  struct Uut : public Builder<Uut, int>{
    Uut():Builder(*this){}
    void onBeforeEnd()override{
      called = true;
    }
  }uut;      
  uut.end();
  CHECK(called);
}


