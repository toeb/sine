#pragma once
#include <string>
namespace IBDS{
class ISimulationObject {
private:
  const char * _name;
public:
  ISimulationObject():_name(0){}
  /**
   * \brief Sets a name.
   *
   * \param name  The name.
   */
  void setName(const char * name){_name = name;}
  
  /**
   * \brief Gets the name.
   *
   * \return  null if it fails, else the name.
   */
  const char * getName()const{return _name;}

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
