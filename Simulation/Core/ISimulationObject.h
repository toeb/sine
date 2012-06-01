#pragma once
#include <string>
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

  ISimulationObject():_name(0), _initialized(false){}
  ~ISimulationObject(){delete _name;}
  /**
   * \brief Sets a name.
   *
   * \param name  The name.
   */
  void setName(const std::string & name ){
    if(!name.compare("")){
      _name=0;
      return;
    }
    _name = new std::string(name);
  }
  
  /**
   * \brief Gets the name.
   *
   * \return  null if it fails, else the name.
   */
  const std::string* getName()const{return _name;}

  /**
   * \brief Initializes this object.
   *
   * \return  true if it succeeds, false if it fails.
   */
  bool initialize(){
    if(_initialized){
      return true;
    }
    _initialized = initializeObject();
    return _initialized;
  };

  bool isInitialized(){
    return _initialized;
  }


  /**
   * \brief Cleans up this object.
   */
  void cleanup(){
    cleanupObject();
    _initialized = false;
  };

protected:
  virtual void cleanupObject(){};
  virtual bool initializeObject(){return true;}
};
}
