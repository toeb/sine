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


}
