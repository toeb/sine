#include <CppUnitLite/TestHarness.h>

#include <core.hub/Hub.h>
#include <core.hub/ModuleBase.h>
#include <core.hub/HubObject.h>
#include <core.hub/CompositeHubObject.h>
using namespace nspace;
TEST(Create1, Hub){
  Hub hub;
  CHECK(hub.modules().size()==0);
  CHECK(hub.size()==0);
}


TEST(Announce1, Hub){
  Hub hub;
  auto object = new Object();
  hub.announce(object);
  CHECK(hub.size()==1);
  CHECK(hub.first()==object);

}

TEST(AnnounceNull, Hub){
  
  Hub hub;
  auto object = (Object*)0;
  hub.announce(object);
  CHECK(hub.size()==0);
}
TEST(Announce3, Hub){
  Hub hub;
  auto object = new Object();
  hub |= object;
  CHECK(hub.size()==1);
  CHECK(hub.first()==object);
}


TEST(AnnounceMultiple, Hub){
  Hub hub;
  
  hub |= new Object();
  hub |= new Object();
  hub |= new Object();
  hub |= new Object();

  CHECK(hub.size()==4);

}
TEST(AnnounceSame, Hub){
  Hub hub;
  auto o = new Object();
  hub |= o;
  hub |= o;
  hub |= o;
  hub |= o;

  CHECK(hub.size()==1);

}

TEST(renounce1, Hub){
  Hub hub;
  auto o = new Object();
  hub |= o;
  hub.renounce(o);
  CHECK(hub.size()==0);

}
TEST(renounce2, Hub){
  Hub hub;
  auto o = new Object();
  hub |= new Object();
  hub |= o;
  hub |= new Object();
  hub.renounce(o);
  CHECK(hub.size()==2);

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
  CHECK(uut.hubs().size()==0);
  hub |= &uut;
  CHECK(uut.hubs().first()==&hub)
  
}
TEST(renounce,HubObject){
  TestModule uut;
  Hub hub;
  hub |= &uut;
  hub.renounce(&uut);
  CHECK(uut.hubs().size()==0);  
}

TEST(announce,Module){
  TestModule uut;
  Hub hub;
  hub |=& uut;
  
  CHECK(uut.objects().size()==0);  
  CHECK(hub.first()==&uut);
}

TEST(announce2,Module){
  TestModule uut;
  Hub hub;
  hub |= &uut;
  hub |= new Object();
  CHECK(uut.objects().size()==1);  
  CHECK(hub.first()==&uut);
}

TEST(renounce,Module){
  TestModule uut;
  Hub hub;
  hub |= &uut;
  Object * obj = new Object();
  hub |= obj;
  hub.renounce(obj);
  CHECK(uut.objects().size()==0);  
  CHECK(hub.first()==&uut);
}

TEST(compositeAdd1, CompositeHubObject){
  CompositeHubObject obj;
  CompositeHubObject * o = &obj;
  auto o1 = new Object;
  auto o2 = new Object;

  obj.components()|=o1;
  obj.components()|=o2;
  Hub hub;
  hub |= &obj;

  CHECK(hub.size()==3);
  CHECK(obj.components().size()==2);
  CHECK(hub.contains(o1));
  CHECK(hub.contains(o2));
  CHECK(hub.contains(&obj)); 


}

TEST(compositeAdd2, CompositeHubObject){
  CompositeHubObject obj;
  CompositeHubObject * o = &obj;
  auto o1 = new Object;
  auto o2 = new Object;

  obj.components()|=o1;
  Hub hub;
  hub |= &obj;
  
  CHECK(hub.size()==2);
  
  obj.components()|=o2;

  CHECK(hub.size()==3);
  CHECK(obj.components().size()==2);
  CHECK(hub.contains(o1));
  CHECK(hub.contains(o2));
  CHECK(hub.contains(&obj)); 


}

TEST(compositeRemove1, CompositeHubObject){
  CompositeHubObject obj;
  CompositeHubObject * o = &obj;
  auto o1 = new Object;
  auto o2 = new Object;

  obj.components()|=o1;
  Hub hub;
  hub |= &obj;
  obj.components()|=o2;

  obj.components()/=o2;

  CHECK(hub.size()==2);
  CHECK(obj.components().size()==1);
  CHECK(hub.contains(o1));
  CHECK(!hub.contains(o2));
  CHECK(hub.contains(&obj)); 
}



TEST(compositeAdd3, CompositeHubObject){
  CompositeHubObject obj;
  CompositeHubObject * o = &obj;
  auto o1 = new Object;
  auto o2 = new Object;

  obj.components()|=o1;
  Hub hub;
  hub |= o1;
  hub |= &obj;
  obj.components()|=o2;


  CHECK(hub.size()==3);
  CHECK(obj.components().size()==2);
  CHECK(hub.contains(o1));
  CHECK(hub.contains(o2));
  CHECK(hub.contains(&obj)); 
}

TEST(compositeRemove3, CompositeHubObject){
  CompositeHubObject obj;
  CompositeHubObject * o = &obj;
  auto o1 = new Object;
  auto o2 = new Object;

  obj.components()|=o1;
  Hub hub;
  hub |= o1;
  hub |= &obj;
  obj.components()|=o2;

  hub /= &obj;

  CHECK(hub.size()==0);
  CHECK(obj.components().size()==2);
  CHECK(obj.components().contains(o1));
  CHECK(obj.components().contains(o2));
  CHECK(!hub.contains(&obj)); 
}

TEST(deleteComposite1, CompositeHubObject){
  CompositeHubObject*  obj = new CompositeHubObject;
  auto o1 = new Object;
  auto o2 = new Object;

  obj->components()|=o1;
  obj->components()|=o2;
  Hub hub;
  hub |= o1;
  hub |= obj;

  delete obj;
  obj = 0;  
  CHECK(hub.size()==0);
  
}