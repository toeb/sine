#include "MemberInfo.h"


using namespace nspace;

void MemberInfo::propertyChanging(std::string, Name){
  if(getDisplayName()!="") return; 
  setDisplayName(newvalue);
}


MemberInfo::MemberInfo() :
  _IsVisible(true),
  _OwningType(0)
{}

MemberInfo::MemberInfo(const std::string & name):_IsVisible(true),_OwningType(0),_Name(name),_DisplayName(name){}
MemberInfo::~MemberInfo(){}