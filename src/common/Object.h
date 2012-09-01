#pragma once

#include <common/Config.h>
#include <ostream>
#include <string>
namespace nspace{



  
typedef const uint TypeId;
//typedef const uint ObjectId;

#define TYPED_OBJECT public: static const TypeId Type = __COUNTER__; virtual inline const TypeId getType()const {return Type;}

class Object{
TYPED_OBJECT;
private:
    
  virtual void toString(std::ostream & out)const{out << "typeID: "<<getType();};
  std::ostream & operator<<(std::ostream & out)const{
    toString(out);
  }
  std::string toString()const;
};



}