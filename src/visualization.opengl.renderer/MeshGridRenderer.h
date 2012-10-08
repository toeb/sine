#pragma once

#include <visualization/Renderer.h>
#include <simulation.kinematics/CoordinateSystem.h>
namespace nspace{
  // renders a mesh grid coordinate system
  class MeshGridRenderer : public Renderer{
    TYPED_OBJECT(MeshGridRenderer);
  private:
    CoordinateSystem _origin;
    uint _points;
    uint _stride;
    Real _spacing;
  public:
    MeshGridRenderer():_origin(CoordinateSystem::identity()),_points(20),_stride(5),_spacing(5.0){

    }
    uint & points(){return _points;}
    uint & stride(){return _stride;}
    Real & spacing(){return _spacing;}
    CoordinateSystem & coordinates(){return _origin;}
    const CoordinateSystem & coordinates()const{return _origin;}
    void render();
  };
}