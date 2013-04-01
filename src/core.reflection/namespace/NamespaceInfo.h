#pragma once
#include <config.h>
#include <core.collection/containers/Set.h>
#include <core.property.h>

#include <memory>
#include <sstream>
#include <core.reflection/ReflectedElement.h>
namespace nspace
{
  
  // forward declaration for type
  class Type;
  class NamespaceInfo : public ScopeInfo{
  public:

    virtual ~NamespaceInfo();
    // returns the global (::) namespace
    static const NamespaceInfo * Global();
    static const NamespaceInfo * Default();
    std::set<const NamespaceInfo *> Namespaces()const;
    std::set<const Type *> Types()const;
    const NamespaceInfo * getNamespace(const std::string & name)const;
    const NamespaceInfo * getParentNamespace()const;
  protected:
    NamespaceInfo(const std::string & name, const NamespaceInfo * parent=Default());
  private:
    // constructor for global namespace
    NamespaceInfo();
    void namespaceAdded(const NamespaceInfo * ns);
    void namespaceRemoved(const NamespaceInfo * ns);

  };
}