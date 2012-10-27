#include "ScheduledTask.h"

using namespace nspace;

bool ScheduledTask::CompareTaskPriority::operator ()(const ScheduledTask * a,const ScheduledTask * b){
  return a->_nextExecutionTime > b->_nextExecutionTime;
};

Time ScheduledTask::nextExecutionTime()const{
  return _nextExecutionTime;
}

void ScheduledTask::calculateNextTimeout(Time time){
  _lastTimeoutTime = time;
  _nextExecutionTime = time +_Interval;
}
void ScheduledTask::run(){
  Time now = systemTime();
  timeout(now - _lastTimeoutTime,now);
}

void ScheduledTask::timeout(Time dt, Time t){}


ScheduledTask::ScheduledTask():_Interval(0.0),_lastTimeoutTime(REAL_MAX),_nextExecutionTime(REAL_MAX),_IsOneTimeTask(true){
  setName("ScheduledTask");
}

bool ScheduledTask::comp(const ScheduledTask * a, const ScheduledTask * b){
  return a->nextExecutionTime() < b->nextExecutionTime();
}