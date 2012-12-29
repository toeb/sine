#include "QtTimeControl.h"
#include "ui_timecontrol.h"

using namespace std;
using namespace nspace;

QtTimeControl::QtTimeControl(QWidget * parent):
  PluginWindow(parent),
  _TimeController(0)
{
  _ui = new Ui_TimeControl();
  _ui->setupUi(this);
  _refreshTimer = new QTimer();
  _refreshTimer->start(30);

  connect(_refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
  connect(_ui->pauseButton, SIGNAL(clicked()), this ,SLOT(pauseCalled()));
  connect(_ui->stepButton, SIGNAL(clicked()), this, SLOT(step()));
  connect(_ui->targetSimulationTimeEdit, SIGNAL(timeChanged(const QTime &)), this, SLOT(targetTimeChanged(const QTime & )));
  connect(_ui->desiredSpeedValue,SIGNAL(valueChanged(double)),this,SLOT(setSpeed(double)));
}

void QtTimeControl::targetTimeChanged(const QTime & t){
  if(!_TimeController)return;
  Real target = QTime().msecsTo(t)/1000.0;
  _TimeController->simulationTimeProvider().advanceTo(target);
}

void QtTimeControl::refresh(){
  if(!_TimeController)return;

  QTime actualTime = QTime().addMSecs(int(_TimeController->simulationTimeProvider().actualTime()*1000));
  _ui->actualSimulationTimeEdit->setTime(actualTime);

  QTime targetTime = QTime().addMSecs(int(_TimeController->simulationTimeProvider().targetTime()*1000));
  if(!_ui->targetSimulationTimeEdit->hasFocus()){
    _ui->targetSimulationTimeEdit->blockSignals(true);
    _ui->targetSimulationTimeEdit->setTime(targetTime);
    _ui->targetSimulationTimeEdit->blockSignals(false);
  }
  QTime appTime = QTime().addMSecs(int(applicationTime()*1000));
  _ui->applicationTimeEdit->setTime(appTime);

  _ui->desiredSpeedValue->setValue(_TimeController->getDesiredSpeed());
  _ui->actualSpeedValue->setValue(_TimeController->simulationTimeProvider().averageActualSpeed());
}

void QtTimeControl::pauseCalled(){
  if(!_TimeController)return;

  _TimeController->togglePause();
}
void QtTimeControl::step(){
  if(!_TimeController)return;
  _TimeController->setPaused(true);
  _TimeController->simulationTimeProvider().advanceBy(_ui->stepSizeValue->value());
}

void QtTimeControl::setSpeed(double value){
  if(!_TimeController)return;
  if(value==0){
    _TimeController->setPaused(true);
    return;
  }
  _TimeController->setPaused(false);

  _TimeController->setDesiredSpeed(value);
}