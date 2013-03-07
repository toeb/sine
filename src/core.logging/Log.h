#pragma once
#include <config.h>
#include <core.h>
#include <core/Time.h>
#include <core.collection.h>

#include <iostream>
#include <sstream>
#include <string>


// these macros work within any class that contains a function to a reference called log (Log & log();}

#define createLogMessage(level, x) {std::stringstream ss; ss << x ; getLog().log(level, ss.str(),__FUNCSIG__,__FILE__,__LINE__);}

// macro for logging a message
#define logMessage(message,level) createLogMessage(level,message)

#define logInfo(x) logMessage(x,3);
#define logWarning(x) logMessage(x,2)
#define logError(x) logMessage(x,1)
#define logFatal(x) logMessage(x,0)

//TODO move to cmake
#define DEBUG
#ifdef  DEBUG
#define debugInfo(x)           logInfo(x)
#define debugWarning(x)        logWarning(x)
#define debugError(x)          logError(x)
#define debugMessage(x,level)  logMessage(x,level)
#else
#define debugInfo(x)
#define debugWarning(x)
#define debugError(x)
#define debugMessage(level,x)
#endif //  DEBUG

namespace nspace{
  class Log;
  // public function which returns the defaul log
  Log & getLog();

  class LogEntry : public  PropertyChangingObject{
    reflect_type(LogEntry);    
    typedef std::string reflect_property(Message);


    typedef int reflect_property(SourceLineNumber);
    typedef std::string reflect_property(SourceFileName);
    typedef std::string reflect_property(FunctionSignature);
    typedef int reflect_property( LogLevel);
    typedef Log* reflect_property( Owner);
    typedef std::string reflect_property( ClassName);
    typedef Time reflect_property( SystemTimeStamp);
    typedef std::string reflect_property( ObjectName);
  public:

  public:
    LogEntry();
    void toString(std::ostream & out)const;
  };
  class Log : public virtual PropertyChangingObject{
    reflect_type(Log);
    typedef int LogLevel;
  public:
    typedef bool reflect_property(LoggingEnabled);
    //DEFAULTVALUE(LoggingEnabled, true);

    typedef int reflect_property(LoggingLevel);
    //DEFAULTVALUE(LoggingLevel, int(3));

    typedef  std::ostream * reflect_property(LogInfoStream);
    typedef  std::ostream * reflect_property(LogWarningStream);
    typedef  std::ostream * reflect_property(LogErrorStream);


    typedef std::function<LogLevel (const LogEntry * )> basic_property(Filter);

    PROPERTYSET(LogEntry*,LogEntries,,);
  protected:

    Log & getLog()const{return *const_cast<Log*>(this);}
  public:
    Log();
    void log(int level,const std::string & message,const std::string & functionsignature="",const std::string & sourcefile ="",int sourcelinenumber=-1);
    void info(const std::string & message,const std::string & functionsignature="",const std::string & sourcefile ="",int sourcelinenumber=-1);
    void warn(const std::string & message,const std::string & functionsignature="",const std::string & sourcefile ="",int sourcelinenumber=-1);
    void error(const std::string & message,const std::string & functionsignature="",const std::string & sourcefile ="",int sourcelinenumber=-1);
    void addEntry(LogEntry * entry);
  };
}
