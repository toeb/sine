#include "MemberAdapter.h"

using namespace nspace;
MemberAdapter::MemberAdapter(){}
MemberAdapter::MemberAdapter(Argument owner):_Owner(owner){
  notify_after_set(Owner);
}


auto MemberAdapter::before_set(Owner){
  return true;
}
auto MemberAdapter::after_set(Owner){

}
