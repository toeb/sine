#pragma once
#include <application.qt.objectview/TreeItem.h>
#include <core.logging.h>
namespace nspace{
  class ObjectTreeItem:public TreeItem, public virtual Log{
    reflect_type(ObjectTreeItem);
  public:
    ObjectTreeItem();
    void doExpand();
  };
}