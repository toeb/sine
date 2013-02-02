#include <core.testing.h>

#include <core/template/TemplateUtilities.h>

#include <sstream>
using namespace nspace;
using namespace std;
/*
UNITTEST(remove_const_from_instance1){
  const std::string str="asdasd";
  auto & result = remove_const_from_instance(str);

  bool success = !std::is_const<decltype(result)>::value && std::is_const<decltype(str)>::value;
  CHECK(success);

}


UNITTEST(remove_const_from_instance2){
  const std::string * str= new std::string;
  auto result = remove_const_from_instance(str);

  bool success = !std::is_const<decltype(result)>::value && std::is_const<decltype(str)>::value;
  CHECK(success);

}

*/
UNITTEST(CheckSingleton1){
  struct A{

  };
  auto isSingleton = is_singleton<A>::value;
  CHECK(!isSingleton);
}
UNITTEST(CheckSingleton2){
  struct A{
    SINGLETON(A){}
  };

  auto isSingleton = is_singleton<A>::value;
  CHECK(isSingleton);

};
TEST(1,default_constructor){
  struct A{ };
  default_constructor<A> constructor;
  auto  instance = constructor();
  CHECK(instance !=0);
}
TEST(2,default_constructor){
  static bool called = false;
  struct A{
    SINGLETON(A){
      called = true;
    }
  };
  CHECK(!called);
  default_constructor<A> constructor;
  auto  instance = constructor();  
  CHECK(instance!=0);
}
TEST(3,default_constructor){
  struct A{
    A(int i){}//no default constructor available
  };

  default_constructor<A> constructor;
  auto instance = constructor();
  CHECK(instance==0);
}

/*


UNITTEST(toString1){
  // Object::toString method overwritten by A str should contain "toString method was called"
  struct A : public Object{
    void toString(std::ostream & out)const{
      out << "toString method was called";
    }
  }a;
  auto str = nspace::toString(a);
  CHECK_EQUAL("toString method was called", str);
}
UNITTEST(toString2){
  // toString method exists str should correctly contain "hallo"
  struct A{
    void toString(std::ostream & out)const{
      out << "hallo";
    }
  }a;
  auto str = nspace::toString(a);
  CHECK_EQUAL("hallo", str);
}
UNITTEST(toString3){
  //toString method does not exist
  // str should be an empty string
  struct A{

  }a;
  auto str= nspace::toString(a);
  CHECK_EQUAL("",str);
}
UNITTEST(toString4){
  //toString method does not exist
  // result should be false
  struct A{

  }a;

  stringstream stream;
  auto result = nspace::toString(a,stream);
  CHECK(!result);
}
UNITTEST(toString5){
  // tostring method exists
  struct A{
    void toString(std::ostream & out)const{
      
    }
  }a;
  stringstream stream;
  // result should be true
  auto result = nspace::toString(a,stream);
  CHECK(result);
}
*/