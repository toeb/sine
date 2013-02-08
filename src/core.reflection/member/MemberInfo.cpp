#include "MemberInfo.h"

using namespace std;
using namespace nspace;

MemberInfo::MemberInfo() :
  _IsVisible(true),
  _OwningType(0)
{}
MemberInfo::~MemberInfo(){}