#include <core.h>
#include <QWidget>
#pragma once

namespace nspace{
  class DynamicWidget : public QWidget{
    Q_OBJECT;
  public:
    DynamicWidget(QWidget * parent):QWidget(parent),_DataContext(0){}
    SIMPLE_PROPERTY(Object *, DataContext){onDataContextChanging(oldvalue,newvalue);}
  protected:
    virtual void onDataContextChanging(Object * oldvalue, Object * newvalue)=0;
  };
}