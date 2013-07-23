#include <core.testing.h>
#include <core.reflection.h>

#include "SampleClasses.h"

#include <core.reflection.builder.h>
using namespace nspace;
using namespace nspace::core::reflection::builder;





UNITTEST(reflect_overloaded_constructor){
  using namespace core::reflection;
  using namespace uninvasiveReflection;  

    auto & type = *
    //! [reflect overloaded constructor]
      reflect<SomeTestClass>()
    ->constructor<int,int>()
    ->end()
    ->end();
    //! [reflect overloaded constructor]
  std::vector<const Type*> types ;
  types.push_back(type_of<int>());
  types.push_back(type_of<int>());
  auto constructor = type.getConstructor(types);

  CHECK(constructor);
  CHECK_EQUAL(2,constructor->Arguments().size());  
}
UNITTEST(reflect_default_constructor){
  using namespace core::reflection;
  using namespace uninvasiveReflection;  
  
  std::vector<const Type*> types;
  // check that default constructor was not yet reflected
  auto constructor_info = type_of<SomeTestClass>()->getConstructor(types);
  CHECK(!constructor_info)

  //! [reflect default constructor]
  reflect<SomeTestClass>()
    ->constructor()  // begins reflection of 0-Argument constructor
    ->end()          // ends reflection of 0-Argument constructor
  ->end();
  //! [reflect default constructor]

  // check that constructor exists
  constructor_info = type_of<SomeTestClass>()->getConstructor(types);
  CHECK(constructor_info)
}
UNITTEST(reflect_complete_class){  
  using namespace core::reflection;
  using namespace uninvasiveReflection;  
  //! [reflect complete class]
  // the following code reflects the class BasicMath completely  
  reflect<BasicMath>()  
    // set fully qualified name of classs
    ->name("::uninvasiveReflection::BasicMath")
    // reflect defualt constructor
      ->constructor()
      ->end()
    // reflect single string parameter constructor
    ->constructor<std::string>()
      ->argument<0>()
      // set name of parameter 0
        ->name("name")
        ->end()
      ->end()
      // reflect constructor accepting a const char *  and set its name
    ->constructor<const char*>()
      ->argument<0>
        ->name("name")
        ->end()
      ->end()
      // reflects the method zero (since method is not overloaded)
      // the address of the method suffices
    ->method(&BasicMath::zero)
      ->name("zero")
      ->end()
    ->method(&BasicMath::one)
      ->name("one")
      ->end()
      // reflects the add method and sets its argument.
      // since add has two overloads -one for adding 2 and another for adding 3
      // numbers the correct signature needs to be chosen via the 
      // signature discriminator method "signature<...>"
    ->method(signature<double,double>(&BasicMath::add)
      ->name("add")
      ->argument<0>
        ->name("a")
        ->end()
      ->argument<1>
        ->name("b")
        ->end()
      ->end()
    ->end()
  //! [reflect complete class]
  CHECK(false)
}
UNITTEST(vectorAccess){
  auto &type = *type_of<std::vector<int>>();

  auto instance = type();

  MethodAdapter push_back(instance,"push_back");
  
  push_back(3);
  push_back(4);
  push_back(2);
  
  MethodAdapter size(instance,"size");
  MethodAdapter at(instance,"at(...)const");

  int result = at(1);
  CHECK_EQUAL(4,result);
  CHECK_EQUAL(3,(int)size());
  

}



UNITTEST(vectorType){
  auto type = type_of<std::vector<int>>();
  CHECK(type);
  CHECK(type->getMethod("size"));
  CHECK(type->getMethod("at"));

}


UNITTEST(primitiveTypes){


  CHECK(type_of<int>()->getName()=="int");
  CHECK(type_of<double>()->getName()=="double");
  CHECK(type_of<std::string>()->getName()=="string");
  CHECK(type_of<void>()->getName()=="void");
  CHECK((bool)core::reflection::findType("int"));
  CHECK((bool)core::reflection::findType("double"));
  CHECK((bool)core::reflection::findType("std::string"));
  CHECK((bool)core::reflection::findType("void"));
}


UNITTEST(reflect_overloaded_method){
  
  using namespace core::reflection;
  using namespace uninvasiveReflection;  

  auto type = 
    //! [reflect overloaded method]
    reflect<SomeTestClass>()
    // start reflecting int, double overload of method1 
    ->method(signature<int,double>(&SomeTestClass::method1))
     ->name("method1") // sets name method1
     ->argument<0>() // begins reflection of first argument
      ->name("ka") // sets name of first argument
      ->end() // ends reflection of first argument
     ->argument<1>() //  begins reflection of second argument of method1
      ->name("d") // set name of second argument
      ->end() // ends reflection of second argument of method1
     ->end()  // ends method1 reflection
    ->end();  // ends class reflection
    //! [reflect overloaded method]
  
  auto method = type->getMethod("method1");
  CHECK(method);
  CHECK_EQUAL(type_of<double>(), method->getReturnType());
  CHECK_EQUAL(type_of<int>(),method->argument(0)->getArgumentType().get());
  CHECK_EQUAL(type_of<double>(),method->argument(1)->getArgumentType().get());
  CHECK_EQUAL("ka",method->argument(0)->getName());
  CHECK_EQUAL("d",method->argument(1)->getName());
}

UNITTEST(SimpleTypeReflection){
  using namespace core::reflection;
  using namespace uninvasiveReflection;   
  //! [simple reflection]
  reflect<SomeTestClass>()
    ->name("::uninvasiveReflection::SomeTestClass")
    ->end();
  //! [simple reflection]

}

/*
UNITTEST(AddUniqueMethod){
  
  using namespace core::reflection;
  using namespace uninvasiveReflection;  
  auto builder = std::make_shared<TypeBuilder<::uninvasiveReflection::SomeTestClass>>();
  builder->begin()
    ->fullyQualifiedName("::uninvasiveReflection::SomeTestClass")
    ->method(&SomeTestClass::method2)
      ->name("method2")
      ->argument<0>()
        ->name("ka")
        ->defaultValue(32)
        ->end()
      ->argument<1>()
        ->name("d")
        ->defaultValue(3213.2)
        ->end()
      ->end()
      ;

  
  auto type = type_of<SomeTestClass>();
  auto method = type->getMethod("method2");
  CHECK(method);
  CHECK_EQUAL("method2(int,double)", method->getName());
  CHECK_EQUAL(2,method->Arguments().size());
  CHECK_EQUAL("ka", method->argument(0)->getName());
  CHECK_EQUAL("d", method->argument(1)->getName());
  CHECK_EQUAL(32, (int)method->argument(0)->getDefaultValue());
  DOUBLES_EQUAL(3213.2,(double)method->argument(1)->getDefaultValue(),0.001);

}

UNITTEST(CreateType){
  using namespace core::reflection;
  using namespace uninvasiveReflection;
  TypeBuilder<::uninvasiveReflection::SomeTestClass> builder;
  auto result = builder
    .begin()
    ->fullyQualifiedName("::uninvasiveReflection::SomeTestClass")
    ->publish()
    ->end();
  auto type = type_of<SomeTestClass>();
  CHECK_EQUAL(type,result.get());
  CHECK_EQUAL("SomeTestClass", result->getName());
  CHECK_EQUAL("::uninvasiveReflection::SomeTestClass::", result->getFullyQualifiedName());
}

UNITTEST(ParentScopeName1){
  using namespace nspace::core::reflection;
  std::string scope = "::";
  auto result = NamespaceBuilder::parentScopeName(scope);
  CHECK_EQUAL("",result)
}

UNITTEST(ParentScopeName2){
  using namespace nspace::core::reflection;
  std::string scope = "::test::";
  auto result = NamespaceBuilder::parentScopeName(scope);
  CHECK_EQUAL("::",result)
}

UNITTEST(ParentScopeName3){
  using namespace nspace::core::reflection;
  std::string scope = "::test::test2";
  auto result = NamespaceBuilder::parentScopeName(scope);
  CHECK_EQUAL("::test::",result)
}
UNITTEST(ParentScopeName4){
  using namespace nspace::core::reflection;
  std::string scope = "::test::Class<Template1,std::vector<std::string>>::";
  auto result = NamespaceBuilder::parentScopeName(scope);
  CHECK_EQUAL("::test::",result)
}
UNITTEST(ParentScopeName5){
  using namespace nspace::core::reflection;
  std::string scope = "::test::Class<Template1,std::vector<std::string>>";
  auto result = NamespaceBuilder::parentScopeName(scope);
  CHECK_EQUAL("::test::",result)
}
UNITTEST(ScopeName1){
  using namespace nspace::core::reflection;
  auto result = NamespaceBuilder::scopeName("::test::test2::");
  CHECK_EQUAL("test2", result);
}
UNITTEST(RegisterType){

}



UNITTEST(RegisterBoxedNamespace){
  using namespace nspace::core::reflection;
  auto name = "::test1::test2::test3::";

  auto builder = std::make_shared<NamespaceBuilder>();
  builder
    ->begin()
    ->fullyQualifiedName(name);

  builder->publishHierarchy();
  auto result = builder->end();

  CHECK_EQUAL(Global().get(), result->getScope()->getScope()->getScope());
}


UNITTEST(GetGlobalScope){
  //setup
  using namespace core::reflection;
  //act
  auto globalScope = Global();
  //check
  CHECK((bool)globalScope);
  CHECK_EQUAL("::", globalScope->getFullyQualifiedName());
  CHECK_EQUAL("",globalScope->getName());
  CHECK(!(bool)globalScope->getScope());
}

UNITTEST(SetParentScope){
  // setup
  using namespace core::reflection;

  auto builder = std::make_shared<NamespaceBuilder>();
  builder
    ->begin()
    ->fullyQualifiedName("::someTestNameSpace");
  //act
  builder->setParentScope();
  //check
  auto result = builder->end();
  CHECK((bool)result);
  CHECK_EQUAL(Global().get(), result->getScope());
  CHECK(contains(Global()->ChildScopes(), result.get()));

}
UNITTEST(RegisterScope){
  // setup
  using namespace core::reflection;  
  auto builder = std::make_shared<NamespaceBuilder>();
  builder
    ->begin()
    ->fullyQualifiedName("::someTestNameSpace");
  //act
  builder->publish();
  //check
  auto result = findScope("::someTestNameSpace::");
  CHECK((bool)result);
}

/**/