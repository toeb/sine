#include "ExtendedTask.h"
#include <core/NamedObject.h>
using namespace nspace;
ExtendedTask::ExtendedTask():_runCount(0),_runTime(0),_running(false){
}
void ExtendedTask::onBeforeRun(){
  _running=true;
  _lastStartTime = systemTime();
}
void ExtendedTask::onAfterRun(){
  _runTime += systemTime()-_lastStartTime;
  _runCount++;
  _running=false;
}

void ExtendedTask:: toString(std::ostream & o)const{
  auto named = dynamic_cast<const NamedObject*>(this);
  o << "<task ";
  if(named)  o << " name=\"" << named->name()  << "\"";
  else  o << "" ;
  o <<" runcount = "<<_runCount<< " runtime = "<<_runTime<<" />";
}