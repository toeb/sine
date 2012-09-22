#pragma once
#include <visualization/IRenderer.h>
#include <anttweakbar/AntTweakBar.h>
#include <simulation.interaction/InputHandler.h>
#include <simulation/ISimulationModule.h>
#include <simulation/SimulationModuleBase.h>
#include <functional>
#include <map>


#include <simulation.access/IAction.h>
#include <simulation.access/IValue.h>


namespace nspace{
  
class TweakBarRenderer 
  :
  public virtual IRenderer, 
  public virtual IInputListener, 
  public virtual ISimulationModule
{
  private:
    bool _initialized;
    TwBar  * _tweakBar;
    std::vector<ISimulationObject * > _unprocessedObjects;
    std::map<std::string, IAction*> _actions;
    std::vector<IValue * > _values;
    void addEntry(ISimulationObject * o);
  public:
    using IRenderer::name;
    using IRenderer::setName;

    ISimulationObject * toSimulationObject(){return static_cast<ISimulationObject*>(static_cast<IRenderer*>(this));}

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
    void addValueCallback(IValue * value);
};
}
