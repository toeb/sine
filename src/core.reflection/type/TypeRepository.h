#pragma once

#include <core.reflection/type/Type.h>
#include <core/patterns/Singleton.h>

namespace nspace{
  
  /**
   * \brief Types. a class containing a set of all types.
   */
  class TypeRepository
  {
private:
    SINGLETON(TypeRepository) {}
    Set< const Type * > _types;
public:
    static const Set< const Type * > & allTypes();
    static const Type * getType(const std::string & name);
    static bool registerType(const Type * type);
  };
}