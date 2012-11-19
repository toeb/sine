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
     
    template<typename T, typename DataType>
    class Factory : public virtual ControlFactory{
    public:
      Factory(){
        setDataType(typeof(DataType));
      }
      DynamicWidget * createInstance(){
        T * t= new T(0);
        return t;
      }

    };


  protected:
    virtual void onDataContextChanging(Object * oldvalue, Object * newvalue)=0;
  };
}