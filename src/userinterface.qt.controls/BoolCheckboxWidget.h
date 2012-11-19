

#pragma once

#include <core.h>
#include <QCheckBox>
#include <userinterface.qt.controls/ValueWidget.h>

namespace nspace{
  class BoolCheckboxWidget : public ValueWidget{
    Q_OBJECT;
  private:
    QCheckBox * _checkbox;
  public:
    BoolCheckboxWidget(QWidget * parent);
  public slots:
    void checkboxStateChanged(int state);
    void updateWidgetValue();
    void updateValueHolder();
  protected:
    
    void onValueHolderChanging(IModifiableValue * oldvalue,IModifiableValue * newvalue);
  };
}