#include <core.testing.h>

#include <core.task/ITask.h>

#include <deque>

namespace nspace{
  namespace core{    
    namespace task{
      namespace scheduling{
        template<typename TTask>
        struct task_traits{
          const static bool is_preemptive = false;
          const static bool is_independent = true;
          const static bool known_exact_execution_time;
          const static bool known_worst_case_exection_time;
          const static bool known_approximate_exectution_time;
          const static bool known_deadline;
        };
        class Scheduler{
          virtual void schedule(std::shared_ptr<ITask> task);

        };
        class FifoScheduler{
          std::deque<std::shared_ptr<ITask>> _taskqueue;
        public:
          void schedule(std::shared_ptr<ITask> task){
            // lock taskqueue;
            _taskqueue.push_back(task);
            // unlock queue;
          }

        };
        class RateMonotonicScheduler{

        };
        class EarliestDeadlineFirstScheduler{

        };
        class LeastLaxityFirstScheduler{

        };
      }
    }
  }
}

using namespace nspace::core::task::scheduling;
using namespace nspace::core::task;
UNITTEST(scheduling1){
  
  FifoScheduler scheduler;
  scheduler.schedule.

};