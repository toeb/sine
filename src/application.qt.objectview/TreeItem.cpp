#include "TreeItem.h"

using namespace nspace;
using namespace std;


TreeItem::TreeItem():_Object(0),_IsExpanded(false),_Model(0){}

void TreeItem::expand(){
  if(getIsExpanded())return; 
  doExpand();
  setIsExpanded(true);
}


string TreeItem::getDisplayName(){
  return getObject()->getType().getName();
}
string TreeItem::getDisplayValue(){
  return "";
}
string TreeItem::getEditValue(){
  return "";

}
string TreeItem::getDescription(){
  return "";
}
Type* TreeItem::getValueType(){
  return 0;
}
std::string TreeItem::getDisplayHint(){
  return "";
}
bool TreeItem::isEditable(){
  return false;
}

bool TreeItem::setEditValue(std::string str){
  return false;
}

TreeItem * TreeItem::parent(){
  if(predecessors().empty())return 0;
  return predecessors().first();
}

Set<TreeItem*> & TreeItem::children(){
  return successors();
}

int TreeItem::childNumber(){
  if(!parent())return 0;
  return parent()->children().indexOf(this);
}

void TreeItem::onPropertyChanged(const std::string & name){
  if(name=="Object")onObjectChanged();
}