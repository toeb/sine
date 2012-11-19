#include "ControlFactory.h"
#include <userinterface.qt.controls.h>
using namespace nspace;
using namespace std;

 ControlFactoryRepository * ControlFactoryRepository::defaultInstance(){
  static ControlFactoryRepository * instance =0;
  if(instance)return instance;
  instance = new ControlFactoryRepository;

  
  instance->Factories() |= new DynamicWidget::Factory<DoubleSpinBoxWidget, double>();
  instance->Factories() |= new DynamicWidget::Factory<BoolCheckboxWidget, bool>();



  return instance;
}
Set<ControlFactory*> ControlFactoryRepository::getFactoriesForType(const Type * type, const std::string & hints){
  Set<ControlFactory*> factories =Factories().subset([type](ControlFactory * factory){return factory->getDataType()->isSuperClassOf(*type);});
  //
  

  return factories;  
}

DynamicWidget * ControlFactoryRepository::createInstanceForType(const Type * type, const  string & hints){
  auto factories = Factories().subset([ type](ControlFactory * factory){return factory->getDataType()==type;});
  debugInfo("found "<< factories.size() << " factories matching type "<< *type); 
  // TODO match hints --> need min max function for set
  if(!factories)return 0;
  return factories.first()->createInstance();
}
DynamicWidget * ControlFactoryRepository::createInstanceForObject(Object * object, const std::string & hints){
  if(!object)return 0;
  auto control = createInstanceForType(&object->getType(),hints);
  if(!control)return 0;
  control->setDataContext(object);
  return control;
}