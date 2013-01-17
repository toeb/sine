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
  positions.push_back(vector);
}
void ObjReader::parseTextureCoordinates(std::istream & stream){
  Vector2D tex;
  deserialize(tex,stream);
  textureCoordinates.push_back(tex);
}
void ObjReader::parseNormal(std::istream & stream){
  Vector3D vector;
  deserialize(vector,stream);
  normalize(vector);
  positions.push_back(vector);
}
void ObjReader::parseFace(std::istream & stream){}
void ObjReader::parseComment(std::istream & stream){
  std::string comment;
  std::getline(stream,comment);
  std::cout << comment;
  comments.push_back(std::move(comment));
}
void ObjReader::parseGroup(std::istream& stream){}
void ObjReader::parseObject(std::istream & object){}
ObjReader::ObjReader(){

  parsers["#"]= [this](std::istream & stream){this->parseComment(stream); };
  parsers["v"]= [this](std::istream & stream){this->parseVertex(stream); };
  parsers["vn"]= [this](std::istream & stream){this->parseNormal(stream); };
  parsers["f"]= [this](std::istream & stream){this->parseFace(stream); };
  parsers["g"]= [this](std::istream & stream){this->parseGroup(stream); };
  parsers["o"]= [this](std::istream & stream){this->parseObject(stream); };
  parsers["p"]= [this](std::istream & stream){this->parseObject(stream); };
  parsers["l"]= [this](std::istream & stream){this->parseObject(stream); };
  /* parsers["curv"]= [this](std::istream & stream){this->parseObject(stream);};
     parsers["curv2"]= [this](std::istream & stream){this->parseObject(stream);};
     parsers["surf"]= [this](std::istream & stream){this->parseObject(stream);};
   */
  /*parsers["vt"]= [this](std::istream & stream){this->parseTextureCoordinates(stream);};
     parsers["vt"]= [this](std::istream & stream){this->parseTextureCoordinates(stream);};
     parsers["vt"]= [this](std::istream & stream){this->parseTextureCoordinates(stream);};*/
}


bool ObjReader::doRead(){
  using namespace std;
  ifstream file("meshes/obj/tetrahedron.h");
  istream & stream=file;

  string line;
  string lineType;
  while(getline(stream,line)) {
    stringstream linestream(line);
    linestream>> lineType;
    if(parsers.find(lineType)!=  parsers.end()) {
      parsers[lineType](linestream);
    }else{
      logWarning("no parser found for "<<lineType);
    }
  }
  return false;

}