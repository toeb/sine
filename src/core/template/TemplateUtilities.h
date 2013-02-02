#pragma once

#include <config.h>

namespace nspace{
  // todo replace issame by std::is_same
  template<typename T1,typename T2>
  class IsSame{
  public:
    static const bool Result=false;
  };
  template<typename T>
  class IsSame<T,T>{
  public:
    static const bool Result=true;
  };
  template<typename T1, typename T2> inline bool isSameType(){
    return IsSame<T1,T2>::Result;
  }

  template<typename T1,typename T2> inline bool isSameType(const T1 & a, const T2 & b){
    return IsSame<T1,T2>::Result;
  }



  template<typename T>
  struct class_of_member_method{};
  template<typename C, typename R, typename A1>
  struct class_of_member_method<R (C::*)(A1)>{
  typedef C type;
  };
template<typename C, typename R, typename A1, typename A2>
  struct class_of_member_method<R (C::*)(A1,A2)>{
  typedef C type;
  };
template<typename C, typename R, typename A1, typename A2, typename A3>
  struct class_of_member_method<R (C::*)(A1,A2,A3)>{
  typedef C type;
  };



  template< typename T >
  struct result_of_static_function {};

  template< typename R >
  struct result_of_static_function< R (*)() > {
    typedef R type;
  };

  template< typename R , typename Arg >
  struct result_of_static_function< R (*)(Arg) > {
    typedef R type;
  };

  template< typename R , typename Arg1, typename Arg2 >
  struct result_of_static_function< R (*)(Arg1,Arg2) > {
    typedef R type;
  };

  struct FalseType{
  static const bool value=false;
};
struct TrueType{

  static const bool value=true;
};




template <typename T>
T&& declval(); // vs2010 does not support std::declval - workaround http://stackoverflow.com/questions/11383722/adl-does-not-work-in-the-specific-situation

/*
  template< typename T >
struct result_of_ptmf {};

template< typename R, typename C, typename A1 >
struct result_of_ptmf< R (C::*)( A1 ) > {
    typedef R type;
};
template< typename R, typename C, typename A1, typename A2 >
struct result_of_ptmf< R (C::*)( A1 ,A2) > {
    typedef R type;
};
template< typename R, typename C, typename A1, typename A2,typename A3 >
struct result_of_ptmf< R (C::*)( A1 ,A2,A3) > {
    typedef R type;
};
*/

}
