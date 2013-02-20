#include "MemberInfo.h"


using namespace nspace;

void MemberInfo::propertyChanging(std::string, Name){
  if(getDisplayName()!="") return; setDisplayName(newvalue);
}


MemberInfo::MemberInfo() :
  _IsVisible(true),
  _OwningType(0)
{}
MemberInfo::~MemberInfo(){}