#pragma once
#include <core.h>
#include <QWidget>
#include <QSpinBox>

namespace nspace{
  class DoubleRangeWidget : public QDoubleSpinBox, public virtual IModifiableValue{
    Q_OBJECT;
    TYPED_OBJECT(IModifiableValue);
  public:
    DoubleRangeWidget(){
      connect(this,SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));
      setValueType(typeof(double));
      setDecimals(3);
      setMinimum(-REAL_MAX);
      setMaximum(REAL_MAX);
    }
    bool storeValue(const void * value){      
      double dvalue = *static_cast<const double*>(value);
      this->setValue(dvalue);
      return true;
    }
    bool retrieveValue(void * value)const{
      double * dvalue = static_cast<double *>(value);
      *dvalue = this->value();
      return true;
    }
  protected slots:
    void valueChanged(double value){
      raiseObjectChanged();
    }
  };

}