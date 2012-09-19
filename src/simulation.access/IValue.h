#pragma once
#include <functional>

#include <common/patterns/Composite.h>
#include <simulation.access/IComponent.h>

namespace nspace{


class IValue : public virtual IComponent{
public:  
  virtual bool isReadonly()const{return false;}
  virtual void toString(std::ostream & out)const{};
  virtual void fromString(std::istream & stream){};
  virtual void set(const void * value){};
  virtual void get(void * value){};
};

class Group : public virtual IComponent, public virtual Composite<IComponent>{
  
};

}
