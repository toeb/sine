#include "ChildElementParser.h"
using namespace nspace;



bool ChildElementParser::parse(tinyxml2::XMLElement * node){
    return SiblingElementParser::parse(node->FirstChildElement());
  
};
