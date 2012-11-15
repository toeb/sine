#include "PropertySetTreeItem.h"
#include <application.qt.objectview/PropertySetElementTreeItem.h>
using namespace nspace;

 void PropertySetTreeItem::propertyChanging(const PropertySetInfo*, PropertySetInfo){
    if(oldvalue){
      oldvalue->removeObserver(getPropertyObject(),this);      
    }
    if(newvalue){
      newvalue->addObserver(getPropertyObject(),this);
    }
  
  }
  std::string PropertySetTreeItem::getDisplayName(){
    return getPropertySetInfo()->getDisplayName();
  }
  std::string PropertySetTreeItem::getDisplayValue(){
    std::stringstream ss;
    ss<<"Set{";
    getPropertySetInfo()->serialize(getPropertyObject(),ss);
    ss<<"}";
    return ss.str();
  }
  bool PropertySetTreeItem::isEditable(){
    return true;
  }
  std::string PropertySetTreeItem::getEditValue(){
    return "";
  }
  bool PropertySetTreeItem::setEditValue(std::string value){
    std::stringstream ss(value);
    return getPropertySetInfo()->deserialize(getPropertyObject(),ss);
  }
  
  void PropertySetTreeItem::onChange(Observable* sender){
    debugInfo("property of underlying object changed");
    resetList();
    refresh();
  }
  PropertySetTreeItem::PropertySetTreeItem():_PropertySetInfo(0),_PropertyObject(0){
    debugInfo("creating PropertySetTreeItem");
  }

  void PropertySetTreeItem::onObjectChanged(){
    auto adapter = dynamic_cast<PropertyAdapter*>(getObject());
    if(!adapter){
      logError("object is not an adapter");
      return;
    }
    auto propertyInfo = adapter->getPropertyInfo();
    auto propertySetInfo = dynamic_cast<const PropertySetInfo*>(propertyInfo);
    auto object = reinterpret_cast<Object*>( adapter->getOwner());
    if(!propertySetInfo){
      logError("no property set info available");
      return;
    }
    setPropertyObject(object);
    setPropertySetInfo(propertySetInfo);

  }
  void PropertySetTreeItem::refresh(){
    
    getModel()->itemChanged(this);
  }
  void PropertySetTreeItem::resetList(){
    debugInfo("resetting set list" );
    children().clear();
    int numberOfElements= getPropertySetInfo()->getElementCount(getPropertyObject());
    
    for(int i=0; i < numberOfElements; i++){
      auto elementItem= new SetElementTreeItem(*this,i);
      elementItem->setModel(getModel());
      children()|=elementItem;
    }

  }
  void PropertySetTreeItem::doExpand(){
    int numberOfElements= getPropertySetInfo()->getElementCount(getPropertyObject());
    
    debugInfo("Expanding PropertySetTreeItem adding "<<numberOfElements <<" elements" );
    resetList();
  }