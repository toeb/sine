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
  auto propertyInfo = &adapter->property();
  auto object = adapter->object();

  setPropertyOwner(object);
  setPropertyInfo(propertyInfo);

}

PropertyTreeItem::PropertyTreeItem(){
  debugInfo("creating PropertyTreeItem");
}
void PropertyTreeItem::doExpand(){
  debugInfo("expanding PropertyTreeItem "<< *this<<" " <<*getPropertyOwner());

  Object * ptr =  getPropertyInfo()->asObjectPointer(getPropertyOwner());
  if(!ptr)return;
  auto item = getModel()->createItem(ptr);
  item->expand();
  successors()|=item->successors();
}