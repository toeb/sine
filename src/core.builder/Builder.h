#pragma once
#include <core.builder/FluentFunctionChainer.h>
#include <memory>
#include <core/patterns/Derivable.h>
namespace nspace{
  namespace core{
    namespace builder{

      // expects Derived::subject() to exist and habe a return type which is castable to Subject
      template<typename Derived,typename Subject>
      class MixIn : public Derivable<Derived>{
      public:
        typedef Subject subject_type;
        typedef std::shared_ptr<Subject> subject_ptr;
      protected:
        subject_ptr subject(){
          return std::dynamic_pointer_cast<subject_type>()->subject();
        }

      };


      template<typename Derived, typename ResultType>
      class Builder : public Derivable<Derived>{        
      public:
        typedef std::shared_ptr<typename ResultType> result_ptr;
        typedef typename ResultType result_type;
      protected:
        Builder(derived_ptr derived),_result(result_ptr()){}
        Builder(derived_ptr derived, result_ptr result):FluentFunctionChainer(derived),_result(result){}
        virtual void onBeforeEnd(){}
        virtual bool validate(){return true;}
        virtual result_ptr createInstance(){
          return std::make_shared<ResultType>();
        }
      public:
        virtual result_ptr & result(){
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