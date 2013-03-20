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
  struct Namespace{

  public:
    // returns the global (::) namespace
    static const Namespace* Global();
    typedef std::string           basic_property(Name);
    typedef std::string           basic_property(FullyQualifiedName);
    typedef const Namespace *     basic_property(ParentNamespace);
    typedef Set<const Namespace*> basic_property(Namespaces);  
    typedef Set<const Type *>     basic_property(Types);
    typedef bool                  basic_property(IsType);
  protected:
    Namespace(const std::string & name, const Namespace * parent=Global());
  private:
    Namespace(int i);

  };
}