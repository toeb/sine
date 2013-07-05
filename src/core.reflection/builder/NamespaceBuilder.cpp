#include "NamespaceBuilder.h"
#include <core.reflection/builder/ScopeBuilder.implementation.template.h>

using namespace nspace::core::reflection::builder;

NamespaceBuilder::NamespaceBuilder(result_ptr ns   ):ScopeBuilder(this, ns){

}
auto NamespaceBuilder::registerNamespace(const std::string & name)->derived_ptr{
  return derived();
}