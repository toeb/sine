#pragma once
#include <QCheckBox>
#include <core/reflection/ITypedModifiableValue.h>
namespace nspace{
  class BoolWidget : public QCheckBox, public virtual ITypedModifiableValue<bool>{
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
   bool storeTypedValue(const bool  & value){
     setChecked(value);
     return true;
   }
   bool retrieveTypeValue(bool & value)const{
     value = isChecked();
     return true;
   }


  };
}