#include "UpdateablesModule.h"


using namespace IBDS;

void UpdatablesModule::update(Real t, Real h){
  foreach([&t,&h](IUpdatable* updatable){
    updatable->update(t,h);
  });
}