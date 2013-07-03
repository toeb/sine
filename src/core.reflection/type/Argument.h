#pragma once
#include <config.h>
#include <memory>

namespace nspace{
  class Type;
  //todo rename to ObjectHandle
  struct Argument{
    template<typename T> Argument(const T & data);
    template<typename T> Argument(std::shared_ptr<T> data);
    Argument(std::shared_ptr<void> data, const Type * type);
    Argument();
    ~Argument();

    static const Argument & VoidArgument();    
    bool isValid()const;
    template<typename T> operator const T & ()const;
    template<typename T> operator T & ();
    
    template<typename T> operator T &&()const;



    template<typename T> operator std::shared_ptr<const T>()const;
    template<typename T> operator std::shared_ptr<T>();

    template<typename T> std::shared_ptr<T> cast();
    template<typename T> std::shared_ptr<const T> cast()const;

    std::shared_ptr<void> data;
    const Type * type;
  };
}
