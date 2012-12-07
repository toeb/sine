#include "State.h"
#include <iomanip>
#include <ostream>
using namespace nspace;
using namespace std;


namespace nspace{
std::ostream& operator<<(std::ostream & out, const SystemState & state){
  
  int width = 16;
  out << std::setw(20)<<"index\\derivative";
  out << "||";
  for(int i=0;i < state.derivatives(); i++){
    out << std::setw(width)<<i;
    out << "|";
  }
  out <<endl;
  out << setw((width+1)* state.derivatives() + 22)<< setfill('-')<< "-";
  out << setfill(' ')<<endl;
  for(uint i=0; i < state.dimension(); i++){
    out << std::setw(20)<<i;
    out << "||";
    for(uint d=0; d < state.derivatives(); d++){
      out << std::setw(width) << std::setprecision(5) << state(i,d);
      out <<"|";
    }
    out << std::endl;
  }
  return out;
}

}

SystemState::SystemState(uint offset, uint dimension, uint derivatives, SystemState & parent):
  _parent(&parent),_stateMatrix(parent._stateMatrix),_offset(offset),_dimension(dimension),_derivatives(derivatives){ }

SystemState::SystemState():_parent(0),_stateMatrix(0),_offset(0),_dimension(0),_derivatives(0){ }
