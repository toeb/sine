#pragma once
#include <QStandardItem>
#include <simulation.access/IComponent.h>
#include <core.collection.h>
namespace nspace{
  class ValueItem;
  class ValueItemFactory{
  public:
    static Set<ValueItem*> create(QStandardItem& parent,  IComponent * component);
  };
}