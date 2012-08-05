#pragma once

#include <common/Object.h>


namespace nspace{



class Simulation;
class ISimulationModule;

class Initializable : public virtual Object{
TYPED_OBJECT;
private:
  bool _initialized;
public:
  Initializable():_initialized(false){}
  const inline bool isInitialized()const{return _initialized;}
  bool initialize();
  bool cleanup();
protected:
  virtual void cleanupObject(){};
  virtual bool initializeObject(){return true;}
  virtual void onObjectInitialized(){};
};

class ISimulationObject : public virtual NamedObject, public virtual Initializable{
  TYPED_OBJECT;
private:
  ISimulationModule * _parent;
  Simulation * _simulation;
public:
  virtual void toString(std:: ostream & out )const;
   
  ISimulationObject();
  ISimulationObject(const std::string & name);

  inline void setParent(ISimulationModule * parent){_parent=parent;}
  inline ISimulationModule * parent(){return _parent;}
  inline void setSimulation(Simulation * simulation){_simulation = simulation;}
  inline Simulation * simulation(){return _simulation;}
protected:
};

}
