#include "BoolCheckboxWidget.h"
#include <QBoxLayout>

using namespace nspace;

BoolCheckboxWidget::BoolCheckboxWidget(QWidget * parent):ValueWidget(parent){
  auto layout = new QHBoxLayout(this);
  setAutoFillBackground(true);
  //layout->setSpacing(1);
  _checkbox = new QCheckBox();
  _checkbox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  setFocusProxy(_checkbox);
  layout->addWidget(_checkbox);
  layout->setSpacing(0);
  layout->setMargin(0);

  connect(_checkbox,SIGNAL(stateChanged(int)),this,SLOT(checkboxStateChanged(int)));
}

void BoolCheckboxWidget::checkboxStateChanged(int state){
  updateValueHolder();
}
void BoolCheckboxWidget::updateWidgetValue(){
  bool value = getValueHolder()->get();
  _checkbox->setCheckState(value?Qt::Checked:Qt::Unchecked);
}
void BoolCheckboxWidget::updateValueHolder(){
  bool value = _checkbox->isChecked();
  getValueHolder()->set(value);
  emit editFinished();
}

void BoolCheckboxWidget::onValueHolderChanging(IModifiableValue * oldvalue,IModifiableValue * newvalue){
  if(oldvalue){
  }
  if(newvalue){
  }
}