#include "ValueWidget.h"

using namespace nspace;

void ValueWidget::propertyChanging(IModifiableValue * , ValueHolder){
  if(oldvalue){
  }
  if(newvalue){
    _ValueHolder=newvalue;
    updateWidgetValue();
  }
  onValueHolderChanging(oldvalue,newvalue);
}
ValueWidget::ValueWidget(QWidget * parent):DynamicWidget(parent),_ValueHolder(0){}

void ValueWidget::onDataContextChanging(Object * oldvalue, Object * newvalue){
  if(newvalue){
    setValueHolder(dynamic_cast<IModifiableValue*>(newvalue));
  }
}