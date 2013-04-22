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
  connect(_spinbox,SIGNAL(valueChanged(double)),this, SLOT(onValueChanged(double)));

  //setLayout(layout);
}

void DoubleSpinBoxWidget::updateWidgetValue(){
  double value;
  if(!getValueHolder())return;
 value=  getValueHolder()->get();
  _spinbox->setValue(value);
}
void DoubleSpinBoxWidget::updateValueHolder(){
  double value = _spinbox->value();
  if(getValueHolder()) getValueHolder()->set(value);
  emit editFinished();
}

void DoubleSpinBoxWidget::onValueChanged(double){
  //  debugInfo("ValueChanged")
  double value = _spinbox->value();
  if(getValueHolder()) getValueHolder()->set(value);
}