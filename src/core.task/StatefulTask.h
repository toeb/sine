/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#pragma once

#include <core.h>

#include <core.logging.h>
#include <core.task/ExtendedTask.h>

namespace nspace {

  
class ProgressReporter : public virtual PropertyChangingObject, public virtual Log{
  reflect_type(ProgressReporter);
  typedef double reflect_property(NumberOfNotifications);
  auto after_set(NumberOfNotifications){
    if(getNumberOfNotifications())setNumberOfNotifications(1.0);
  }
  typedef double reflect_property(TotalProgress);
  auto after_set(TotalProgress){  
    setNotificationInterval(getTotalProgress()/getNumberOfNotifications());
  }
  
  typedef double reflect_property(Progress);
  typedef int    reflect_property(ProgressLogLevel);
  typedef double reflect_property(NotificationInterval);
  typedef bool   reflect_property( LogProgress);
public:
  ProgressReporter():    
    _NumberOfNotifications(200.0),
    _TotalProgress(1),
    _Progress(0),
    _ProgressLogLevel(4),
    _NotificationInterval(0.01),
    _LogProgress(true){
    resetProgress();
  
  };
  double percent()const{
    return quotient()*100.0;
  }
  double quotient()const{
    return getProgress()/getTotalProgress();
  }

private:
  double _lastNotification;
protected:
  void resetProgress(double totalProgress){
    resetProgress();
    setTotalProgress(totalProgress);
  }
  void resetProgress(){
    _lastNotification=0;
    setProgress(0.0);  
  }
  void incrementProgress(double value){
    reportProgress(getProgress()+value);
  }
  void reportProgress(double value){
    _Progress = value;
    if(getProgress()>_lastNotification+getNotificationInterval()){
      _lastNotification=getProgress();
      notify_after_set(Progress);
      if(getLogProgress()){

        logMessage("Progress: "<< percent() << "%",getProgressLogLevel());
      }
    }    
  }
};


  class StatefulTask : public virtual ExtendedTask,public virtual Log, public virtual NamedObject {
    reflect_type(StatefulTask);
    reflect_superclasses(ExtendedTask,Log);

protected:
    // method to override
    virtual bool runTaskReturnSuccess()=0;
public:
    enum State {
      Unknown,
      Running,
      Succeeded,
      Failed
    };
    static std::string stateToString(const State & state);
    typedef State reflect_property(State);
    auto before_set(State);

    ACTION(Reset);
    ACTION(Run);

public:
    virtual void clearResult();

    bool runStatefulTask();

    StatefulTask();
private:
    // overridden from extended task
    void runTask();
  };
  META(StatefulTask::State);
}
