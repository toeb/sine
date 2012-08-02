#include "State.h"
#include <iomanip>
#include <ostream>
using namespace nspace;
using namespace std;


StateRange::StateRange( IState &data, uint start, uint length ) :
_start(start),
  _length(length),
  _state(data)
{

}
StateRange::StateRange(const IState & state, uint start, uint length):
_start(start),_length(length),_state(const_cast<IState&>(state)){

}

Real & nspace::StateRange::value( uint index, uint derivative )
{
	return _state(index+_start,derivative);
}

Real StateRange::value( uint index, uint derivative ) const
{
	return _state(index+_start, derivative);
}

void StateRange::resize( uint dimension, uint derivatives )
{
	if(derivatives < _state.derivatives()){
		derivatives = _state.derivatives();
	}
	_state.resize(_state.dimension() + dimension - _length,derivatives);
}

State::State( const StateMatrix & data ) :_data(const_cast<StateMatrix&>(data))
{

}

State::State() :_data(*new StateMatrix())
{

}

State::State( StateMatrix & data ) :_data(data)
{

}


Real & State::value( uint index, uint derivative )
{
  return _data(index,derivative);
}

Real State::value( uint index, uint derivative ) const
{
  return _data(index,derivative);
}

void State::resize( uint dimension, uint derivatives )
{
  _data.resize(dimension,derivatives);
	_data.setZero();
}
namespace mbslib{
std::ostream& operator<<(std::ostream & out, const IState & state){
  
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
  for(int i=0; i < state.dimension(); i++){
    out << std::setw(20)<<i;
    out << "||";
    for(int d=0; d < state.derivatives(); d++){
      out << std::setw(width) << std::setprecision(5) << state(i,d);
      out <<"|";
    }
    out << std::endl;
  }
  return out;
}

}

