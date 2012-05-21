#pragma once
#include <Visualization/IRenderer.h>
#include <AntTweakBar/AntTweakBar.h>
#include <Visualization/InputHandler.h>
#include <Simulation/ISimulationModule.h>
#include <Simulation/SimulationModuleBase.h>
#include <functional>
#include <map>
namespace IBDS{
class IAction : public virtual ISimulationObject{
public:
  virtual void execute()=0;
};

class DelegateAction : public virtual IAction{
std::function<void()>  _function;
public:
  DelegateAction(const std::string & name, std::function<void()>  function){
    _function = function;
      setName(name);
  }
  void execute(){
    _function();
  }
};

class ValueCallback : public virtual ISimulationObject{
public:
  ValueCallback(const std::string & name){setName(name);};
  virtual void set(const void * value)=0;
  virtual void get(void * value)=0;
};

class RealCallback : public virtual ValueCallback{
public:
  std::function<void (Real v)> setter;
  std::function<Real ()> getter;

  RealCallback(const std::string & name, std::function<Real ()> get,std::function<void (Real v)> set):ValueCallback(name){
    setter = set;
    getter = get;
  }
  void set(const void * val){
    const Real * realValue = reinterpret_cast<const Real*>(val);
    setter(*realValue);
  }
  void get(void * val){
    Real * value = reinterpret_cast<Real*>(val);
    *value = getter();

  }
};

  
class TweakBarRenderer 
  :public virtual IRenderer, 
  public IInputListener, 
  public virtual ISimulationModule
{
  private:
    bool _initialized;
  TwBar  * _tweakBar;
  std::vector<ISimulationObject * > _unprocessedObjects;
  std::map<std::string, IAction*> _actions;
  std::vector<ValueCallback * > _values;
  void addEntry(ISimulationObject * o);
  public:
    TweakBarRenderer();
    bool addSimulationObject(ISimulationObject * object);

    void processTweakBarEntries(ISimulationObject * object);
    bool removeSimulationObject(ISimulationObject * object);  
    
    void onKeyDown(Keys key);
    void onMouseDown(MouseButtons b);
    void onMouseUp(MouseButtons b);
    void onMouseMove(int x, int y, int dx,int dy);

    void render();    
    void sceneResized(int newWidth, int newHeight);
protected:
  
  bool initializeObject();
  void cleanupObject();
private:
   void addAction(IAction * action);
    void addValueCallback(ValueCallback * value);
  };
}