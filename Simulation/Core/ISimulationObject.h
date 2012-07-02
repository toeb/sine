#pragma once
#include <string>
#include <map>
namespace IBDS{

typedef const char * TypeId;

class ISimulationObject {
private:
  const std::string * _name;
  bool _initialized;
public:
  /**
   * \brief Gets the type (sublasses may implement if needed else it returns "ISimulationObject".  
   *
   * \return The type.
   */
  virtual const TypeId getType()const;

  ISimulationObject();
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
   const std::string* getName()const;


  /**
   * \brief Initializes this object.
   *
   * \return  true if it succeeds, false if it fails.
   */
  bool initialize();

  /**
   * \brief Query if this object is initialized.
   *
   *
   * \return true if initialized, false if not.
   */
  bool isInitialized()const;


  /**
   * \brief Cleans up this object.
   */
  void cleanup();

  /**
   * \brief Converts this object to a simulation object. (This may seem strange, however when multiple inheritance
   * 				is used this method may be overriden to return the correct inheritanc hierarchy see C2594 compiler error
   * 				(which is thus worked around)
   *
   * \author Tobi
   * \date 01.07.2012
   *
   * \return null if it fails, else this object as an ISimulationObject*.
   */
  virtual ISimulationObject * toSimulationObject(){return this;}
  ISimulationObject * operator()(){
    return toSimulationObject();
  }
protected:
  virtual void cleanupObject(){};
  virtual bool initializeObject(){return true;}
};

}
