#include "TrajectoryReader.h"

using namespace nspace;
using namespace std;

template<typename TY>
class LinearInterpolation : public Function<TY, Real>{  
public:
  TY _a;
  TY _b;
  LinearInterpolation(const TY & a, const TY & b):_a(a),_b(b){
  }
  inline bool evaluate(TY & result, const Real & x){
    // expect x to be between 0 and 1
    result = _a*(1-x)+_b*x;
    return true;
  }
};


template<typename TY, typename Func>
class NormalizedBoundedFunction : public Function<TY,Real>{
public :
  Interval _interval;
  Func _function;
  NormalizedBoundedFunction(const Interval & interval, const Func &  function):_function(function),_interval(interval){}
  
  inline bool evaluate(TY & result, const Real & x){
    // normalize x
    Real normalizedX = x - _interval.a;
    normalizedX /= _interval.length();
    return _function.evaluate(result, normalizedX);
  }
};
bool TrajectoryReader::read(std::istream & stream, PiecewiseFunction<VectorND>** trajectory){    
  if(!stream)return false;

  // read dimension of the trajectory
  int dim;
  stream >> dim;
  string line1;
  string line2;
  getline(stream,line1);
  getline(stream,line2);
  // read the number of knots
  uint knots;
  stream >> knots;
  // read the interval over which the function is defined
  Interval d;
  stream >> d.a; stream >> d.b;
  getline(stream,line1);
  // read all names
  vector<std::string> names;
  for(int i=0; i < dim; i++){
    string name;
    getline(stream,name);
    names.push_back(name);
  }
  // read all doubles
  vector<double> doubles;
  while(stream){
    double tmp;    
    stream >> tmp;
    doubles.push_back(tmp);
  }
  //remove last double because it is invalid. (hopefully always
  doubles.pop_back();
  // time entries
  int order=3;
  // calculate the number of doubles needed for cubic or linear piecwise function 
  int cubic = (dim*(order+1)+2)*(knots-1)+dim+1;
  int linear = (dim+1)*knots;
  PiecewiseFunction<VectorND> * piecewise= new PiecewiseFunction<VectorND>;


  if(doubles.size()==cubic){      
    if(!  parseCubicPiecewiseFunction(piecewise,doubles,dim))return false;
  }else if(doubles.size()==linear){
    if(!  parseLinearPiecewiseFunction(piecewise,doubles,dim))return false;
  }    else{
    return false;
  }
  // add a zero polynom as the last element
  piecewise->add(d.b,0);
  setLastTrajectory(piecewise);
  if(trajectory)*trajectory=piecewise;
  return true;
}

bool TrajectoryReader::parseCubicPiecewiseFunction(PiecewiseFunction<VectorND> * piecewise, std::vector<double> & doubles, int dim){
  
  std::vector<MatrixNxM> a;
  std::vector<Real> t;  
  uint k=0;
  
  uint stride = dim*4+2;
  uint lastStride = dim+1;

  // 
  for(int offset=0; offset < doubles.size()-lastStride; offset+=stride){    
    Real t_k = doubles[offset+0];
    Real t_k_plus1= doubles[offset+1];
    int coeffOffset_k = offset+2;
    MatrixNxM a_k;    
    a_k.resize(dim,4);
    a_k.setZero();
    for(int j=0; j < dim; j++){
        a_k(j,0)=doubles[coeffOffset_k+j*4+0];
        a_k(j,1)=doubles[coeffOffset_k+j*4+1];
        a_k(j,2)=doubles[coeffOffset_k+j*4+2];
        a_k(j,3)=doubles[coeffOffset_k+j*4+3];
    }

    t.push_back(t_k);
    a.push_back(a_k);
    k++;
  }
  t.push_back(doubles[doubles.size()-lastStride]);
  uint i=0;
  for(int offset=doubles.size()-lastStride+1; offset < doubles.size();offset++ ){
    
    MatrixNxM a_k;
    a_k.resize(dim,4);
    a_k.setZero();
    a_k(i,0)=doubles[offset];
    a_k(i,1)=0;
    a_k(i,2)=0;
    a_k(i,3)=0;
    i++ ;
  }
  k++;
  uint n =k;



  typedef NormalizedBoundedFunction<VectorND,Polynom<VectorND,MatrixNxM>> NormalizedCubicInterpolation;

  NormalizedCubicInterpolation * f_k=0;
  for(int i=0; i < n-1;i++){
    
    Interval interval(t[i],t[i+1]);

    Polynom<VectorND,MatrixNxM> polynom;
    polynom.setCoefficients(a[i]);
    f_k = new NormalizedCubicInterpolation(interval,polynom);
    piecewise->add(t[i],f_k);

  }
  return true;
}



typedef  NormalizedBoundedFunction<VectorND,LinearInterpolation<VectorND>> NormalizedLinearInterpolation;

bool TrajectoryReader::parseLinearPiecewiseFunction(PiecewiseFunction<VectorND> * piecewise, std::vector<double> & doubles, int dim){
  // create all sample points and times
  std::vector<Real> t;
  std::vector<VectorND> u;
  uint n=0;
  for(int i=0; i < doubles.size(); i+=(1+dim)){

    Real t_k = doubles[i];
    VectorND u_k;
    u_k.resize(dim,1);

    for(int j=0; j < dim; j++){
      u_k(j)=doubles[i+1+j];
    }
    t.push_back(t_k);
    u.push_back(u_k);
    n++;
  }
  NormalizedLinearInterpolation * f_k=0;
  
  for(int k=0; k < n-1;k++){
    Interval interval(t[k],t[k+1]); // create interval
    LinearInterpolation<VectorND> interpolation(u[k] ,u[k+1]);// create linear interpolation between two sample points
    f_k = new NormalizedLinearInterpolation(interval,interpolation); // create normalized interpolation function
    piecewise->add(t[k],f_k);    
  }
  return true;
}
