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
#include <core/Reflection.h>
#include <core.logging.h>
class Ui_TaskWidget;
namespace nspace{

  class QtTaskRunner : public Plugin, public virtual CompositeHubObject, public virtual TypedModuleBase<ITask>,public virtual Log{
    Q_OBJECT;
    REFLECTABLE_OBJECT(QtTaskRunner);
    SUBCLASSOF(Log);
    SUBCLASSOF(Plugin);

  private:
    ScheduledTaskRunner _scheduledTaskRunner;
    SerialTaskRunner _serialTaskRunner;
    QTimer * _taskTimer;
    Ui_TaskWidget * _ui;

  public:
    QtTaskRunner();
  protected:
    void onElementAdded(ITask * task);
    void onElementRemoved(ITask * task);
    void onComponentAdded(Object * o);
    void onComponentRemoved(Object * o);
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