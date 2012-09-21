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
    static inline void setBlock(StateMatrix & matrix, const StateMatrix & block, uint rowIndex, uint colIndex){
      
#if MATRIX_CLASSES == 3
      uint newrows = block.rows();
      uint newcols = block.cols();
      matrix.block(rowIndex,colIndex,newrows,newcols) = block;
#else
      matrix.setBlock(rowIndex,colIndex,block);
#endif

    }
    static inline void getBlock(StateMatrix & block, const StateMatrix & matrix, uint rowIndex,uint colIndex){
#if MATRIX_CLASSES == 3
      uint newrows = block.rows();
      uint newcols = block.cols();
      block= matrix.block(rowIndex,colIndex,newrows,newcols);
#else
      matrix.getBlock(block,rowIndex,colIndex);
#endif
    }
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
      Real * data = _stateMatrix->data();
      return data +(derivative*_stateMatrix->cols()+_offset);
      //return _stateMatrix->rowData(derivative)+_offset;
    }
    void getState(StateMatrix & state){      
      if(_derivatives == 0 && _dimension==0)return;
      state.resize(_derivatives,_dimension);
      //state.resize(_derivatives,_dimension,false);
      
      getBlock(state,*_stateMatrix,0,_offset);
      //state = _stateMatrix->block(0,_offset,_derivatives,_dimension);
      //_stateMatrix->getBlock(state,0,_offset);
    }
    void setState(StateMatrix & state){
      if(state.rows()!=derivatives() || state.cols()!=dimension()){
        std::cerr << "State::Could not set state " << std::endl;
        return;
      }
      
      setBlock(*_stateMatrix,state,0,_offset);
      //_stateMatrix->block(0,_offset,_derivatives,_dimension) = state;
      //_stateMatrix->setBlock(0,_offset,state);
    }
    void getX(StateMatrix & x)const{
      //x.resize(_derivatives-1,_dimension,false);
      x.resize(_derivatives-1,_dimension);
      //x = _stateMatrix->block(0,_offset,_derivatives-1,_dimension);
      getBlock(x,*_stateMatrix,0,_offset);
      //_stateMatrix->getBlock(x,0,_offset);
    }
    void getXDot(StateMatrix & xDot)const{
      //xDot.resize(_derivatives-1,_dimension,false);
      //_stateMatrix->getBlock(xDot,1,_offset);
      xDot.resize(_derivatives-1,_dimension);
      
      getBlock(xDot,*_stateMatrix,1,_offset);
      //x = _stateMatrix->block(1,_offset,_derivatives-1,_dimension);
      
    }
    void setX(const StateMatrix & x){
      if(x.rows()!=derivatives()-1 || x.cols()!=dimension()){
        std::cerr << "State::Could not set state " << std::endl;
        return;
      }
      setBlock(*_stateMatrix,x,0,_offset);
      //_stateMatrix->setBlock(0,_offset,x);
    }

    void resize(uint newDim, uint newDerivs){
      if(!_stateMatrix )_stateMatrix = new StateMatrix();
      if(_parent)return;
      _derivatives = newDerivs;
      _dimension = newDim;
      _stateMatrix->resize(newDerivs,newDim);
      //_stateMatrix->resize(newDerivs,newDim,false);
    }
    State * range(uint offset, uint dim ,uint derivatives){
      State * result = new State(offset,dim,derivatives,*this);
      return result;
    }
  };

  std::ostream & operator << (std::ostream & o, const State & state);
}