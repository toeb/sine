#include "DoubleSpinBoxWidget.h"

using namespace nspace;

DoubleSpinBoxWidget::DoubleSpinBoxWidget(QWidget * parent):ValueWidget(parent){
  _spinbox = new QDoubleSpinBox(this); 
  _spinbox->setDecimals(3);
  _spinbox->setRange(-DBL_MAX,DBL_MAX);
  _spinbox->setSingleStep(0.01);
  connect(_spinbox,SIGNAL(editingFinished()),this,SLOT(updateValueHolder()));
}

void DoubleSpinBoxWidget::updateWidgetValue(){
  double value;
  getValueHolder()->get(value);
  _spinbox->setValue(value);
}
void DoubleSpinBoxWidget::updateValueHolder(){
  double value = _spinbox->value();
  getValueHolder()->set(value);
  emit editFinished();
}   