#include <CppUnitLite/TestHarness.h>

#include <core.hub/Hub.h>
#include <core.hub/ModuleBase.h>
#include <core.hub/HubObject.h>
using namespace nspace;
TEST(Create1, Hub){
  Hub hub;
  CHECK(hub.modules().size()==0);
  CHECK(hub.objects().size()==0);
}


TEST(Announce1, Hub){
  Hub hub;
  auto object = new Object();
  hub.announce(object);
  CHECK(hub.objects().size()==1);
  CHECK(hub.objects().first()==object);

}

TEST(AnnounceNull, Hub){
  
  Hub hub;
  auto object = (Object*)0;
  hub.announce(object);
  CHECK(hub.objects().size()==0);
}
TEST(Announce3, Hub){
  Hub hub;
  auto object = new Object();
  hub << object;
  CHECK(hub.objects().size()==1);
  CHECK(hub.objects().first()==object);
}


TEST(AnnounceMultiple, Hub){
  Hub hub;
  
  hub << new Object();
  hub << new Object();
  hub << new Object();
  hub << new Object();

  CHECK(hub.objects().size()==4);

}
TEST(AnnounceSame, Hub){
  Hub hub;
  auto o = new Object();
  hub << o;
  hub << o;
  hub << o;
  hub << o;

  CHECK(hub.objects().size()==1);

}

TEST(renounce1, Hub){
  Hub hub;
  auto o = new Object();
  hub << o;
  hub.renounce(o);
  CHECK(hub.objects().size()==0);

}
TEST(renounce2, Hub){
  Hub hub;
  auto o = new Object();
  hub << new Object();
  hub << o;
  hub << new Object();
  hub.renounce(o);
  CHECK(hub.objects().size()==2);

}

class TestModule : public virtual ModuleBase, public virtual HubObject{
  TYPED_OBJECT;
protected:
  bool accept(Object * o){
    return true;
  }
};

TEST(announce,HubObject){
  TestModule uut;
  Hub hub;
  CHECK(uut.hub()==0);
  hub << uut;
  CHECK(uut.hub()==&hub)
  
}
TEST(renounce,HubObject){
  TestModule uut;
  Hub hub;
  hub << uut;
  hub.renounce(&uut);
  CHECK(uut.hub()==0);  
}

TEST(announce,Module){
  TestModule uut;
  Hub hub;
  hub << uut;
  
  CHECK(uut.objects().size()==1);  
  CHECK(uut.objects().first()==&uut);
}

TEST(announce2,Module){
  TestModule uut;
  Hub hub;
  hub << uut;
  hub << new Object();
  CHECK(uut.objects().size()==2);  
  CHECK(uut.objects().first()==&uut);
}

TEST(renounce,Module){
  TestModule uut;
  Hub hub;
  hub << uut;
  Object * obj = new Object();
  hub << obj;
  hub.renounce(obj);
  CHECK(uut.objects().size()==1);  
  CHECK(uut.objects().first()==&uut);
}

