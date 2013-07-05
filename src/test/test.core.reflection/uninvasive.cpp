#include <core.testing.h>
#include <core.reflection.h>

#include "SampleClasses.h"

#include <core.reflection.builder.h>
using namespace nspace;
using namespace nspace::core::reflection::builder;





UNITTEST(constrcutor1){
  using namespace core::reflection;
  using namespace uninvasiveReflection;  


  auto & type = * reflect<SomeTestClass>()
    ->constructor<int,int>()
    ->end()
    ->end();
  std::vector<const Type*> types ;
  types.push_back(type_of<int>());
  types.push_back(type_of<int>());
  auto constructor = type.getConstructor(types);

  CHECK(constructor);
  CHECK_EQUAL(2,constructor->Arguments().size());  
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

/*
UNITTEST(AddOverloadedMethod){
  
  using namespace core::reflection;
  using namespace uninvasiveReflection;  

  auto type = reflect<SomeTestClass>()
    ->method(signature<int,double>(&SomeTestClass::method1))
    ->name("method1")
    ->argument<0>()
    ->name("ka")
    ->end()
    ->argument<1>()
    ->name("d")
    ->end()
    ->end()
    ->end();

  
  auto method = type->getMethod("method1");
  CHECK(method);
  CHECK_EQUAL(type_of<double>(), method->getReturnType());
  CHECK_EQUAL(type_of<int>(),method->argument(0)->getArgumentType().get());
  CHECK_EQUAL(type_of<double>(),method->argument(1)->getArgumentType().get());
  CHECK_EQUAL("ka",method->argument(0)->getName());
  CHECK_EQUAL("d",method->argument(1)->getName());
}


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