#include "Node.h"
using namespace mbslib;
using namespace std;


void Comparator<Node*,const char*>::operation(bool & result, const Node * a, const char * c){
  result = *a==string(c);
}
