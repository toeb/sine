#pragma once

#include <common/Config.h>
#include <common/Node.h>
#include <list>
#include <common/Set.h>
namespace nspace{



  
class ValueObserver{
public:
  virtual void valueChanged(void * sender )=0;
};

class ValueObserverDelegate : public ValueObserver{
private:
  std::function<void (void* sender)> _callback;
public:
  ValueObserverDelegate(std::function<void (void* sender)> callback):_callback(callback){

  }
  void valueChanged(void * sender){
    _callback(sender);
  }
};

class Value{
public:
  virtual const void * pointer()const=0;
  virtual void * pointer()=0;
  inline void notifyChange(){
    onValueChanged();
  }
protected:
  virtual void onValueChanged(){}
};


template< typename T>
class TypedValue : public virtual Value{
private:
  T _value;
public:
  virtual const void * pointer()const{
    return &_value;
  }
  virtual void * pointer(){
    return &_value;
  }
  
  T operator()()const{
    return get();
  }
  T get()const{return _value;}
  T & reference(){return _value;}
  const T & reference()const{return _value;}
  void set(const T & val){
    _value = val;
    notifyChange();
  }
protected:
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
protected:
  void onValueChanged(){
    if(_observers){
      _observers.foreachElement([this](ValueObserver* observer){
        observer->valueChanged(this);
      });
    }
  }
};

template<typename T>
class TypedObservableValue : public virtual TypedValue<T>, public virtual ObservableValue{

};

template<typename T>
class ValueHistory : private ValueObserver{
private:  
  unsigned int _n;
  unsigned int _maxHistory;
  std::list<T> _historyQueue;
  TypedObservableValue<T> & _value;
public:
  ValueHistory(TypedObservableValue<T> & value,unsigned int maxHistory):_value(value),_maxHistory(maxHistory),_n(0){
    _value.addObserver(this);
    valueChanged(&_value);
  }

  ~ValueHistory(){
    _value.removeObserver(this);
  }
  void toStream(std::ostream & out)const{
    unsigned int i=0;
    T value;
    out << "n = "<<_n<<" ";
    while(get(value,i)){
      out << "t_"<<(_n-i-1)<<": "<<value<<" ";
      i++;
    }
  }
  friend std::ostream & operator<<(std::ostream & out, const ValueHistory<T> & history){
    history.toStream(out);
    return out;
  }
protected:
  void valueChanged(void * value){
    _n++;
    _historyQueue.push_back(_value.get());

    while(_historyQueue.size() >= _maxHistory){
      _historyQueue.pop_front();
    }
  }

  // assigns result the element t_{n-i} element
  bool get(T & result, unsigned int t_n_minus_i)const{
    auto it = _historyQueue.rbegin();
    unsigned int i=0;
    //loop until index is reached
    while(true){     
      if(it==_historyQueue.rend())return false;
      if(i==t_n_minus_i)break;
      it++;
      i++;
    }
    // get the value at the iterator t_n-1
    result = * it;
    return true;
  }



};

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




/**
 * \brief Allows the sharing / desharing of a value.
 * 				Inspiration was taken from the Dissertation of Martin Friedmann (SIM Tu Darmstadt)
 *
 */
template<typename T>
class ValueHolder{
private:
  T _privateValue;
  T* _sharedValue;
public:

  /**
   * \brief Constructor.
   *  sorry for the bad comment.
   * \author Tobi
   * \date 01.07.2012
   *
   * \param emptyFlag    I added this parameter as a hack so that noconfusion arises when doing somehting like position = Vector3D / position() = Vector3D....
   * \param initialValue The initial value.
   */
  ValueHolder(const T * initialValue):_privateValue(*initialValue),_sharedValue(&_privateValue){

  }
  ValueHolder():_sharedValue(&_privateValue){

  }
  ~ValueHolder(){
    unshare();
  }

  /**
   * \brief Unshares the value continues using a local copy
   *
   */
  void unshare(){
    _privateValue = *_sharedValue;
    _sharedValue = & _privateValue;
  }

  /**
   * \brief Shares newValue with this ValueHolder
   *
   * 
   *
   * \param [in,out] newValue The new value.
   */
  void share(T & newValue ){
    _sharedValue = &newValue;
  }
  // causes the other value holders shared value to be copied to this shared value
  void mirror(ValueHolder<T> & source){
    _sharedValue = source._sharedValue;
  }

  /**
   * \brief accessor for the value
   */
  inline T & operator()(){
    return *_sharedValue;
  }  
  /**
   * \brief const accessor for the value
   */
  inline const T & operator()()const{    
    return *_sharedValue;
  }

    /**
   * \brief shorthand for share using rhs valueholder as source
   */
  ValueHolder<T> & operator<< (ValueHolder<T> & source){
    mirror(source);
    return *this;
  }
      /**
   * \brief shorthand for share using lhs valueholder as source
   */
  ValueHolder<T> & operator>> (ValueHolder<T> & sink){
    sink.mirror(*this);
    return *this;
  }
};



}