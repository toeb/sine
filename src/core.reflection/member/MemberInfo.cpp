#include "MemberInfo.h"


using namespace nspace;

MemberInfo::MemberInfo() :
  _IsVisible(true),
  _OwningType(0)
{}

MemberInfo::MemberInfo(const std::string & name):_IsVisible(true),_OwningType(0),_Name(name){}
MemberInfo::~MemberInfo(){}