#include "ControlFactory.h"
#include <userinterface.qt.controls.h>
using namespace nspace;
using namespace std;

 ControlFactoryRepository * ControlFactoryRepository::defaultInstance(){
  static ControlFactoryRepository * instance =0;
  if(instance)return instance;
  instance = new ControlFactoryRepository;

  
  instance->Factories() |= new ValueWidget::Factory<DoubleSpinBoxWidget, double>();
  instance->Factories() |= new ValueWidget::Factory<BoolCheckboxWidget, bool>();
  instance->Factories() |= new ActionWidget::Factory();


  return instance;
}
Set<ControlFactory*> ControlFactoryRepository::getApplicableFactories(const Type * type,Object * object, const std::string & hints){  
  auto factories = Factories().subset([ type,object,&hints](ControlFactory * factory){
    return factory->match(type,object,hints);
  });
  return factories;
}

DynamicWidget * ControlFactoryRepository::createWidget(const Type * type,Object * object, const std::string & hints){
  auto factories = getApplicableFactories(type,object,hints);
  if(!factories.size())return 0;
  return factories.first()->createInstance();
}