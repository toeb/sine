/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#include "ObjReader.h"
#include <fstream>
using namespace std;
using namespace nspace;


void ObjReader::parseVertex(std::istream & stream){
  Vector3D vector;
  deserialize(vector,stream);
  getBuilder()->position(move(vector));
}
void ObjReader::parseTextureCoordinates(std::istream & stream){
  Vector2D tex;
  deserialize(tex,stream);
  getBuilder()->textureCoordinates(move(tex));
}
void ObjReader::parseNormal(std::istream & stream){
  Vector3D vector;
  deserialize(vector,stream);
  normalize(vector);
  getBuilder()->normal(move(vector));
}
void ObjReader::parseFace(std::istream & stream){
  string line;
  getline(stream,line);
  line = stringtools::trim(line);
  auto tuples = stringtools::split(line);
   
  Face face;
  
    face.smoothingGroup = currentSmoothingGroup;
    face.object =currentObject;
    face.material =currentMaterial;
//  for(auto tuple : tuples){      
    for(auto it = tuples.begin() ; it!=tuples.end(); it++){
        auto & tuple = *it;

    MeshFaceVertex vertex;
    std::vector<unsigned int> indices;

    tuple = stringtools::trim(tuple);
    auto parts = stringtools::split(tuple,'/');
    
    unsigned int count=0;    
    // for(auto part : parts){
    for(auto it = parts.begin(); it!=parts.end(); it++){
      auto & part = *it;
      indices.push_back(0);
      parse(indices[count],part);
      count++;
    }    
    switch(count){
    case 3:
      vertex.normal=indices[2];
    case 2:
      vertex.textureCoordinates=indices[1];
    case 1:
      vertex.position=indices[0];
    default:
      break;
    };
    face.push_back(vertex);
  }
  
  
  
  //for(auto group :currentGroups.elements()){
    for(auto it=currentGroups.elements().begin(); it!= currentGroups.elements().end(); it++){
      auto & group = *it;

    Face groupFace = face;
    groupFace.group=group;
    builder().face(move(groupFace));
  }

  builder().face(move(face));

}
void ObjReader::parseComment(std::istream & stream){
  std::string comment;
  std::getline(stream,comment);  
  comments.push_back(std::move(comment));
}
void ObjReader::parseGroup(std::istream& stream){
 string line;
 getline(stream,line);
 line=stringtools::trim(line);
 // split string into groups
 auto groupstatements = stringtools::split(line);
 // remove all groups from currentgroups
 currentGroups.clear();
 // add all groups to currentgroups
// for(auto group : groupstatements){
 for(auto it = groupstatements.begin(); it != groupstatements.end(); it++){
   auto & group = *it;
   bool added = groups.add(group);
   currentGroups |=groups.indexOf(group);     
   if(added)getBuilder()->group(move(group));
 }

}
void ObjReader::parseObject(std::istream & stream){
  string object;
  getline(stream,object);
  object = stringtools::trimFront(object);  
  bool added = objects.add(object);
  currentObject= objects.indexOf(object);  
  if(added)getBuilder()->object(move(object));
}

void ObjReader::parseMaterialLibrary(std::istream & stream){
  string filename;
  getline(stream,filename);
  filename = stringtools::trim(filename);
  getBuilder()->materialLibrary(move(filename));
}
void ObjReader::parseUseMaterial(std::istream & stream){
  string materialName;
  getline(stream, materialName);
  materialName=stringtools::trim(materialName);

  bool added = materials.add(materialName);
  currentMaterial=materials.indexOf(materialName);
  if(added)getBuilder()->material(move(materialName));

}
void ObjReader::parseSmoothingGroup(std::istream &stream){
  unsigned int smoothingGroup;
  stream >> smoothingGroup;
  currentSmoothingGroup = smoothingGroup;
}
ObjReader::ObjReader(){
  currentSmoothingGroup =0;
  currentGroups.clear();
  currentObject=0;
  currentMaterial = 0;
  //currentGroup="default";
  //currentObject="default";
  parsers["#"] = [this](std::istream & stream){this->parseComment(stream); };
  parsers["v"] = [this](std::istream & stream){this->parseVertex(stream); };
  parsers["vn"]= [this](std::istream & stream){this->parseNormal(stream); };
  parsers["f"] = [this](std::istream & stream){this->parseFace(stream); };
  // old files use face outline
  parsers["fo"] = [this](std::istream & stream){this->parseFace(stream); };

  parsers["g"] = [this](std::istream & stream){this->parseGroup(stream); };
  parsers["o"] = [this](std::istream & stream){this->parseObject(stream); };
  parsers["vt"]= [this](std::istream & stream){this->parseTextureCoordinates(stream);};
  parsers["mtllib"] = [this](istream & stream){this->parseMaterialLibrary(stream);};
  parsers["usemtl"] = [this](istream & stream){this->parseUseMaterial(stream);};
  parsers["s"] = [this](istream & stream){this->parseSmoothingGroup(stream);};
  //parsers["p"] = [this](std::istream & stream){this->parseObject(stream); };
  //parsers["l"] = [this](std::istream & stream){this->parseObject(stream); };
  /* parsers["curv"]= [this](std::istream & stream){this->parseObject(stream);};
     parsers["curv2"]= [this](std::istream & stream){this->parseObject(stream);};
     parsers["surf"]= [this](std::istream & stream){this->parseObject(stream);};
   */
  /*parsers["vt"]= [this](std::istream & stream){this->parseTextureCoordinates(stream);};
     ;
     parsers["vt"]= [this](std::istream & stream){this->parseTextureCoordinates(stream);};*/
}


bool ObjReader::readMesh(IMeshBuilder & builder){
  using namespace std;


  string line;
  string lineType;
  builder.begin();
  int lineCounter =0;
  while(getline(stream(),line)) {
    stringstream linestream(line);
    linestream>> lineType;
    
    if(parsers.find(lineType)!=  parsers.end()) {
      parsers[lineType](linestream);
    }else{
      //logWarning("no parser found for "<<lineType);
    }


    lineCounter++;
    if(lineCounter%1000)reportProgress(stream().tellg());
  }
  builder.end();

  return true;
}