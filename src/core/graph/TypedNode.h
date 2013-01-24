#pragma once

#include <core/graph/DerivableDataNode.h>

namespace nspace{
  template<class T>
  class TypedNode :public virtual T, public DerivableDataNode<T*, TypedNode<T>> {
  };
}
