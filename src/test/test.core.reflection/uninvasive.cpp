#include <core.testing.h>
#include <core.reflection.h>
#include <map>
#include <memory>

using namespace nspace;
namespace nspace{
  template<typename T>
  struct TypeName{        
    const std::string & name(){
      static std::string _name = T::getTypeName();
      return _name;
    }
  };

#define DS_TYPE_NAME(TYPE)            \
  template<>                      \
  struct TypeName<::TYPE>{          \
  const std::string & name(){   \
  static std::string _name = DS_STRINGIFY(::TYPE);\
  return _name;\
  }  \
  }
  namespace core{
    namespace reflection{


      template<typename Derived>
      class FluentChainer {
        Derived & _derived;
      protected:
        FluentChainer(Derived & derived):_derived(derived){}
      public:
        Derived & derived(){return _derived;}
        const Derived & derived()const{return _derived;}
      };


      template<typename Derived, typename ResultType>
      class Builder : public FluentChainer<Derived>{        
      protected:
        typedef std::shared_ptr<ResultType> result_ptr;
      private:
        result_ptr _result;
      protected:
        Builder(Derived & derived):FluentChainer(derived),_result(result_ptr()){}
        Builder(Derived & derived, result_ptr result):FluentChainer(derived),_result(result){}
        virtual void onBeforeEnd(){}
        virtual bool validate(){return true;}
        virtual result_ptr createInstance(){
          return std::make_shared<ResultType>();
        }
      public:
        result_ptr & result(){
          return _result;
        }
        bool isValid(){
          return (bool)result()&&validate();
        }

        Derived & begin(){
          if((bool)result()) throw new std::exception("another instance currently is being built. call ::end() before calling begin()");
          result() = createInstance();
          return derived();
        }

        result_ptr end(){
          onBeforeEnd();
          auto res = result();
          result().reset();
          return res;
        }

      };

      template<typename Derived, typename ParentBuilder, typename ResultType>
      class NestedBuilder : public Builder<Derived,ResultType>{
        ParentBuilder & _parentBuilder;
      public:
        NestedBuilder(Derived& derived, ParentBuilder & parent):Builder(derived),_parentBuilder(parent){

        }
        ParentBuilder & parent(){
          return _parentBuilder;
        }
        ParentBuilder & end(){
          Builder<Derived,ResultType>::end();
          return _parentBuilder;
        }

      };


      template<typename Derived>
      class FluentFunctionChainer : public FluentChainer<Derived>{
      protected:
        FluentFunctionChainer(Derived & derived):FluentChainer(derived){}
      public:
        Derived & call(std::function<void()> function){
          function();
          return derived();
        }
      };


      typedef std::shared_ptr<ScopeInfo> ScopePointer;
      typedef std::map<std::string,ScopePointer> ScopeRegistryType;
      ScopeRegistryType _registry;
      ScopeRegistryType & registry(){return _registry;}
      ScopePointer scope(const std::string &  fullName){
        auto it = _registry.find(fullName);
        if(std::end(_registry)==it)return std::shared_ptr<ScopeInfo>();
        return it->second;
      }


      const std::shared_ptr<const ScopeInfo> findScope(const std::string & fullyQualifiedName){
        return scope(fullyQualifiedName);
      }
      const std::shared_ptr<const NamespaceInfo> findNamespace(const std::string & fullyQualifiedName){
        auto scope = findScope(fullyQualifiedName);
        return std::dynamic_pointer_cast<const NamespaceInfo>(scope);
      }
      const std::shared_ptr<const NamespaceInfo> findType(const std::string & fullyQualifiedName){
        auto scope = findScope(fullyQualifiedName);
        return std::dynamic_pointer_cast<const NamespaceInfo>(scope);
      }


      const std::shared_ptr<const NamespaceInfo> Global(){
        return std::dynamic_pointer_cast<const NamespaceInfo>(findScope("::"));
      }




      template<typename Derived, typename ResultType>
      class ScopeBuilder : 
        public Builder<Derived, ResultType>, 
        public FluentFunctionChainer<Derived>{
      protected:
        ScopeBuilder(Derived & derived, std::shared_ptr<ResultType> result):
          Builder(derived, result),FluentFunctionChainer(derived){
        }
      public:
        Derived & derived(){
          return Builder::derived();
        }

        // loads the scope specified by name - if not found the instance being built is set to empty
        Derived & loadScope(const std::string & fullyQualifiedName){
          result() = std::dynamic_pointer_cast<ResultType>(scope(fullyQualifiedName));
          return derived();
        }

        // gets the scope / derivative identified by the name or creates it but does not publish it
        Derived & require(const std::string & fullName){    
          loadScope(fullName);
          if((bool)result())return derived();
          begin();
          fullyQualifiedName(fullName);
          return derived();
        }

        Derived & fullyQualifiedName(std::string name){
          if(!(bool)result())throw new std::exception("result is not set");
          if(name.empty()||!stringtools::startsWith(name,"::"))
            throw new std::exception("fully qualified name has invalid format");
          if(!stringtools::endsWith(name,"::") ) name = name + "::";
          result()->setFullyQualifiedName(name);
          auto n = scopeName(name);
          result()->setName(n);
          return derived();
        }

        // publishes the scope into global registry and creates parent scopes as namespaces if they do not exist
        Derived & publishHierarchy(){
          publish();
          auto fullName = result()->getFullyQualifiedName();
          if(scope(fullName)==Global())return derived();         

          auto parentName = parentScopeName(fullName);          
          NamespaceBuilder builder;
          builder.require(parentName);
          builder.publishHierarchy();  

          setParentScope();

          return derived();
        }
        static std::string removeTemplates(const std::string & name){
          std::stringstream  stream;
          auto a = name.find_first_of('<');
          auto b = name.find_last_of('>');
          if(a==b)return name;
          stream << name.substr(0,a)<<name.substr(b);
          return stream.str();
        }
        // returns the parent scope of the passed scope name
        static std::string parentScopeName(const std::string & name){
          auto identifier = removeTemplates(name);
          identifier = identifier.substr(0,identifier.size()-2);
          auto end = std::min(identifier.find_last_of("::"),identifier.size());
          identifier = identifier.substr(0,end+1);          
          return identifier;
        }
        static std::string scopeName(const std::string & name){
          auto parentname = parentScopeName(name);
          if(parentname=="")return "";
          auto result = name.substr(parentname.size(),name.size()-parentname.size()-2);
          return result;
        }
        Derived& check(){
          if(!isValid())throw new std::exception("no instance set");         
        }
        Derived & setParentScope(const std::string & name){
          check();
          auto parentName = parentScopeName(name);
          auto parent = scope(parentName);
          if(!(bool)parent)throw new std::exception("parent scope not found");
          result()->setScope(parent.get());
          return derived();
        }
        Derived & setParentScope(){
          std::string fullname = result()->getFullyQualifiedName();
          setParentScope(fullname);
          return derived();
        }

        // publishes the type to the global scope registry
        Derived & publish(){
          if(!(bool)result())throw new std::exception("no instance is being built currently");
          auto scope = std::static_pointer_cast<ScopeInfo>(result());
          for(auto name: registrationNames()){
            registry()[name]=scope ;
          }
          return derived(); 
        }



        virtual std::vector<std::string> registrationNames(){ 
          if(!(bool)result())throw new std::exception("no instance is being built currently");
          std::vector<std::string> names;
          names.push_back(result()->getFullyQualifiedName());
          return names;
        }
      };

      
      template<typename T>
      class TypeBuilder;

      template<typename T, typename Method>
      class MethodBuilder : public NestedBuilder<MethodBuilder<T,Method>,TypeBuilder<T>, MethodInfo>{
      private:
        Method _method;
      public:
        MethodBuilder(TypeBuilder<T> & parentBuilder, Method method):
          NestedBuilder<MethodBuilder<T,Method>,TypeBuilder<T>, MethodInfo>(*this,parentBuilder){
          
        }
        result_ptr createInstance(){
          //@@!!todo change all pointers to shared ptrs
          return *new  std::make_shared<TypedMethodInfo<Method>>(_method);
        }

        void onBeforeEnd()override{
          parent().result()->Members()|=result().get()
        }

      };

      template<typename T>
      class TypeBuilder :public ScopeBuilder<TypeBuilder<T>, Type> {
      protected:
        result_ptr createInstance()override{
          return TypeInfo<T>::instance();
        }
      public:
        TypeBuilder(result_ptr type):ScopeBuilder(*this,type){

        }
        TypeBuilder():ScopeBuilder(*this,result_ptr()){

        }
        template<typename Method>
        MethodBuilder<T,Method> method(Method method){
          MethodBuilder<T,Method> builder(*this,method);

          return builder;
        }
      };

      //class ScopeBuilder : public Builder<ScopeInfo>

      class NamespaceBuilder : public ScopeBuilder<NamespaceBuilder, NamespaceInfo>{
      public:
        NamespaceBuilder(result_ptr ns =result_ptr()  ):ScopeBuilder(*this, ns){

        }
        NamespaceBuilder & registerNamespace(const std::string & name){
          return derived();
        }
      };






      std::shared_ptr<NamespaceInfo> _global=[]()->std::shared_ptr<NamespaceInfo>{
        NamespaceBuilder builder;
        return builder
          .begin()
          .fullyQualifiedName("::")
          .publish()
          .end();        

      }();

      /*
      #define Namespace(NAME)\
      Namespace()\
      .Require(DS_STRINGIFY(DS_CONCAT(::,NAME)))
      */




#define reflectType(TYPE) 
#define reflectTemplatedType(TYPE,...)

    }}} 

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



// some test classes with hierachy/templates and members
namespace uninvasiveReflection{
  class SomeOtherClass{
    int j;
    std::string k;
  };

  template<typename T1,typename T2>
  class SomeTemplateClass{

  };

  class SomeTestClass{
  public:
    int i;
    int j;
    std::string str;
    std::shared_ptr<int> iptr;
    std::shared_ptr<SomeTestClass> classPtr;
    int * irawptr;
    SomeOtherClass classmember;

    const int & getI()const{return i;}
    void setI(const int & i){this->i = i;}

    double method1(int ka, double d){return ka*d;}
    double method1(int ka, double d,std::string third){return ka*d;}

    double method2(int ka, double d){return ka*d;}


    template<typename TK>
    double method3(double a, double b){return a+b;}
  };
  class SomeDerivedClass : public SomeTestClass{
  public:
    int k;
    std::string str2;
  };

}

namespace nspace{
  DS_TYPE_NAME(uninvasiveReflection::SomeTestClass);
  DS_TYPE_NAME(uninvasiveReflection::SomeOtherClass);

  //    return nspace::TypeInfo<T>::instance().get();


}

UNITTEST(AddMethod){

  using namespace core::reflection;
  using namespace uninvasiveReflection;  

  TypeBuilder<::uninvasiveReflection::SomeTestClass> builder;
  auto result = builder
    .begin()
    .fullyQualifiedName("::uninvasiveReflection::SomeTestClass")
      .method<decltype(&SomeTestClass::method2)>()
      ;
  result.end();
   
  

  

  auto type = type_of<SomeTestClass>();
  auto method = type->getMethod("method2");
  SomeTestClass t;
  MethodAdapter m2(t,"method2");
  double res = m2(101,3.40);
}

UNITTEST(CreateType){
  using namespace core::reflection;
  using namespace uninvasiveReflection;
  TypeBuilder<::uninvasiveReflection::SomeTestClass> builder;
  auto result = builder
    .begin()
    .fullyQualifiedName("::uninvasiveReflection::SomeTestClass")
    .publish()
    .end();
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
  NamespaceBuilder builder;
  builder
    .begin()
    .fullyQualifiedName(name);

  builder.publishHierarchy();
  auto result = builder.end();

  auto & r = registry();

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
  NamespaceBuilder ns;
  ns.begin()
    .fullyQualifiedName("::someTestNameSpace");
  //act
  ns.setParentScope();
  //check
  auto result = ns.end();
  CHECK((bool)result);
  CHECK_EQUAL(Global().get(), result->getScope());
  CHECK(contains(Global()->ChildScopes(), result.get()));

}
UNITTEST(RegisterScope){
  // setup
  using namespace core::reflection;
  NamespaceBuilder ns;
  ns.begin();
  ns.fullyQualifiedName("::someTestNameSpace");
  //act
  ns.publish();
  //check
  auto result = findScope("::someTestNameSpace::");
  CHECK((bool)result);
}

