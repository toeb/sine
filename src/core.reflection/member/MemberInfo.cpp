#include "MemberInfo.h"
#include <core.reflection.builder.h>

using namespace nspace;

MemberInfo::MemberInfo() :
  _AccessModifier(Unknown),
  _OwningType(0)
{}

MemberInfo::MemberInfo(const std::string & name):_AccessModifier(Unknown),_OwningType(0),_Name(name){}
MemberInfo::~MemberInfo(){}



bool MemberInfo::initializeType(){
  core::reflection::builder::reflect<MemberInfo>()
    ->fullyQualifiedName(DS_STRINGIFY(::nspace::MemberInfo))
    ->publishHierarchy()
    ->end();
  return true;
}