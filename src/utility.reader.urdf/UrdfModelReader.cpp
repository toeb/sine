#include "UrdfModelReader.h"

#include <tinyxml2/tinyxml2.h>
#include <fstream>

#include <core/StringTools.h>

#include <simulation.model/builder/ModelBuilderHolder.h>

#include <utility.reader.urdf/UrdfModelReader.h>
#include <utility.reader.urdf/parsers/RobotElementParser.h>

using namespace std;
using namespace nspace;

UrdfModelReader * UrdfModelReader::_instance =0;
UrdfModelReader::UrdfModelReader(){}

bool UrdfModelReader::parse(IModelBuilder & builder, std::istream & data){
  // read all data of inputstream
  string s = readToEnd(data);
  const char * text = s.c_str();

  // parse tinyxml2 document 
  tinyxml2::XMLDocument document;
  int errorCode = document.Parse(text);

  //return false if document could not be parsed (this indicates that xml was not valid
  if(errorCode){
    ERROR("tinyxml2 Parse error number " <<errorCode);
    return false;
  }


  
  // create a robot parser and parse all nodes of document
  RobotElementParser robotParser(builder);
  robotParser.parseSiblingsOf(document.FirstChildElement());
 
}