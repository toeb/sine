#pragma once


#include <urdfreader/parsers/general/NamedElementParser.h>
#include <urdfreader/parsers/general/CompositeChildParser.h>
#include <urdfreader/ModelBuilderHolder.h>
#include <urdfreader/common/Node.h>

namespace mbslib{
  
//class for parsing a urdf robot xml node. it builds a model and calls IModelBuilders beginModel and endModel for every robot node ecountered
class RobotElementParser : public NamedElementParser, public ModelBuilderHolder{
private:
  CompositeChildParser _children;
public:
  RobotElementParser(IModelBuilder & builder);
protected: 
  bool parseNamedElement(XMLElement * element);
private:  
  Node * findRoot();
  void convertLink(Node * node);
  void convertConnector(Node * node);
  void convertConnection(Node * node);
  void convertJoint(Node * node);
  void convert();
};

}