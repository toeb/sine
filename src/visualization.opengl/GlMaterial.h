#pragma once
#include <config.h>
#include <math/definitions.h>
namespace nspace{
class GlMaterial{
public:
  static GlMaterial * jade;
  static GlMaterial * rubber;
  static GlMaterial * plastic;
  static GlMaterial * sinn;
  static GlMaterial * bronze;
 

static void setup();

  void set();
  GlMaterial(){}
  GlMaterial(
    Real r,
    Real g,
    Real b, 
    Real ambient,
    Real diffuse, 
    Real specular, 
    Real alpha, 
    Real shininess);
  GlMaterial(
    Real Ra,
    Real Ga,
    Real Ba,
    Real Rd,
    Real Gd,
    Real Bd,
    Real Rs,
    Real Gs,
    Real Bs,
    Real alpha,
    Real shininess
    );
  Vector3D ambient;
  Vector3D diffuse;
  Vector3D specular;
  Real shininess;
  Real alpha;
};
}
