#include "TrajectoryReader.h"

using namespace nspace;
using namespace std;

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
  Polynom<VectorND,MatrixNxM>* part = new Polynom<VectorND,MatrixNxM>;
  MatrixNxM a;
  a.resize(dim,2);
  a.setZero();    
  setLastTrajectory(piecewise);
  if(trajectory)*trajectory=piecewise;
  return true;
}

bool TrajectoryReader::parseCubicPiecewiseFunction(PiecewiseFunction<VectorND> * piecewise, std::vector<double> & doubles, int dim){
  return false;
}

bool TrajectoryReader::parseLinearPiecewiseFunction(PiecewiseFunction<VectorND> * piecewise, std::vector<double> & doubles, int dim){
  Polynom<VectorND,MatrixNxM> * part=0;
  for(int i=0; i < doubles.size();i+=(1+dim)){
    part = new Polynom<VectorND,MatrixNxM>;
    double startTime=doubles[i];
    VectorND startValue;
    startValue.resize(dim,1);
    startValue.setZero();
    piecewise->evaluate(startValue, startTime);
    MatrixNxM a;
    a.resize(dim,2);
    a.setZero();
    for(int j=0; j < dim; j++){
      a(j,1)=doubles[i+1+j];
      a(j,0)=startValue(j);
    }
    part->setCoefficients(a);
    piecewise->add(startTime,part);

  }
  return true;
}