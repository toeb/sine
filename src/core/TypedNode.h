#pragma once

#include <core/DerivableDataNode.h>

namespace nspace{
  template<class T>
  class TypedNode :public virtual T, public DerivableDataNode<T*, TypedNode<T>> {
  };
}
