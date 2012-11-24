#include "ObjectPropertyViewModel.h"

#include <application.qt.objectview/ObjectTreeItem.h>
#include <application.qt.objectview/PropertyTreeItem.h>
#include <application.qt.objectview/PropertySetTreeItem.h>
#include <application.qt.objectview/MethodTreeItem.h>
using namespace nspace;






QVariant ObjectPropertyViewModel::headerData ( int section, Qt::Orientation orientation, int role) const{
  if(role!=Qt::DisplayRole)return QVariant();
  if(orientation==Qt::Horizontal){
    if(section==0)return QVariant::fromValue(tr("Property"));
    if(section==1)return QVariant::fromValue(tr("Value"));
  }
  if(orientation==Qt::Vertical){
    return QVariant::fromValue(tr("lol"));
  }
  return QVariant();
}

void ObjectPropertyViewModel::onPropertyChanged(const std::string  & name){
  if(name=="RootItem") reset();      
}
TreeItem* ObjectPropertyViewModel::createItem(Object * object){
  auto methodAdpater = dynamic_cast<MethodAdapter*>(object);
  if(methodAdpater){
    auto item = new MethodTreeItem();
    item->setObject(methodAdpater);
    item->setModel(this);
    return item;
  }


  auto propertyAdapter = dynamic_cast<PropertyAdapter*>(object);
  if(propertyAdapter){
    auto propertySetInfo =  dynamic_cast<const PropertySetInfo*>(propertyAdapter->getPropertyInfo());
    if(propertySetInfo){
      auto item = new PropertySetTreeItem();
      item->setObject(propertyAdapter);
      item->setModel(this);
      return item;
    }
    
    auto item = new PropertyTreeItem();
    item->setObject(propertyAdapter);
    item->setModel(this);
    return item;
  }
  

  auto item = new ObjectTreeItem();
  item->setObject(object);
  item->setModel(this);
  return item;

}

void ObjectPropertyViewModel::propertyChanging(TreeItem*, RootItem){
  debugInfo("RootItem changed - resetting view");
  reset();
}
void ObjectPropertyViewModel::propertyChanging(Object *,CurrentObject){
  if(oldvalue){
    auto pc = dynamic_cast<PropertyChangingObject*>(oldvalue);
    if(pc)pc->listeners()/=this;
  }
  if(newvalue){        
    auto pc = dynamic_cast<PropertyChangingObject*>(newvalue);
    if(pc)pc->listeners()|=this;
  }
  debugInfo("CurrentObject changed");

  auto item = createItem(newvalue);
  setRootItem(item);
}


void ObjectPropertyViewModel::itemChanged(TreeItem * treeItem){
  emit layoutChanged();
  //reset();
}
TreeItem* ObjectPropertyViewModel::getItem(const QModelIndex & index)const{
  TreeItem* item=0;
  if(index.isValid()){
    item = static_cast<TreeItem*>(index.internalPointer());
  }

  if(!item)item = getRootItem();
  if(item)item->setModelIndex(index);
  return item;
}
ObjectPropertyViewModel::ObjectPropertyViewModel():_CurrentObject(0),_RootItem(0){}

QModelIndex  ObjectPropertyViewModel::parent( const QModelIndex& index ) const {
  if(!index.isValid())return QModelIndex();
  auto item = getItem(index);
  auto parent = item->parent();
  if(!parent)return QModelIndex();
  if(parent==getRootItem())return QModelIndex();
  return createIndex(parent->childNumber(),0,parent);

}
bool ObjectPropertyViewModel::hasChildren(const QModelIndex& parent)const{      
  auto item = getItem(parent);
  if(!item)return false;
  
  item->successors().addObjectObserver(const_cast<ObjectPropertyViewModel*>(this));
  item->expand();
  
  return !item->successors().empty();
}

void ObjectPropertyViewModel::onChange(Observable * observable){
  emit layoutChanged();
}
const PropertyInfo* ObjectPropertyViewModel::getProperty(const QModelIndex & index)const{
  if(!index.isValid())return 0;
  auto object = getCurrentObject();
  if(!object)return 0;
  int row = index.row();
  auto prop = object->getType().Properties().at(row);      
  return prop;
}

bool ObjectPropertyViewModel::setData(const QModelIndex & index, const QVariant & value, int role){
  auto item = getItem(index);
  if(!item)return false;
  std::string stdstring = value.toString().toUtf8().constData();
  bool result = item->setEditValue(stdstring);
  if(result)emit dataChanged(index,index);
  return result;

}

Qt::ItemFlags ObjectPropertyViewModel::flags(const QModelIndex & index)const{
  auto item = getItem(index);

  if(index.column()==1 && item&&item->isEditable()){
    Qt::ItemFlags result = QAbstractItemModel::flags(index)|Qt::ItemIsEditable;
    return result;
  }
  return QAbstractItemModel::flags(index);
}
QModelIndex ObjectPropertyViewModel::index(int row, int column, const QModelIndex & parent)const{    
  auto parentItem= getItem(parent);
  if(!parentItem)return QModelIndex();
  auto childItem = parentItem->children().at(row);
  if(!childItem) return QModelIndex();
  return createIndex(row,column,childItem);

}

int  ObjectPropertyViewModel::rowCount(const QModelIndex &parent)const{
  auto parentItem = getItem(parent);
  return parentItem->children();
}
int  ObjectPropertyViewModel::columnCount(const QModelIndex &parent)const{
  if(!getItem(parent))return 0;
  return 2;
}
QVariant  ObjectPropertyViewModel::data(const QModelIndex & index, int role)const{      
  auto item  =getItem(index);
  if(index.column()==0){
    switch(role){
    case Qt::DisplayRole:
      return QVariant::fromValue(tr(item->getDisplayName().c_str()));
    case Qt::WhatsThisRole:
    case Qt::ToolTipRole:
      return QVariant::fromValue(tr(item->getDescription().c_str()));
    }

  }
  if(index.column()==1){

    switch(role){
    case (Qt::UserRole+5):
      return qVariantFromValue((void*)item->getObject());
      break;
    case Qt::DisplayRole:    {  
      // todo return custom qvariant if needed
      auto type = item->getValueType();
      if(type){
        return QVariant();
      }
      return QVariant::fromValue(tr(item->getDisplayValue().c_str()));
                             }
    case Qt::EditRole:
      return QVariant::fromValue(tr(item->getEditValue().c_str()));
    case Qt::WhatsThisRole:
    case Qt::ToolTipRole:
      return QVariant::fromValue(tr(item->getDescription().c_str()));
    }
  }
  return QVariant();
}


void ObjectPropertyViewModel::onPropertyChanged(Object * sender, const std::string & name){
  //if(result)emit dataChanged(index,index);
  auto object = getCurrentObject();
  const Set<const PropertyInfo*> properties = object->getType().Properties();

  for(int i=0; i < properties; i++){
    if(properties.at(i)->getName()==name){
      auto idx = index(i,1);
      emit dataChanged(idx,idx);
    }
  }
}