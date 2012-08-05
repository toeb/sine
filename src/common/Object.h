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

class NamedObject  : public virtual Object{
  TYPED_OBJECT;
private:
  std::string * _name;
public:
  static const std::string & DefaultName;
  NamedObject(const std::string & name);
  NamedObject();
  ~NamedObject();
  const std::string & getName()const;
  bool hasName()const;
  void setName(const std::string & name);
  void setName(const std::string * name);
};

}