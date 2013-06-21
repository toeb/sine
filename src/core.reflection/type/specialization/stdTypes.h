#pragma once


#include <core.reflection/type/TypeInfo.h>
#include <core.reflection/type/TypeInfo.implementation.template.h>
#include <string>
#include <iostream>
#include <fstream>

namespace nspace{


  // meta information for std::types

  META(::std::string);
  //DS_DEFAULT_CONSTRUCTOR_ENABLE(std::string);
  

  META(::std::ostream);
  META(::std::istream);
  META(::std::iostream);
  META(::std::ifstream);
  META(::std::ofstream);
}

#include <functional>
namespace nspace{

  template<typename TResult>
  class TypeInfo<std::function<TResult(void)>> : public  TraitType<std::function<TResult(void)>> {
    TEMPLATEDSINGLETON(TypeInfo, std::function<TResult(void)>):
      TraitType(DS_INLINE_STRING("std::function<" << typeof(TResult)->getFullyQualifiedName()<<"(void)>"),0){       
    } 
  };
}

#include <memory>
namespace nspace{


  //std::memory
  template<typename T> 
  class TypeInfo<std::shared_ptr<T>>: public TraitType< std::shared_ptr<T>>{ 
    TEMPLATEDSINGLETON(TypeInfo, std::shared_ptr<T>):
      TraitType(DS_INLINE_STRING("std::shared_ptr<" << typeof(T)->getFullyQualifiedName()<<">")){ 
    } 
  };

  template<typename T>
  class TypeInfo<std::unique_ptr<T>>: public TraitType< std::unique_ptr<T>>{ 
    TEMPLATEDSINGLETON(TypeInfo, std::unique_ptr<T>):
      TraitType(DS_INLINE_STRING("std::unique_ptr<" << typeof(T)->getFullyQualifiedName()<<">")){ 

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
    TEMPLATEDSINGLETON(TypeInfo,std::map<TKey,TValue>):TraitType(DS_INLINE_STRING("::std::std::map<"<<typeof(TKey)->getFullyQualifiedName()<<", "<<typeof(TValue)->getFullyQualifiedName()<<">"),0){}
  };
  template<typename T>
  class TypeInfo<std::set<T>> :public TraitType<std::set<T>>{
    TEMPLATEDSINGLETON(TypeInfo,std::set<T> ):TraitType(DS_INLINE_STRING("::std::set<"<<typeof(T)->getFullyQualifiedName()<<">")){
    }
  };
  template<typename T>
  class TypeInfo<std::vector<T>> :public TraitType<std::vector<T>>{
    TEMPLATEDSINGLETON(TypeInfo,std::vector<T>):TraitType(DS_INLINE_STRING("::std::vector<"<<typeof(T)->getFullyQualifiedName()<<">")){
      
    }
  };

}