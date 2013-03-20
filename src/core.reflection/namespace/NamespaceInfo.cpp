#include "NamespaceInfo.h"
#include <core.utility/StringTools.h>
using namespace nspace;


NamespaceInfo::NamespaceInfo():
  _Name(""),
  _FullyQualifiedName("::"),
  _ParentNamespace(0),
  _IsType(false){

}

void NamespaceInfo::namespaceAdded(const NamespaceInfo * ns){

}
void NamespaceInfo::namespaceRemoved(const NamespaceInfo * ns){
}
const NamespaceInfo* NamespaceInfo::Global(){
  static std::unique_ptr<NamespaceInfo> info(new NamespaceInfo());
  return info.get();
}

const NamespaceInfo* NamespaceInfo::Default(){
  static std::unique_ptr<NamespaceInfo> info(new NamespaceInfo("defaultNamespace",Global()));
  return info.get();
}

std::string createName(const std::string & name, const NamespaceInfo * parent){
  std::stringstream stream;
  if(parent==0) parent = NamespaceInfo::Global();
  stream << parent->getFullyQualifiedName() << name << "::";
  return stream.str();
}


NamespaceInfo::~NamespaceInfo(){

}

NamespaceInfo::NamespaceInfo(const std::string & name, const NamespaceInfo * parent):
  _IsType(false),
  _Name(name),
  _FullyQualifiedName(createName(name,parent)),
  _ParentNamespace(parent)
{
  _Namespaces.addObserver(new ObservableCollection<const NamespaceInfo*>::DelegateObserver([this](ObservableCollection<const NamespaceInfo*>* collection, const NamespaceInfo * ns){namespaceAdded(ns);},[this](ObservableCollection<const NamespaceInfo*>* collection, const NamespaceInfo * ns){namespaceRemoved(ns);}));
  // should it be registered here?
  const_cast<NamespaceInfo*>(parent)->_Namespaces|=this;
}


