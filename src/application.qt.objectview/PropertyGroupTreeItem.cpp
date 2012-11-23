#include "PropertyGroupTreeItem.h"


using namespace nspace;
using namespace std;


std::string PropertyGroupTreeItem::getDisplayName(){
  return getGroupName();
}
std::string PropertyGroupTreeItem::getDisplayValue(){
  return "";
}
std::string PropertyGroupTreeItem::getDescription(){
  return "Group of Properties";
}
std::string PropertyGroupTreeItem::getDisplayHint(){
  return "";
}
void PropertyGroupTreeItem::onObjectChanged(){

}
void PropertyGroupTreeItem:: doExpand(){

}