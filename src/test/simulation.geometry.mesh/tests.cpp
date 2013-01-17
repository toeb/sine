#include <CppUnitLite/TestHarness.h>
#include <math/core.h>
#include <math.matrix.h>
#include <math.matrix.dslib/core.h>
#include <visualization/Material.h>

#include <utility.reader.h>
#include <utility.reader.ply.h>
#include <utility.reader.obj.h>
#include <utility.reader.mtl.h>
#include <map>
#include <simulation.geometry/mesh/MeshOperations.h>
#include <iostream>
#include <fstream>


using namespace nspace;
TEST(7, CustomMesh){
  CustomMesh uut;
  uut.setFaceCount(10);
  uut.setVertexCount(11);
  uut.initialize();
  uut.vertex(0).position() = Vector3D(1,0,0);
  auto vertex = meshVertexGet(uut,0);
  auto result = isSameType(vertex,CustomVertex(0,uut));

  CHECK(result);

}

TEST(1,Test){
  MyVertex v;
  setVertexPosition(v,Vector3D(1,0,0));
  CHECK(v.position(0,0)==1);
}


TEST(2,CustomMesh){
  CustomMesh myMesh;
  auto result = isSameType<MESH_VERTEX_INDEX_TYPE(CustomMesh), size_t>();
  CHECK(result);
}
TEST(3, CustomMesh){
  CustomMesh myMesh;
  auto result = isSameType<MESH_VERTEX_TYPE(CustomMesh), CustomVertex>();
  CHECK(result);
}
TEST(4, CustomMesh){
  CustomMesh myMesh;
  auto result = meshVertexCount(myMesh);
  CHECK(result==0);
}
TEST(5, CustomMesh){
  CustomMesh myMesh;
  myMesh.setVertexCount(40);
  auto result = meshVertexCount(myMesh);
  CHECK(result==40);
}
TEST(6, CustomMesh){
  {
    CustomMesh uut;
    uut.setVertexCount(1);
    uut.initialize();
    uut.vertex(0).position()=Vector3D::UnitY();
    auto result = meshVertexGet(uut,0);
    CHECK(result.index == 0);
    CHECK(&result.mesh ==&uut);
    CHECK(result.position()(2)==0);
    CHECK(result.position()(1)==1);
    CHECK(result.position()(0)==0);
  }
}







TEST(1, MtlReader){
  MtlReader reader;
  bool result = reader.readFile("material/mtl/example.mtl");
  CHECK(result);
}

TEST(1, ObjReader){
  ObjReader obj;
  obj.run();

}


TEST(LoadPly, MeshReader){
  PlyReader reader;
  
  auto result = reader.readFile("meshes/ply/horse.ply");

  CHECK(result);
}

TEST(LoadObj, MeshReader){


}


