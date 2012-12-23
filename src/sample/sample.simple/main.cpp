#include <application.sample.h>
#include <visualization.opengl.renderer.geometry.h>
#include <simulation.dynamics.h>
#include <simulation.utility/DynamicsAlgorithm.h>
#include <fstream>
#include <utility.reader/Reader.h>
#include <utility.reader.trajectory.h>
#include <userinterface.qt.controls/DoubleRangeWidget.h>
#include <QDeclarativeView>
#include <QApplication>
#include <userinterface.qt.controls/DoubleSliderWidget.h>
#include <userinterface.qt.controls/StringWidget.h>
#include <core/binding/Binding.h>
#include <userinterface.qt.controls/BoolWidget.h>
#include <csignal>
#include <algorithm>
using namespace nspace;
using namespace std;

class TrajectorySystemFunction : public virtual ISystemFunction, public virtual PropertyChangingObject{
  REFLECTABLE_OBJECT(TrajectorySystemFunction);
public:
  typedef Function<StateMatrix,Real> Trajectory;
  SIMPLE_PROPERTY(Trajectory*, Trajectory){}
  SIMPLE_PROPERTY(StatefulObject*, StatefulObject){}
public:

  TrajectorySystemFunction():_Trajectory(0),_StatefulObject(0){

  }
  virtual void evaluate(Time t, Time h){
    auto trajectory = getTrajectory();
    auto state=getStatefulObject();
    if(!trajectory)return;
    if(!state)return;
    VectorND x;
    trajectory->evaluate(x,t);

    //s.setState();


  }
};

class MySample : public Sample, public virtual PropertyChangingObject, public virtual NamedObject{
  REFLECTABLE_OBJECT(MySample);
  PROPERTY(Real, value){}
  ACTION(TestAction){
    cout << " test message " <<endl;
  }
public:

  Sphere * sphere;
  Time time;
  PiecewiseFunction<Vector3D> * f;
  void operator()(Time dt, Time t){
    if(!sphere)return;
    time+=dt;
    Vector3D v;
    f->evaluate(v,time);
    sphere->coordinates().position()=v;

  }

  MySample():sphere(0){
    setName("MySample");
  }
  void setup(){
    time=0;
    auto algorithm = new DynamicsAlgorithm();

    auto body = new RigidBody();

    auto evaluator = new Evaluator(body->kinematics(),algorithm);
    application().getIntegrator()->setEvaluator(evaluator);
    f = new PiecewiseFunction<Vector3D>();

    MatrixNxM tmp(3,4);
    auto poly1=new Polynom<Vector3D,MatrixNxM>();
    tmp(0,0)=0;
    tmp(1,0)=0;
    tmp(2,0)=0;
    tmp(0,1)=1;
    tmp(1,1)=1;
    tmp(2,1)=1;
    tmp(0,2)=0;
    tmp(1,2)=0;
    tmp(2,2)=0;
    tmp(0,3)=0;
    tmp(1,3)=0;
    tmp(2,3)=0;
    poly1->setCoefficients(tmp);
    auto poly2=new Polynom<Vector3D,MatrixNxM>();
    tmp(0,0)=1;
    tmp(1,0)=1;
    tmp(2,0)=1;
    tmp(0,1)=-1;
    tmp(1,1)=-1;
    tmp(2,1)=-1;
    tmp(0,2)=1;
    tmp(1,2)=0;
    tmp(2,2)=0;
    tmp(0,3)=0;
    tmp(1,3)=0;
    tmp(2,3)=0;
    poly2->setCoefficients(tmp);
    f->add(0,poly1);
    f->add(1,poly2);
    f->add(2,poly1);
    f->add(3,poly2);
    f->add(4,poly1);
    f->add(5,poly2);
    f->add(6,poly1);
    f->add(7,poly2);
    f->add(8,poly1);
    f->add(9,poly2);
    f->add(10,poly1);
    f->add(11,poly2);
    f->add(12,poly1);
    f->add(13,poly2);
    f->add(14,poly1);

    // create a sphere with radius 0.5
    sphere = new Sphere(0.5);

    auto task = new ScheduledTaskDelegate<MySample>(*this);
    task->setInterval(0.001);
    task->setIsOneTimeTask(false);
    Components()|=task;

    Components()|=algorithm;

    // create a sphere renderer
    auto sphereRenderer = new SphereRenderer();
    // add renderer to component set
    Components() |= sphereRenderer;

    // add sphere to renderer
    *sphereRenderer |= sphere;

    // print setup of sample app
    // application().printSetup();
    // application().printHierarchy();
  }
};

class NumberRangeAttribute{

};
class ValidationAttribute{

};

#define ATTRIBUTE(TARGET,ATTRIBUTENAME,CODE)\
  STATIC_INITIALIZER(TARGET##ATTRIBUTENAME,  {auto attribute = new ATTRIBUTENAME##Attribute(); { CODE;} })

class Test : public virtual PropertyChangingObject{
  TYPED_OBJECT(Test);


  //ATTRIBUTE(IntValue, new NumberRangeAttribute(-5,5));
  //ATTRIBUTE(IntValue, new ValidationAttribute([](bool & valid){}));
  //ATTRIBUTE(IntValue, new DisplayAttribute()

  PROPERTY(int, IntValue){}


};

/*
template<typename ElementType, typename CollectionType, typename IndexType>
class CollectionConstAccess{
public:
static bool operation(ElementType& element, const CollectionType & collection, const IndexType & index){    
element = list[index];
return true;
}
};


template<typename ElementType, typename CollectionType, typename IndexType>
class CollectionInsert{
public:
static bool operation(CollectionType & collection, ElementType& element, const IndexType & index){
return false;
}
};
template<typename ElementType, typename CollectionType, typename IndexType>
class CollectionRemove{
public:
static bool operation(CollectionType & collection, const ElementType& element,const IndexType & index){
return false;
}
};
template<typename ElementType, typename CollectionType, typename IndexType>
class CollectionSwap{
public:
static bool operation(CollectionType & collection, const IndexType & indexOld,const IndexType & indexNew){
return false;  
}
};

template<typename ElementType, typename CollectionType, typename IndexType, typename Function>
class CollectionIterate{
public:
static bool operation(Function & function, CollectionType & collection){
for(IndexType i =0; i < size(collection); i++){
function(element(collection,i));
}
}
};
template<typename ElementType, typename CollectionType, typename IndexType, typename Function>
bool iterate(Function & function, CollectionType & container){
return CollectionIterate<ElementType,CollectionType,IndexType,Function>::operation(function,container);
}

template<typename ListIndex, typename IndexType=uint, IndexType RowCount=0, IndexType ColumnCount=0>
class RowMajorIndex{
public:
static inline ListIndex operation(const IndexType & i, const IndexType& j){
return 
}
};

template<typename Coefficient, typename Mat, typename Index>
class MatrixCoefficentMutableAccess{
public:
static Coefficient & operation(Mat & mat, const Index &i, const Index & j){
return mat(i,j);
}  
};
template<typename Coefficient, typename Mat, typename Index>
class MatrixCoefficentConstAccess{
public:
static const Coefficient & operation(const Mat & mat, const Index &i, const Index & j){
return mat[Index(i,j)]
}  
};


template<typename T,typename Mat, typename Index>
T & coefficient(Mat & mat, const Index & i, const Index & j){
return MatrixCoefficentMutableAccess<T,Mat,Index>::operation(mat)
}
template<typename T,typename Mat, typename Index>
const T & coefficient(const Mat & mat, const Index & i, const Index & j){
return MatrixCoefficentConstAccess<T,Mat,Index>::operation(mat);
}



*/
#include <iostream> // u.a. fuer cin/cout
#include <string> // fuer Datentyp string
#include <fstream> // fuer Dateiverarbeitung
#include <sstream> // fuer Stringverarbeitung
using namespace std;




int main(int argc,  char ** argv)
{

//  return 0;
  // instanciate sample
  MySample sample;
  // create sample application
  SampleApplication app(argc,argv, sample);
  // run sample application
  return app.run();
}
