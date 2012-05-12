#pragma once
#include <string>
namespace IBDS{
class ISimulationObject {
private:
  const std::string * _name;
public:
  ISimulationObject():_name(0){}
  ~ISimulationObject(){delete _name;}
  /**
   * \brief Sets a name.
   *
   * \param name  The name.
   */
  void setName(std::string name ){
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
  virtual bool initialize(){return true;};


  /**
   * \brief Cleans up this object.
   */
  virtual void cleanup(){};
};
}
