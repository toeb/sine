#pragma once
#include <config.h>
#include <core/template/template_argument.h>
namespace nspace{
  template<typename T0=nspace::Nil, typename T1=nspace::Nil, typename T2=nspace::Nil, typename T3=nspace::Nil, typename T4=nspace::Nil, typename T5=nspace::Nil, typename T6=nspace::Nil, typename T7=nspace::Nil, typename T8=nspace::Nil, typename T9=nspace::Nil>
  struct type_tuple{
    static const size_t size =10;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.operator()<T0, 0>();
      functor.operator()<T1, 1>();
      functor.operator()<T2, 2>();
      functor.operator()<T3, 3>();
      functor.operator()<T4, 4>();
      functor.operator()<T5, 5>();
      functor.operator()<T6, 6>();
      functor.operator()<T7, 7>();
      functor.operator()<T8, 8>();
      functor.operator()<T9, 9>();
    }
  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct type_tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, nspace::Nil>{
    static const size_t size =9;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3, T4, T5, T6, T7, T8>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.operator()<T0, 0>();
      functor.operator()<T1, 1>();
      functor.operator()<T2, 2>();
      functor.operator()<T3, 3>();
      functor.operator()<T4, 4>();
      functor.operator()<T5, 5>();
      functor.operator()<T6, 6>();
      functor.operator()<T7, 7>();
      functor.operator()<T8, 8>();
    }
  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct type_tuple<T0, T1, T2, T3, T4, T5, T6, T7, nspace::Nil, nspace::Nil>{
    static const size_t size =8;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3, T4, T5, T6, T7>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.operator()<T0, 0>();
      functor.operator()<T1, 1>();
      functor.operator()<T2, 2>();
      functor.operator()<T3, 3>();
      functor.operator()<T4, 4>();
      functor.operator()<T5, 5>();
      functor.operator()<T6, 6>();
      functor.operator()<T7, 7>();
    }
  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct type_tuple<T0, T1, T2, T3, T4, T5, T6, nspace::Nil, nspace::Nil, nspace::Nil>{
    static const size_t size =7;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3, T4, T5, T6>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.operator()<T0, 0>();
      functor.operator()<T1, 1>();
      functor.operator()<T2, 2>();
      functor.operator()<T3, 3>();
      functor.operator()<T4, 4>();
      functor.operator()<T5, 5>();
      functor.operator()<T6, 6>();
    }
  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct type_tuple<T0, T1, T2, T3, T4, T5, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil>{
    static const size_t size =6;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3, T4, T5>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.operator()<T0, 0>();
      functor.operator()<T1, 1>();
      functor.operator()<T2, 2>();
      functor.operator()<T3, 3>();
      functor.operator()<T4, 4>();
      functor.operator()<T5, 5>();
    }
  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4>
  struct type_tuple<T0, T1, T2, T3, T4, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil>{
    static const size_t size =5;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3, T4>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.operator()<T0, 0>();
      functor.operator()<T1, 1>();
      functor.operator()<T2, 2>();
      functor.operator()<T3, 3>();
      functor.operator()<T4, 4>();
    }
  };

  template<typename T0, typename T1, typename T2, typename T3>
  struct type_tuple<T0, T1, T2, T3, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil>{
    static const size_t size =4;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2, T3>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.operator()<T0, 0>();
      functor.operator()<T1, 1>();
      functor.operator()<T2, 2>();
      functor.operator()<T3, 3>();
    }
  };

  template<typename T0, typename T1, typename T2>
  struct type_tuple<T0, T1, T2, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil>{
    static const size_t size =3;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1, T2>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.operator()<T0, 0>();
      functor.operator()<T1, 1>();
      functor.operator()<T2, 2>();
    }
  };

  template<typename T0, typename T1>
  struct type_tuple<T0, T1, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil>{
    static const size_t size =2;
    template<size_t i> 
    struct at:public template_argument<i, T0, T1>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.operator()<T0, 0>();
      functor.operator()<T1, 1>();
    }
  };

  template<typename T0>
  struct type_tuple<T0, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil>{
    static const size_t size =1;
    template<size_t i> 
    struct at:public template_argument<i, T0>{};
    template<typename Functor>
    static void for_each(Functor & functor){
      functor.operator()<T0, 0>();
    }
  };

  template<>
  struct type_tuple<nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil, nspace::Nil>{
    static const size_t size =0;
    template<size_t i> 
    struct at:public template_argument<i>{};
    template<typename Functor>
    static void for_each(Functor & functor){
    }
  };


}
