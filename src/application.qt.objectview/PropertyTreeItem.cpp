#include "PropertyTreeItem.h"
#include <application.qt.objectview/ObjectTreeItem.h>
using namespace nspace;

bool PropertyTreeItem::isEditable(){
  return getPropertyInfo()->getHasSetter();
}
std::string PropertyTreeItem::getEditValue(){
  return "";
}
bool PropertyTreeItem::setEditValue(std::string value){
  std::stringstream ss(value);
  return getPropertyInfo()->deserialize(getPropertyOwner(),ss);
}

std::string PropertyTreeItem::getDescription(){
  std::stringstream ss;
  auto info = getPropertyInfo();
  ss << info->getDescription();
  /* if(info->getDefaultValue()){
  ss << "(Default Value: '"<< <<"')";
  }*/
  return ss.str();

  return getPropertyInfo()->getDescription();
}
std::string PropertyTreeItem::getDisplayName(){
  return getPropertyInfo()->getDisplayName();
}
std::string PropertyTreeItem::getDisplayValue(){
  std::stringstream ss;
  getPropertyInfo()->serialize(getPropertyOwner(),ss);
  return ss.str();
}
void PropertyTreeItem::onObjectChanged(){
  auto adapter = dynamic_cast<PropertyAdapter*>(getObject());
  if(!adapter){
    logError("object is not an adapter");
    return;
  }
  auto propertyInfo = adapter->getPropertyInfo();
  auto object = adapter->getOwner();

  setPropertyOwner(object);
  setPropertyInfo(propertyInfo);
}

PropertyTreeItem::PropertyTreeItem(){
  setLoggingLevel(1);
  debugInfo("creating PropertyTreeItem");
}
void PropertyTreeItem::doExpand(){
  debugInfo("expanding PropertyTreeItem "<< *this<<" " <<*getPropertyOwner());

  getPropertyInfo()->addObserver(getPropertyOwner(), this);

  //Object * ptr =  getPropertyInfo()->asObjectPointer(getPropertyOwner());

  onChange(0);
  /*
  if(!ptr)return;
  auto item = getModel()->createItem(ptr);
  item->expand();
  successors()|=item->successors();*/
}

void PropertyTreeItem::onChange(Observable* sender){
  Object * ptr =  getPropertyInfo()->asObjectPointer(getPropertyOwner());
  successors().clear();
  if(!ptr)return;
  auto item = getModel()->createItem(ptr);
  item->expand();
  successors()|=item->successors();
}