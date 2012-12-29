#pragma once

#include <simulation.model/builder/IModelBuilder.h>
#include <string>
#include <istream>

namespace nspace{
  class ModelReader{
  private:
  protected:
    std::string readToEnd(std::istream & input)const;
  public:
    virtual bool parse(IModelBuilder & builder, std::istream & input)=0;
    virtual bool parseFile(IModelBuilder & bulder, const std::string & filename);
    virtual bool parseString(IModelBuilder & builder, const std::string & textData);
  };
}