#pragma once

#include <core.h>
namespace nspace{


  


  template<typename StateType, typename TokenType>
  class FiniteStateMachine{
  public:
    typedef StateType State;
    typedef TokenType Token;
    SIMPLE_PROPERTY(State*, CurrentState){
      if(oldvalue)oldvalue->leave(newvalue);
      if(newvalue)newvalue->enter(oldvalue);
    }
    SIMPLE_PROPERTY(State*, InitialState){
      _InitialState=newvalue;
      reset();
    }
  private:

  public:
    FiniteStateMachine(State * initialState):_CurrentState(0),_InitialState(initialState){
      reset();
    }
    void reset(){
      setCurrentState(0);
      setCurrentState(getInitialState());
    }
    void process(Token token){
      auto current = getCurrentState();
      if(!current)return;
      if(current->steal(token))return;
      current = current->transition(token);
      if(current)setCurrentState(current);
      getCurrentState()->consume(token);
    }




  };
  
  template<typename StateType, typename TokenType>
  class FiniteState : public Derivable<StateType>{
  public:    
    typedef StateType State;
    typedef TokenType Token;
    virtual State * transition(Token token){return 0;}
    virtual bool steal(Token token){return false;}
    virtual void consume(Token token){}
    virtual void enter(State * predecessor){}
    virtual void leave(State * successor){}
  };
  
template<typename StateType, typename TokenType>
class ExtendedFiniteState:public FiniteState<StateType,TokenType>{
public:
typedef StateType State;
typedef TokenType Token;
std::map<std::string,State*> transitions;
ExtendedFiniteState(){

}
virtual std::string token2str(const Token token){return "";}
void registerTransition(const Token token, State* state){
transitions[token2str(token)]=state;
}
void registerTransition(const std::string  & tokenName, State* state){
transitions[tokenName]=state;
}

virtual State* transition(Token token){
return transition(token2str(token));
}
private:
State* transition(const std::string & token){
auto it  = transitions.find(token);
if(it==transitions.end())return 0;
return it->second;
};
};

  template<typename Derived, typename TToken>
  class HierarchicalStateMachine :public Derivable<Derived>, public Object{    
  public:

    typedef Derived State;
    typedef TToken TokenType;

    SIMPLE_PROPERTY(State*,CurrentState){
      if(oldvalue)oldvalue->leave(newvalue);
      if(newvalue)newvalue->enter(oldvalue);
    }
    SIMPLE_PROPERTY(State*, ParentState){onParentSet(newvalue);}
    SIMPLE_PROPERTY(State*, InitialState){
      _InitialState = newvalue;
      reset();
    }
  public:


    State * parent(){
        return getParentState();
    }

    HierarchicalStateMachine():_CurrentState(0), _ParentState(0), _InitialState(0){
      enter(0);
    }

    virtual State * process(TokenType token){
      if(recursiveConsume(token))return &this->derived();

      auto newState = transition(token);
      recursiveConsume(token);
      return &this->derived();
    }

    int stateDepth()const{
      if(getCurrentState())return getCurrentState()->stateDepth()+1; 
      return 0;
    }
    State * currentChildState(int depth){
      if(depth){
        if(getCurrentState())return getCurrentState().currentChildState()-1;
        return 0;
      }
      return & this->derived();
    }

    inline State * leafState(){
      if(getCurrentState())return getCurrentState()->leafState();
      return &this->derived();
    }
  protected:
    virtual State* transition(TokenType token){ 
      auto current = getCurrentState();
      if(current){
        auto newstate = current->transition(token);
        setCurrentState(newstate);
      }
      if(getCurrentState())setCurrentState(getCurrentState()->transition(token));
      return &this->derived();
    }
    virtual bool consume(TokenType token){return false;}        

    virtual void enter(State*  predecessor){enter();};
    virtual void enter(){}
    virtual void leave(State*  successor){leave();}
    virtual void leave(){}
    virtual void onParentSet(State * parent){}
    
    void reset(){
      // so thate enter leave is called with 0
      setCurrentState(0);
      setCurrentState(getInitialState());
      onReset();
    }

    virtual void onReset(){}
  private:

    bool recursiveConsume(TokenType token){
      if(getCurrentState())return getCurrentState()->recursiveConsume(token);
      return consume(token);
    }


  };
  /*
  class Builder : public HierarchicalStateMachine<Builder>{

  };

  class VertexBuilder:public Builder{

  };

  class MeshBuilder2 : public Builder{
  protected:
  State transition(TokenType token){

  }
  };
  class tmpl{
  void dosmthn(){
  MeshBuilder2 b;
  b.process("vertex");
  b.process("vertex");

  b.process("face");
  }
  };*/

}
