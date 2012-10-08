#pragma once


#include <utility.xml/NamedElementParser.h>
#include <utility.xml/CompositeChildParser.h>
#include <simulation.model/builder/ModelBuilderHolder.h>
#include <core/Node.h>

namespace nspace{
  
//class for parsing a urdf robot xml node. it builds a model and calls IModelBuilders beginModel and endModel for every robot node ecountered
class RobotElementParser : public NamedElementParser, public ModelBuilderHolder{
private:
  CompositeChildParser _children;
public:
  RobotElementParser(IModelBuilder & builder);
protected: 
  bool parseNamedElement(XMLElement * element);
private:  
  ModelNode * findRoot();
  void convertLink(ModelNode * node);
  void convertConnector(ModelNode * node);
  void convertConnection(ModelNode * node);
  void convertJoint(ModelNode * node);
  void convertSpring(ModelNode * node);
  void convert();
};

}