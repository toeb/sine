#pragma once
#include <core.h>
#include <QWidget>
#include <userinterface.qt.controls/ControlFactory.h>

namespace nspace{
  class DynamicWidget : public QWidget{
    Q_OBJECT;
   SIMPLE_PROPERTY(Object *, DataContext){onDataContextChanging(oldvalue,newvalue);}
  public:
    DynamicWidget(QWidget * parent):QWidget(parent),_DataContext(0){}
     




  protected:
    virtual void onDataContextChanging(Object * oldvalue, Object * newvalue)=0;
  };
}