#pragma once

#include <core.reflection/builder/ScopeBuilder.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{
        class NamespaceBuilder : public ScopeBuilder<NamespaceBuilder, NamespaceInfo>{
        public:
          NamespaceBuilder(result_ptr ns =result_ptr()  ):ScopeBuilder(this, ns){

          }
          derived_ptr registerNamespace(const std::string & name){
            return derived();
          }
        };
      }
    }
  }
}