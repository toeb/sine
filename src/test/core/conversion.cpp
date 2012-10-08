#include "conversion.h"


SimpleString StringFrom (int value)
{
  std::stringstream s;
  s << value;
  return SimpleString(s.str().c_str());
}
SimpleString StringFrom (uint value)
{
  std::stringstream s;
  s << value;
  return SimpleString(s.str().c_str());
}