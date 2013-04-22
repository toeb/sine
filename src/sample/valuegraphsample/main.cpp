#include <utility.valuegraph/valuegraph.h>
#include <iostream>
#include <math/core.h>
#include <core.graph/Node.h>
#include <core.collection/ValueLookup.h>
#include <core.logging.h>
#include <core.reflection/binding/Binding.h>
#include <core.reflection/binding/ValueConverter.h>
using namespace nspace;
using namespace std;


/*
template<typename T>
class DependentValue : public TypedValue<T>{
private:
  Set<ChangeTracker*> _trackedValues;
public:
  DependentValue(){}
  ~DependentValue(){
    _trackedValues.foreachElement([](ChangeTracker * tracker){
      delete tracker;
    });
  }
  bool dirty(){
    bool result=false;
    _trackedValues.foreachElement([&result](ChangeTracker * changeTracker){
      if(result)return;
      result = changeTracker->hasChanged();
    });
    return result;
  }

  virtual T calculate()=0;


  void update(){
    if(dirty()) this->set(calculate());
  }

protected:
  void addDependency(const Value & value){
    _trackedValues.add(new ChangeTracker(value));
  }
};

class IntAddition : public DependentValue<int>{
private:
  const int & _a;
  const int & _b;
public:
  
  IntAddition(const TypedValue<int> & a, const TypedValue<int> & b):_a(a.reference()),_b(b.reference()){
    addDependency(a);
    addDependency(b);
    update();
  }

  int calculate(){
    return _a+_b;
  }
};
class VectorTransform :public DependentValue<Vector3D>{
private:
  const Quaternion & _orientation;
  const Vector3D & _position;
  const Vector3D & _relativePosition;
public:
  VectorTransform(const Vector3D & relativePosition, const TypedValue<Quaternion> & orientation, const TypedValue<Vector3D> & position):
      _orientation(orientation),_position(position),_relativePosition(relativePosition){

  }
  Vector3D calculate(){
    //Matrix3x3 R;
    //_orientation.toRotationMatrix(R);
	  Matrix3x3 R = _orientation.toRotationMatrix();
    return _position + R * _relativePosition;
  }
};

class Coordinates{

};
class NamedValueHolder{

};
class PropertyObject{
public:
  ValueLookup * _lookup;
  
  PropertyObject():_lookup(0){}

  void setData(ValueLookup * lookup){

  }
  ValueLookup * lookup(){
    return _lookup;
  }

  virtual void setupValues()=0;

  void require(NamedValueHolder & valueHolder){
    
  }

};
class Body : public PropertyObject{
public:
  TypedValue<Quaternion> orientation;
  TypedValue<Vector3D> position;

  void setupValues(ValueLookup & lookup){
    
  }

  

};
class AutoConnector{
public:
  AutoConnector(Body & body):p_wcs(p_ocs,body.orientation,body.position){}
  TypedValue<Vector3D> p_ocs;
  VectorTransform p_wcs;  
};


class TestClass : public virtual PropertyChangingObject{
  REFLECTABLE_OBJECT(TestClass);
  PROPERTY(nspace::Vector3D,Vec){cout << "value changed from "<<oldvalue <<" "<<newvalue<<endl;}
  PROPERTY(int, IntegerValue){cout << "value changed from "<<oldvalue <<" "<<newvalue<<endl;}
  PROPERTY(int, OtherInt){cout << "value changed from "<<oldvalue <<" "<<newvalue<<endl;}
};



int main(int argc, const char ** argv){
  TestClass c1,c2;
  
  Binding::create(&c1,"IntegerValue", &c2, "OtherInt");
  Binding::create(&c2,"OtherInt", &c1, "IntegerValue");
  
  c1.setIntegerValue(3);

  TypedObservableValue<int> a =0;
  ValueHistory<int>  history(a);

  a.addObserver(new ValueObserverDelegate([&history](void * sender){
    cout << history <<endl;
  }));
  ChangeTracker tracker = a;

  CachedValue<int> cachedA = a;
  ValueHistory<int>  cachedHistory(cachedA,10U);
  
  cachedA.addObserver(new ValueObserverDelegate([&cachedHistory](void * sender){
    cout << "cached history " <<cachedHistory<<endl;
  }));


  bool dirty = tracker.hasChanged();
  
  cout << "dirty: "<<dirty<<endl;
  
  
  for(int i=0; i < 20; i++)a.set(i);

  cachedA.cache();
  cachedA.cache();
  cout << "dirty: "<<tracker.hasChanged()<<endl;

  TypedValue<int> b =5;

  
  IntAddition sum(a,b);

  
  sum.update();
  cout << sum <<endl;
  a.set(30);
  sum.update();
  cout << sum <<endl;
}
*/