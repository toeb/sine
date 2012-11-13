#include "Log.h"

using namespace nspace;

  Log & nspace::getLog(){
    static Log * log=0;
    if(!log){
     log = new Log();
    }
    return *log;
  }