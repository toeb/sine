#pragma once
#include <core.builder/FluentFunctionChainer.h>
namespace nspace{
namespace core{
namespace builder{

      template<typename Derived, typename ResultType>
      class Builder : public FluentFunctionChainer<Derived>{        
      public:
        typedef std::shared_ptr<typename ResultType> result_ptr;
        typedef typename ResultType result_type;
      private:
        result_ptr _result;

      protected:
        Builder(derived_ptr derived):FluentFunctionChainer(derived),_result(result_ptr()){}
        Builder(derived_ptr derived, result_ptr result):FluentFunctionChainer(derived),_result(result){}
        virtual void onBeforeEnd(){}
        virtual bool validate(){return true;}
        virtual result_ptr createInstance(){
          return std::make_shared<ResultType>();
        }
      public:
        result_ptr & result(){
          return _result;
        }
        bool isValid(){
          return (bool)result()&&validate();
        }

        derived_ptr begin(){
          if((bool)result()) throw new std::exception("another instance currently is being built. call ::end() before calling begin()");
          result() = createInstance();
          return derived();
        }

        result_ptr end(){
          onBeforeEnd();
          auto res = result();
          result().reset();
          return res;
        }

      };
}
}
}