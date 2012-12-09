#pragma once

#include <config.h>
#include <ostream>
#include <string>
#include <memory>

#include <core/Set.h>
#include <core/Node.h>
#include <core/Comparator.h>
#include <core/Members.h>
#include <core/reflection/Type.h>

namespace nspace{
// Base class.  Contains Type information and some standard methods like the streamout operator <<
class Object{
TYPED_OBJECT(Object);
private:
public:  
  Object();
  virtual ~Object();
  // tostring method which converts this object to a string representation (should be overridden by subclasses)
  virtual void toString(std::ostream & out)const;
  
  // to string operator
  //std::ostream & operator<<(std::ostream & out)const;
  // tostring method which returns the string
  std::string toString()const;

  friend std::ostream & operator << (std::ostream & out, const Object * obj);  
  friend std::ostream & operator << (std::ostream & out, const Object & obj);

  friend bool operator == (const Object & a, const Object & b){
    return &a==&b;
  }
};
}
