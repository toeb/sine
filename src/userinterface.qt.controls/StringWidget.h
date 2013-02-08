#pragma once
#include <QLineEdit>
#include <core.reflection/value/ITypedModifiableValue.h>
#include <core.reflection/DefaultTypes.h>
namespace nspace{
  class StringWidget : public QLineEdit, public virtual ITypedModifiableValue<std::string>{
    Q_OBJECT;
    TYPED_OBJECT(StringWidget);
  public:
    StringWidget(){
      connect(this,SIGNAL(textChanged(const QString &)),this,SLOT(raiseTextChanged(const QString &)));
    }

    protected slots:
      void raiseTextChanged(const QString& qstring){
        raiseObjectChanged();
      }
  protected:
    bool storeTypedValue(const std::string  & value){
      setText(tr(value.c_str()));
      return true;
    }
    bool retrieveTypeValue(std::string & value)const{
      value = text().toUtf8().constData();
      return true;
    }
  };
}