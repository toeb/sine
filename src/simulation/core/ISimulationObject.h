#pragma once
#include <common/Config.h>
#include <string>
#include <map>
#include <vector>
namespace nspace{

typedef const char * TypeId;

class Simulation;

class ISimulationObject{
private:
  Simulation * _simulation;
  const std::string * _name;
  bool _initialized;
public:
  /**
   * \brief Gets the type (sublasses may implement if needed else it returns "ISimulationObject".  
   *
   * \return The type.
   */
  virtual const TypeId getType()const;
  virtual void toString(std::ostream & out)const;
  ISimulationObject();
  ISimulationObject(const std::string & name);
  ~ISimulationObject();

  /**
   * \brief Sets a name.
   *
   * \param name  The name.
   */
  void setName(const std::string & name );
  
  /**
   * \brief Gets the name.
   *
   * \return  null if it fails, else the name.
   */
  const std::string& getName()const;

  /**
   * \brief Initializes this object.
   *
   * \return  true if it succeeds, false if it fails.
   */
  bool initialize();

  bool isInitialized()const;


  /**
   * \brief Cleans up this object.
   */
  void cleanup();

  inline void setSimulation(Simulation * simulation){_simulation = simulation;}
  inline Simulation * simulation(){return _simulation;}
protected:
  virtual void cleanupObject(){};
  virtual bool initializeObject(){return true;}
  virtual void onObjectInitialized(){};
};

}
