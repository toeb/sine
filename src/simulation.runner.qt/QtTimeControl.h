#pragma once
#include <QTimer>
#include <QDockWidget>
#include <simulation.runner.qt/SimulationDockWidget.h>
#include <simulation.time/SimulationTimeController.h>
#include <application.qt/PluginWindow.h>

#include <core.h>

class Ui_TimeControl;
namespace nspace{

  class QtTimeControl : public PluginWindow,public virtual PropertyChangingObject{
  Q_OBJECT;
  REFLECTABLE_OBJECT(QtTimeControl);
  public:    
    REFLECTABLE_NOTIFYING_PROPERTY(SimulationTimeController*, TimeController){}
  private:
    QTimer * _refreshTimer;
    Ui_TimeControl * _ui;
  public:
    QtTimeControl( QWidget * parent=0);    
  public slots:
    void refresh();
    void pauseCalled();
    void step();
    void targetTimeChanged(const QTime & t);
    void setSpeed(double value);
  };
}