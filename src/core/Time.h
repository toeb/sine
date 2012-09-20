#pragma once
#include <config.h>
namespace nspace{
  
  /**
   * \brief Defines an alias representing the time.
   */
  typedef Real Time;

  /**
   * \brief Gets the current  system time. 
   *
   * (Currently only implemented under windows using Performance timer)
   *
   * \return .
   */
  Time systemTime();
  Time startupTime();
  Time applicationTime();
}