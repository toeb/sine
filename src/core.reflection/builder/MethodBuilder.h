#pragma once

#include <core.reflection/builder/MemberBuilder.h>

namespace nspace{
  class MethodInfo;
  namespace core{
    namespace reflection{
      namespace builder{
        template<typename T, typename Method>
        class MethodBuilder : 
          public MemberBuilder<MethodBuilder<T,Method>,T, MethodInfo>{
        private:
          Method _method;
        public:
          MethodBuilder(parent_ptr parentBuilder, Method method);
          // sets the name part of the signature / causes fullname and pure name as well as name to be set
          derived_ptr name(const std::string &purename) override;

            /*  template<unsigned int ArgumentIndex> std::shared_ptr<ArgumentBuilder<T,Method,ArgumentIndex>> argument(); */
        protected:
          result_ptr createInstance()override;
          void onBeforeEnd()override;

        };
      }
    }
  }
}