#pragma once
#include <core.reflection/member/constructor/ConstructorInfo.h>
#include <core.reflection/callable/TypedCallableInfo.h>
#include <core/template/make_types.h>
namespace nspace{
  // contains typed constructor info for constructors with up to 10 arguments
  template<typename Class, typename T0 = std::_Nil, typename T1 = std::_Nil, typename T2 = std::_Nil, typename T3 = std::_Nil, typename T4 = std::_Nil, typename T5 = std::_Nil, typename T6 = std::_Nil, typename T7 = std::_Nil, typename T8 = std::_Nil, typename T9 = std::_Nil>
  struct TypedConstructorInfo
    :public ConstructorInfo{
      TypedConstructorInfo(){
        setMakeShared(shared_callable(static_signature<T0&& , T1&& , T2&& , T3&& , T4&& , T5&& , T6&& , T7&& , T8&& , T9&& >(&make<Class>::shared_10<ClassT0, T1, T2, T3, T4, T5, T6, T7, T8, T9>)));
        setMakeRaw(shared_callable(static_signature<T0&& , T1&& , T2&& , T3&& , T4&& , T5&& , T6&& , T7&& , T8&& , T9&& >(&make<Class>::raw_10<ClassT0, T1, T2, T3, T4, T5, T6, T7, T8, T9>)));
        setMakePlacement(shared_callable(static_signature<void*T0&& , T1&& , T2&& , T3&& , T4&& , T5&& , T6&& , T7&& , T8&& , T9&& >(, &make<Class>::placement_10<ClassT0, T1, T2, T3, T4, T5, T6, T7, T8, T9>)));
      }
  };
  template <typename Class>
  struct TypedConstructorInfo<Class, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil>:public ConstructorInfo{
    TypedConstructorInfo(){
      setMakeShared(shared_callable_info(static_signature(&make<Class>::shared_0)));
      setMakeRaw(shared_callable_info(static_signature(&make<Class>::raw_0)));
      setMakePlacement(shared_callable_info(static_signature<void*>(&make<Class>::placement_0)));
    }
  };
  template <typename Class, typename T0>
  struct TypedConstructorInfo<Class, T0, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil>:public ConstructorInfo{
    TypedConstructorInfo(){
      setMakeShared(shared_callable_info(static_signature<T0&& >(&make<Class>::shared_1<T0>)));
      setMakeRaw(shared_callable_info(static_signature<T0&& >(&make<Class>::raw_1<T0>)));
      setMakePlacement(shared_callable_info(static_signature<void*, T0&& >(&make<Class>::placement_1<T0>)));
    }
  };
  template <typename Class, typename T0, typename T1>
  struct TypedConstructorInfo<Class, T0, T1, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil>:public ConstructorInfo{
    TypedConstructorInfo(){
      setMakeShared(shared_callable_info(static_signature<T0&& , T1&& >(&make<Class>::shared_2<T0, T1>)));
      setMakeRaw(shared_callable_info(static_signature<T0&& , T1&& >(&make<Class>::raw_2<T0, T1>)));
      setMakePlacement(shared_callable_info(static_signature<void*, T0&& , T1&& >(&make<Class>::placement_2<T0, T1>)));
    }
  };
  template <typename Class, typename T0, typename T1, typename T2>
  struct TypedConstructorInfo<Class, T0, T1, T2, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil>:public ConstructorInfo{
    TypedConstructorInfo(){
      setMakeShared(shared_callable_info(static_signature<T0&& , T1&& , T2&& >(&make<Class>::shared_3<T0, T1, T2>)));
      setMakeRaw(shared_callable_info(static_signature<T0&& , T1&& , T2&& >(&make<Class>::raw_3<T0, T1, T2>)));
      setMakePlacement(shared_callable_info(static_signature<void*, T0&& , T1&& , T2&& >(&make<Class>::placement_3<T0, T1, T2>)));
    }
  };
  template <typename Class, typename T0, typename T1, typename T2, typename T3>
  struct TypedConstructorInfo<Class, T0, T1, T2, T3, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil>:public ConstructorInfo{
    TypedConstructorInfo(){
      setMakeShared(shared_callable_info(static_signature<T0&& , T1&& , T2&& , T3&& >(&make<Class>::shared_4<T0, T1, T2, T3>)));
      setMakeRaw(shared_callable_info(static_signature<T0&& , T1&& , T2&& , T3&& >(&make<Class>::raw_4<T0, T1, T2, T3>)));
      setMakePlacement(shared_callable_info(static_signature<void*, T0&& , T1&& , T2&& , T3&& >(&make<Class>::placement_4<T0, T1, T2, T3>)));
    }
  };
  template <typename Class, typename T0, typename T1, typename T2, typename T3, typename T4>
  struct TypedConstructorInfo<Class, T0, T1, T2, T3, T4, std::_Nil, std::_Nil, std::_Nil, std::_Nil, std::_Nil>:public ConstructorInfo{
    TypedConstructorInfo(){
      setMakeShared(shared_callable_info(static_signature<T0&& , T1&& , T2&& , T3&& , T4&& >(&make<Class>::shared_5<T0, T1, T2, T3, T4>)));
      setMakeRaw(shared_callable_info(static_signature<T0&& , T1&& , T2&& , T3&& , T4&& >(&make<Class>::raw_5<T0, T1, T2, T3, T4>)));
      setMakePlacement(shared_callable_info(static_signature<void*, T0&& , T1&& , T2&& , T3&& , T4&& >(&make<Class>::placement_5<T0, T1, T2, T3, T4>)));
    }
  };
  template <typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, std::_Nil, std::_Nil, std::_Nil, std::_Nil>:public ConstructorInfo{
    TypedConstructorInfo(){
      setMakeShared(shared_callable_info(static_signature<T0&& , T1&& , T2&& , T3&& , T4&& , T5&& >(&make<Class>::shared_6<T0, T1, T2, T3, T4, T5>)));
      setMakeRaw(shared_callable_info(static_signature<T0&& , T1&& , T2&& , T3&& , T4&& , T5&& >(&make<Class>::raw_6<T0, T1, T2, T3, T4, T5>)));
      setMakePlacement(shared_callable_info(static_signature<void*, T0&& , T1&& , T2&& , T3&& , T4&& , T5&& >(&make<Class>::placement_6<T0, T1, T2, T3, T4, T5>)));
    }
  };
  template <typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6, std::_Nil, std::_Nil, std::_Nil>:public ConstructorInfo{
    TypedConstructorInfo(){
      setMakeShared(shared_callable_info(static_signature<T0&& , T1&& , T2&& , T3&& , T4&& , T5&& , T6&& >(&make<Class>::shared_7<T0, T1, T2, T3, T4, T5, T6>)));
      setMakeRaw(shared_callable_info(static_signature<T0&& , T1&& , T2&& , T3&& , T4&& , T5&& , T6&& >(&make<Class>::raw_7<T0, T1, T2, T3, T4, T5, T6>)));
      setMakePlacement(shared_callable_info(static_signature<void*, T0&& , T1&& , T2&& , T3&& , T4&& , T5&& , T6&& >(&make<Class>::placement_7<T0, T1, T2, T3, T4, T5, T6>)));
    }
  };
  template <typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6, T7, std::_Nil, std::_Nil>:public ConstructorInfo{
    TypedConstructorInfo(){
      setMakeShared(shared_callable_info(static_signature<T0&& , T1&& , T2&& , T3&& , T4&& , T5&& , T6&& , T7&& >(&make<Class>::shared_8<T0, T1, T2, T3, T4, T5, T6, T7>)));
      setMakeRaw(shared_callable_info(static_signature<T0&& , T1&& , T2&& , T3&& , T4&& , T5&& , T6&& , T7&& >(&make<Class>::raw_8<T0, T1, T2, T3, T4, T5, T6, T7>)));
      setMakePlacement(shared_callable_info(static_signature<void*, T0&& , T1&& , T2&& , T3&& , T4&& , T5&& , T6&& , T7&& >(&make<Class>::placement_8<T0, T1, T2, T3, T4, T5, T6, T7>)));
    }
  };
  template <typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct TypedConstructorInfo<Class, T0, T1, T2, T3, T4, T5, T6, T7, T8, std::_Nil>:public ConstructorInfo{
    TypedConstructorInfo(){
      setMakeShared(shared_callable_info(static_signature<T0&& , T1&& , T2&& , T3&& , T4&& , T5&& , T6&& , T7&& , T8&& >(&make<Class>::shared_9<T0, T1, T2, T3, T4, T5, T6, T7, T8>)));
      setMakeRaw(shared_callable_info(static_signature<T0&& , T1&& , T2&& , T3&& , T4&& , T5&& , T6&& , T7&& , T8&& >(&make<Class>::raw_9<T0, T1, T2, T3, T4, T5, T6, T7, T8>)));
      setMakePlacement(shared_callable_info(static_signature<void*, T0&& , T1&& , T2&& , T3&& , T4&& , T5&& , T6&& , T7&& , T8&& >(&make<Class>::placement_9<T0, T1, T2, T3, T4, T5, T6, T7, T8>)));
    }
  };
}