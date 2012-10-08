#pragma once

#include <core/Object.h>
#include <string>

namespace nspace{
  // a base class for objects that need to be named
  class NamedObject  : public virtual Object{
    TYPED_OBJECT(NamedObject);
  private:
    // the name field
    std::string * _name;
  public:
    // the default name. (if a named object does not have a name set it will be returned)
    static const std::string & DefaultName;
    // constructor accepting a string name 
    NamedObject(const std::string & name);
    // default constructor
    NamedObject();
    // default destructor
    ~NamedObject();
    // returns the name of this object
    const std::string & name()const;
    // returns true iff the object has a name
    bool hasName()const;
    // sets the name of this object by reference
    void setName(const std::string & name);
    // sets the name of this object by pointer
    void setName(const std::string * name);
    // equality operator. returns true of this objects name equals the string
    bool operator == (const std::string & str)const;
    // equalitiy operator. returns true if this objects name equals the c string
    bool operator==(const char * str)const;
    // equality operator compares a NamedObject's name to a std::string and returns true iff they are equal
    bool friend operator==(const NamedObject * obj, const std::string & name);
  protected:
    // extension point which is called when the name of this named object changes.  subclasses may override this
    virtual void nameChanged(const std::string& newName){}
  };

  // method for extracting the name of a named object
  const std::string & name(Object * object);

}