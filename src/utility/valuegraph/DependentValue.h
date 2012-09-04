#pragma once

#include <utility/valuegraph/DependentValue.h>

namespace nspace{
  
template<typename T>
class DependentValue : public virtual TypedObservableValue<T>, public virtual ValueObserver, public virtual ObservableCollection<ObservableValue*>::Observer{
private:
  Set<ObservableValue *> _dependencies;
public:
  DependentValue(){
    _dependencies.addObserver(this);
  }
  
  void valueChanged(void * sender){
    recalculate();
  }
  void recalculate(){
    set(calculate());  
  }
  void elementAdded(ObservableCollection<ObservableValue*> * sender, ObservableValue* element){
    element->addObserver(this);
    recalculate();
    
  }
  void elementRemoved(ObservableCollection<ObservableValue*> * sender, ObservableValue* element){
    element->removeObserver(this);
    recalculate();
  }


protected:  
  virtual T calculate()=0;
  Set<ObservableValue*> & dependencies(){return _dependencies;}
};
}