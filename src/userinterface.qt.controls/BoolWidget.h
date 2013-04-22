#pragma once
#include <QCheckBox>
#include <core.reflection.h>
#include <core.reflection/value/ITypedModifiableValue.h>
namespace nspace{
  class BoolWidget : public QCheckBox, public virtual IModifiableValue{
    Q_OBJECT;
    TYPED_OBJECT(BoolWidget);
  public:
    BoolWidget(){
      connect(this,SIGNAL(stateChanged(int)),this,SLOT(checkBoxToggled(int)));
    }
    protected slots:
      void checkBoxToggled(int value){
        raiseObjectChanged();
      }
      bool storeValue(Argument value)override{
        setChecked(value);
        return true;
      }
      Argument retrieveValue()const override{
        return isChecked();
      }
  };
}