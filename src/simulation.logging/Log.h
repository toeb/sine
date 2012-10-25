#pragma once
#include <config.h>
#include <core/Object.h>
#include <core/NamedObject.h>
#include <core/Reflection.h>
#include <core/Time.h>

#include <iostream>
#include <sstream>
#include <string>


// these macros work within any class that contains a function to a reference called log (Log & log();}
#define logInfo(x) {std::stringstream ss; ss << x ; log().info(ss.str(),__FUNCSIG__,__FILE__,__LINE__);}
#define logWarning(x) {std::stringstream ss; ss << x ; log().warn(ss.str(),__FUNCSIG__,__FILE__,__LINE__);}
#define logError(x) {std::stringstream ss; ss << x ; log().error(ss.str(),__FUNCSIG__,__FILE__,__LINE__);}
#define logMessage(level, x) {std::stringstream ss; ss << x ; log().log(level, ss.str(),__FUNCSIG__,__FILE__,__LINE__);}
//TODO move to cmake
#define DEBUG
#ifdef  DEBUG
#define logDebug(x) logMessage(5,x) 
#else 
#define logDebug(x)
#endif //  DEBUG

namespace nspace{
  
  class Log;
  class LogEntry : public virtual PropertyChangingObject{
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

    PROPERTY(std::ostream *, LogInfoStream){}
    PROPERTY(std::ostream *, LogWarningStream){}
    PROPERTY(std::ostream *, LogErrorStream){}    
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
    
    Log & log()const{return *const_cast<Log*>(this);}
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
        auto entry = new LogEntry();
        entry->setLogLevel(3);
        entry->setMessage(message);
        entry->setFunctionSignature(functionsignature);
        entry->setSourceFileName(sourcefile);
        entry->setSourceLineNumber(sourcelinenumber);
        addEntry(entry);
      }
    
    void warn(
      const std::string & message,
      const std::string & functionsignature="",
      const std::string & sourcefile ="",
      int sourcelinenumber=-1){
        auto entry = new LogEntry();
        entry->setLogLevel(2);
        entry->setMessage(message);
        entry->setFunctionSignature(functionsignature);
        entry->setSourceFileName(sourcefile);
        entry->setSourceLineNumber(sourcelinenumber);
        addEntry(entry);
      }
      
      void error(
      const std::string & message,
      const std::string & functionsignature="",
      const std::string & sourcefile ="",
      int sourcelinenumber=-1){
        auto entry = new LogEntry();
        entry->setLogLevel(1);
        entry->setMessage(message);
        entry->setFunctionSignature(functionsignature);
        entry->setSourceFileName(sourcefile);
        entry->setSourceLineNumber(sourcelinenumber);
        addEntry(entry);
      }
    void addEntry(LogEntry * entry){
      if(!getLoggingEnabled())return;
      if(getLoggingLevel()<entry->getLogLevel())return; // TODO delete entry? or discontinue * usage or accept entry and check logging level elsewhere?
      entry->setOwner(this);
      const TypeData & td = getTypeData();
      if(entry->getClassName()=="")entry->setClassName(getTypeData().name);
      if(entry->getObjectName()=="")entry->setObjectName(name(this));
      
      LogEntries()|=entry;
    }
  };
}
