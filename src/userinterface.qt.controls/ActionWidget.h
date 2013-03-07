#pragma once
#include <core.h>

#include <core.reflection/callable/Action.h>
#include <userinterface.qt.controls/DynamicWidget.h>
#include <userinterface.qt.controls/ControlFactory.h>
#include <QPushButton>
namespace nspace{
  class ActionWidget : public DynamicWidget, public virtual PropertyChangingObject{
    reflect_type(ActionWidget);
    Q_OBJECT;
    QPushButton * _button;
    typedef Action * reflect_property(Action);
  public:
    ActionWidget(QWidget * parent);

    class Factory : public virtual ControlFactory{
    public:
      virtual bool match(const Type * type, Object * object, const std::string& hints=""){
        auto action = dynamic_cast<Action*>(object);
        if(!action )return false;
        return true;
      }
      DynamicWidget * createInstance(){
        return new ActionWidget(0);
      }
    };

    protected slots:
      void performAction();

  protected:
    void onDataContextChanging(Object * oldvalue, Object * newvalue);
  };
}