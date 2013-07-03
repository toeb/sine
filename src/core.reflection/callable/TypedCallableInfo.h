#pragma once
#include <core.reflection/callable/TypedCallableInfoBase.h>
#include <core.reflection/callable/TypedArgumentInfo.h>
#include <memory>
#include <core/template/signature_discriminator.h>
namespace nspace{
  template<typename Callable>
  struct TypedCallableInfo{};
  // specializations for 0 args
  // specialization for void valued const member method with 0 arguments
  template<typename Class>
  struct TypedCallableInfo<void(Class::*)()const> : public TypedCallableInfoBase<void(Class::*)()const, void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)();
      return result;
    }

  };

  // specialization for const member method with 0 arguments
  template<typename ReturnType, typename Class>
  struct TypedCallableInfo<ReturnType(Class::*)()const> : public TypedCallableInfoBase<ReturnType(Class::*)()const, ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)();
      return result;
    }

  };

  // specialization for void valued member method with 0 arguments
  template<typename Class>
  struct TypedCallableInfo<void(Class::*)()> : public TypedCallableInfoBase<void(Class::*)(), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)();
      return result;
    }

  };

  // specialization for member method with 0 arguments
  template<typename ReturnType, typename Class>
  struct TypedCallableInfo<ReturnType(Class::*)()> : public TypedCallableInfoBase<ReturnType(Class::*)(), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)();
      return result;
    }

  };

  // specialization for void valued static method with 0 arguments
  template<>
  struct TypedCallableInfo<void(*)()> : public TypedCallableInfoBase<void(*)(), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = Argument::VoidArgument();
      (*callable)();
      return result;
    }

  };

  // specialization for static method with 0 arguments
  template<typename ReturnType>
  struct TypedCallableInfo<ReturnType(*)()> : public TypedCallableInfoBase<ReturnType(*)(), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = (*callable)();
      return result;
    }

  };

  // specializations for 1 args
  // specialization for void valued const member method with 1 arguments
  template<typename Class, typename T0>
  struct TypedCallableInfo<void(Class::*)(T0)const> : public TypedCallableInfoBase<void(Class::*)(T0)const, void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1]);
      return result;
    }

  };

  // specialization for const member method with 1 arguments
  template<typename ReturnType, typename Class, typename T0>
  struct TypedCallableInfo<ReturnType(Class::*)(T0)const> : public TypedCallableInfoBase<ReturnType(Class::*)(T0)const, ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1]);
      return result;
    }

  };

  // specialization for void valued member method with 1 arguments
  template<typename Class, typename T0>
  struct TypedCallableInfo<void(Class::*)(T0)> : public TypedCallableInfoBase<void(Class::*)(T0), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1]);
      return result;
    }

  };

  // specialization for member method with 1 arguments
  template<typename ReturnType, typename Class, typename T0>
  struct TypedCallableInfo<ReturnType(Class::*)(T0)> : public TypedCallableInfoBase<ReturnType(Class::*)(T0), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1]);
      return result;
    }

  };

  // specialization for void valued static method with 1 arguments
  template<typename T0>
  struct TypedCallableInfo<void(*)(T0)> : public TypedCallableInfoBase<void(*)(T0), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = Argument::VoidArgument();
      (*callable)((T0)args[0]);
      return result;
    }

  };

  // specialization for static method with 1 arguments
  template<typename ReturnType, typename T0>
  struct TypedCallableInfo<ReturnType(*)(T0)> : public TypedCallableInfoBase<ReturnType(*)(T0), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = (*callable)((T0)args[0]);
      return result;
    }

  };

  // specializations for 2 args
  // specialization for void valued const member method with 2 arguments
  template<typename Class, typename T0, typename T1>
  struct TypedCallableInfo<void(Class::*)(T0, T1)const> : public TypedCallableInfoBase<void(Class::*)(T0, T1)const, void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2]);
      return result;
    }

  };

  // specialization for const member method with 2 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1)const> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1)const, ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2]);
      return result;
    }

  };

  // specialization for void valued member method with 2 arguments
  template<typename Class, typename T0, typename T1>
  struct TypedCallableInfo<void(Class::*)(T0, T1)> : public TypedCallableInfoBase<void(Class::*)(T0, T1), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2]);
      return result;
    }

  };

  // specialization for member method with 2 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1)> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2]);
      return result;
    }

  };

  // specialization for void valued static method with 2 arguments
  template<typename T0, typename T1>
  struct TypedCallableInfo<void(*)(T0, T1)> : public TypedCallableInfoBase<void(*)(T0, T1), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = Argument::VoidArgument();
      (*callable)((T0)args[0], (T1)args[1]);
      return result;
    }

  };

  // specialization for static method with 2 arguments
  template<typename ReturnType, typename T0, typename T1>
  struct TypedCallableInfo<ReturnType(*)(T0, T1)> : public TypedCallableInfoBase<ReturnType(*)(T0, T1), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = (*callable)((T0)args[0], (T1)args[1]);
      return result;
    }

  };

  // specializations for 3 args
  // specialization for void valued const member method with 3 arguments
  template<typename Class, typename T0, typename T1, typename T2>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2)const> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2)const, void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3]);
      return result;
    }

  };

  // specialization for const member method with 3 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2)const> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2)const, ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3]);
      return result;
    }

  };

  // specialization for void valued member method with 3 arguments
  template<typename Class, typename T0, typename T1, typename T2>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2)> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3]);
      return result;
    }

  };

  // specialization for member method with 3 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2)> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3]);
      return result;
    }

  };

  // specialization for void valued static method with 3 arguments
  template<typename T0, typename T1, typename T2>
  struct TypedCallableInfo<void(*)(T0, T1, T2)> : public TypedCallableInfoBase<void(*)(T0, T1, T2), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = Argument::VoidArgument();
      (*callable)((T0)args[0], (T1)args[1], (T2)args[2]);
      return result;
    }

  };

  // specialization for static method with 3 arguments
  template<typename ReturnType, typename T0, typename T1, typename T2>
  struct TypedCallableInfo<ReturnType(*)(T0, T1, T2)> : public TypedCallableInfoBase<ReturnType(*)(T0, T1, T2), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = (*callable)((T0)args[0], (T1)args[1], (T2)args[2]);
      return result;
    }

  };

  // specializations for 4 args
  // specialization for void valued const member method with 4 arguments
  template<typename Class, typename T0, typename T1, typename T2, typename T3>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2, T3)const> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2, T3)const, void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4]);
      return result;
    }

  };

  // specialization for const member method with 4 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2, typename T3>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2, T3)const> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2, T3)const, ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4]);
      return result;
    }

  };

  // specialization for void valued member method with 4 arguments
  template<typename Class, typename T0, typename T1, typename T2, typename T3>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2, T3)> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2, T3), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4]);
      return result;
    }

  };

  // specialization for member method with 4 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2, typename T3>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2, T3)> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2, T3), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4]);
      return result;
    }

  };

  // specialization for void valued static method with 4 arguments
  template<typename T0, typename T1, typename T2, typename T3>
  struct TypedCallableInfo<void(*)(T0, T1, T2, T3)> : public TypedCallableInfoBase<void(*)(T0, T1, T2, T3), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = Argument::VoidArgument();
      (*callable)((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3]);
      return result;
    }

  };

  // specialization for static method with 4 arguments
  template<typename ReturnType, typename T0, typename T1, typename T2, typename T3>
  struct TypedCallableInfo<ReturnType(*)(T0, T1, T2, T3)> : public TypedCallableInfoBase<ReturnType(*)(T0, T1, T2, T3), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = (*callable)((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3]);
      return result;
    }

  };

  // specializations for 5 args
  // specialization for void valued const member method with 5 arguments
  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2, T3, T4)const> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2, T3, T4)const, void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5]);
      return result;
    }

  };

  // specialization for const member method with 5 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2, typename T3, typename T4>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2, T3, T4)const> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2, T3, T4)const, ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5]);
      return result;
    }

  };

  // specialization for void valued member method with 5 arguments
  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2, T3, T4)> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2, T3, T4), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5]);
      return result;
    }

  };

  // specialization for member method with 5 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2, typename T3, typename T4>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2, T3, T4)> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2, T3, T4), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5]);
      return result;
    }

  };

  // specialization for void valued static method with 5 arguments
  template<typename T0, typename T1, typename T2, typename T3, typename T4>
  struct TypedCallableInfo<void(*)(T0, T1, T2, T3, T4)> : public TypedCallableInfoBase<void(*)(T0, T1, T2, T3, T4), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = Argument::VoidArgument();
      (*callable)((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4]);
      return result;
    }

  };

  // specialization for static method with 5 arguments
  template<typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4>
  struct TypedCallableInfo<ReturnType(*)(T0, T1, T2, T3, T4)> : public TypedCallableInfoBase<ReturnType(*)(T0, T1, T2, T3, T4), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = (*callable)((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4]);
      return result;
    }

  };

  // specializations for 6 args
  // specialization for void valued const member method with 6 arguments
  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2, T3, T4, T5)const> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2, T3, T4, T5)const, void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6]);
      return result;
    }

  };

  // specialization for const member method with 6 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5)const> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5)const, ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6]);
      return result;
    }

  };

  // specialization for void valued member method with 6 arguments
  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2, T3, T4, T5)> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2, T3, T4, T5), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6]);
      return result;
    }

  };

  // specialization for member method with 6 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5)> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6]);
      return result;
    }

  };

  // specialization for void valued static method with 6 arguments
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct TypedCallableInfo<void(*)(T0, T1, T2, T3, T4, T5)> : public TypedCallableInfoBase<void(*)(T0, T1, T2, T3, T4, T5), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = Argument::VoidArgument();
      (*callable)((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5]);
      return result;
    }

  };

  // specialization for static method with 6 arguments
  template<typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct TypedCallableInfo<ReturnType(*)(T0, T1, T2, T3, T4, T5)> : public TypedCallableInfoBase<ReturnType(*)(T0, T1, T2, T3, T4, T5), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = (*callable)((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5]);
      return result;
    }

  };

  // specializations for 7 args
  // specialization for void valued const member method with 7 arguments
  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2, T3, T4, T5, T6)const> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2, T3, T4, T5, T6)const, void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6], (T6)args[7]);
      return result;
    }

  };

  // specialization for const member method with 7 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6)const> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6)const, ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6], (T6)args[7]);
      return result;
    }

  };

  // specialization for void valued member method with 7 arguments
  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2, T3, T4, T5, T6)> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2, T3, T4, T5, T6), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6], (T6)args[7]);
      return result;
    }

  };

  // specialization for member method with 7 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6)> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6], (T6)args[7]);
      return result;
    }

  };

  // specialization for void valued static method with 7 arguments
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct TypedCallableInfo<void(*)(T0, T1, T2, T3, T4, T5, T6)> : public TypedCallableInfoBase<void(*)(T0, T1, T2, T3, T4, T5, T6), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = Argument::VoidArgument();
      (*callable)((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6]);
      return result;
    }

  };

  // specialization for static method with 7 arguments
  template<typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct TypedCallableInfo<ReturnType(*)(T0, T1, T2, T3, T4, T5, T6)> : public TypedCallableInfoBase<ReturnType(*)(T0, T1, T2, T3, T4, T5, T6), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = (*callable)((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6]);
      return result;
    }

  };

  // specializations for 8 args
  // specialization for void valued const member method with 8 arguments
  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7)const> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7)const, void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T7, 7>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6], (T6)args[7], (T7)args[8]);
      return result;
    }

  };

  // specialization for const member method with 8 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7)const> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7)const, ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T7, 7>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6], (T6)args[7], (T7)args[8]);
      return result;
    }

  };

  // specialization for void valued member method with 8 arguments
  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7)> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T7, 7>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6], (T6)args[7], (T7)args[8]);
      return result;
    }

  };

  // specialization for member method with 8 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7)> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T7, 7>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6], (T6)args[7], (T7)args[8]);
      return result;
    }

  };

  // specialization for void valued static method with 8 arguments
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct TypedCallableInfo<void(*)(T0, T1, T2, T3, T4, T5, T6, T7)> : public TypedCallableInfoBase<void(*)(T0, T1, T2, T3, T4, T5, T6, T7), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T7, 7>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = Argument::VoidArgument();
      (*callable)((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7]);
      return result;
    }

  };

  // specialization for static method with 8 arguments
  template<typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct TypedCallableInfo<ReturnType(*)(T0, T1, T2, T3, T4, T5, T6, T7)> : public TypedCallableInfoBase<ReturnType(*)(T0, T1, T2, T3, T4, T5, T6, T7), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T7, 7>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = (*callable)((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7]);
      return result;
    }

  };

  // specializations for 9 args
  // specialization for void valued const member method with 9 arguments
  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)const> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)const, void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T7, 7>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T8, 8>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6], (T6)args[7], (T7)args[8], (T8)args[9]);
      return result;
    }

  };

  // specialization for const member method with 9 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)const> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)const, ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(true);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T7, 7>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T8, 8>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6], (T6)args[7], (T7)args[8], (T8)args[9]);
      return result;
    }

  };

  // specialization for void valued member method with 9 arguments
  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct TypedCallableInfo<void(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)> : public TypedCallableInfoBase<void(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T7, 7>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T8, 8>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = Argument::VoidArgument();
      (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6], (T6)args[7], (T7)args[8], (T8)args[9]);
      return result;
    }

  };

  // specialization for member method with 9 arguments
  template<typename ReturnType, typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct TypedCallableInfo<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)> : public TypedCallableInfoBase<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(false);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T7, 7>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T8, 8>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      Class * object = (Class*)(void*)args[0];
      result = (object->*callable)((T0)args[1], (T1)args[2], (T2)args[3], (T3)args[4], (T4)args[5], (T5)args[6], (T6)args[7], (T7)args[8], (T8)args[9]);
      return result;
    }

  };

  // specialization for void valued static method with 9 arguments
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct TypedCallableInfo<void(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)> : public TypedCallableInfoBase<void(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8), void>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T7, 7>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T8, 8>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = Argument::VoidArgument();
      (*callable)((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8]);
      return result;
    }

  };

  // specialization for static method with 9 arguments
  template<typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct TypedCallableInfo<ReturnType(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)> : public TypedCallableInfoBase<ReturnType(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8), ReturnType>{
    TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){
      setIsConst(false);
      setIsStatic(true);
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T0, 0>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T1, 1>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T2, 2>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T3, 3>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T4, 4>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T5, 5>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T6, 6>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T7, 7>>());
      Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<T8, 8>>());
    }

    Argument callImplementation(const ArgumentList & args)const{
      callable_type callable = Callable();
      Argument result;
      result = (*callable)((T0)args[0], (T1)args[1], (T2)args[2], (T3)args[3], (T4)args[4], (T5)args[5], (T6)args[6], (T7)args[7], (T8)args[8]);
      return result;
    }

  };


  template<typename T>
  TypedCallableInfo<T> callable_info(T info){
    return TypedCallableInfo<T>(info);
  }

  template<typename T>
  std::shared_ptr<TypedCallableInfo<T>> shared_callable_info(T callable){
    static auto info  = std::make_shared<TypedCallableInfo<T>>(callable);
    return info;
  }}
