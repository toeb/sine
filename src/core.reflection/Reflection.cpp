#include "Reflection.h"
#include <core.reflection/builder/NamespaceBuilder.h>
namespace nspace{
  namespace core{
    namespace reflection{
      typedef std::shared_ptr<ScopeInfo> ScopePointer;
      typedef std::map<std::string,ScopePointer> ScopeRegistryType;



      ScopeRegistryType & registry(){
        static ScopeRegistryType _registry;
        static bool init = []()->bool{
          std::make_shared<nspace::core::reflection::builder::NamespaceBuilder>()
            ->begin()
            ->fullyQualifiedName("::")
            ->publish()
            ->end();
          return true;
        }();
        return _registry;
      }
      
      ScopePointer scope(const std::string &  fullName){
        auto it = registry().find(fullName);
        if(std::end(registry())==it)return std::shared_ptr<ScopeInfo>();
        return it->second;
      }

      const std::shared_ptr<const ScopeInfo> findScope(const std::string & fullyQualifiedName){
        std::stringstream stream;
        if(!stringtools::startsWith(fullyQualifiedName,"::"))stream<<"::";
        stream<<fullyQualifiedName;
        if(!stringtools::endsWith(fullyQualifiedName,"::"))stream<<"::";
        return scope(stream.str());
      }
      const std::shared_ptr<const NamespaceInfo> findNamespace(const std::string & fullyQualifiedName){
        auto scope = findScope(fullyQualifiedName);
        return std::dynamic_pointer_cast<const NamespaceInfo>(scope);
      }
      const std::shared_ptr<const Type> findType(const std::string & fullyQualifiedName){
        auto scope = findScope(fullyQualifiedName);
        return std::dynamic_pointer_cast<const Type>(scope);
      }
      const std::shared_ptr<const NamespaceInfo> Global(){
        return std::dynamic_pointer_cast<const NamespaceInfo>(findScope("::"));
      }
    }
  }
}