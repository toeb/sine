#include <core.testing.h>

#include <core/template/TemplateUtilities.h>
#include <core/template/is_same_type.h>
#include <core/template/is_singleton.h>

#include <core/template/result_of_static_function.h>

#include <core/template/to_string.h>
#include <core/template/default_constructor.h>

#include <core/template/function_traits.h>
#include <sstream>
using namespace nspace;
using namespace std;



TEST(0,function_traits){ 
  TEST_DESCRIPTION(tests traits for a simple void function)
  auto f = [](){};
  typedef function_traits<decltype(f)> traits;
  // the number of arguments of f should be 0
  CHECK_EQUAL(1,traits::arity);
  // the type of argument 0 should be int
  CHECK_TYPES(traits::arg<0>::type,int);
  // the result type of f should be void
  CHECK_TYPES(traits::result_type,void);
}
TEST(1,function_traits){
  TEST_DESCRIPTION( test for a simple function which accepts an int and returns nothing)
  auto f = [](int i){};
  typedef function_traits<decltype(f)> traits;
  // the number of arguments of f should be 1
  CHECK_EQUAL(1,traits::arity);
  // the type of argument 0 should be int
  CHECK_TYPES(traits::arg<0>::type,int);
  // the result type of f should be void
  CHECK_TYPES(traits::result_type,void);
}

TEST(2,function_traits){
  TEST_DESCRIPTION( test for a simple function which just returns a int )
  auto f = []()->int{return 0;};
  typedef function_traits<decltype(f)> traits;
  // the number of arguments of f should be 0
  CHECK_EQUAL(0,traits::arity);
  // the type of argument 0 should be int
  CHECK_TYPES(traits::arg<0>::type,void);
  // the result type of f should be void
  CHECK_TYPES(traits::result_type,int);

}
TEST(3,function_traits){
  TEST_DESCRIPTION( test for a  function with a longer signature)
  auto f = [](int a, double b, std::string c, std::vector<int> d)->std::tuple<std::string, int>{return std::make_tuple(std::string(""),int(0));};
  typedef function_traits<decltype(f)> traits;
  // the number of arguments of f should be 0
  CHECK_EQUAL(4,traits::arity);
  // the type of argument 0 should be int
  CHECK_TYPES(traits::arg<0>::type,int);
  CHECK_TYPES(traits::arg<1>::type,double);
  CHECK_TYPES(traits::arg<2>::type,std::string);
  CHECK_TYPES(traits::arg<3>::type,std::vector<int>);
  // the result type of f should be void
  CHECK_TYPES(traits::result_type,std::tuple<std::string,int>);

}



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
  auto instance = default_constructor<A>::construct();
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
  auto instance = default_constructor<A>::construct();
  CHECK(instance!=0);
 CHECK(called);
}
TEST(3,default_constructor){
  struct A{
    A(int i){}//no default constructor available
  };
  auto instance = default_constructor<A>::construct();
  CHECK(instance==0);
}
TEST(4,default_constructor){
  // tests if a constructed object is destructed correctly
  static bool constructed = false;
  static bool destructed =false;
  struct A{  
    A(){
      constructed= true;
    }
    ~A(){
      destructed = true;
    }
  };



  CHECK(!constructed && !destructed);
  {
  auto instance = default_constructor<A>::construct();
    CHECK(constructed);
  }
  CHECK(destructed);
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