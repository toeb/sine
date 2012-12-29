#pragma once

#include <simulation.time/ITimeProvider.h>

namespace nspace{
  class RealTimeProvider:public virtual ITimeProvider{
  private:
    Time _t0;
  public:
    static const RealTimeProvider & defaultInstance();
    RealTimeProvider();
    inline Time time() const;
  };
}
