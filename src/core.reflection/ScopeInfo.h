#pragma once

#include <config.h>
#include <core.property.h>
#include <set>
#include <memory>

namespace nspace{
  class NamespaceInfo;
  class ScopeInfo{
  public:
    extensible_property_class;
    virtual ~ScopeInfo();
    static const ScopeInfo* Global();
    static const ScopeInfo* requireScope(const std::string & name);
    static const ScopeInfo* findScope(const std::string & name);
    static const ScopeInfo* findParentScope(const std::string & name);


    static std::string parentScopeName(const std::string & fullyQualifiedName);
    static std::string normalizeName(const std::string & nameOrFullyQualifiedName);
    static std::string normalizeFullyQualifiedName(const std::string & nameOrFullyQualifiedName);


    const ScopeInfo * findChild(const std::string & name)const;

    const std::set<const ScopeInfo*> & ChildScopes()const;
    // needs to be initialized before name
    std::string getFullyQualifiedName()const;
    typedef std::string basic_property(Name);
    typedef const ScopeInfo* extensible_property(Scope);


    bool addChildScope(const ScopeInfo*  node);
    bool removeChildScope(const ScopeInfo* node);
    auto before_set(Scope);
    auto after_set(Scope);
  protected:
    ScopeInfo(const std::string & nameOrFullyQualifiedName);
    virtual void onScopeSet(const ScopeInfo*  parent);
    virtual void onChildScopeAdded(const ScopeInfo*  child);
    virtual void onChildScopeRemoved(const ScopeInfo*  child);
  private:
    std::set<const ScopeInfo*> _ChildScopes;
    
    friend class NamespaceInfo;
    ScopeInfo();
    void init();
  };
}