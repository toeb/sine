#pragma once

#include <userinterface.qt.controls/DynamicWidget.h>
#include <core.reflection/value/IModifiableValue.h>

namespace nspace{
  class ValueWidget : public DynamicWidget{
    Q_OBJECT;
    SIMPLE_PROPERTY(IModifiableValue * , ValueHolder);
    public slots:
      virtual void updateWidgetValue(){};
      virtual void updateValueHolder(){};
  public:

    template<typename T,typename ValueType>
    class Factory : public virtual ControlFactory{
    public:
      bool match(const Type * type, Object * object, const std::string & hints){
        if(!object)return false;
        auto valueHolder = dynamic_cast<IModifiableValue*>(object);
        if(!valueHolder)return false;
        auto result = typeof(ValueType)->isSuperClassOf(valueHolder->getValueType());

        return result;
      }
      DynamicWidget * createInstance(){
        return new T(0);
      }
    };

    ValueWidget(QWidget * parent);
  protected:
    void onDataContextChanging(Object * oldvalue, Object * newvalue);
    virtual void onValueHolderChanging(IModifiableValue * oldvalue,IModifiableValue * newvalue){}
signals:
    void editFinished();
  };
}