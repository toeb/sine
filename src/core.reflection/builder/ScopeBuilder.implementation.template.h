#pragma once

#include "ScopeBuilder.h"

#include <core.reflection/builder/AttributeTargetBuilder.implementation.template.h>
#include <core.utility/StringTools.h>
#include <core.reflection/Reflection.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{

        template<typename Derived, typename ResultType>          
        ScopeBuilder<Derived,ResultType>::ScopeBuilder(derived_ptr derived, result_ptr result):
          AttributeTargetBuilder(derived,result){

        }



        // loads the scope specified by name - if not found the instance being built is set to empty
        template<typename Derived, typename ResultType>          
        auto ScopeBuilder<Derived,ResultType>::loadScope(const std::string & fullyQualifiedName)->derived_ptr{
          result() = std::dynamic_pointer_cast<ResultType>(scope(fullyQualifiedName));
          return derived();
        }

        // gets the scope / derivative identified by the name or creates it but does not publish it
        template<typename Derived, typename ResultType>          
        auto  ScopeBuilder<Derived,ResultType>::require(const std::string & fullName)->derived_ptr{    
          loadScope(fullName);
          if((bool)result())return derived();
          begin();
          fullyQualifiedName(fullName);
          return derived();
        }

        template<typename Derived, typename ResultType>          
        auto ScopeBuilder<Derived,ResultType>::fullyQualifiedName(std::string name)->derived_ptr{
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
        template<typename Derived, typename ResultType>          
        auto  ScopeBuilder<Derived,ResultType>::publishHierarchy()->derived_ptr{
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
        template<typename Derived, typename ResultType>          
        std::string  ScopeBuilder<Derived,ResultType>::removeTemplates(const std::string & name){
          std::stringstream  stream;
          auto a = name.find_first_of('<');
          auto b = name.find_last_of('>');
          if(a==b)return name;
          stream << name.substr(0,a)<<name.substr(b);
          return stream.str();
        }
        // returns the parent scope of the passed scope name
        template<typename Derived, typename ResultType>          
        std::string  ScopeBuilder<Derived,ResultType>::parentScopeName(const std::string & name){
          auto identifier = removeTemplates(name);
          identifier = identifier.substr(0,identifier.size()-2);
          auto end = std::min(identifier.find_last_of("::"),identifier.size());
          identifier = identifier.substr(0,end+1);          
          return identifier;
        }
        template<typename Derived, typename ResultType>          
        std::string  ScopeBuilder<Derived,ResultType>::scopeName(const std::string & name){
          auto parentname = parentScopeName(name);
          if(parentname=="")return "";
          auto result = name.substr(parentname.size(),name.size()-parentname.size()-2);
          return result;
        }
        template<typename Derived, typename ResultType>          
        auto  ScopeBuilder<Derived,ResultType>::check()->derived_ptr{
          if(!isValid())throw new std::exception("no instance set");  
          return derived();
        }
        template<typename Derived, typename ResultType>          
        auto  ScopeBuilder<Derived,ResultType>::setParentScope(const std::string & name)->derived_ptr{
          check();
          auto parentName = parentScopeName(name);
          auto parent = scope(parentName);
          if(!(bool)parent)throw new std::exception("parent scope not found");
          result()->setScope(parent.get());
          return derived();
        }

        template<typename Derived, typename ResultType>          
        auto  ScopeBuilder<Derived,ResultType>::setParentScope()->derived_ptr{
          std::string fullname = result()->getFullyQualifiedName();
          setParentScope(fullname);
          return derived();
        }

        // publishes the type to the global scope registry
        template<typename Derived, typename ResultType>          
        auto  ScopeBuilder<Derived,ResultType>::publish()->derived_ptr{
          if(!(bool)result())throw new std::exception("no instance is being built currently");
          auto scope = std::static_pointer_cast<ScopeInfo>(result());
          for(auto name: registrationNames()){
            registry()[name]=scope ;
          }
          return derived(); 
        }

        template<typename Derived, typename ResultType>          
        std::vector<std::string>  ScopeBuilder<Derived,ResultType>::registrationNames(){ 
          if(!(bool)result())throw new std::exception("no instance is being built currently");
          std::vector<std::string> names;
          names.push_back(result()->getFullyQualifiedName());
          return names;
        }
      }
    }
  }
}