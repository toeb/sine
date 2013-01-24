#pragma once

#include <core.reflection.h>

namespace nspace{
  class CompilerInfo: public PropertyChangingObject{
    REFLECTABLE_OBJECT(CompilerInfo);    
    PROPERTY(std::string, CompilationDate){}
    PROPERTY(std::string, CompilationTime){}
  };
  class SourceInfo : public PropertyChangingObject{
    REFLECTABLE_OBJECT(SourceInfo);
  public:
    SourceInfo(const std::string & file, int line, const std::string & func):_File(file),_Line(line),_Function(func){}
    void toString(std::ostream & out)const{
      out <<"Source: Line: "<< getLine()<< " File: "<<getFile()<<" Function: "<<getFunction();
    }
    PROPERTY(std::string, File){}
    PROPERTY(int, Line){}
    PROPERTY(std::string, Function){}

  };

#define DS_SOURCE_INFO() nspace::SourceInfo(__FILE__,__LINE__,__FUNCSIG__)
#define DS_SOURCE_INFO_PTR() new DS_SOURCE_INFO()

#ifndef SOURCE_INFO
#define SOURCE_INFO DS_SOURCE_INFO()
#endif

}