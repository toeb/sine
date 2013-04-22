#pragma once

#include <application.qt.objectview/TreeItem.h>
#include <core.logging/Log.h>

namespace nspace{
  class PropertyTreeItem :
    public TreeItem,
    public virtual Log,
    public virtual ObjectObserver
  {
    reflect_type(PropertyTreeItem);    // the propertyinfo object
    propdef const PropertyInfo* basic_property(PropertyInfo);
    // the ownign object of the property
    propdef Object * reflect_property(PropertyOwner);
  public:
    PropertyTreeItem();

    virtual bool isEditable();
    virtual std::string getEditValue();
    virtual bool setEditValue(std::string value);
    virtual std::string getDescription();
    virtual std::string getDisplayName();
    virtual std::string getDisplayValue();

    void onChange(Observable* sender);
    void onObjectChanged();
    void doExpand();
  };
}
