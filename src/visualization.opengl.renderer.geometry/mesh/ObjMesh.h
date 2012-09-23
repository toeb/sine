#pragma once

#include <iostream>
#include <string>

#include <visualization.opengl.renderer.geometry/mesh/Mesh.h>
#include <vector>
namespace nspace{



struct VertexData{
  VertexData():positionIndex(-1),textureCoordinateIndex(-1),normalIndex(-1){}
  Index positionIndex;
  Index textureCoordinateIndex;
  Index normalIndex;
};

typedef std::vector<VertexData> VertexList;

class IMeshBuilder{
public:
  virtual void addPosition(const Vector3D & position)=0;
  virtual void addTextureCoordinates(const Vector2D & uv)=0;
  virtual void addNormal(const Vector3D & normal)=0;
  virtual void addLine(const Index & posA, const Index & posB){}
  virtual void addFace(const VertexList & vertices){}
  virtual void beginGroup(){}
  virtual void endGroup(){}
  virtual void setGroupName(const std::string & name){}
  //needs to be called before data is read
  virtual void begin(){}
  //needs to be called when all data is ready
  virtual void end(){}
};

class MeshBuilder : public IMeshBuilder{
private:
  std::vector<Vector3D> _positions;
  std::vector<Vector3D> _normals;
  std::vector<Vector2D> _uvs;  
  std::vector<VertexList> _faces;
  std::vector<std::pair<Index,Index> > _lines;
  
public:
  void addPosition(const Vector3D & vector){
    _positions.push_back(vector);
  };
  void addTextureCoordinates(const Vector2D & vector){
    _uvs.push_back(vector);
  };
  void addNormal(const Vector3D & normal){
    _normals.push_back(normal);
  };
  void addFace(const VertexList & vertices){
    _faces.push_back(vertices);
  }
  void addLine(const Index & a, const Index & b){
    _lines.push_back(std::pair<Index,Index>(a,b));
  }
  
  void begin(){
    clear();
  }
  void end(){
    build();
    clear();
  }
protected:
  const std::vector<Vector3D> & positions()const{return _positions;}
  const std::vector<Vector3D> & normals()const{return _normals;}
  const std::vector<Vector2D> & textureCoordinates()const{return _uvs;}
  const std::vector<VertexList> & faces()const{return _faces;}

  const Vector3D & position(Index i)const{
    return _positions[i];
  }
  const Vector3D & normal(Index i)const{
    return _normals[i];
  }
  const Vector2D & textureCoordinate(Index i)const{
    return _uvs[i];
  }
  const VertexList & face(Index i)const{
    return _faces[i];
  }
  


  virtual void build(){}
  void clear(){
    _positions.clear();
    _normals.clear();
    _uvs.clear();
  }


};

class ObjLoader{
private:
  ObjLoader();
  static ObjLoader * _instance;
public:
  static ObjLoader & instance(){
    if(!_instance)_instance = new ObjLoader();
    return *_instance;
  }
  bool load(IMeshBuilder & builder, std::istream & inputStream);
  bool load(IMeshBuilder & builder, const std::string & filename);
};

class ObjMesh:public Mesh, public virtual MeshBuilder{
private:
  std::string _filename;
public:
  using Mesh::face;

  ObjMesh(const std::string & filename):_filename(filename){

  }
  void setGroupName(const std::string & name){
    setName(name);
  }
  //called by mesh
  void load(){
    ObjLoader::instance().load(*this,_filename);
  }
  //called by when data is ready
  void build(){
    for(int i=0; i < positions().size(); i++){
      const Vector3D & pos = position(i);
      addVertex(pos);
    }

    for(int i=0; i < faces().size(); i++){
      const VertexList & vertices =MeshBuilder::face(i);
      
      Face * f = new Face();
      f->id =i;
      
      for(int j=0; j < vertices.size(); j++){
        const VertexData & vertexData = vertices[j];
        Vertex & v = *vertex(vertexData.positionIndex);
        
        Vector3D n(1,0,0);
        if(normals().size() > vertexData.normalIndex){
          n = normal(vertexData.normalIndex);        
        }else{
          std::cout << " normal not available for index " << vertexData.normalIndex<<std::endl;
        }

        v.normal = n;
        f->vertices.push_back(&v);
      }
      Mesh::addFace(f);

    }

  }

};

}