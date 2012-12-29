#pragma once

#include <config.h>

#include <core/Object.h>

namespace nspace{
  class UrdfGeometry : public virtual Object{
    TYPED_OBJECT;
  private:
  public:
  };

  class UrdfBox : public UrdfGeometry{
    TYPED_OBJECT;
  public:
    Vector3D size;
  };

  class UrdfCylinder : public UrdfGeometry{
    TYPED_OBJECT;
  public:
    Real radius;
    Real length;
  };

  class UrdfSphere : public UrdfGeometry{
    TYPED_OBJECT;
  public:
    Real radius;
  };
  class UrdfMesh : public UrdfGeometry{
    TYPED_OBJECT;
  public:
    std::string filename;
    Vector3D scale;
  };
}