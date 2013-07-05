#pragma once
#include <config.h>
#include <tuple>
#include <iterator>
#include <memory>
#include <core/template/type_tuple.h>
namespace nspace{
  // default implementation assumes that Callable is a functor - only works for types with single operator()
  // overloaded operators are not supported
  template<typename Callable>
  struct callable_traits:public callable_traits<decltype(&Callable::operator())>{  
    static const bool is_functor = true;
    template<typename TContainer>
    static auto call(const Callable & callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      // decay type because it would be a reference
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      std::vector<argument_type> args;      
      args.push_back(&callable);    
      args.insert(args.end(),std::begin(container),std::end(container));
      return callable_traits<decltype(&Callable::operator())>::call(&Callable::operator(),args);
    }
    // assumes that the first element in container is the functor object and the following are its parameters
    template<typename TContainer>
    static auto call(const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      return callable_traits<decltype(&Callable::operator())>::call(&Callable::operator(),container);
    }
  };

  //calls any callable with any container of arguments (arguments can be converted from and to any type inkl rvalues)
  // expects first argument to be a pointer to the correct object if is_member is true
  template<typename Callable,typename TContainer>
  auto call_callable(Callable & callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
    return callable_traits<Callable>::call(callable, container);
  }
  // callable traits for 0 arguments
  template<typename Class, typename ReturnType>
  struct callable_traits<ReturnType(Class::*)()const>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)()const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)();
    }

  };

  template<typename Class>
  struct callable_traits<void(Class::*)()const>{
    typedef void return_type;
    typedef void(Class::*callable_type)()const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)();
      return nspace::Void();
    }

  };

  template<typename Class, typename ReturnType>
  struct callable_traits<ReturnType(Class::*)()>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)();
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)();
    }

  };

  template<typename Class>
  struct callable_traits<void(Class::*)()>{
    typedef void return_type;
    typedef void(Class::*callable_type)();
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)();
      return nspace::Void();
    }

  };

  template<typename ReturnType>
  struct callable_traits<ReturnType(*)()>{
    typedef ReturnType return_type;
    typedef ReturnType(*callable_type)();
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      return (*callable)();
    }

  };

  template<>
  struct callable_traits<void(*)()>{
    typedef void return_type;
    typedef void(*callable_type)();
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      (*callable)();
      return nspace::Void();
    }

  };

  // callable traits for 1 arguments
  template<typename Class, typename ReturnType, typename T0>
  struct callable_traits<ReturnType(Class::*)(T0)const>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>());
    }

  };

  template<typename Class, typename T0>
  struct callable_traits<void(Class::*)(T0)const>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>());
      return nspace::Void();
    }

  };

  template<typename Class, typename ReturnType, typename T0>
  struct callable_traits<ReturnType(Class::*)(T0)>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>());
    }

  };

  template<typename Class, typename T0>
  struct callable_traits<void(Class::*)(T0)>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>());
      return nspace::Void();
    }

  };

  template<typename ReturnType, typename T0>
  struct callable_traits<ReturnType(*)(T0)>{
    typedef ReturnType return_type;
    typedef ReturnType(*callable_type)(T0);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      return (*callable)((it+0)->convert<T0>());
    }

  };

  template<typename T0>
  struct callable_traits<void(*)(T0)>{
    typedef void return_type;
    typedef void(*callable_type)(T0);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      (*callable)((it+0)->convert<T0>());
      return nspace::Void();
    }

  };

  // callable traits for 2 arguments
  template<typename Class, typename ReturnType, typename T0, typename T1>
  struct callable_traits<ReturnType(Class::*)(T0, T1)const>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>());
    }

  };

  template<typename Class, typename T0, typename T1>
  struct callable_traits<void(Class::*)(T0, T1)const>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>());
      return nspace::Void();
    }

  };

  template<typename Class, typename ReturnType, typename T0, typename T1>
  struct callable_traits<ReturnType(Class::*)(T0, T1)>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>());
    }

  };

  template<typename Class, typename T0, typename T1>
  struct callable_traits<void(Class::*)(T0, T1)>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>());
      return nspace::Void();
    }

  };

  template<typename ReturnType, typename T0, typename T1>
  struct callable_traits<ReturnType(*)(T0, T1)>{
    typedef ReturnType return_type;
    typedef ReturnType(*callable_type)(T0, T1);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      return (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>());
    }

  };

  template<typename T0, typename T1>
  struct callable_traits<void(*)(T0, T1)>{
    typedef void return_type;
    typedef void(*callable_type)(T0, T1);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>());
      return nspace::Void();
    }

  };

  // callable traits for 3 arguments
  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2)const>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2>
  struct callable_traits<void(Class::*)(T0, T1, T2)const>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>());
      return nspace::Void();
    }

  };

  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2)>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2>
  struct callable_traits<void(Class::*)(T0, T1, T2)>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>());
      return nspace::Void();
    }

  };

  template<typename ReturnType, typename T0, typename T1, typename T2>
  struct callable_traits<ReturnType(*)(T0, T1, T2)>{
    typedef ReturnType return_type;
    typedef ReturnType(*callable_type)(T0, T1, T2);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      return (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>());
    }

  };

  template<typename T0, typename T1, typename T2>
  struct callable_traits<void(*)(T0, T1, T2)>{
    typedef void return_type;
    typedef void(*callable_type)(T0, T1, T2);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>());
      return nspace::Void();
    }

  };

  // callable traits for 4 arguments
  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2, typename T3>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2, T3)const>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2, T3)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2, T3>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2, typename T3>
  struct callable_traits<void(Class::*)(T0, T1, T2, T3)const>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2, T3)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2, T3>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>());
      return nspace::Void();
    }

  };

  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2, typename T3>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2, T3)>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2, T3);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2, typename T3>
  struct callable_traits<void(Class::*)(T0, T1, T2, T3)>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2, T3);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>());
      return nspace::Void();
    }

  };

  template<typename ReturnType, typename T0, typename T1, typename T2, typename T3>
  struct callable_traits<ReturnType(*)(T0, T1, T2, T3)>{
    typedef ReturnType return_type;
    typedef ReturnType(*callable_type)(T0, T1, T2, T3);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      return (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>(), (it+3)->convert<T3>());
    }

  };

  template<typename T0, typename T1, typename T2, typename T3>
  struct callable_traits<void(*)(T0, T1, T2, T3)>{
    typedef void return_type;
    typedef void(*callable_type)(T0, T1, T2, T3);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>(), (it+3)->convert<T3>());
      return nspace::Void();
    }

  };

  // callable traits for 5 arguments
  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2, T3, T4)const>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2, T3, T4)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4>
  struct callable_traits<void(Class::*)(T0, T1, T2, T3, T4)const>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2, T3, T4)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>());
      return nspace::Void();
    }

  };

  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2, T3, T4)>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2, T3, T4);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4>
  struct callable_traits<void(Class::*)(T0, T1, T2, T3, T4)>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2, T3, T4);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>());
      return nspace::Void();
    }

  };

  template<typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4>
  struct callable_traits<ReturnType(*)(T0, T1, T2, T3, T4)>{
    typedef ReturnType return_type;
    typedef ReturnType(*callable_type)(T0, T1, T2, T3, T4);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      return (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>(), (it+3)->convert<T3>(), (it+4)->convert<T4>());
    }

  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4>
  struct callable_traits<void(*)(T0, T1, T2, T3, T4)>{
    typedef void return_type;
    typedef void(*callable_type)(T0, T1, T2, T3, T4);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>(), (it+3)->convert<T3>(), (it+4)->convert<T4>());
      return nspace::Void();
    }

  };

  // callable traits for 6 arguments
  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5)const>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2, T3, T4, T5)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct callable_traits<void(Class::*)(T0, T1, T2, T3, T4, T5)const>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2, T3, T4, T5)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>());
      return nspace::Void();
    }

  };

  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5)>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2, T3, T4, T5);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct callable_traits<void(Class::*)(T0, T1, T2, T3, T4, T5)>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2, T3, T4, T5);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>());
      return nspace::Void();
    }

  };

  template<typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct callable_traits<ReturnType(*)(T0, T1, T2, T3, T4, T5)>{
    typedef ReturnType return_type;
    typedef ReturnType(*callable_type)(T0, T1, T2, T3, T4, T5);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      return (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>(), (it+3)->convert<T3>(), (it+4)->convert<T4>(), (it+5)->convert<T5>());
    }

  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  struct callable_traits<void(*)(T0, T1, T2, T3, T4, T5)>{
    typedef void return_type;
    typedef void(*callable_type)(T0, T1, T2, T3, T4, T5);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>(), (it+3)->convert<T3>(), (it+4)->convert<T4>(), (it+5)->convert<T5>());
      return nspace::Void();
    }

  };

  // callable traits for 7 arguments
  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6)const>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2, T3, T4, T5, T6)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>(), (it+7)->convert<T6>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct callable_traits<void(Class::*)(T0, T1, T2, T3, T4, T5, T6)const>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2, T3, T4, T5, T6)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>(), (it+7)->convert<T6>());
      return nspace::Void();
    }

  };

  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6)>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2, T3, T4, T5, T6);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>(), (it+7)->convert<T6>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct callable_traits<void(Class::*)(T0, T1, T2, T3, T4, T5, T6)>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2, T3, T4, T5, T6);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>(), (it+7)->convert<T6>());
      return nspace::Void();
    }

  };

  template<typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct callable_traits<ReturnType(*)(T0, T1, T2, T3, T4, T5, T6)>{
    typedef ReturnType return_type;
    typedef ReturnType(*callable_type)(T0, T1, T2, T3, T4, T5, T6);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      return (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>(), (it+3)->convert<T3>(), (it+4)->convert<T4>(), (it+5)->convert<T5>(), (it+6)->convert<T6>());
    }

  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  struct callable_traits<void(*)(T0, T1, T2, T3, T4, T5, T6)>{
    typedef void return_type;
    typedef void(*callable_type)(T0, T1, T2, T3, T4, T5, T6);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>(), (it+3)->convert<T3>(), (it+4)->convert<T4>(), (it+5)->convert<T5>(), (it+6)->convert<T6>());
      return nspace::Void();
    }

  };

  // callable traits for 8 arguments
  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7)const>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2, T3, T4, T5, T6, T7)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6, T7>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>(), (it+7)->convert<T6>(), (it+8)->convert<T7>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct callable_traits<void(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7)const>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2, T3, T4, T5, T6, T7)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6, T7>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>(), (it+7)->convert<T6>(), (it+8)->convert<T7>());
      return nspace::Void();
    }

  };

  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7)>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2, T3, T4, T5, T6, T7);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6, T7>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>(), (it+7)->convert<T6>(), (it+8)->convert<T7>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct callable_traits<void(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7)>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2, T3, T4, T5, T6, T7);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6, T7>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>(), (it+7)->convert<T6>(), (it+8)->convert<T7>());
      return nspace::Void();
    }

  };

  template<typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct callable_traits<ReturnType(*)(T0, T1, T2, T3, T4, T5, T6, T7)>{
    typedef ReturnType return_type;
    typedef ReturnType(*callable_type)(T0, T1, T2, T3, T4, T5, T6, T7);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6, T7>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      return (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>(), (it+3)->convert<T3>(), (it+4)->convert<T4>(), (it+5)->convert<T5>(), (it+6)->convert<T6>(), (it+7)->convert<T7>());
    }

  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  struct callable_traits<void(*)(T0, T1, T2, T3, T4, T5, T6, T7)>{
    typedef void return_type;
    typedef void(*callable_type)(T0, T1, T2, T3, T4, T5, T6, T7);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6, T7>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>(), (it+3)->convert<T3>(), (it+4)->convert<T4>(), (it+5)->convert<T5>(), (it+6)->convert<T6>(), (it+7)->convert<T7>());
      return nspace::Void();
    }

  };

  // callable traits for 9 arguments
  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)const>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2, T3, T4, T5, T6, T7, T8)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>(), (it+7)->convert<T6>(), (it+8)->convert<T7>(), (it+9)->convert<T8>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct callable_traits<void(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)const>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2, T3, T4, T5, T6, T7, T8)const;
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=true;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      const Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>(), (it+7)->convert<T6>(), (it+8)->convert<T7>(), (it+9)->convert<T8>());
      return nspace::Void();
    }

  };

  template<typename Class, typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct callable_traits<ReturnType(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)>{
    typedef ReturnType return_type;
    typedef ReturnType(Class::*callable_type)(T0, T1, T2, T3, T4, T5, T6, T7, T8);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      return (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>(), (it+7)->convert<T6>(), (it+8)->convert<T7>(), (it+9)->convert<T8>());
    }

  };

  template<typename Class, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct callable_traits<void(Class::*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)>{
    typedef void return_type;
    typedef void(Class::*callable_type)(T0, T1, T2, T3, T4, T5, T6, T7, T8);
    static const bool is_functor=false;
    static const bool is_member=true;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    //the first argument must be to a void * which points to a object of type Class
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      Class * object = (Class*)(void*)*it;
      if(!object){
        throw new std::exception("invalid call: first argument may not be null");
      }
      (object->*callable)((it+1)->convert<T0>(), (it+2)->convert<T1>(), (it+3)->convert<T2>(), (it+4)->convert<T3>(), (it+5)->convert<T4>(), (it+6)->convert<T5>(), (it+7)->convert<T6>(), (it+8)->convert<T7>(), (it+9)->convert<T8>());
      return nspace::Void();
    }

  };

  template<typename ReturnType, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct callable_traits<ReturnType(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)>{
    typedef ReturnType return_type;
    typedef ReturnType(*callable_type)(T0, T1, T2, T3, T4, T5, T6, T7, T8);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      return (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>(), (it+3)->convert<T3>(), (it+4)->convert<T4>(), (it+5)->convert<T5>(), (it+6)->convert<T6>(), (it+7)->convert<T7>(), (it+8)->convert<T8>());
    }

  };

  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
  struct callable_traits<void(*)(T0, T1, T2, T3, T4, T5, T6, T7, T8)>{
    typedef void return_type;
    typedef void(*callable_type)(T0, T1, T2, T3, T4, T5, T6, T7, T8);
    static const bool is_functor=false;
    static const bool is_member=false;
    static const bool is_const=false;

    struct arguments : public type_tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>{
    };
    static const int expected_arguments = arguments::size + (is_member?1:0);
    //expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,
    //also it must have a static method called Void() which returns the argument for void
    template<typename TContainer>
    static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      auto start = std::begin(container);
      auto end = std::end(container);
      if(std::distance(start,end)!=expected_arguments){
        throw new std::exception("invalid call: expected argument count differs from actual argument count");
      }
      auto it = start;
      (*callable)((it+0)->convert<T0>(), (it+1)->convert<T1>(), (it+2)->convert<T2>(), (it+3)->convert<T3>(), (it+4)->convert<T4>(), (it+5)->convert<T5>(), (it+6)->convert<T6>(), (it+7)->convert<T7>(), (it+8)->convert<T8>());
      return nspace::Void();
    }

  };


}
