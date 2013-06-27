#pragma once
#include <map>
#include <memory>
#include <core.reflection/type/Type.h>
#include <core.reflection/namespace/NamespaceInfo.h>
#include <core.reflection/ScopeInfo.h>
namespace nspace{
  namespace core{
    namespace reflection{
      typedef std::shared_ptr<ScopeInfo> ScopePointer;
      typedef std::map<std::string,ScopePointer> ScopeRegistryType;
      ScopeRegistryType & registry();      
      ScopePointer scope(const std::string &  fullName);
      const std::shared_ptr<const ScopeInfo> findScope(const std::string & fullyQualifiedName);
      const std::shared_ptr<const NamespaceInfo> findNamespace(const std::string & fullyQualifiedName);
      const std::shared_ptr<const Type> findType(const std::string & fullyQualifiedName);
      const std::shared_ptr<const NamespaceInfo> Global();
    }
  }
}