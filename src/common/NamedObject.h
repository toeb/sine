#pragma once


#include <string>

namespace mbslib{
  
  class NamedObject{
  private:
    std::string _name;
  public:
    bool operator == (const std::string & name)const{
      return _name==name;
    }

    bool operator==(const char * name)const{
      return *this==std::string(name);
    }

    bool friend operator==(const NamedObject * obj, const std::string & name){
      return *obj==name;
    }

    const std::string & name()const{
      return _name;
    }
    void setName(const std::string & name){
      _name = name;
      nameChanged(_name);
    }
  protected:
    virtual void nameChanged(const std::string& newName){}
  };
}