#pragma once

#include <core.serialization.h>

namespace nspace{
namespace core{
namespace serialization{

  class Writer : public virtual StatefulTask, public virtual ProgressReporter{
    reflect_type(Writer);
    reflect_superclasses(StatefulTask);

    typedef bool reflect_property(Abort);
    REFERENCE(protected,bool,Abort);

  protected:
    virtual bool doWrite()=0;
    std::ostream & stream(){return std::cout;};
    virtual void clearResult(){}

  public:
    Writer();
    bool write(Argument value);

  private:
    bool runTaskReturnSuccess();
    std::ostream * _stream;


  };
  class Serializer :Writer{

  };
  class JsonSerializer{
  public:
    JsonSerializer();

    std::string serialize(Argument value);

  };
}
}
}