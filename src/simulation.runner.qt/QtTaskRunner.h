#pragma once

#include <simulation.runner/SimulationRunner.h>
#include <core/NamedObject.h>
#include <QObject>
#include <application.qt/Plugin.h>
#include <application.qt/PluginApplication.h>
#include <QTimer>
class Ui_TaskWidget;
namespace nspace{
  
  class QtTaskRunner : public Plugin, public virtual SimulationRunner {
    Q_OBJECT;
    TYPED_OBJECT;
  private:
    QTimer * _taskTimer;
    Ui_TaskWidget * _ui;
  public:
    QtTaskRunner();
  protected:
    //these methods need to be implemented by a SimulationRunner
    int executeRunner();
    
   void stopRunner();
    bool initializeRunner();
    public slots:
      void timeout();
  public:
    void install(PluginContainer & container);
    void uninstall(PluginContainer & container);
    void enable();
    void disable();
  };
}