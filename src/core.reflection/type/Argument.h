#pragma once
#include <config.h>
#include <memory>

namespace nspace{
  class Type;


  template<typename T,bool is_rvalue=std::is_rvalue_reference<T>::value,bool is_ref = std::is_reference<T>::value>
  struct choose_reference{
    template<typename Arg>
    static T choose(Arg& arg){
      return arg.ref<T>();
    }
  };
  template<typename T>
  struct choose_reference<T,true,true>{
    template<typename Arg>
    static typename std::remove_reference<T>::type  choose(Arg &arg){
      typename std::remove_reference<T>::type val = arg;
      return val;
    }
  };
  template<typename T>
  struct choose_reference<T,false,true>{
    template<typename Arg>
    static typename std::remove_reference<T>::type choose(Arg& arg){
      typename std::remove_reference<T>::type val = arg;
      return val;
    }
  };
  //todo rename to ObjectHandle
  struct Argument{
    Argument(const nspace::Void & v);
    template<typename T> Argument(const T & data);
    template<typename T> Argument(std::shared_ptr<T> data);
    Argument(std::shared_ptr<void> data, const Type * type);
    Argument();
    ~Argument();

    // obsolete use Void() instead
    static const Argument & VoidArgument();    
    static const Argument & Void();    

    bool isValid()const;
    template<typename T> operator const T & ()const;
    template<typename T> operator T & ();    
    //template<typename T> operator T &&()const;

    template<typename T> const T& ref()const;
    template<typename T> T& ref();
    template<typename T> T rvalue()const;

    template<typename T> auto convert ()const->decltype(choose_reference<T>::choose(Argument()));


    template<typename T> operator std::shared_ptr<const T>()const;
    template<typename T> operator std::shared_ptr<T>();

    template<typename T> std::shared_ptr<T> cast();
    template<typename T> std::shared_ptr<const T> cast()const;

    std::shared_ptr<void> data;
    const Type * type;
  };
}
