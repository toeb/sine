#pragma once
#include <application.qt.objectview/TreeItem.h>
#include <core.logging.h>
namespace nspace{
  class ObjectTreeItem:public TreeItem, public virtual Log{
    REFLECTABLE_OBJECT(ObjectTreeItem);
  public:
    ObjectTreeItem();
    void doExpand();
  };
}