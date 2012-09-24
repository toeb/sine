#include "QtTimeControl.h"
#include "ui_timecontrol.h"

using namespace std;
using namespace nspace;

QtTimeControl::QtTimeControl(QWidget * parent):_realTimeModule(0),SimulationDockWidget(parent){
  _ui = new Ui_TimeControl();
  _ui->setupUi(this);
  _refreshTimer = new QTimer();
  _refreshTimer->start(30);

  _maxSpeed = 20;
  connect(_refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
  connect(_ui->pauseButton, SIGNAL(clicked()), this ,SLOT(pauseCalled()));
  connect(_ui->speedDial, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
  connect(_ui->stepButton, SIGNAL(clicked()), this, SLOT(step()));
  connect(_ui->targetSimulationTimeEdit, SIGNAL(timeChanged(const QTime &)), this, SLOT(targetTimeChanged(const QTime & )));
  connect(_ui->frequencyDial, SIGNAL(valueChanged(int)), this, SLOT(setCallFrequency(int)));
}


void QtTimeControl::targetTimeChanged(const QTime & t){
  if(!_realTimeModule)return;
  Real target = QTime().msecsTo(t)/1000.0;
  _realTimeModule->simulationTimeProvider().advanceTo(target);
}

void QtTimeControl::refresh(){
  if(!_realTimeModule)return;

  /*
  int speedDialPosition = _realTimeModule->desiredSpeed()*_maxSpeed/100.0;
  _ui->speedDial->setValue(speedDialPosition);
  
  */
  QTime actualTime = QTime().addMSecs(int(_realTimeModule->simulationTimeProvider().actualTime()*1000));
  _ui->actualSimulationTimeEdit->setTime(actualTime);


  QTime targetTime = QTime().addMSecs(int(_realTimeModule->simulationTimeProvider().targetTime()*1000));
  if(!_ui->targetSimulationTimeEdit->hasFocus()){
  _ui->targetSimulationTimeEdit->blockSignals(true);
  _ui->targetSimulationTimeEdit->setTime(targetTime);
  _ui->targetSimulationTimeEdit->blockSignals(false);
  }
  QTime appTime = QTime().addMSecs(int(applicationTime()*1000));
  _ui->applicationTimeEdit->setTime(appTime);

  _ui->desiredSpeedValue->setValue(_realTimeModule->desiredSpeed());

  _ui->actualSpeedValue->setValue(_realTimeModule->simulationTimeProvider().averageActualSpeed());

  _ui->actualFrequency->setValue(_realTimeModule->actualFrequencyAverage());
  _ui->desiredFrequency->setValue(_realTimeModule->desiredFrequency());
  _ui->callFrequency->setValue(_realTimeModule->callFrequencyAverage());
}


void QtTimeControl::pauseCalled(){
  if(!_realTimeModule)return;

  _realTimeModule->togglePause();
  
}
void QtTimeControl::step(){
 if(!_realTimeModule)return;
 _realTimeModule->setPause(true);
 _realTimeModule->simulationTimeProvider().advanceBy(_ui->stepSizeValue->value());
}
void QtTimeControl::setCallFrequency(int hz){
  if(!_realTimeModule)return;
  _realTimeModule->setDesiredFrequency(hz);
}
void QtTimeControl::setSpeed(int val){
  if(!_realTimeModule)return;
  if(val==0){
    _realTimeModule->setPause(true);
    return;
  }
  _realTimeModule->setPause(false);

  Real speed = _maxSpeed * (val/100.0);

  _realTimeModule->desiredSpeed() = speed;
}