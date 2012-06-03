#include "Vector3DValue.h"
#include <Common/StringTools.h>
using namespace IBDS;

using namespace std;

Vector3DValue::Vector3DValue(const string & name, Vector3D  & value):_value(value),
  x(name+" x",value[0]),y(name+" y",value[1]),z(name+ " z",value[2])
{
  setName(name);
}


