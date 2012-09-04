#pragma once
#include <list>
#include <utility/valuegraph/TypedObservableValue.h>

namespace nspace{ 

template<typename T>
class ValueHistory : private ValueObserver{
private:  
  unsigned int _n;
  unsigned int _maxHistory;
  std::list<T> _historyQueue;
  TypedObservableValue<T> & _value;
public:
  ValueHistory(TypedObservableValue<T> & value,unsigned int maxHistory=3):_value(value),_maxHistory(maxHistory),_n(0){
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
}