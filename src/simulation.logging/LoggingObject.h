#pragma once
#include <config.h>
#include <simulation/ISimulationObject.h>
#include <iostream>
#include <sstream>
#if 1
#define logInfo(x) {std::stringstream ___stringStr; ___stringStr << x ; addEntry(___stringStr.str(),0,__FILE__,__FUNCSIG__,__LINE__);}
#define logWarning(x) {std::stringstream ___stringStr; ___stringStr << x ; addEntry(___stringStr.str(),1,__FILE__,__FUNCSIG__,__LINE__);}
#define logError(x) {std::stringstream ___stringStr; ___stringStr << x ; addEntry(___stringStr.str(),2,__FILE__,__FUNCSIG__,__LINE__);}
#else
#define log(x)
#define warn(x)
#define error(x)
#endif
namespace nspace{
class LoggingObject : public virtual ISimulationObject{
private:

public:
  LoggingObject(){}
protected:
  void addEntry(const std::string & message, int level, const std::string & file, const std::string & functionSignature, int line ){
    switch(level){
    case 1: std::cout <<"Info   : ";
    case 2:std::cout << "Warning: ";
    case 3:std::cout << "Error  : ";
    }
    
    std::cout << functionSignature <<": " << message << std::endl;
  }
};
}