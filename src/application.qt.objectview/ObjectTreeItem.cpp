#include "ObjectTreeItem.h"
#include <application.qt.objectview/PropertyGroupTreeItem.h>
using namespace nspace;

ObjectTreeItem::ObjectTreeItem(){
  logInfo("creating ObjectTreeItem");
}
void ObjectTreeItem::doExpand(){
  debugInfo("Expanding ObjectTreeItem --> "<<*getObject());
  auto type =& getObject()->getType();

  Set<PropertyGroupTreeItem*> groups;
  Set<TreeItem*> directChildren;
  for(int i=0; i < type->Members(); i++){
    auto member = type->Members().at(i);

    TreeItem * child=0;
    auto prop = dynamic_cast<const PropertyInfo*>(member);
    auto method = dynamic_cast<const MethodInfo*>(member);
    if(prop){
      auto propertyAdapter = new PropertyAdapter(getObject(),prop);
      child =getModel()->createItem(propertyAdapter);
    }else if(method){
      auto methodAdapter = new MethodAdapter(getObject(),method);
      child=getModel()->createItem(methodAdapter);
    }
    if(!child)continue;

    std::string groupName = "";
    if(member->getGroupName()!=""){
      groupName = member->getGroupName();
    }

    if(groupName=="" && member->getOwningType()&&member->getOwningType()!=type){
      groupName = member->getOwningType()->getName();
    }

    auto group = groups.first([&groupName](PropertyGroupTreeItem* item){
      return item->getGroupName()==groupName;
    });

    if(groupName != "" && !group){
      group = new PropertyGroupTreeItem();
      group->setModel(getModel());
      group->setGroupName(groupName);
      groups|=group;
    }
    if(group){
      group->children()|=child;
      continue;
    }
    directChildren|=child;
  }
  children()|=groups.subset<TreeItem*>();
  children()|=directChildren;
}