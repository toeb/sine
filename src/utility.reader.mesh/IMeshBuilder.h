#pragma once
#include <math.matrix.h>
#include <utility.reader.h>
namespace nspace{  
  struct MeshElement;
  struct MeshFaceVertex;
  struct MeshFace;

  class IMeshBuilder : public IBuilder{
    TYPED_OBJECT(IMeshBuilder);
  protected:
    typedef unsigned int Index;
    typedef MeshFace FaceType;
  public:
    virtual void begin();
    virtual void position(Vector3D && position);
    virtual void normal(Vector3D && normal);
    virtual void textureCoordinates(Vector3D && tex);
    virtual void material(std::string && material);
    virtual void materialLibrary(std::string && library);
    virtual void group( std::string && name);
    virtual void object( std::string && object);
    virtual void face(FaceType && face);
    virtual void end();
  };

  struct MeshElement{
    //index is 1 based - 0 indicates a missing object or default id
    typedef unsigned int Index;
    MeshElement();
    Index index;
  };
  struct MeshFaceVertex : public MeshElement{
    MeshFaceVertex();
    
    Index position;
    Index normal;
    Index textureCoordinates;
  };
  struct MeshFace : public std::vector<MeshFaceVertex>, public MeshElement{
    MeshFace();
    Index group;
    Index smoothingGroup;
    Index object;
    Index material;
  };



}