#pragma once

#include <core.reflection/callable/Callable.h>
#include <core.reflection/callable/CallableFunctor.h>
#include <core.reflection/type/TypeInfo.h>
namespace nspace{
  struct DynamicCallableImplementation;

  struct DynamicCallable : public Callable{
    reflect_type_declaration(nspace::DynamicCallable);
    std::shared_ptr<DynamicCallableImplementation> implementation;
  public:
    DynamicCallable(Callable * callable);
    DynamicCallable(Callable & callable);
    DynamicCallable(std::shared_ptr<Callable> callable);
    DynamicCallable(std::shared_ptr<DynamicCallableImplementation> implementation);
    DynamicCallable();

    template<typename TCallable> DynamicCallable(CallableFunctor<TCallable> callable);


    bool isValid()const override final;
    Argument callImplementation(const ArgumentList &args)override final;
  };

}