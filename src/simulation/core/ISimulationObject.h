#pragma once
#include <common/Config.h>
#include <common/Object.h>
#include <string>
#include <map>
#include <vector>
namespace nspace{



class Simulation;

class ISimulationObject : virtual Object{
  TYPED_OBJECT;
private:
  Simulation * _simulation;
  const std::string * _name;
  bool _initialized;
public:
  virtual void toString(std:: ostream & out )const;
  /**
   * \brief Gets the type (sublasses may implement if needed else it returns "ISimulationObject".  
   *
   * \return The type.
   */
 
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

  bool hasName()const;

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
