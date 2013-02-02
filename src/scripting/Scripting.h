#pragma once

#include <core.logging.h>

namespace nspace{

  class VirtualScriptMachine : public Log{

  public:
    virtual void registerFunction(){}
    virtual void registerType(const Type * type){}
    virtual void registerObject(){}
    virtual void callFunction(){}
    virtual void get(){}

    virtual bool loadStream(std::istream & stream);
    bool loadString(const std::string & script);
    bool loadFile(const std::string & filename);
  };
}

