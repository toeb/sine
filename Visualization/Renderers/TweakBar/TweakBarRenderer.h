#pragma once
#include <Visualization/IRenderer.h>
#include <AntTweakBar/AntTweakBar.h>
#include <Visualization/InputHandler.h>
#include <Simulation/ISimulationModule.h>
#include <Simulation/SimulationModuleBase.h>
#include <functional>
#include <map>

#include <Visualization/UserInterface/IComponent.h>
#include <Visualization/UserInterface/IAction.h>
#include <Visualization/UserInterface/IValue.h>
#include <Visualization/UserInterface/IUserInterface.h>

namespace IBDS{
  
class TweakBarRenderer 
  :public virtual IRenderer, 
  public virtual IInputListener, 
  public virtual ISimulationModule,
  public virtual IUserInterface
{
  private:
    bool _initialized;
    TwBar  * _tweakBar;
    std::vector<ISimulationObject * > _unprocessedObjects;
    std::map<std::string, IAction*> _actions;
    std::vector<IValue * > _values;
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

    void addComponent(IComponent * component);

protected:
  
  bool initializeObject();
  void cleanupObject();
private:
    void addAction(IAction * action);
    void addValueCallback(IValue * value);
};
}