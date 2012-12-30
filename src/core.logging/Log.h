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
#define logMessage_0(x) createLogMessage(0,x)
#define logMessage_1(x) createLogMessage(1,x)
#define logMessage_2(x) createLogMessage(2,x)
#define logMessage_3(x) createLogMessage(3,x)
#define logMessage_4(x) createLogMessage(4,x)
#define logMessage_5(x) createLogMessage(5,x)
#define logMessage_6(x) createLogMessage(6,x)
#define logMessage_7(x) createLogMessage(7,x)
#define logMessage_8(x) createLogMessage(8,x)
#define logMessage_9(x) createLogMessage(9,x)
// default level
#define logMessage_(x) logMessage_3(x)

// macro for logging a message
#define logMessage(message,level) logMessage_##level(message)

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
    REFLECTABLE_OBJECT(LogEntry);
    PROPERTY(std::string, Message){}
    PROPERTY(int, SourceLineNumber){}
    PROPERTY(std::string, SourceFileName){}
    PROPERTY(std::string, FunctionSignature){}
    PROPERTY(int, LogLevel){}
    PROPERTY(Log*, Owner){}
    PROPERTY(std::string, ClassName){}
    PROPERTY(Time, SystemTimeStamp){}
    PROPERTY(std::string, ObjectName){}
  public:

  public:
    LogEntry():_LogLevel(100),_Owner(0){
      setSystemTimeStamp(systemTime());
    }
    void toString(std::ostream & out)const{
      switch(getLogLevel()){
      case 3:out<< "Info    : ";
        break;
      case 2:out << "Warning : ";
        break;
      case 1:out << "Error   : ";
        break;
      default: out << "Message(lvl "<<getLogLevel()<<"): ";
      }
      out << getSystemTimeStamp()<<"s : ";
      out << getMessage();
      out << " (in "<<getObjectName()<<")";
      //out <<" "<<getFunctionSignature();
    }
  };
  class Log : public virtual PropertyChangingObject{
    REFLECTABLE_OBJECT(Log);

    PROPERTY(bool,LoggingEnabled){};
    DEFAULTVALUE(LoggingEnabled, true);

    PROPERTY(int, LoggingLevel){};
    DEFAULTVALUE(LoggingLevel, int(3));

    SIMPLE_PROPERTY(std::ostream *, LogInfoStream){}
    SIMPLE_PROPERTY(std::ostream *, LogWarningStream){}
    SIMPLE_PROPERTY(std::ostream *, LogErrorStream){}

    PROPERTYSET(LogEntry*,LogEntries,{
      std::ostream * out=0;
      switch(item->getLogLevel()){
      case 1:
        out = getLogErrorStream();
        break;
      case 2:
        out = getLogWarningStream();
        break;
      default:
        out = getLogInfoStream();
        break;
      }
      if(!out)return;
      *out << *item << std::endl;
    },{})
  protected:

    Log & getLog()const{return *const_cast<Log*>(this);}
  public:

    Log():_LogInfoStream(0),_LogWarningStream(0),_LogErrorStream(0){
      setLogInfoStream(&std::cout);
      setLogErrorStream(&std::cerr);
      setLogWarningStream(&std::cout);
      setLoggingLevelToDefault();
      setLoggingEnabledToDefault();
    }
    void log(
      int level,
      const std::string & message,
      const std::string & functionsignature="",
      const std::string & sourcefile ="",
      int sourcelinenumber=-1){
        auto entry = new LogEntry();
        entry->setLogLevel(level);
        entry->setMessage(message);
        entry->setFunctionSignature(functionsignature);
        entry->setSourceFileName(sourcefile);
        entry->setSourceLineNumber(sourcelinenumber);
        addEntry(entry);
    }
    void info(
      const std::string & message,
      const std::string & functionsignature="",
      const std::string & sourcefile ="",
      int sourcelinenumber=-1){
        log(3,message,functionsignature,sourcefile,sourcelinenumber);
    }

    void warn(
      const std::string & message,
      const std::string & functionsignature="",
      const std::string & sourcefile ="",
      int sourcelinenumber=-1){
        log(2,message,functionsignature,sourcefile,sourcelinenumber);
    }

    void error(
      const std::string & message,
      const std::string & functionsignature="",
      const std::string & sourcefile ="",
      int sourcelinenumber=-1){
        log(1,message,functionsignature,sourcefile,sourcelinenumber);
    }

    void addEntry(LogEntry * entry){
      if(!getLoggingEnabled()){
        delete entry;
        entry = 0;
        return;
      }
      if(getLoggingLevel()<entry->getLogLevel()){
        delete entry;
        entry = 0;
        return;
      }
      entry->setOwner(this);
      /*const Type& td = getType();*/
      if(entry->getClassName()=="")entry->setClassName(getType().getName());
      if(entry->getObjectName()=="")entry->setObjectName(name(this));

      LogEntries()|=entry;
    }
  };
}
