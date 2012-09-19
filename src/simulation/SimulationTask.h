#pragma once
#include <common/patterns/ITask.h>
#include <simulation/ISimulationObject.h>
namespace nspace{

/**
 * \brief Simulation task. The task's run method is called as often as possible.  
 * 				
 *
 */
class SimulationTask : public virtual ISimulationObject, public virtual ITask{
public:
  

};


}