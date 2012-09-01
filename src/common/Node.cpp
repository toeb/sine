#include "Node.h"
using namespace nspace;
using namespace std;


void Comparator<Node*,const char*>::operation(bool & result, const Node * a, const char * c){
  result = *a==string(c);
}
