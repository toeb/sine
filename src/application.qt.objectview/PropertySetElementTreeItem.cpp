#include "PropertySetElementTreeItem.h"
using namespace nspace;
using namespace std;
bool SetElementTreeItem::setEditValue(std::string value){
  std::stringstream ss(value);
  return getParentSetItem()->getPropertySetInfo()->deserializeElement(getParentSetItem()->getPropertyObject(),getItemIndex(),  ss);

}
std::string SetElementTreeItem::getDisplayValue(){
  std::stringstream ss;
  ss<<"Item{";
  getParentSetItem()->getPropertySetInfo()->serializeElement(getParentSetItem()->getPropertyObject(),getItemIndex(),  ss);
  ss<<"}";
  return ss.str();
}

SetElementTreeItem::SetElementTreeItem(PropertySetTreeItem & parent, uint index):_ParentSetItem(&parent){
  setItemIndex(index);
  logInfo("creating SetElementTreeItem for item "<<index);
}
void SetElementTreeItem::doExpand(){

  auto setItem = getParentSetItem();
  auto setInfo = setItem->getPropertySetInfo();
  if(!setInfo->getIsPointerCollection())return;

  auto object = setInfo->elementAsObjectPointer(setItem->getPropertyObject(),getItemIndex());
  if(!object)return;
  auto item = getModel()->createItem(object);
  item->expand();
  successors()|=item->successors();


  
}
bool SetElementTreeItem::isEditable(){
  return true;
}
std::string SetElementTreeItem::getEditValue(){
  return "";
}


std::string SetElementTreeItem::getDescription(){
  std::stringstream ss;
  ss<<(getItemIndex()+1)<<". Item";
  return ss.str();
}
std::string SetElementTreeItem::getDisplayName(){
  std::stringstream ss;
  ss << getItemIndex();
  return ss.str();
}