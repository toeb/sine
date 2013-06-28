#include "MemberAdapter.h"

using namespace nspace;

#include <core.reflection.builder.h>

reflect_type_default_definition(nspace::MemberAdapter);

MemberAdapter::MemberAdapter(){}
MemberAdapter::MemberAdapter(Argument owner):_Owner(owner){
  notify_after_set(Owner);
}


auto MemberAdapter::before_set(Owner){
  return BeforeSetAction::Accept;
}
auto MemberAdapter::after_set(Owner){

}
