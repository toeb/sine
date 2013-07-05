#pragma once
#include <core.reflection/builder/MemberBuilder.h>
//#include <core.reflection/builder/CallableBuilder.h>
#include <core.reflection/builder/ArgumentBuilder.h>
namespace nspace{
  namespace core{
    namespace reflection{
      namespace builder{

        template<typename T,typename ConstructorInfoType>
        class ConstructorBuilder : public MemberBuilder<ConstructorBuilder<T,ConstructorInfoType>,T,ConstructorInfoType>{
        public:  

          ConstructorBuilder(parent_ptr parent):
            MemberBuilder<derived_type,T,ConstructorInfoType>(this,parent){}


          result_ptr createInstance(){
            static auto instance = std::make_shared<ConstructorInfoType>();
            return instance;
          }

          void onBeforeEnd()override{
            parent()->result()->Members()|=result().get();
          }
        };
      }
    }
  }
}