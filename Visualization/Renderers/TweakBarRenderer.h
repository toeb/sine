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
/*
class SimulationObjectSelector : public SimulationModuleBase<ISimulationObject> {
private:
  std::function<void(ISimulationObject *)> displayName;
  std::function<const char * (ISimulationObject * )> onSelection;
public:
  SimulationObjectSelector(const std::string & name){
    setName(name);
  };
  void setDisplayNameDelegate(std::function<std::string (ISimulationObject * )> f){displayName=f;}
  void setOnSelectionDelegate(std::function<void(ISimulationObject *)> f){onSelection = f;}
};
*/

class RealValue : public virtual ISimulationObject{
private:
  Real & _value;
public:
  RealValue(const std::string & name, Real & value):_value(value){
    setName(name);
  }
  Real & getValue(){
    return _value;
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
  std::vector<RealValue * > _values;
 // std::map<std::string, SimulationObjectSelector*> _selectors;
 // std::map<std::string, Value * > _values;
 
  void addEntry(ISimulationObject * o);
  public:
    TweakBarRenderer();
    bool addSimulationObject(ISimulationObject * object);

    void processTweakBarEntries(ISimulationObject * object);

    bool removeSimulationObject(ISimulationObject * object);

    void addAction(IAction * action);
   // void addSelector(SimulationObjectSelector * selector);
    void addValue(RealValue * value);
    
    void onKeyDown(Keys key);
    void onMouseDown(MouseButtons b);
    void onMouseUp(MouseButtons b);
    void onMouseMove(int x, int y, int dx,int dy);

    void render();    
    void sceneResized(int newWidth, int newHeight);
protected:
  
  bool initializeObject();
  void cleanupObject();
  };
}