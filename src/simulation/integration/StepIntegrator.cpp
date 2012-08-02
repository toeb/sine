/*
* Copyright (C) 2011
* Simulation, Systems Optimization and Robotics Group (SIM)
* Technische Universitaet Darmstadt
* Hochschulstr. 10
* 64289 Darmstadt, Germany
* www.sim.tu-darmstadt.de
*
* This file is part of the mbslib.
* All rights are reserved by the copyright holder.
*
* The mbslib is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* You may use the mbslib or parts of it only with the written permission of the copyright holder.
* You may NOT modify or redistribute any part of the mbslib without the prior written
* permission by the copyright holder.
*
* Any violation of the rights and restrictions mentioned above will be prosecuted by civil and penal law.
* Any expenses associated with the prosecution will be charged against the violator.
*/

#include "StepIntegrator.h"
using namespace nspace ;

void StepIntegrator::doIntegration(Real  a, Real b){
  setLowerBound(a);
  setUpperBound(b);
  _t=a;
  while(needsIntegration()){   
    //std::cout << f(_t,x(),0.1) << std::endl;
    step();
  }
}

/*
void StepIntegrator::log(const TVectorX & x_i,  TTime t, TTime h, int step)const{
  if(!this->getLog())return;
  std::ostream & o = *(this->getLog());    
  o<<"<step number=\""<<step<<"\" time=\""<<t<<"\" h=\""<<h<<"\" errorEstimate=\""<<getErrorEstimation()<<"\" evaluations=\""<<getEvaluationCount()<<"\">\n  <state>";
  for(int i=0; i < x_i.rows()-1;i++){
    o<<x_i[i]<<" ";
  }
  o<<x_i[x_i.rows()-1];    
  o<<"</state>\n</step>\n";    
};*/

void StepIntegrator::logParameters(std::ostream & o)const{
  o << "<parameter name=\"stepSize\">"<<h0()<<"</parameter>\n"; 
}
