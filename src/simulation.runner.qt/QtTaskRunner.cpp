#include "QtTaskRunner.h"

#include "ui_taskwidget.h"

#include <iostream>

using namespace std;
using namespace nspace;


QtTaskRunner::QtTaskRunner():_taskTimer(0){
  setName("simulation.runner.qt.taskrunner");
  _taskTimer = new QTimer(this);
  _taskTimer->setInterval(5);
  connect(_taskTimer,SIGNAL(timeout()), this, SLOT(timeout()));
}
//these methods need to be implemented by a SimulationRunner
int QtTaskRunner::executeRunner(){
  _taskTimer->start();
  return 0;
}

void QtTaskRunner::stopRunner(){
  _taskTimer->stop();

}
bool QtTaskRunner::initializeRunner(){
  return true;
}
void QtTaskRunner::timeout(){
  executeTasks();
}
void QtTaskRunner::enable(){
  run();
}
void QtTaskRunner::disable(){
  stop();
}
void QtTaskRunner::install(PluginContainer & container){
  

  _ui = new Ui_TaskWidget();
  PluginWindow * window = new PluginWindow();
  _ui->setupUi(window);
  container.setPluginWindow(window);

}

void QtTaskRunner::uninstall(PluginContainer & container){

}