#pragma once
#include <core.reflection.h>
#include <core/PropertyChangingObject.h>
#include <core.logging.h>
namespace nspace{
  
class ProgressReporter : public virtual PropertyChangingObject, public virtual Log{
  reflect_type(nspace::ProgressReporter);
  typedef double reflect_property(NumberOfNotifications);
  auto after_set(NumberOfNotifications);
  typedef double reflect_property(TotalProgress);
  auto after_set(TotalProgress);  
  typedef double reflect_property(Progress);
  typedef int    reflect_property(ProgressLogLevel);
  typedef double reflect_property(NotificationInterval);
  typedef bool   reflect_property(LogProgress);
  
public:
  ProgressReporter();
  double percent()const;
  double quotient()const;
private:
  double _lastNotification;
protected:
  void resetProgress(double totalProgress);
  void resetProgress();
  void incrementProgress(double value);
  void reportProgress(double value);
  
};

}