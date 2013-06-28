#pragma once

#include <core.reflection/builder/AttributeTargetBuilder.h>
#include <core.utility/StringTools.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename Derived, typename ResultType>
        class ScopeBuilder : 
          public nspace::core::reflection::builder::AttributeTargetBuilder<Derived,ResultType>
        {
        protected:
          ScopeBuilder(derived_ptr derived, result_ptr result):
            AttributeTargetBuilder(derived,result){
              
          }

        public:


          // loads the scope specified by name - if not found the instance being built is set to empty
          derived_ptr loadScope(const std::string & fullyQualifiedName){
            result() = std::dynamic_pointer_cast<ResultType>(scope(fullyQualifiedName));
            return derived();
          }

          // gets the scope / derivative identified by the name or creates it but does not publish it
          derived_ptr require(const std::string & fullName){    
            loadScope(fullName);
            if((bool)result())return derived();
            begin();
            fullyQualifiedName(fullName);
            return derived();
          }

          derived_ptr fullyQualifiedName(std::string name){
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
          derived_ptr publishHierarchy(){
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
          derived_ptr check(){
            if(!isValid())throw new std::exception("no instance set");  
            return derived();
          }
          derived_ptr setParentScope(const std::string & name){
            check();
            auto parentName = parentScopeName(name);
            auto parent = scope(parentName);
            if(!(bool)parent)throw new std::exception("parent scope not found");
            result()->setScope(parent.get());
            return derived();
          }
          derived_ptr setParentScope(){
            std::string fullname = result()->getFullyQualifiedName();
            setParentScope(fullname);
            return derived();
          }

          // publishes the type to the global scope registry
          derived_ptr publish(){
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
      }
    }
  }
}