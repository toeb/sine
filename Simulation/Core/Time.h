#pragma once
#include <Math/MathDefs.h>
namespace IBDS{

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
  Time currentTime();
}