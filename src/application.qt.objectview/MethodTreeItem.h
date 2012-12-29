#pragma once

#include <application.qt.objectview/TreeItem.h>
#include <core.logging/Log.h>

namespace nspace{
  class MethodTreeItem :
    public TreeItem,
    public virtual Log{
      REFLECTABLE_OBJECT(MethodTreeItem);
      // the method info object
      PROPERTY(const MethodInfo*, MethodInfo){}
      // the ownign object of the property
      PROPERTY(Object *, PropertyOwner){}
  public:
    MethodTreeItem();

    virtual std::string getDescription();
    virtual std::string getDisplayName();
    virtual std::string getDisplayValue();
    virtual bool isEditable();

    void onObjectChanged();
    void doExpand();
  };
}