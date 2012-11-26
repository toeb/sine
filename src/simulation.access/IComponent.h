#pragma once
#include <string>
#include <config.h>
#include <core.h>

namespace nspace{

  class IComponent : public virtual NamedObject, public virtual PropertyChangingObject{
    REFLECTABLE_OBJECT(IComponent);
  private:
    PROPERTY(std::string, DisplayName){}
    PROPERTY(std::string, Description){}
    PROPERTY(Object *, Parent){}
  public:
    IComponent(Object * parent=0):_Parent(parent),_DisplayName(""),_Description(""){}

    void toString(std::ostream & out)const{
      out << "Component{DisplayName='"<< getDisplayName()<<"', Description='"<< getDescription()<<"'";
      out << ", Parent='";
      if(getParent()){
        out << ", "<<*getParent();
      }else{
        out << "0" ;
      }
      out <<"'}";
      
    }

  };
}
