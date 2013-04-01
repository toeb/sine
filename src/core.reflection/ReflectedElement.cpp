
#include "ReflectedElement.h"
#include <core.reflection/type/Type.h>
#include <core.reflection/namespace/NamespaceInfo.h>
#include <string>
#include <core.utility/StringTools.h>
using namespace nspace;
using namespace std;

template<typename T> auto make_mutable(T t)->typename std::remove_const<T>::type{
  return const_cast<typename std::remove_const<T>::type>(t);
}

auto ScopeInfo::ChildScopes()const->const std::set<const ScopeInfo*> & {return _ChildScopes;}
bool ScopeInfo:: addChildScope(const ScopeInfo*  node){
  if(!_ChildScopes.insert(node).second){
    return false;
  }
  onChildScopeAdded(node);
  return true;
}
bool ScopeInfo::removeChildScope( const ScopeInfo* node){
  auto it = _ChildScopes.find(node);
  if(it== std::end(_ChildScopes))return false;
  _ChildScopes.erase(it);
  return true;
}
const ScopeInfo* ScopeInfo::Global(){
  return NamespaceInfo::Global();
}
const ScopeInfo * ScopeInfo::Unknown(){
  static ScopeInfo scope("UNKNOWN_SCOPE",0);
  return &scope;
}
const ScopeInfo * ScopeInfo::Default(){

  return NamespaceInfo::Default();
}

std::string createName(const std::string & fullyQualifiedName){
  if(fullyQualifiedName=="UNKNOWN_SCOPE")return fullyQualifiedName;
  auto name = fullyQualifiedName;
  if(stringtools::endsWith(name,"::"))name = name.substr(0,name.size()-2);
  auto start = name.find_last_of("::")+1;
  name = name.substr(start);
  return name;

}

std::string createFullyQualifiedName(const std::string & name, const ScopeInfo * parent){
  using namespace stringtools;
  if(name=="UNKNOWN_SCOPE"){
    return name;
  }
  // std::string
  // nspace::Object
  // nspace::stringtools::lol
  // ::std::istream
  string fName=name;
  if(startsWith(fName,"::")){
    if(!endsWith(fName,"::")) fName = stringtools::operator+(fName,"::");
    // global
    return fName;
  }
  auto parts = split(fName, "::");
  if(parts.size()!=1){
    parent = NamespaceInfo::Default();
    fName = createName(fName);
  }
  std::stringstream stream;
 
  stream << parent->getFullyQualifiedName() << fName<<"::";
  auto result = stream.str();
  if(!startsWith(result,"::")){
    result = "::"+result;

  }
  return result;
}

ScopeInfo::ScopeInfo(const std::string & nameOrFullyQualifiedName, const ScopeInfo* scope):
  _Scope(scope||stringtools::startsWith(nameOrFullyQualifiedName,"::")?Global():scope),
  _FullyQualifiedName(createFullyQualifiedName(nameOrFullyQualifiedName,scope)),
  _Name(createName(createFullyQualifiedName(_FullyQualifiedName,scope)))
{
  if(!scope)return;
  const_cast<ScopeInfo*>(scope)->addChildScope(this);
}
ScopeInfo::~ScopeInfo(){
  setScope(0);
  for_each(begin(ChildScopes()),end(ChildScopes()),[](const ScopeInfo * it){
    auto child = const_cast<ScopeInfo*>(it);
    child->setScope(Unknown());

  
  });




}

void ScopeInfo::init(){

}

ScopeInfo::ScopeInfo():_FullyQualifiedName("::"){
  init();
}
auto ScopeInfo::before_set(Scope){
  auto newScope = const_cast<ScopeInfo*>(*newvalue);
  auto currentScope = const_cast<ScopeInfo*>(_Scope);
  if(newScope==currentScope)return BeforeSetAction::Cancel;
  if(currentScope)currentScope->removeChildScope(this);
  return BeforeSetAction::Accept;
}
auto ScopeInfo::after_set(Scope){
  auto scope =const_cast<ScopeInfo*>(getScope());
  if(!scope)return ;
  scope->addChildScope(this);;
  onScopeSet(scope);
}

void ScopeInfo::onScopeSet(const ScopeInfo * parent){

}

void ScopeInfo::onChildScopeAdded(const ScopeInfo *  child){
  std::cout << "added "<< child->getName()<< " to " << getFullyQualifiedName() << std::endl;

}
void ScopeInfo::onChildScopeRemoved(const ScopeInfo * child){

  std::cout << "removed "<< child->getName()<< " from " << getFullyQualifiedName()<<std::endl;
}