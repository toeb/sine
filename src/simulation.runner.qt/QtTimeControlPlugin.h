#pragma once
#include <application.qt/Plugin.h>
#include <application.qt/PluginContainer.h>
#include <core.h>
#include <simulation.runner.qt/QtTimeControl.h>
namespace nspace{
  class QtTimeControlPlugin :public Plugin,public virtual PropertyChangingObject{
    REFLECTABLE_OBJECT(QtTimeControlPlugin)
  private:
    REFLECTABLE_NOTIFYING_PROPERTY(SimulationTimeController*, TimeController){
      if(_timeControl)_timeControl->setTimeController(newvalue);
    }

    QtTimeControl * _timeControl;
  public:
    QtTimeControlPlugin():_TimeController(0),_timeControl(0){
      setName("Time Control");
    }

    virtual void install(PluginContainer & container){
      auto timeControl = new QtTimeControl();
      timeControl->setTimeController(getTimeController());
      container.setPluginWindow(timeControl);
      container.toggleWindow(true);
    }
    virtual void enable(){}
    virtual void disable(){}
    virtual void uninstall(PluginContainer & container){
      container.setPluginWindow(0);
      delete _timeControl;
      _timeControl=0;
    }
  };
}
