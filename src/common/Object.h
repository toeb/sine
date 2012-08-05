#pragma once

#include <common/Config.h>
#include <ostream>
namespace nspace{
typedef const uint TypeId;

#define TYPED_OBJECT public: static const TypeId Type = __COUNTER__; virtual const TypeId getType()const {return Type;}

class Object{
private:
  virtual const TypeId getType()const=0;
  virtual void toString(std::ostream & out)const{out << "typeID: "<<getType();};
  std::ostream & operator<<(std::ostream & out)const{
    toString(out);
  }
};


}