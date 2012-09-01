#include "Object.h"
#include <sstream>
#include <string>
using namespace nspace;
using namespace std;

std::string Object::toString()const{
  stringstream ss;
  toString(ss);
  return ss.str();
}
