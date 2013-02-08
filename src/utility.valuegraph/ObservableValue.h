#pragma once

#include <config.h>
#include <functional>
#include <core.collection/containers/Set.h>
#include <utility.valuegraph/Value.h>

namespace nspace{
  class ValueObserver{
  public:
    virtual void valueChanged(void * sender )=0;
  };

  class ObservableValue : public virtual Value{
  private:
    Set<ValueObserver *> _observers;
  public:
    void addObserver(ValueObserver * observer){
      _observers.add(observer);
    }

    void removeObserver(ValueObserver * observer){
      _observers.remove(observer);
    }

    inline void onValueChanged(){
      if(_observers){
        _observers.foreachElement([this](ValueObserver* observer){
          observer->valueChanged(this);
        });
      }
    }
  };

  class ValueObserverDelegate : public ValueObserver{
  private:
    std::function<void (void* sender)> _callback;
  public:
    ValueObserverDelegate(std::function<void (void* sender)> callback){
      _callback=callback;
    }
    ~ValueObserverDelegate(){
    }
    /*ValueObserverDelegate(const std::function<void (void*sender)> & callback):_callback(callback){
    }*/

    void valueChanged(void * sender){
      _callback(sender);
    }
  };
}