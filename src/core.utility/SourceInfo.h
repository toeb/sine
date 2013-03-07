#pragma once
#include <core.reflection.h>
#include <core/PropertyChangingObject.h>
namespace nspace{
  class CompilerInfo: public PropertyChangingObject{
    reflect_type(CompilerInfo);

    typedef std::string reflect_property(CompilationDate);
    typedef std::string reflect_property(CompilationTime);
    typedef std::string reflect_property(TimeStamp);
  public:
    CompilerInfo(){}
    CompilerInfo(const std::string compileTime, const std::string &compileDate,const std::string & timestamp)
      :_CompilationDate(compileDate),_CompilationTime(compileTime),_TimeStamp(timestamp){}
  };

#define DS_COMPILER_INFO() nspace::CompilerInfo(__TIME__,__DATE__,__TIMESTAMP__)
#ifndef COMPILER_INFO
#define COMPILER_INFO DS_COMPILER_INFO()
#endif

  class SourceInfo : public PropertyChangingObject{
    reflect_type(SourceInfo);
  public:
    SourceInfo(const std::string & file, int line, const std::string & func):_File(file),_Line(line),_Function(func){}
    void toString(std::ostream & out)const{
      out <<"Source: Line: "<< getLine()<< " File: "<<getFile()<<" Function: "<<getFunction();
    }
    typedef std::string reflect_property(File);
    typedef int         reflect_property(Line);
    typedef std::string reflect_property(Function);

  };

#define DS_SOURCE_INFO() nspace::SourceInfo(__FILE__,__LINE__,__FUNCSIG__)
#define DS_SOURCE_INFO_PTR() new DS_SOURCE_INFO()

#ifndef SOURCE_INFO
#define SOURCE_INFO DS_SOURCE_INFO()
#endif
}