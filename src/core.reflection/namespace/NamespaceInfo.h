#pragma once
#include <config.h>
#include <core.collection/containers/Set.h>
#include <core.property.h>

#include <memory>
#include <sstream>

namespace nspace
{
  // forward declaration for type
  class Type;
  struct NamespaceInfo{
  public:
    virtual ~NamespaceInfo();
    // returns the global (::) namespace
    static const NamespaceInfo* Global();
    static const NamespaceInfo* Default();
    typedef std::string basic_property(Name);
    typedef std::string basic_property(FullyQualifiedName);
    typedef const NamespaceInfo * basic_property(ParentNamespace);
    typedef Set<const NamespaceInfo*> basic_property(Namespaces);  
    property_reference(Namespaces);
    typedef Set<const Type *>     basic_property(Types);
    property_reference(Types);
    typedef bool                  basic_property(IsType);
  protected:
    NamespaceInfo(const std::string & name, const NamespaceInfo * parent=Global());
  private:
    NamespaceInfo();
    void namespaceAdded(const NamespaceInfo * ns);
    void namespaceRemoved(const NamespaceInfo * ns);

  };
}