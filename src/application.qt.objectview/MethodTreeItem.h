#pragma once

#include <application.qt.objectview/TreeItem.h>
#include <core.logging/Log.h>

namespace nspace{
  class MethodTreeItem :
    public TreeItem,
    public virtual Log{
      reflect_type(MethodTreeItem);
      // the method info object
      typedef const MethodInfo * basic_property(MethodInfo);
      // the ownign object of the property
      typedef Object * reflect_property(PropertyOwner);
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
