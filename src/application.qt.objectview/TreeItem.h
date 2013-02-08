#pragma once

#include <core.graph/Node.h>
#include <core.h>
#include <application.qt.objectview/ObjectPropertyViewModel.h>

namespace nspace{
  class TreeItem :
    public Node<TreeItem>,
    public virtual PropertyChangingObject
  {
    REFLECTABLE_OBJECT(TreeItem);
    // the object which this tree item wraps
    PROPERTY(Object*, Object){}
    // tracks if this item is expanded or not
    PROPERTY(bool, IsExpanded){}
    // pointer to the viewmodel
    PROPERTY(ObjectPropertyViewModel*, Model){}
    // index model index of this item
    SIMPLE_PROPERTY(QModelIndex, ModelIndex){}
  public:
    // expands the this item. this method must be called before accessing children
    void expand();
    //default constructor
    TreeItem();
    ~TreeItem();

    // some data access method
    virtual std::string getDisplayName();
    virtual std::string getDisplayValue();
    virtual std::string getEditValue();
    virtual std::string getDescription();
    virtual Type * getValueType();
    virtual std::string getDisplayHint();
    virtual bool isEditable();
    virtual bool setEditValue(std::string str);
    // gets the parent tree item
    TreeItem * parent();
    // gets the children
    Set<TreeItem*> & children();
    // gets the index of this element in reference to its parent
    int childNumber();
    void onPropertyChanged(const std::string & name);
  protected:
    virtual void onObjectChanged(){};
    virtual void doExpand()=0;
  };
}