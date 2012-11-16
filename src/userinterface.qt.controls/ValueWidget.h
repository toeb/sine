#pragma once

#include <userinterface.qt.controls/DynamicWidget.h>
#include <core/reflection/IModifiableValue.h>

namespace nspace{  
  class ValueWidget : public DynamicWidget{
    Q_OBJECT;
    SIMPLE_PROPERTY(IModifiableValue * , ValueHolder);
  public slots:
    virtual void updateWidgetValue(){};
    virtual void updateValueHolder(){};
  public:
    ValueWidget(QWidget * parent);
  protected:    
    void onDataContextChanging(Object * oldvalue, Object * newvalue);
    virtual void onValueHolderChanging(IModifiableValue * oldvalue,IModifiableValue * newvalue){}
  signals:
    void editFinished();    
  };
}