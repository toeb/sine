#pragma once

#include <core.logging.h>

namespace nspace{

  class ScriptObject : public Object{
    reflect_type(ScriptObject);

  public:
    void toString(std::ostream & out)const{
    //  getObjectType()->objectToString(getObjectPointer().get(),out);
    }
    ScriptObject():_ObjectType(0){}
    typedef std::shared_ptr<void> basic_property(ObjectPointer);
    typedef const Type * basic_property(ObjectType);
    template<typename T> std::shared_ptr<T> object(){return std::static_pointer_cast<T>(getObjectPointer());}
  };

  class VirtualScriptMachine : public Log{
    reflect_type(VirtualScriptMachine);
    reflect_superclasses(Log);
    
    PROPERTYSET(std::shared_ptr<Object>, ManagedObjects,{},{});
  public:
    virtual bool registerType(const Type * type){return false;}
    virtual bool registerObject(std::shared_ptr<Object> object){return false;}

    virtual void scriptObjectConstructed(ScriptObject & object){}
    virtual void scriptObjectDestroyed(ScriptObject & object){}
    virtual bool loadStream(std::istream & stream);
    bool loadString(const std::string & script);
    bool loadFile(const std::string & filename);
  };
}

