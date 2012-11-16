#pragma once

#include <core.h>
#include <QDoubleSpinBox>
#include <userinterface.qt.controls/ValueWidget.h>

namespace nspace{
  class DoubleSpinBoxWidget : public ValueWidget{
    Q_OBJECT;
  private:
    QDoubleSpinBox * _spinbox;
  public:
    DoubleSpinBoxWidget(QWidget * parent);
  public slots:
    void updateWidgetValue();
    void updateValueHolder();
  };
}