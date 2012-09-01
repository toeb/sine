#pragma once


#include <urdfreader/parsers/urdf/RootParser.h>
#include <urdfreader/parsers/urdf/ConnectionParser.h>
#include <urdfreader/parsers/urdf/ConnectorParser.h>

namespace mbslib{
class UrdfExtensionParser:public NamedElementParser, public ModelBuilderHolder{
private:
  CompositeChildParser _childParser;
  RootLinkParser _rootParser;
  ConnectorParser _connectorParser;
  ConnectionParser _connectionParser;
public:
  UrdfExtensionParser(IModelBuilder & builder):NamedElementParser("extensions"),ModelBuilderHolder(builder),_rootParser(builder),_connectorParser(builder),_connectionParser(builder){
    _childParser.composite().add(&_rootParser);
    _childParser.composite().add(&_connectorParser);
    _childParser.composite().add(&_connectionParser);
  }
protected:
  virtual bool parseNamedElement(XMLElement * node){
    bool result = _childParser.parse(node);
    return true;
  }
};


}