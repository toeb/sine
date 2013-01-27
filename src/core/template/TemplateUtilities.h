#pragma once

#include <config.h>

namespace nspace{
  
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



  template <typename ReturnType, typename Argument> ReturnType get_return_type(ReturnType (*)(Argument));
  template< class T >
  struct result_of_static_function {};

  template< class R, class ... A >
  struct result_of_static_function< R (*)( A ... ) > {
      typedef R type;
  };


}
