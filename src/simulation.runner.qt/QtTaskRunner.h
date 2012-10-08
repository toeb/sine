#pragma once

#include <simulation.runner/SimulationRunner.h>
#include <core/NamedObject.h>
#include <QObject>
#include <application.qt/Plugin.h>
#include <application.qt/PluginApplication.h>
#include <core.task/SerialTaskRunner.h>
#include <core.task/ScheduledTaskRunner.h>
#include <core.hub/CompositeHubObject.h>
#include <QTimer>
class Ui_TaskWidget;
namespace nspace{

  class QtTaskRunner : public Plugin, public virtual CompositeHubObject, public virtual TypedModuleBase<ITask>{
    Q_OBJECT;
    TYPED_OBJECT(QtTaskRunner);
  private:
    ScheduledTask *_breakTask;
    ScheduledTaskRunner _scheduledTaskRunner;
    SerialTaskRunner _serialTaskRunner;
    QTimer * _taskTimer;
    Ui_TaskWidget * _ui;
  public:
    QtTaskRunner();
  protected:
    void onElementAdded(ITask * task);
    void onElementRemoved(ITask * task);
    bool accept(ITask * task);
    public slots:
    void timeout();
  public:
    void install(PluginContainer & container);
    void uninstall(PluginContainer & container);
    void enable();
    void disable();


  };
}