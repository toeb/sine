#pragma once

#include <config.h>
#include <vector>
namespace nspace{
    // TODO REWORK OBSERVABLE OBJECTS for performance
  class Observable;
  class ObjectObserver{
  public:
    virtual void onChange(Observable * sender)=0;
  };

  class Observable{
    typedef std::vector<ObjectObserver*>   ObserverList;
  private:
    ObserverList * _observers;
  public:
    Observable();
    ~Observable();
  protected:
    bool hasObservers()const;
    ObserverList & observers();
    void raiseObjectChanged();
  public:
    void addObjectObserver(ObjectObserver* oo);
    void removeObjectObserver(ObjectObserver * oo);
  };
}