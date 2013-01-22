#pragma once

namespace nspace{


/*
template<typename VertexType, typename FaceType, typename EdgeType>
class DynamicMesh{

};

template<typename ObjectType>
struct IndexType{typedef void Type;};





template<typename Index=size_t, typename Vertex=Vector3D, typename Face=std::vector<unsigned int>>
class MeshBuilder{
public:



  virtual void setVertexCount(Index count);
  virtual void setFaceCount(Index count);
  virtual Vertex createVertex(Index i, std::vector<double>)=0;
  virtual Face createFace()=0;

};

enum VertexPropertyId{
  VertexDynamic,
  VertexPosition,
  VertexColor
};

template<typename Vertex, typename Type, typename VertexPropertyId>
struct VertexPropertyType{
};

template<typename Vertex, unsigned int PropertyId=Dynamic>
struct VertexProperty{
  typedef char Type;
  const static bool IsSupported=false;
  static inline bool getProperty(const Vertex & vertex, Type& value){return false;}
  static inline bool setProperty(Vertex& vertex, const Type && value){return false;}
  static Type & property(const Vertex& vertex){return Type();}
};

struct MyVertex{
  Vector3D position;
  float color[4];
  unsigned int id;
};

template<>
struct VertexProperty<MyVertex,VertexPosition>{
  typedef Vector3D Type;
  const static bool IsSupported=true;
  static inline bool getProperty(const MyVertex & vertex, Vector3D & value){
    value = vertex.position;
    return true;
  }
  static inline bool setProperty(MyVertex & vertex, const Vector3D & value){
    vertex.position =value;
    return true;
  }

};



template<typename VertexType, unsigned int PropertyId>
inline bool isVertexPropertySupported(const VertexType & vertex){
  return VertexProperty<VertexType,PropertyId>::IsSupported;
}

template<typename VertexType, unsigned int PropertyId>
inline typename VertexProperty<VertexType, PropertyId>::Type getVertexProperty(const VertexType & vertex){
  typename VertexProperty<VertexType, PropertyId>::Type propertyValue;
  VertexProperty<VertexType, PropertyId>::getProperty(vertex,propertyValue);
  return propertyValue;
}

template<typename VertexType, unsigned int PropertyId>
inline void setVertexProperty(VertexType & vertex,  const typename VertexProperty<VertexType, PropertyId>::Type & value){
  VertexProperty<VertexType, PropertyId>::setProperty(vertex,value);
}

template<typename VertexType>
inline typename  VertexProperty<VertexType, VertexPosition>::Type getVertexPosition(const VertexType & vertex){
  return getVertexProperty<VertexType,VertexPosition>(vertex);
}

template<typename VertexType>
inline void setVertexPosition(VertexType & vertex, const typename VertexProperty<VertexType, VertexPosition>::Type & position){
  setVertexProperty<VertexType,VertexPosition>(vertex,position);
}

#define MESH_OPERATION(NAME) Mesh##NAME
#define MESH_OPERATION_CLASS(NAME) struct MESH_OPERATION(NAME)
#define MESH_OPERATION_SIGNATURE public: static inline auto operation
#define MESH_OPERATION_METHOD(NAME) mesh##NAME
template<typename MeshType>
MESH_OPERATION_CLASS(VertexIndexType){
//  typedef std::_Nil Type;
};
#define MESH_VERTEX_INDEX_TYPE(MESHTYPE)  MESH_OPERATION(VertexIndexType)<MESHTYPE>::Type

template<typename MeshType>
MESH_OPERATION_CLASS(FaceIndexType){
  //typedef std::_Nil Type;
};

#define MESH_FACE_INDEX_TYPE(MESHTYPE)  MESH_OPERATION(FaceIndexType)<MESHTYPE>::Type

template<typename MeshType>
MESH_OPERATION_CLASS(EdgeIndexType){
  //typedef std::_Nil Type;
};
#define MESH_EDGE_INDEX_TYPE(MESHTYPE) MESH_OPERATION(EdgeIndexType)<MESHTYPE>::Type

template<typename MeshType>
MESH_OPERATION_CLASS(VertexType){
  //typedef std::_Nil Type;
};
#define MESH_VERTEX_TYPE(MESHTYPE) MESH_OPERATION(VertexType)<MESHTYPE>::Type

template<typename MeshType>
MESH_OPERATION_CLASS(FaceType){
  //typedef std::_Nil Type;
};
#define MESH_FACE_TYPE(MESHTYPE) MESH_OPERATION(FaceType)<MESHTYPE>::Type

template<typename MeshType>
MESH_OPERATION_CLASS(EdgeType){
  //typedef std::_Nil Type;
};
#define MESH_EDGE_TYPE(MESHTYPE) MESH_OPERATION_CLASS(EdgeType)<MESHTYPE>::Type

template<typename MeshType>
MESH_OPERATION_CLASS(VertexCount){
  MESH_OPERATION_SIGNATURE(const MeshType & mesh)->typename MESH_VERTEX_INDEX_TYPE(MeshType){
    return mesh.getVertexCount();
  }
};
template<typename MeshType>
inline typename MESH_VERTEX_INDEX_TYPE(MeshType) MESH_OPERATION_METHOD(VertexCount)(const MeshType & mesh){
  return MESH_OPERATION(VertexCount)<MeshType>::operation(mesh);
}

template<typename MeshType>
MESH_OPERATION_CLASS(FaceCount){
  MESH_OPERATION_SIGNATURE(const MeshType & mesh)->typename MESH_FACE_INDEX_TYPE(MeshType){
    return mesh.getFaceCount();
  }
};

template<typename MeshType>
typename MESH_FACE_INDEX_TYPE(MeshType) MESH_OPERATION_METHOD(FaceCount)(const MeshType & mesh){
  return MESH_OPERATION(FaceCount)<MeshType>::operation(mesh);
};


template<typename MeshType>
MESH_OPERATION_CLASS(EdgeCount){
  MESH_OPERATION_SIGNATURE(const MeshType & mesh)->typename MESH_EDGE_INDEX_TYPE(MeshType){
    return mesh.getEdgeCount();
  }
};

template<typename MeshType>
inline typename MESH_EDGE_INDEX_TYPE(MeshType) edgeCount(const MeshType & mesh){
  return MESH_OPERATION(EdgeCount)::operation(mesh);
};


template<typename MeshType>
MESH_OPERATION_CLASS(VertexGet){
  MESH_OPERATION_SIGNATURE (MeshType & mesh, typename MESH_VERTEX_INDEX_TYPE(MeshType) i)->typename MESH_VERTEX_TYPE(MeshType){
    return mesh.getVertex(i);
  }
};

template<typename MeshType>
inline typename MESH_VERTEX_TYPE(MeshType) MESH_OPERATION_METHOD(VertexGet)(MeshType & mesh, typename MESH_VERTEX_INDEX_TYPE(MeshType) i){
  return MESH_OPERATION(VertexGet)<MeshType>::operation(mesh,i);
};



template<typename MeshType>
MESH_OPERATION_CLASS(FaceGet){
  MESH_OPERATION_SIGNATURE (MeshType & mesh, typename MESH_FACE_INDEX_TYPE(MeshType) i)->typename MESH_FACE_TYPE(MeshType){
    return mesh.getFace(i);
  }
};


template<typename MeshType>
inline typename MESH_FACE_TYPE(MeshType) getFace(MeshType & mesh, typename MESH_FACE_INDEX_TYPE(MeshType) i){
  return MeshFaceGet<MeshType>::get(mesh,i);
};


template<typename MeshType>
struct MeshClear{
  static inline void clear(MeshType & mesh){
    mesh.clear();
  }
};
template<typename MeshType>
void meshClear(MeshType & mesh){
  MeshClear<MeshType>::clear(mesh);
}


template<typename MeshType>
struct MeshAllocateVertices{
  static inline void allocate(MeshType& mesh, const typename MESH_VERTEX_INDEX_TYPE(MeshType) n){
    mesh.allocateVertices(n);
  }
};

template<typename MeshType>
inline void meshAllocateVertices(MeshType &  mesh,const typename MESH_VERTEX_INDEX_TYPE(MeshType) n){
  MeshAllocateVertices<MeshType>::allocate(mesh,n);
}

template<typename MeshType>
struct MeshAllocateFaces{
  static inline void allocate(MeshType & mesh, const typename MESH_FACE_INDEX_TYPE(MeshType) n){
    mesh.allocateFaces(n);
  }
};
template<typename MeshType>
inline void meshAllocateFaces(MeshType & mesh, const typename MESH_FACE_INDEX_TYPE(MeshType) n){
  MeshAllocateFaces<MeshType>::allocate(mesh,n);
}






template<typename MeshType>
struct MeshFaceSet{
  static inline void set(MeshType & mesh, typename MESH_FACE_INDEX_TYPE(MeshType) i, const typename MESH_FACE_TYPE(MeshType) & face){
    mesh.setFace(i,face); 
  }
};
template<typename MeshType>
inline void setFace(MeshType & mesh, typename MESH_FACE_INDEX_TYPE(MeshType) i, const typename MESH_FACE_TYPE(MeshType) & face){
  MeshFaceSet<MeshType>::set(mesh,i,face);
}
template<typename MeshType>
struct MeshVertexSet{
  static inline void set(MeshType & mesh, typename MESH_VERTEX_INDEX_TYPE(MeshType) i, const typename MESH_VERTEX_TYPE(MeshType) & vertex){
    mesh.setVertex(i,vertex);
  }
};
template<typename MeshType>
inline void setVertex(MeshType & mesh, typename MESH_VERTEX_INDEX_TYPE(MeshType) i, const typename MESH_VERTEX_TYPE(MeshType) &vertex){
  MeshVertexSet<MeshType>::set(mesh,i,vertex);
}




class Mesh{
public:
  typedef unsigned int IndexType;
  typedef Vector3D VertexType; 
  typedef std::vector<IndexType> FaceType;
  void setVertexCount(IndexType n_vertices);
  void setFaceCount(IndexType n_faces);

  VertexType & vertex(IndexType i);
  FaceType & face(IndexType i);
};
struct CustomVertex;
struct CustomFace;
struct CustomEdge;
struct CustomMesh{
  typedef unsigned int IndexType;
  typedef Vector3D VertexType; 
  typedef std::vector<IndexType> FaceType;

  std::vector<Vector3D> positions;
  std::vector<Vector3D> velocities;
  std::vector<Vector3D> forces;
  std::vector<Vector3D> normals;
  std::vector<Vector3D> colors;
  std::vector<FaceType> faces;
  std::vector<std::pair<IndexType, IndexType> > edges;
  IndexType vertexCount;
  IndexType faceCount;
  CustomMesh():vertexCount(0),faceCount(0){
  }
  ~CustomMesh(){

  }
  void setVertexCount(IndexType nVertices){
    vertexCount=nVertices;
  }
  void setFaceCount(IndexType nFaces){
    faceCount=nFaces;
  }
  bool initialize(){    

    if(vertexCount){
      positions.reserve(vertexCount);
      velocities.reserve(vertexCount);
      normals.reserve(vertexCount);

      for(int i=0; i < vertexCount; i++){
        positions.push_back(Vector3D::Zero());
        velocities.push_back(Vector3D::Zero());
        normals.push_back(Vector3D::UnitX());
      }
    }
    if(faceCount){
      while(faces.size()<faceCount)faces.push_back(FaceType());
    }
    return true;
  }

  inline CustomVertex vertex(IndexType i);
  inline CustomFace face(IndexType i);
  inline CustomEdge edge(IndexType i);

};
struct CustomVertex{
  typedef unsigned int IndexType;
  IndexType index;
  CustomMesh & mesh;
  CustomVertex(IndexType index, CustomMesh & mesh):index(index),mesh(mesh){}
  inline Vector3D & position(){
    return mesh.positions[index];
  }
  inline Vector3D & velocity(){
    return mesh.velocities[index];
  }
};



struct CustomEdge{
};
struct CustomFace{

};
inline CustomVertex CustomMesh::vertex(IndexType i){
  return CustomVertex(i,*this);
}
inline CustomFace CustomMesh::face(IndexType i){
  return CustomFace();
}
inline CustomEdge CustomMesh::edge(IndexType i){
  return CustomEdge();
}
class IVertex{
public:
};
class IFace{};
class IEdge{};


class IVertexProperty{
  typedef size_t VertexIndex;
  typedef size_t PropertyIndex;
public:
  virtual void setProperty(VertexIndex i)=0;
};

class IMesh{
public:
  std::vector<IVertexProperty> properties;
};

class PositionXProperty : public IVertexProperty{

};
class PositionProperty : public IVertexProperty{
  std::vector<Vector3D> data;

};


template<> MESH_OPERATION_CLASS(VertexIndexType)<CustomMesh>{typedef unsigned int Type;};
template<> MESH_OPERATION_CLASS(VertexType)<CustomMesh>{typedef CustomVertex Type;};
template<> unsigned int MESH_OPERATION(VertexCount)<CustomMesh>::operation(const CustomMesh& mesh){return mesh.vertexCount;}
template<> CustomVertex MESH_OPERATION(VertexGet)<CustomMesh>::operation(CustomMesh& mesh, const unsigned index){return mesh.vertex(index);}


class MeshWriter{

};


template<typename PositionType, typename ObjectType, typename IndexType>
PositionType position(ObjectType & object, const IndexType index){return PositionType();}

template<typename VelocityType, typename ObjectType, typename IndexType>
VelocityType velocity(ObjectType &object, const IndexType index){return VelocityType();}

template<typename AccelerationType, typename ObjectType, typename IndexType>
AccelerationType acceleration(ObjectType &object, const IndexType index){return AccelerationType();}
#define DATATYPENAME(NAME) NAME##Type
#define DATATYPEOF(NAME) DATATYPENAME(NAME)
#define DATA(TYPE,NAME) typedef TYPE DATATYPENAME(NAME);



class TestTest{
private:
  typedef int AValue;
public:
  AValue result(){
    return 1;
  }
};
*/
}
