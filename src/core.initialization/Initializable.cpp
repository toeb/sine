#include "Initializable.h"

using namespace nspace;

bool Initializable::initialize(){
  if(_initialized){
    return true;
  }
  _initialized = initializeObject();
  if(_initialized)onObjectInitialized();
  return _initialized;
};

bool Initializable::cleanup(){
  cleanupObject();
  _initialized = false;
  return true;
};