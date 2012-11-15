#include "MethodTreeItem.h"
#include <application.qt.objectview/ObjectTreeItem.h>
using namespace nspace;


std::string MethodTreeItem::getDescription(){
  std::stringstream ss;
  auto info = getMethodInfo();
  ss << info->getDescription();
  /* if(info->getDefaultValue()){
       ss << "(Default Value: '"<< <<"')";
     }*/
  return ss.str();

  return getMethodInfo()->getDescription();
}
std::string MethodTreeItem::getDisplayName(){
  return getMethodInfo()->getDisplayName();
}
std::string MethodTreeItem::getDisplayValue(){
  std::stringstream ss;
  ss << "[Method]";
  return ss.str();
}
void MethodTreeItem::onObjectChanged(){
  auto adapter = dynamic_cast<MethodAdapter*>(getObject());
  if(!adapter){
      logError("object is not an adapter");
      return;
    }
  auto methodInfo = &adapter->methodInfo();
  auto object = adapter->object();

  setPropertyOwner(object);
  setMethodInfo(methodInfo);

}

MethodTreeItem::MethodTreeItem(){
  debugInfo("creating MethodTreeItem");
}
void MethodTreeItem::doExpand(){
 
}
