#pragma once

#include <utility.reader.urdf/structs/UrdfLink.h>
#include <utility.reader.urdf/parsers/InertialFrameParser.h>
#include <utility.reader.urdf/parsers/VisualParser.h>


namespace nspace{

class LinkParser : public NamedElementParser, public ModelBuilderHolder{
private:
public:
  LinkParser(IModelBuilder & builder):NamedElementParser("link"),ModelBuilderHolder(builder){
    
  }
  protected:
  virtual bool parseNamedElement(XMLElement * linkElement){
    //create node
    Node * node=new Node;

    //set nodes name
    parseName(node,linkElement);
    

    //create and set struct holding link information
    UrdfLink * link = new UrdfLink;
    node->set("urdflink",link);
    
    // create inertial fram parser and parse children of link element
    InertialFrameParser inertialFrame;
    inertialFrame.parse(linkElement);
    link->mass = inertialFrame.massConfiguration.mass();
    link->inertia = inertialFrame.massConfiguration.inertia();
    link->origin = inertialFrame.origin;


    VisualParser visual;
    visual.parse(linkElement);

    
    //add new node to current model
    model().nodes().add(node);


    return true;
  }
};
}