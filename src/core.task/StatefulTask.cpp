#include "StatefulTask.h"


using namespace nspace;
using namespace std;

std::string StatefulTask::stateToString(const State & state){
  switch(state){
  case Unknown: return "Unknown";
  case Running:return "Running";
  case Succeeded: return "Suceeded";
  case Failed: return "Failed";
  default: return "";
  }
}

void StatefulTask::propertyChanging(State, State){
  logInfo("StatefuleTask state Changed from: "<<stateToString(oldvalue) <<" to " << stateToString(newvalue));
}
void StatefulTask::Reset(){
  logInfo("resetting task");
  clearResult();
  setState(Unknown);

}
void StatefulTask::Run(){
  runStatefulTask();
}
void StatefulTask::clearResult(){}
void StatefulTask::runTask(){
  logInfo("running task")
    if(getState()!=Unknown){
      Reset();
    }
    setState(Running);
    bool result=false;
    try{
      result =  runTaskReturnSuccess();
    }catch(std::exception){
      result = false;
    }

    if(result)
      setState(Succeeded);
    else
      setState(Failed);
    logInfo("finished task");
}

bool StatefulTask::runStatefulTask(){
  run();
  return getState()==Succeeded;
}
StatefulTask::StatefulTask(){
  setState(Unknown);
  setName("StatefulTask");
}