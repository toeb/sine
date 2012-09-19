#pragma once


#include <utility.reader.urdf/parsers/RootParser.h>
#include <utility.reader.urdf/parsers/ConnectionParser.h>
#include <utility.reader.urdf/parsers/ConnectorParser.h>

namespace nspace{
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