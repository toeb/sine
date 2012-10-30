#pragma once

#include <application.qt.objectview/TreeItem.h>
#include <core.logging/Log.h>

namespace nspace{

class PropertyTreeItem :
  public TreeItem, 
  public virtual Log{
  REFLECTABLE_OBJECT(PropertyTreeItem);
  // the propertyinfo object
  PROPERTY(const Property*, PropertyInfo){}
  // the ownign object of the property
  PROPERTY(Object *, PropertyOwner){}
public:
  PropertyTreeItem();
  
  virtual bool isEditable();
  virtual std::string getEditValue();
  virtual bool setEditValue(std::string value);
  virtual std::string getDescription();
  virtual std::string getDisplayName();
  virtual std::string getDisplayValue();
  
  void onObjectChanged();
  void doExpand();
};
}