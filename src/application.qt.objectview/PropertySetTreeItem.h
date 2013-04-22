#pragma once

#include <application.qt.objectview/TreeItem.h>
#include <core.logging/Log.h>
#include <core.reflection/member/property/PropertySetInfo.h>
namespace nspace{
  /*
  // TODO: make set item inherit from treeitem
  class PropertySetTreeItem : public TreeItem, public virtual Log, public virtual ObjectObserver{
    reflect_type(PropertySetTreeItem);
    // the propertyset info object
    propdef const PropertySetInfo* basic_property(PropertySetInfo);
    // the object to which the propertyset belongs
    propdef Object * reflect_property(PropertyObject);
  public:
    std::string getDisplayName();
    std::string getDisplayValue();
    bool isEditable();
    bool setEditValue(std::string value);
    std::string getEditValue();
    void onChange(Observable* sender);
    PropertySetTreeItem();
    void onObjectChanged();
    void refresh();
    void resetList();
    void doExpand();
  };*/
}
