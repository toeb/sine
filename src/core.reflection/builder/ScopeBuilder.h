#pragma once

#include <core.reflection/builder/AttributeTargetBuilder.h>

#include <core.utility/StringTools.h>
#include <core.reflection/Reflection.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename Derived, typename ResultType>
        class ScopeBuilder : 
          public nspace::core::reflection::builder::AttributeTargetBuilder<Derived,ResultType>
        {
        protected:
          ScopeBuilder(derived_ptr derived, result_ptr result);
        public:
          // loads the scope specified by name - if not found the instance being built is set to empty
          derived_ptr loadScope(const std::string & fullyQualifiedName);
          // gets the scope / derivative identified by the name or creates it but does not publish it
          derived_ptr require(const std::string & fullName);
          // sets the fully qualified name for the current scope
          derived_ptr fullyQualifiedName(std::string name);
          // publishes the scope into global registry and creates parent scopes as namespaces if they do not exist
          derived_ptr publishHierarchy();
          static std::string removeTemplates(const std::string & name);
          // returns the parent scope of the passed scope name
          static std::string parentScopeName(const std::string & name);
          // sets the name only of this scope
          static std::string scopeName(const std::string & name);
          // checks wether the scope being built is valid or not
          derived_ptr check();
          // sets the paretn scope
          derived_ptr setParentScope(const std::string & name);
          derived_ptr setParentScope();
          // publishes the type to the global scope registry
          derived_ptr publish();
          virtual std::vector<std::string> registrationNames();
        };
      }
    }
  }
}