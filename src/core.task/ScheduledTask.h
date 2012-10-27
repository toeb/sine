#pragma once

#include <core/Time.h>
#include <core.task/ITask.h>
#include <simulation.logging/Log.h>

namespace nspace{
  class ScheduledTaskRunner;
  class ScheduledTask : 
    public virtual ITask, 
    public virtual PropertyChangingObject,
    public virtual Log,
    public virtual NamedObject
  {
    REFLECTABLE_OBJECT(ScheduledTask);
    SUBCLASSOF(Log);
  private:
    DESCRIPTION(Interval,"The timeout Interval in seconds");
    DISPLAYNAME(Interval,"Timeout Interval");
    PROPERTY(Time, Interval){logMessage("setting timeout to: "<<newvalue,4);}

    DESCRIPTION(IsOneTimeTask, "This flag Indicates whether to run the task repeatedly or only once");
    DISPLAYNAME(IsOneTimeTask, "Run Task Only Once")
    PROPERTY(bool, IsOneTimeTask){logMessage("setting IsOneTimeTask to: "<<newvalue,4);}

    // the last time this task has timed out
    Time _lastTimeoutTime;
    // the next time this task is to be run
    Time _nextExecutionTime;
  public:
    // Default Constructor creates a Task which is run directly and only once
    ScheduledTask();
    // returns the requested next execution time
    Time nextExecutionTime()const;
    // overridable method which is called to calculate the next execution time 
    virtual void calculateNextTimeout(Time time);
    // implementation of the run method. Class the virtual timeout method
    void run();
    // TimeoutMethod gets the time passed since last execution/creation and the absolute time as arguments
    virtual void timeout(Time dt, Time t);
    // struct for comparing task priority (those with tasks with less time have a higher ie lower value priority
    struct CompareTaskPriority{
    public :
      bool operator ()(const ScheduledTask * a,const ScheduledTask * b);
    };
    // compares two tasks to and returns true if a comes before b 
    static bool comp(const ScheduledTask * a, const ScheduledTask * b);
    friend class ScheduledTaskRunner;
  };


}
