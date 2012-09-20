#pragma once

#include <core/Object.h>
#include <string>

namespace nspace{
class NamedObject  : public virtual Object{
  TYPED_OBJECT;
private:
  std::string * _name;
public:
  static const std::string & DefaultName;
  NamedObject(const std::string & name);
  NamedObject();
  ~NamedObject();
  const std::string & name()const;
  bool hasName()const;
  void setName(const std::string & name);
  void setName(const std::string * name);

    bool operator == (const std::string & str)const{
      return name()==str;
    }

    bool operator==(const char * str)const{
      return *this==std::string(str);
    }

    bool friend operator==(const NamedObject * obj, const std::string & name){
      return *obj==name;
    }
protected:
    virtual void nameChanged(const std::string& newName){}
};

}