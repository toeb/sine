#pragma once


#include <core.reflection/type/TypeInfo.h>

#include <string>
#include <iostream>

namespace nspace{
  

    // meta information for std::types

  META_DEFAULTCONSTRUCTOR(std::string);

  META(std::ostream);
  META(std::istream);
  META(std::iostream);
  META(std::ifstream);
  META(std::ofstream);
}

#include <functional>
namespace nspace{

  template<typename TResult>
  class TypeInfo<std::function<TResult(void)>> : public  TraitType<std::function<TResult(void)>> {
    TEMPLATEDSINGLETON(TypeInfo, std::function<TResult(void)>){ 
      setName(DS_INLINE_STRING("function<" << typeof(TResult)->getName()<<"(void)>"));      
    } 
  };
}

#include <memory>
namespace nspace{


  //std::memory
  template<typename T> 
  class TypeInfo<std::shared_ptr<T>>: public TraitType< std::shared_ptr<T>>{ 
    TEMPLATEDSINGLETON(TypeInfo, std::shared_ptr<T>){ 
      setName(DS_INLINE_STRING("std::shared_ptr<" << typeof(T)->getName()<<">"));
    } 
  };

  template<typename T>
  class TypeInfo<std::unique_ptr<T>>: public TraitType< std::unique_ptr<T>>{ 
    TEMPLATEDSINGLETON(TypeInfo, std::unique_ptr<T>){ 
      setName(DS_INLINE_STRING("std::unique_ptr<" << typeof(T)->getName()<<">"));
    } 
  };



}

// containers
#include <set>
#include <vector>
#include <map>
namespace nspace{
  template<typename TKey,typename TValue>
  class TypeInfo<std::map<TKey,TValue>> : public TraitType<std::map<TKey,TValue>>{
    TEMPLATEDSINGLETON(TypeInfo,std::map<TKey,TValue>){
      setName(DS_INLINE_STRING("std::map<"<<typeof(TKey)->getName()<<", "<<typeof(TValue)->getName()<<">"));
    }
  };
  template<typename T>
  class TypeInfo<std::set<T>> :public TraitType<std::set<T>>{
    TEMPLATEDSINGLETON(TypeInfo,std::set<T> ){
      setName(DS_INLINE_STRING("set<"<<typeof(T)->getName()<<">"));
    }
  };
  template<typename T>
  class TypeInfo<std::vector<T>> :public TraitType<std::vector<T>>{
    TEMPLATEDSINGLETON(TypeInfo,std::vector<T>){
      setName(DS_INLINE_STRING("vector<"<<typeof(T)->getName()<<">"));
    }
  };

}