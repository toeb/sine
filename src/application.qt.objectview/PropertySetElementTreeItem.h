#pragma once
#pragma once;
#include <application.qt.objectview/TreeItem.h>
#include <core.logging/Log.h>
#include <core/Reflection.h>
#include <application.qt.objectview/PropertySetTreeItem.h>

namespace nspace{
  
class SetElementTreeItem :public TreeItem, public virtual PropertyChangingObject, public virtual Log{
  REFLECTABLE_OBJECT(SetElementTreeItem);
  PROPERTY(PropertySetTreeItem*, ParentSetItem){}
  PROPERTY(uint, ItemIndex){}
public:
  SetElementTreeItem(PropertySetTreeItem & parent, uint index);
  void doExpand();
  virtual bool isEditable();
  virtual std::string getEditValue();
  virtual bool setEditValue(std::string value);
  virtual std::string getDisplayValue();

  virtual std::string getDescription();
  virtual std::string getDisplayName();


};

}