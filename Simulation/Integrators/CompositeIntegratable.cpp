#include "CompositeIntegratable.h"

using namespace IBDS;
using namespace std;


CompositeIntegratable::CompositeIntegratable(){}

void CompositeIntegratable::addIntegratable(IIntegratable  * integratable){

}

void CompositeIntegratable::evaluate(const Real * x, Real * xDot){

}

void CompositeIntegratable::getState(Real * x) const{
}
void CompositeIntegratable::setState(const Real * x){
}
int CompositeIntegratable::getStateDimension()const{
return 0;
}