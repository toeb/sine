#pragma once


namespace IBDS{
  
template<typename T>
class ValueHolder{
private:
  T _privateValue;
  T* _sharedValue;
public:

  /**
   * \brief Constructor.
   *  sory for the bad comment.
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
  void unshare(){
    _privateValue = *_sharedValue;
    _sharedValue = & _privateValue;
  }

  void share(T & newValue ){
    _sharedValue = &newValue;
  }
  // causes the other value holders shared value to be copied to this shared value
  void mirror(ValueHolder<T> & source){
    _sharedValue = source._sharedValue;
  }
  inline T & operator()(){
    return *_sharedValue;
  }
  inline const T & operator()()const{    
    return *_sharedValue;
  }

  
  ValueHolder<T> & operator<< (ValueHolder<T> & source){
    mirror(source);
    return *this;
  }

  ValueHolder<T> & operator>> (ValueHolder<T> & sink){
    sink.mirror(*this);
    return *this;
  }
};
}