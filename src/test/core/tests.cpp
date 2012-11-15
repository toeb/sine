#include <CppUnitLite/TestHarness.h>
#include <core/Object.h>
#include <core/NamedObject.h>
#include <core/DataNode.h>
#include <core/Graph.h>
#include "conversion.h"
#include <string>
#include <sstream>
#include <core.h>

using namespace nspace;
using namespace std;
namespace nspace{

  /*class SomeClass : public nspace::PropertyChangingObject{
  REFLECTABLE_OBJECT(SomeClass);
  PROPERTY(int, Val){};
  ACTION(SuperAction){cout << "val = "<<getVal()<<endl;};
};

class SomeDerivedClass : public SomeClass{
  REFLECTABLE_OBJECT(SomeDerivedClass);
  SUBCLASSOF(SomeClass);
  PROPERTY(std::string, SomeStringVar){};
  ACTION(TestAction){cout << "lololo"<<endl;}

};

int main(int argc,  char ** argv){  
  SomeDerivedClass c;
  c.setVal(234);
  cout << c.getPropertyValue<int>("Val")<<endl;

  c.setSomeStringVar("asdasd");
  cout << c.getSomeStringVar()<<endl;
  cout << c.getPropertyValue<std::string>("SomeStringVar")<<endl;
  
  c.getMethodAdapter("TestAction").call();
  c.getMethodAdapter("SuperAction").call();
}
*/
  

class TestClass  : public PropertyChangingObject{
  REFLECTABLE_OBJECT(TestClass);
public:
  TestClass():_IntegerValue(0){}
  PROPERTY(int, IntegerValue){}
  PROPERTY(std::string, StringValue){}
  ACTION(PrintALineOfText){cout << "LOL"<<endl;}
};
void testvalueAndAction(){
  //todo... make a test out of this method
  TestClass theobject;
  PropertyAdapter prop1(&theobject,"IntegerValue");
  PropertyAdapter prop2(&theobject,"StringValue");
  MethodAdapter act1(&theobject, "PrintALineOfText");
  prop1.serialize(cout);
  cout <<endl;
  prop1.deserialize(cin);
  cout <<endl;
  prop1.serialize(cout);
  cout <<endl;

  prop2.serialize(cout);
  cout << endl;
  std::string str;
  cin >> str;
  stringstream sss(str);


  act1.execute();

  prop2.deserialize(sss);
  prop2.serialize(cout);
  cout << endl;
  

  int aNumber=3;
  auto value = new ReferenceValue<int>(aNumber);
  cout << value->get<int>()<<endl;
  value->set(5);

  cout << aNumber<<endl; 

  stringstream ss;
  ss << "54";

  value->deserialize(cin);

  cout << value->get<int>();

  value->serialize(cout);

}

class A {
  TYPED_OBJECT(A);
};
class B:public virtual A{
  TYPED_OBJECT(B);
  SUBCLASSOF(A);


};

class C:public virtual B{
  TYPED_OBJECT(C);
  SUBCLASSOF(B);

};
class D : public virtual A{
  TYPED_OBJECT(D);
  SUBCLASSOF(A);

};
class E {
  TYPED_OBJECT(E);

};
class F: public virtual E, public virtual C{
  TYPED_OBJECT(F);
  SUBCLASSOF(E);
  SUBCLASSOF(C);

};
}
TEST(instanceOf1, Object){
  
  A a;
  B b;
  C c;
  D d;
  E e;
  F f;
 CHECK(f.isInstanceOf(typeof(A)));
}

TEST(instanceOf2, Object){
  
  A a;
  B b;
  C c;
  D d;
  E e;
  F f;
 CHECK(f.isInstanceOf(typeof(E)));
}
TEST(instanceOf3, Object){
  
  A a;
  B b;
  C c;
  D d;
  E e;
  F f;
 CHECK(!e.isInstanceOf(typeof(A)));
}

TEST(Create, Object){
  Object o;
  CHECK(o.getType()==*typeof(Object));
  
}

TEST(Create1, NamedObject){
  NamedObject o;
  CHECK(o.name()==NamedObject::DefaultName);

}
TEST(Create2, NamedObject){
  NamedObject o("testname");
  CHECK(o.name()=="testname");

}


TEST(CreateNode,DataNode){
  DataNode<int> uut(2);
  CHECK(uut.data()==2);
}

TEST(CreateNode2,DataNode){
  DataNode<int> uut(2);
  uut = 9;
  CHECK(uut.data()==9);
}

TEST(CreateNode3,DataNode){
  DataNode<int> uut(2);
  uut = 9;
  int a = uut;
  CHECK(a==9);
}


TEST(Connect1,DataNode){
  DataNode<int> uut1(1);
  DataNode<int> uut2(2);
  uut1 << uut2;
  CHECK(uut1.predecessors().contains(&uut2));
  CHECK(uut2.successors().contains(&uut1));

}


TEST(DisConnect1,DataNode){
  DataNode<int> uut1(1);
  DataNode<int> uut2(2);
  uut1 << uut2;
  
  uut2.successors() /= &uut1;

  CHECK(!uut1.predecessors().contains(&uut2));
  CHECK(!uut2.successors().contains(&uut1));

}

TEST(DisConnect2,DataNode){
  DataNode<int> uut1(1);
  DataNode<int> uut2(2);
  uut1 << uut2;
  
  uut2.remove(&uut1);

  CHECK(!uut1.predecessors().contains(&uut2));
  CHECK(!uut2.successors().contains(&uut1));

}

TEST(DFS1,DataNode){
  DataNode<int> uut1 = 1;
  DataNode<int> uut2 = 2;
  DataNode<int> uut3 = 3;
  DataNode<int> uut4 = 4;
  DataNode<int> uut5 = 5;
  DataNode<int> uut6 = 6;
  DataNode<int> uut7 = 7;

  uut1 >> uut2;
  uut1 >> uut3;
  uut2 >> uut4;
  uut2 >> uut5;
  uut3 >> uut6;
  uut3 >> uut7;

  Set<DataNode<int> *> order;
  uut1.dfs([&order](bool & b, DataNode<int> * node){
    order|=node;
  
  },[](Set<DataNode<int>* > & successors, const DataNode<int> & current){
    successors |= current.successors();
  });

  int current = 0;
  int actualorder []={1,2,4,5,3,6,7};
  
  order.foreachElement([&actualorder, &current,this,&result_](DataNode<int> * n){
    int cv = n->data();
    CHECK_EQUAL(actualorder[current++],cv);
  });

}


TEST(BFS1,DataNode){
  DataNode<int> uut1 = 1;
  DataNode<int> uut2 = 2;
  DataNode<int> uut3 = 3;
  DataNode<int> uut4 = 4;
  DataNode<int> uut5 = 5;
  DataNode<int> uut6 = 6;
  DataNode<int> uut7 = 7;

  uut1 >> uut2;
  uut1 >> uut3;
  uut2 >> uut4;
  uut2 >> uut5;
  uut3 >> uut6;
  uut3 >> uut7;

  Set<DataNode<int> *> order;
  uut1.bfs([&order](bool & b, DataNode<int> * node){
    order|=node;
  
  },[](Set<DataNode<int>* > & successors, const DataNode<int> & current){
    successors |= current.successors();
  });

  int current = 0;
  int actualorder []={1,2,3,4,5,6,7};
  
  order.foreachElement([&actualorder, &current,this,&result_](DataNode<int> * n){
    int cv = n->data();
    CHECK_EQUAL(actualorder[current++],cv);
  });

}
TEST(GraphCreate1, Graph){
  Graph<DataNode<int> > uut;
  

  DataNode<int> n1 = 1;
  DataNode<int> n2 = 2;
  DataNode<int> n3 = 3;
  DataNode<int> n4 = 4;
  DataNode<int> n5 = 5;
  DataNode<int> n6 = 6;
  DataNode<int> n7 = 7;

  uut.nodes() |= &n1;
  CHECK(uut.leaves().size()==1);
  n1 >> n2;
  n1 >> n3;
  n2 >> n4;
  n2 >> n5;
  n3 >> n6;
  n3 >> n7;
  
  CHECK_EQUAL(7U, uut.nodes().size());
  CHECK(uut.leaves().size()==4);
}
