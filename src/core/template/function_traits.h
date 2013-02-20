#pragma once

#include <core/preprocessor/Reduce.h>
#include <tuple>
#include <utility>
#include <cstdlib>
namespace nspace{



// ifdef msvc10 -> no template
#define nested_template template

  // I got the code from http://stackoverflow.com/questions/7943525/is-it-possible-to-figure-out-the-parameter-type-and-return-type-of-a-lambda
  // by user KennyTM.  I modified it so that it works without variadic templates for up to 4 arguments

template <typename T>
struct function_traits
    : public function_traits< decltype(&T::operator())>
{
  
};


#define DS_ADD_TYPENAME(X) typename X
#define DS_FUNCTIONTRAITS(...)                                                                                     \
template <typename ClassType, typename ReturnType, DS_REDUCE_COMMA(DS_ADD_TYPENAME,__VA_ARGS__)>                     \
struct function_traits<ReturnType(ClassType::*)(DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__) ) const>                          \
{                                                                                                                    \
  enum { arity = DS_NUM_ARGS(__VA_ARGS__) };                                                                         \
    typedef ReturnType result_type;                                                                                  \
    template <size_t i>                                                                                              \
    struct arg                                                                                                       \
    {                                                                                                                \
        typedef typename std::tuple_element<i, std::tuple<DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__)> >::type type;         \
    };                                                                                                               \
};
template <typename ClassType, typename ReturnType>                   
struct function_traits<ReturnType(ClassType::*)() const>                      
{                                                                                                                  
  enum { arity = 0 };                                                                       
    typedef ReturnType result_type;                                                                                
    template <size_t i>                                                                                            
    struct arg                                                                                                     
    {                                                                                                              
        typedef void type;      
    };                                                                                                             
};

DS_FUNCTIONTRAITS(A1)
DS_FUNCTIONTRAITS(A1,A2)
DS_FUNCTIONTRAITS(A1,A2,A3)
DS_FUNCTIONTRAITS(A1,A2,A3,A4)
DS_FUNCTIONTRAITS(A1,A2,A3,A4,A5)


}

