#include "QtTaskRunner.h"

#include "ui_taskwidget.h"
#include <core/StringTools.h>
#include <iostream>

using namespace std;
using namespace nspace;

using namespace std::extensions;

QtTaskRunner::QtTaskRunner():_taskTimer(0){
  setName("TaskRunner");
  _taskTimer = new QTimer(this);
  _taskTimer->setInterval(5);
  connect(_taskTimer,SIGNAL(timeout()), this, SLOT(timeout()));
  components() |= &_scheduledTaskRunner;
  components() |= &_serialTaskRunner;
}
void QtTaskRunner::timeout(){
  _scheduledTaskRunner.run();
  _serialTaskRunner.run();  
}
bool QtTaskRunner::accept(ITask * task){
 
  // ignore the taskrunners (which are also tasks)
  if(&_scheduledTaskRunner==task)return false;
  if(&_serialTaskRunner==task)return false;
  return true;
}
void QtTaskRunner::onElementAdded(ITask * task){
  if(_scheduledTaskRunner.addTask(task))return;
  _serialTaskRunner.addTask(task);
}
void QtTaskRunner::onElementRemoved(ITask * task){}

void QtTaskRunner::enable(){
  _taskTimer->start();
}
void QtTaskRunner::disable(){
  _taskTimer->stop();
}
void QtTaskRunner::install(PluginContainer & container){


  _ui = new Ui_TaskWidget();
  PluginWindow * window = new PluginWindow();
  _ui->setupUi(window);
  window->setWindowTitle((name()+" Window").c_str());
  container.setPluginWindow(window);

}

void QtTaskRunner::uninstall(PluginContainer & container){

}