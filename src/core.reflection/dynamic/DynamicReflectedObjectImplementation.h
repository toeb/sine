#pragma once

#include <core.reflection/dynamic/DynamicObjectImplementation.h>

namespace nspace{
  class ReflectedDynamicObjectImplementation : public DynamicObjectImplementation{

    Argument getMember(const std::string  & name)override final;
    MemberList getMemberNames()override final;
  };
}