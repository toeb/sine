#pragma once

#include <application.qt.objectview/TreeItem.h>

namespace nspace{
  class PropertyGroupTreeItem : public virtual TreeItem{    
    REFLECTABLE_OBJECT(PropertyGroupTreeItem);
    PROPERTY(std::string, GroupName){}
  public:
    virtual std::string getDisplayName();
    virtual std::string getDisplayValue();
    virtual std::string getDescription();
    virtual std::string getDisplayHint();
  protected:    
    virtual void onObjectChanged();    
    virtual void doExpand();
  };
}