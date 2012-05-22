#pragma once
#include <Visualization\UserInterface\IComponent.h>
namespace IBDS{
class IUserInterface{
public:
  virtual void addComponent(IComponent * component)=0;
};
}