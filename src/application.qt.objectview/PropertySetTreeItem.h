#pragma once

#include <application.qt.objectview/TreeItem.h>
#include <core.logging/Log.h>

namespace nspace{
  // TODO: make set item inherit from treeitem
  class PropertySetTreeItem : public TreeItem, public virtual Log, public virtual ObjectObserver{
    REFLECTABLE_OBJECT(PropertySetTreeItem);
    // the propertyset info object
    PROPERTY(const PropertySetInfo*, PropertySetInfo);
    // the object to which the propertyset belongs
    PROPERTY(Object *, PropertyObject){}
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
  };
}