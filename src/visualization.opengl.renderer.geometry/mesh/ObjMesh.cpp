#include "ObjMesh.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace nspace;
using namespace std;


ObjLoader::ObjLoader(){

}
ObjLoader * ObjLoader::_instance = 0;


bool ObjLoader::load(IMeshBuilder & builder, istream & instream){
  builder.begin();
  string line;
  char delimiter;
  bool groupStarted = false;
  while(getline(instream,line)){
    stringstream lineStream(line);
    string type;
    lineStream >> type;

    if(type == "v"){
      Vector3D position;
      lineStream>> position(0) >> position(1) >> position(2);
      builder.addPosition(position);
    }else if(type=="vt"){
      Vector2D uv;
      lineStream >> uv(0) >> uv(1);
      builder.addTextureCoordinates(uv);
    }else if(type == "vn"){
      Vector3D n;
      lineStream >> n(0) >>n(1)>>n(2);
      builder.addNormal(n);
    }else if(type =="l"){
      Index a,b;
      lineStream >> a >> b;
      builder.addLine(a,b);
    }else if(type == "g"){
      if(groupStarted)builder.endGroup();
      builder.beginGroup();
      string name;
      getline(lineStream,name);
      builder.setGroupName(name);
      
    }else if(type == "f"){
      VertexList faceVertices;
      

      while(lineStream){
        string vertexString;
        lineStream >> vertexString;
        string token;
        stringstream vertexStream(vertexString);
        
        vector<unsigned int> indices;
        string part;
        while(getline(vertexStream,part,'/')){
          unsigned int idx;
          stringstream indexStream(part);
          indexStream>>idx;
          //obj indices are 1 based and internal represetnation is 0 based
          idx -=1;
          indices.push_back(idx);
        }
        VertexData vertex;
        if(!indices.size())continue;
        if(indices.size()>0) vertex.positionIndex = indices[0];
        if(indices.size()>1) vertex.normalIndex = indices[1];
        if(indices.size()>2) vertex.textureCoordinateIndex = indices[2];
        if(indices.size()>3) cout << "obj loader does not know the vertex type" << endl;
                
        faceVertices.push_back(vertex);      
      }
      builder.addFace(faceVertices);
    }
  }
  if(groupStarted) builder.endGroup();
  builder.end();
  return true;
}
bool ObjLoader::load(IMeshBuilder & builder, const string & filename){
  fstream file;
  file.open(filename.c_str());
  if(!file)return false;
  return load(builder,file);
}

