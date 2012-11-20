#include "DoubleSpinBoxWidget.h"
#include <QBoxLayout>
using namespace nspace;

DoubleSpinBoxWidget::DoubleSpinBoxWidget(QWidget * parent):ValueWidget(parent){
  auto layout = new QHBoxLayout(this);
  //layout->setSpacing(1);
  _spinbox = new QDoubleSpinBox();
  _spinbox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  setFocusProxy(_spinbox);
  layout->addWidget(_spinbox);
  layout->setSpacing(0);
  layout->setMargin(0);

  setAutoFillBackground(true);
  
  _spinbox->setDecimals(3);
  _spinbox->setRange(-DBL_MAX,DBL_MAX);
  _spinbox->setSingleStep(0.01);
  connect(_spinbox,SIGNAL(editingFinished()),this,SLOT(updateValueHolder()));

  
  //setLayout(layout);
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