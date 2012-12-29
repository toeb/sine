#pragma once

#include <core/Object.h>

namespace nspace{
  class Visitor : public virtual Object{
    TYPED_OBJECT;
  };
  template<typename T>
  class TypedVisitor : public virtual Visitor{
    TYPED_OBJECT;
  public:
    virtual void visit(T & t)=0;
  };

  template<class DerivedVisitable>
  class Visitable{
    TYPED_OBJECT;
  public:
    bool accept(Visitor & v){
      TypedVisitor<DerivedVisitable> * typedVisitor = dynamic_cast<  TypedVisitor<DerivedVisitable> *>(&v);
      if(!typedVisitor)return false;
      typedVisitor->visit(*static_cast<DerivedVisitable*>(this));
      return true;
    }
  };
}