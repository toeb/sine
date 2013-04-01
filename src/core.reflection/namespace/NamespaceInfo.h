#pragma once
#include <config.h>
#include <core.collection/containers/Set.h>
#include <core.property.h>

#include <memory>
#include <sstream>
#include <core.reflection/ScopeInfo.h>
namespace nspace
{

  // forward declaration for type
  class Type;
  class NamespaceInfo : public ScopeInfo{
  public:

    virtual ~NamespaceInfo();
    // returns the global (::) namespace
    static const NamespaceInfo * Global();
    std::set<const NamespaceInfo *> Namespaces()const;
    std::set<const Type *> Types()const;
    const NamespaceInfo * getNamespace(const std::string & name)const;
    const NamespaceInfo * getParentNamespace()const;
  protected:
    friend class ScopeInfo;
    NamespaceInfo(const std::string & name);
  private:
    // constructor for global namespace
    NamespaceInfo();
    void namespaceAdded(const NamespaceInfo * ns);
    void namespaceRemoved(const NamespaceInfo * ns);

  };
}