#pragma once

#include <common/Config.h>

namespace nspace{ 

/**
 * \brief Defines an alias representing identifier for the version of a value.
 */
typedef long ValueVersionId;

/**
 * \brief Value class. 
 */
class Value{
private:
  ///< The version
  ValueVersionId _version;
public:

  /**
   * \brief Gets the const pointer to the value
   *
   */
  virtual const void * pointer()const=0;

  /**
   * \brief Gets the pointer to the value.
   *
   * \return  null if it fails, else.
   */
  virtual void * pointer()=0;

  /**
   * \brief gets called when notifyChange is called
   */
  virtual void onValueChanged(){}  

  /**
   * \brief Default constructor. initializes the version to zero
   */
  Value():_version(0){}

  /**
   * \brief Gets the version of this value.  Everytime the notifyChange is called the version is increased by one
   *
   * \return  .
   */
  inline const ValueVersionId & version()const{return _version;}

  /**
   * \brief Notifies the value that it changed .  Subclasses should call this every time the value changes
   * 				causes version to increase by one
   * 				calles onValueChanged(){]
   */
  inline void notifyChange(){
    _version++;
    onValueChanged();
  }  
};
}