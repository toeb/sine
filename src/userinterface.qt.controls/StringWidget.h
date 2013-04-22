#pragma once
#include <QLineEdit>
#include <core.reflection/value/IModifiableValue.h>
namespace nspace{
  class StringWidget : public QLineEdit, public virtual IModifiableValue{
    Q_OBJECT;
    reflect_type(StringWidget);
  public:
    StringWidget(){
      connect(this,SIGNAL(textChanged(const QString &)),this,SLOT(raiseTextChanged(const QString &)));
    }

    protected slots:
      void raiseTextChanged(const QString& qstring){
        raiseObjectChanged();
      }
  protected:
    
    bool storeValue(Argument argument)override{
      std::string value =  argument;
      setText(tr(value.c_str()));
      return true;
      
    }
    
    Argument retrieveValue()const override{
      std::string value = text().toUtf8().constData();
      return value;
    }
  };
}