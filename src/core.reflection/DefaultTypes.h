#pragma once

#include <core/reflection/TypeInfo.h>

#include <iostream>
#include <string>
#include <core/collection/containers/Set.h>

namespace nspace{



  /*
  DS_META_TRIVIAL_TYPE(int);
  DS_META_TRIVIAL_TYPE(double);
  DS_META_TRIVIAL_TYPE(bool);
  DS_META_TRIVIAL_TYPE(float);
  DS_META_TRIVIAL_TYPE(char);
  DS_META_TRIVIAL_TYPE(short);
  DS_META_TRIVIAL_TYPE(unsigned int);
  DS_META_TRIVIAL_TYPE(long);
  DS_META_TRIVIAL_TYPE(long long);
  DS_META_TRIVIAL_TYPE(unsigned char);

  DS_META_TRIVIAL_TYPE(std::string);


  META(std::ostream);
  META(std::istream);
  META(std::iostream);
  META(std::ifstream);
  META(std::ofstream);

  template<typename T>
  struct meta_type_name<Set<T>>{
    static const std::string & value(){
      static std::unique_ptr<std::string> ptr;
      if(!ptr){
        ptr = std::unique_ptr<std::string>(new std::string());    
        std::stringstream stream;
        stream << "Set<"<<meta_type_name<TypeInfo<T>::type>::value()<<">"<<std::endl;
        *ptr = stream.str();
      }
      return *ptr;
    }
  };
  
/*
template<typename T> DS_TYPENAME_METAFIELD(nspace::Set<T>){


}
*/
// meta information for default types  TODO: move to DefaultTypes.  but be sure to include correclty else TypedValue has compilation problems




//template<typename T> struct getTypeNameImpl<Set<T>>{ static const  std::string & getTypeName(){ static std::string name  = "Set<T>" ;return name; } };

/*
template<typename T>
class TypeInfo<std::vector<T>>:public Type{
TEMPLATEDSINGLETON(TypeInfo,<std::vector<T> >){
setCreateInstanceFunction([](){return new std::vector<T>();});
setDeleteInstanceFunction([](void * v){delete static_cast<std::vector<T>*>(v);});

setName(DS_INLINE_STRING("std::vector<"<<typeof(T)->getName()<<">"));
}
};
//need serializers
*/
}