#include "DoubleSliderWidget.h"

using namespace nspace;

DoubleSliderWidget::DoubleSliderWidget(){
  setMinValue(-1000);
  setMaxValue(1000);
  setSteps(2000);
  //setValueType(typeof(double));
  connect(this,SIGNAL(valueChanged(int)),this, SLOT(valueChanged(int)));
}
void DoubleSliderWidget::valueChanged(int i){
  raiseObjectChanged();
}
bool DoubleSliderWidget::retrieveTypeValue(double & value)const{
  double factor = ((double)sliderPosition())/((double)getSteps());
  double newvalue = getMinValue()+(getMaxValue()-getMinValue())*factor;
  value = newvalue;
  return true;
}
bool DoubleSliderWidget::storeTypedValue(const double  & value){
  double newvalue = value;
  if(newvalue > getMaxValue())return false;
  if(newvalue < getMinValue())return false;
  newvalue -= getMinValue();
  newvalue /= getMaxValue()-getMinValue();
  int ivalue = newvalue*getSteps();
  setSliderPosition(ivalue);
  return true;
}