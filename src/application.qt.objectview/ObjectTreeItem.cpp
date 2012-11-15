#include "ObjectTreeItem.h"

using namespace nspace;

ObjectTreeItem::ObjectTreeItem(){
  logInfo("creating ObjectTreeItem");
}
void ObjectTreeItem::doExpand(){
  debugInfo("Expanding ObjectTreeItem --> "<<*getObject());
  auto type =& getObject()->getType();

  for(int i=0; i < type->Members(); i++){
    auto member = type->Members().at(i);
    auto prop = dynamic_cast<const PropertyInfo*>(member);
    if(prop){
      auto propertyAdapter = new PropertyAdapter(getObject(),prop);
      children()|=getModel()->createItem(propertyAdapter);
      continue;
    }
    auto method = dynamic_cast<const MethodInfo*>(member);
    if(method){
      auto methodAdapter = new MethodAdapter(getObject(),method);
      children()|=getModel()->createItem(methodAdapter);
      continue;
    }

  }

}