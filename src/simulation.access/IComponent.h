#pragma once
#include <string>
#include <config.h>
#include <simulation/ISimulationObject.h>

namespace nspace{

  class IComponent : public virtual ISimulationObject{
  private:
    std::string _displayName;
    std::string _desription;
    ISimulationObject * _parent;
  public:
    IComponent(ISimulationObject * parent=0):_parent(parent),_displayName(""),_desription(""){}
    void setDisplayName(const std::string & displayName){_displayName=displayName;}
    const std::string & displayName()const{return _displayName;}
    void setDescription(const std::string & despription){_desription = despription;}
    const std::string & description()const{return _desription;}
    void setParent(ISimulationObject * obj){_parent = obj;};
    ISimulationObject * parent(){return _parent;}

  };
}