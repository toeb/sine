#pragma once
#include <config.h>
namespace nspace{
  //alias for a time
  typedef Real Time;
  // returns the system time
  Time systemTime();
  // returns the system time when the application started up
  Time startupTime();
  // returns the time since application startup
  Time applicationTime();
}
