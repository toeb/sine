#pragma once
#include <QTimer>
#include <QDockWidget>
#include <simulation.runner.qt/SimulationDockWidget.h>
#include <simulation.time/SimulationTimeController.h>

class Ui_TimeControl;
namespace nspace{

  class QtTimeControl : public SimulationDockWidget{
  Q_OBJECT;
  private:
    SimulationTimeController * _realTimeModule;
    QTimer * _refreshTimer;
    Ui_TimeControl * _ui;
    int _maximumTime;
    Real _maxSpeed;
  public:
    QtTimeControl( QWidget * parent=0);    
    void setRealTimeModule(SimulationTimeController * module){
      _realTimeModule = module;
    }
  public slots:
    void refresh();
    void pauseCalled();
    void step();
    void setCallFrequency(int hz);
    void targetTimeChanged(const QTime & t);
    void setSpeed(int value);
  };
}