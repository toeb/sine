#pragma once
#include <simulation.geometry/polygon/Polygon.h>
#include <math/core.h>
namespace nspace{
  class Rectangle : public virtual Polygon{
  private:
    Vector2D _dimension;
  public:
    Rectangle(const Vector2D & dimension);

    void setDimension(const Vector2D & dim);
    void setDimension(Real x,Real y);
    const Vector2D & getDimension()const;

    void getNormal(Vector3D & normal)const;

  protected:
    void createGeometry();
  };
}
