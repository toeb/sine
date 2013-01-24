#include "QtTaskRunner.h"

#include "ui_taskwidget.h"
#include <core.utilities.h>
#include <iostream>
#include <core.task/ScheduledTask.h>

using namespace std;
using namespace nspace;

QtTaskRunner::QtTaskRunner():_taskTimer(0),_ui(0){
  setName("TaskRunner");
  _taskTimer = new QTimer(this);
  _taskTimer->setInterval(5);
  connect(_taskTimer,SIGNAL(timeout()), this, SLOT(timeout()));
  Components() |= &_scheduledTaskRunner;
  Components() |= &_serialTaskRunner;
}
void QtTaskRunner::timeout(){
  logMessage(" timing out --> executing scheduledtaskrunner and serialtaskrunner",4);
  _scheduledTaskRunner.step();
  _serialTaskRunner.step();
}
bool QtTaskRunner::accept(ITask * task){;
// ignore the taskrunners (which are also tasks)
if(&_scheduledTaskRunner==task)return false;
if(&_serialTaskRunner==task)return false;
logInfo("accepted task: "<<nspace::name(task)<<"");
return true;
}
void QtTaskRunner::onElementAdded(ITask * task){
  if(_scheduledTaskRunner.addTask(task))return;
  _serialTaskRunner.addTask(task);
}
void QtTaskRunner::onElementRemoved(ITask * task){
  _scheduledTaskRunner.removeTask(task);
  _serialTaskRunner.removeTask(task);
}

void QtTaskRunner::enable(){
  _taskTimer->start();
}
void QtTaskRunner::disable(){
  _taskTimer->stop();
}
void QtTaskRunner::install(PluginContainer & container){
  //logWarning("not implemented");
}

void QtTaskRunner::uninstall(PluginContainer & container){
  //logError("Function Not implemented");
}

void QtTaskRunner::onComponentAdded(Object * o){
  debugInfo("adding " <<*o);
}
void QtTaskRunner::onComponentRemoved(Object * o){
  debugInfo("removing "<< *o);
}