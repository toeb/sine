#pragma once
#include <ostream>
#include <math/definitions.h>

namespace nspace{

  typedef MatrixNxM StateMatrix;

  class State{
    State * _parent;
    StateMatrix *_stateMatrix;
    uint _offset;
    uint _dimension;
    uint _derivatives;

    State(uint offset, uint dimension, uint derivatives, State & parent):_parent(&parent),_offset(offset),_derivatives(derivatives),_stateMatrix(parent._stateMatrix),_dimension(dimension){

    }
  public:

    State():_parent(0),_derivatives(0),_offset(0),_dimension(0),_stateMatrix(0){

    }

    ~State(){
      //if(!_parent)delete &_stateMatrix;
    }
    inline uint derivatives()const{return _derivatives;}
    inline uint dimension()const{return _dimension;}
    inline Real & operator()(uint stateIndex, uint derivative){
      return _stateMatrix->operator()(_offset+stateIndex,derivative);
    }
    inline const Real & operator()(uint stateIndex, uint derivative)const{
      return _stateMatrix->operator()(_offset+stateIndex,derivative);
    }

    Real * stateVector(uint derivative){
      return _stateMatrix->rowData(derivative)+_offset;
    }
    void getState(StateMatrix & state){
      state.resize(_derivatives,_dimension,false);
      _stateMatrix->getBlock(state,0,_offset);
    }
    void setState(StateMatrix & state){
      if(state.rows()!=derivatives() || state.cols()!=dimension()){
        std::cerr << "State::Could not set state " << std::endl;
        return;
      }
      _stateMatrix->setBlock(0,_offset,state);
    }
    void getX(StateMatrix & x)const{
      x.resize(_derivatives-1,_dimension,false);
      _stateMatrix->getBlock(x,0,_offset);
    }
    void getXDot(StateMatrix & xDot)const{
      xDot.resize(_derivatives-1,_dimension,false);
      _stateMatrix->getBlock(xDot,1,_offset);
    }
    void setX(const StateMatrix & x){
      if(x.rows()!=derivatives()-1 || x.cols()!=dimension()){
        std::cerr << "State::Could not set state " << std::endl;
        return;
      }
      _stateMatrix->setBlock(0,_offset,x);
    }

    void resize(uint newDim, uint newDerivs){
      if(!_stateMatrix )_stateMatrix = new StateMatrix();
      if(_parent)return;
      _derivatives = newDerivs;
      _dimension = newDim;
      _stateMatrix->resize(newDerivs,newDim,false);
    }
    State * range(uint offset, uint dim ,uint derivatives){
      State * result = new State(offset,dim,derivatives,*this);
      return result;
    }
  };

  std::ostream & operator << (std::ostream & o, const State & state);
}