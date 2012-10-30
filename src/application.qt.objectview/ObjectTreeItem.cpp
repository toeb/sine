#include "ObjectTreeItem.h"

using namespace nspace;

ObjectTreeItem::ObjectTreeItem(){
  logInfo("creating ObjectTreeItem");
}
void ObjectTreeItem::doExpand(){
  debugInfo("Expanding ObjectTreeItem --> "<<*getObject());
  auto type =& getObject()->getTypeData();

  for(int i=0; i < type->Properties(); i++){
    auto propertyAdapter = new PropertyAdapter(getObject(),*type->Properties().at(i));
    children()|=getModel()->createItem(propertyAdapter);
  }

}