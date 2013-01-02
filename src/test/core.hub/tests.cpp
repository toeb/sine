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
  TYPED_OBJECT(TestModule);
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
  //CompositeHubObject * o = &obj;
  auto o1 = new Object;
  auto o2 = new Object;

  obj.Components()|=o1;
  obj.Components()|=o2;
  Hub hub;
  hub |= &obj;

  CHECK(hub.size()==3);
  CHECK(obj.Components().size()==2);
  CHECK(hub.contains(o1));
  CHECK(hub.contains(o2));
  CHECK(hub.contains(&obj)); 


}

TEST(compositeAdd2, CompositeHubObject){
  CompositeHubObject obj;
  //CompositeHubObject * o = &obj;
  auto o1 = new Object;
  auto o2 = new Object;

  obj.Components()|=o1;
  Hub hub;
  hub |= &obj;
  
  CHECK(hub.size()==2);
  
  obj.Components()|=o2;

  CHECK(hub.size()==3);
  CHECK(obj.Components().size()==2);
  CHECK(hub.contains(o1));
  CHECK(hub.contains(o2));
  CHECK(hub.contains(&obj)); 


}

TEST(compositeRemove1, CompositeHubObject){
  CompositeHubObject obj;
  //CompositeHubObject * o = &obj;
  auto o1 = new Object;
  auto o2 = new Object;

  obj.Components()|=o1;
  Hub hub;
  hub |= &obj;
  obj.Components()|=o2;

  obj.Components()/=o2;

  CHECK(hub.size()==2);
  CHECK(obj.Components().size()==1);
  CHECK(hub.contains(o1));
  CHECK(!hub.contains(o2));
  CHECK(hub.contains(&obj)); 
}



TEST(compositeAdd3, CompositeHubObject){
  CompositeHubObject obj;
  //CompositeHubObject * o = &obj;
  auto o1 = new Object;
  auto o2 = new Object;

  obj.Components()|=o1;
  Hub hub;
  hub |= o1;
  hub |= &obj;
  obj.Components()|=o2;


  CHECK(hub.size()==3);
  CHECK(obj.Components().size()==2);
  CHECK(hub.contains(o1));
  CHECK(hub.contains(o2));
  CHECK(hub.contains(&obj)); 
}

TEST(compositeRemove3, CompositeHubObject){
  CompositeHubObject obj;
  //CompositeHubObject * o = &obj;
  auto o1 = new Object;
  auto o2 = new Object;

  obj.Components()|=o1;
  Hub hub;
  hub |= o1;
  hub |= &obj;
  obj.Components()|=o2;

  hub /= &obj;

  CHECK(hub.size()==0);
  CHECK(obj.Components().size()==2);
  CHECK(obj.Components().contains(o1));
  CHECK(obj.Components().contains(o2));
  CHECK(!hub.contains(&obj)); 
}

TEST(HubGraph , Hub){
  Hub uut;
  CompositeHubObject n1;
  CompositeHubObject n2;
  Object n3;
  Object n4;


  uut |= &n1;
  n1.Components() |= &n2;
  n2.Components() |= &n3;
  n1.Components() |= &n4;
  
  Set<Object *> order;

  uut.dfs([&order](DataNode<Object* > * node){
    order |= node->data();
  });
  
  CHECK(order.at(0) == & uut);
  CHECK(order.at(1) == & n1);
  CHECK(order.at(2) == & n2);
  CHECK(order.at(3) == & n3);
  CHECK(order.at(4) == & n4);


  
}
class A : public virtual CompositeHubObject{

};

TEST(compositeBoxedAdd, CompositeHubObject){
  CompositeHubObject a;
  A b;
  A c;
  Object o;

  Hub h;

  a.Components()|=&b;
  b.Components()|=&c;
  c.Components()|=&o;
  h|=&a;

  CHECK(h.size()==4);
}



