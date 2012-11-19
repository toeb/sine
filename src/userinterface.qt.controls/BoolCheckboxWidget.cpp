#include "BoolCheckboxWidget.h"


using namespace nspace;

BoolCheckboxWidget::BoolCheckboxWidget(QWidget * parent):ValueWidget(parent){
  _checkbox = new QCheckBox(this);   
  connect(_checkbox,SIGNAL(stateChanged(int)),this,SLOT(checkboxStateChanged(int)));
}

void BoolCheckboxWidget::checkboxStateChanged(int state){
  updateValueHolder();
}
void BoolCheckboxWidget::updateWidgetValue(){
  bool value;
  getValueHolder()->get(value);
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