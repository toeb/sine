#include "opengl.h"
#include "Utility.h"
#include <math/core.h>



using namespace nspace;
GlMaterial * nspace::GlMaterial::jade=new GlMaterial(0.14,0.22,0.16,0.54,0.89,0.63,0.32,0.32,0.32,0.9,12.8);
GlMaterial * nspace::GlMaterial::rubber= new GlMaterial(0.02,0.02,0.02,0.01,0.01,0.01,0.4,0.4,0.4,1.0,10.0);
GlMaterial * nspace::GlMaterial::plastic=new GlMaterial(0,0,0,0.01,0.01,0.01,0.5,0.5,0.5,1.0,32.0);  
GlMaterial * nspace::GlMaterial::sinn=new GlMaterial(0.14,0.22,0.16,0.54,0.89,0.63,0.32,0.32,0.32,0.9,12.8);
GlMaterial * nspace::GlMaterial::bronze=new GlMaterial(0.21,0.13,0.05,0.71,0.43,0.18,0.39,0.27,0.17,1,25.6);

void nspace::glTriangle(const Vector3D & a,const Vector3D & b,const Vector3D & c,const Vector3D & n){
  glBegin(GL_TRIANGLES);
  glNormal(n);
  glTexCoord2f (0.0, 0.0);
  glVertex(a);
  glTexCoord2f (1.0, 0.0);
  glVertex(b);
  glTexCoord2f (0.0,1.0);
  glVertex(c);
  glEnd();
}
void nspace::glQuad(const Vector3D & a,const Vector3D & b,const Vector3D & c,const Vector3D & d,const Vector3D & n){
  glBegin(GL_TRIANGLES);
  glNormal(n);
  glTexCoord2f (0.0, 0.0);
  glVertex(a);
  glTexCoord2f (1.0, 0.0);
  glVertex(b);
  glTexCoord2f (1.0,1.0);
  glVertex(c);
  glTexCoord2f (0.0,1.0);
  glVertex(c);
  glEnd();
}

void nspace::convert(const nspace::Matrix3x3 &from, double* to){
  
  to[0] = from(0,0);
  to[1] = from(1,0);
  to[2] = from(2,0);
  to[3] = 0;

  to[4] = from(0,1);
  to[5] = from(1,1);
  to[6] = from(2,1);
  to[7] = 0;

  to[ 8] = from(0,2);
  to[ 9] = from(1,2);
  to[10] = from(2,2);
  to[11] = 0;

  to[12] = 0;
  to[13] = 0;
  to[14] = 0;
  to[15] = 1;
}
// copied from murosimf
void nspace::glRotate(const Real u, const Real x, const Real y, const Real z)
{
  glRotated(u, x, y, z);
}


void nspace::glTransformation(const CoordinateSystem & coordinates){
  glRotate(coordinates.orientation().toTransposedRotationMatrix());
  glTranslate(coordinates.position());
}
void nspace::glRotateQuaternion(const Quaternion & q){
  glRotate(q.toRotationMatrix());
}
void nspace::glScale(const Vector3D & s){
  glScale(s(0),s(1),s(2));
}
void nspace::glScale(Real s){
  glScale(s,s,s);
}
void nspace::glScale(const Real x, const Real y, const Real z)
{
  glScaled(x, y, z);
}


void nspace::glTranslate(const Real x, const Real y, const Real z)
{
  glTranslated(x, y, z);
}


void nspace::glColor(const Color & color){
  glColor4d(color.r(),color.g(),color.b(),color.a());
}
void nspace::glSetClearColor(const Color & color){
  glClearColor(color.r(),color.g(),color.b(),color.a());
}



void nspace::glLight(int light, 
  const Vector3D & position, 
  const Vector3D & ambience, 
  const Vector3D & diffuse, 
  const Vector3D& specular)
{
  float amb[4];
  float dif[4];
  float spec[4];
  float pos[4];

  amb[0] = ambience.x();
  amb[1] = ambience.y();
  amb[2] =ambience.z();
  amb[3] = 1;
  dif[0] = diffuse.x();
  dif[1] = diffuse.y();
  dif[2] = diffuse.z();
  dif[3] = 1;
  spec[0] = specular.x();
  spec[1] = specular.y();
  spec[2] =specular.z();
  spec[3] = 1;
  pos[0] = position.x();
  pos[1] = position.y();
  pos[2] = position.z();
  pos[3] = 1;

  glLightfv(light, GL_POSITION, pos);
  glLightfv(light, GL_AMBIENT, amb);
  glLightfv(light, GL_DIFFUSE, dif);
  glLightfv(light, GL_SPECULAR, spec);
}

void setMaterialFloat(float* vec, Vector3D value, Real factor, Real a)
{
  vec[0] = value(0) * factor;
  vec[1] = value(1) * factor;
  vec[2] = value(2) * factor;
  vec[3] = a;
}


void nspace::glMaterial(
  const Vector3D & color
  ,const Real & ambient
  , const Real & diffuse
  , const Real & specular
  , const Real & shininess
  , const Real & alpha)
{
  float vec[4];

  setMaterialFloat(vec,color,ambient, alpha);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, vec);

  setMaterialFloat(vec, color,diffuse, alpha);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, vec);
  glColor3fv(vec);

  setMaterialFloat(vec,color, specular,alpha);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vec);

  float zero[4] = {0.f, 0.f, 0.f, 0.f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, zero);

  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  glColor3f(color.x(), color.y(),color.z());
}



void nspace::glMaterial(nspace::GlMaterial & material){
  float vec[4];

  setMaterialFloat(vec,material.ambient,1, material.alpha);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, vec);

  setMaterialFloat(vec, material.diffuse,1,  material.alpha);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, vec);
  glColor3fv(vec);

  setMaterialFloat(vec,material.specular, 1, material.alpha);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vec);

  float zero[4] = {0.f, 0.f, 0.f, 0.f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, zero);

  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);

};
    




