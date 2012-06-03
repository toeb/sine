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

  bool isInitialized()const;


  /**
   * \brief Cleans up this object.
   */
  void cleanup();

protected:
  virtual void cleanupObject(){};
  virtual bool initializeObject(){return true;}
};

}
