#pragma once
#include <ostream>
#include <math/core.h>

namespace nspace{

  typedef MatrixNxM StateMatrix;

  // represents the state and its derivatives.
  // this class manages the vectors for each derivative by putting them into one large matrix
  // state is a recursive datatype allowing substates which have the same data as the parent state
  // TODO: error checking needs to be done so that no unintended behaviour occurs when the state is empty
  class State{
    State * _parent;
    StateMatrix *_stateMatrix;
    uint _offset;
    // number of state vars = dimension of state
    uint _dimension;
    // number of derivatives x => 1;  x xDot => 2; x, xDot, xDotDot => 3 
    uint _derivatives;

    // private constructor
    State(uint offset, uint dimension, uint derivatives, State & parent);
  public:
    // public constructor initializes state to an empty state
    // clients need to resize it to their needs
    State();

    ~State(){
      //if(!_parent)delete &_stateMatrix;
    }

    // the number of derivatives
    inline uint derivatives()const{return _derivatives;}
    // the dimension
    inline uint dimension()const{return _dimension;}

    // matrix style access
    inline Real & operator()(uint stateIndex, uint derivative){
      return _stateMatrix->operator()(_offset+stateIndex,derivative);
    }

    // matrix style const access
    inline const Real & operator()(uint stateIndex, uint derivative)const{
      return _stateMatrix->operator()(_offset+stateIndex,derivative);
    }

    // returns the data pointer to the state vector
    inline Real * stateVector(uint derivative){
      Real * data = _stateMatrix->data();
      return data +(derivative*_stateMatrix->cols()+_offset);
      //return _stateMatrix->rowData(derivative)+_offset;
    }

    // files the state matrix with the state ( it will resize the matrix accordingly)
    inline void getState(StateMatrix & state){      
      if(_derivatives == 0 && _dimension==0)return;
      state.resize(_derivatives,_dimension);
      //state.resize(_derivatives,_dimension,false);
      matrix::getBlock(state,*_stateMatrix,0,_offset);
      //state = _stateMatrix->block(0,_offset,_derivatives,_dimension);
      //_stateMatrix->getBlock(state,0,_offset);
    }

    // sets the state to the values of the statematrix passed
    inline void setState(StateMatrix & state){
      if(state.rows()!=derivatives() || state.cols()!=dimension()){
        std::cerr << "State::Could not set state " << std::endl;
        return;
      }
      
      matrix::setBlock(*_stateMatrix,state,0,_offset);
      //_stateMatrix->block(0,_offset,_derivatives,_dimension) = state;
      //_stateMatrix->setBlock(0,_offset,state);
    }

    // gets the 0th derivative
    void getX(StateMatrix & x)const{      
      if(_derivatives==0){/* ERROR("There are no derivatives present"); */return ;}
      //x.resize(_derivatives-1,_dimension,false);
      x.resize(_derivatives-1,_dimension);
      x.setZero();
      //x = _stateMatrix->block(0,_offset,_derivatives-1,_dimension);
      matrix::getBlock(x,*_stateMatrix,0,_offset);
      //_stateMatrix->getBlock(x,0,_offset);
    }

    // gets the first derivative
    void getXDot(StateMatrix & xDot)const{
      //xDot.resize(_derivatives-1,_dimension,false);
      //_stateMatrix->getBlock(xDot,1,_offset);
      if(_derivatives==0){ /*ERROR("There are no derivatives present");*/ return ;}
      xDot.resize(_derivatives-1,_dimension);
      xDot.setZero();
      matrix::getBlock(xDot,*_stateMatrix,1,_offset);
      //x = _stateMatrix->block(1,_offset,_derivatives-1,_dimension);
      
    }

    // sets the 0th derivative
    void setX(const StateMatrix & x){
      if(x.rows()!=derivatives()-1 || x.cols()!=dimension()){
        std::cerr << "State::Could not set state " << std::endl;
        return;
      }
      matrix::setBlock(*_stateMatrix,x,0,_offset);
      //_stateMatrix->setBlock(0,_offset,x);
    }
    // resizes the state
    void resize(uint newDim, uint newDerivs){
      if(!_stateMatrix )_stateMatrix = new StateMatrix();
      if(_parent)return;
      _derivatives = newDerivs;
      _dimension = newDim;
      _stateMatrix->resize(newDerivs,newDim);
      //_stateMatrix->resize(newDerivs,newDim,false);
    }

    // returns a state range 
    State * range(uint offset, uint dim ,uint derivatives){
      State * result = new State(offset,dim,derivatives,*this);
      return result;
    }
  };

  // prints the state
  std::ostream & operator << (std::ostream & o, const nspace::State & state);
}
