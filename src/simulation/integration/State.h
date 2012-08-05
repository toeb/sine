#pragma once
#include <ostream>
#include <valarray>


#include <math/definitions.h>

namespace nspace{

  typedef MatrixNxM StateMatrix;


  class IState{
  public:    
    inline Real & operator()(uint index, uint derivative){
      return value(index,derivative);
    }
    inline Real operator()(uint index, uint derivative)const{
      return value(index,derivative);
    }
    virtual void resize(uint dimension, uint derivative)=0;
    virtual uint dimension()const=0;
    virtual uint derivatives()const=0;


    void assign(const IState & b){
      IState & a = *this;
      a.resize(b.dimension(),b.derivatives());
      for(uint i = 0; i < a.dimension(); i++){
        for(uint j=0; j < a.derivatives(); j++){
          a(i,j) = b(i,j);
        }
      }
      
     
    }

    friend std::ostream & operator<<(std::ostream & out, const IState & state);
  protected:
    virtual Real & value(uint index, uint derivative)=0;
    virtual Real value(uint index, uint derivative)const=0;
  };

  
  class State: public IState{
  private:
    StateMatrix & _data;
  public:
    StateMatrix & data(){return _data;}
		const StateMatrix & data()const{return _data;}
    State(const StateMatrix & data);
    State(StateMatrix & data);
    State();

    virtual void resize(uint dimension, uint derivatives);
    IState* range(uint start, uint length);
    virtual uint dimension()const{return _data.rows();}
    virtual uint derivatives()const{return _data.cols();}

  protected:
    Real & value( uint index, uint derivative );
    Real value( uint index, uint derivative ) const;
  };



  class StateRange : public IState{
  private:
    uint _start;
    uint _length;
		IState & _state;
  public:
    StateRange(IState & state, uint start, uint length);
		StateRange(const IState & state, uint start, uint length);
    void resize(uint dimension, uint derivatives);
    uint dimension()const{return _length;}
		uint derivatives()const{return _state.derivatives();}
  protected:
    inline Real & value( uint index, uint derivative ){
      return _state(index+_start, derivative);
    }
    inline Real value( uint index, uint derivative ) const{
      return _state(index+_start, derivative);      
    }
  };

 
}