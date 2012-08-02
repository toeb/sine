#include "opengl.h"
#include "Utility.h"
#include <math/definitions.h>


using namespace nspace;
GlMaterial * nspace::GlMaterial::jade=new GlMaterial(0.14,0.22,0.16,0.54,0.89,0.63,0.32,0.32,0.32,0.9,12.8);
GlMaterial * nspace::GlMaterial::rubber= new GlMaterial(0.02,0.02,0.02,0.01,0.01,0.01,0.4,0.4,0.4,1.0,10.0);
GlMaterial * nspace::GlMaterial::plastic=new GlMaterial(0,0,0,0.01,0.01,0.01,0.5,0.5,0.5,1.0,32.0);  
GlMaterial * nspace::GlMaterial::sinn=new GlMaterial(0.14,0.22,0.16,0.54,0.89,0.63,0.32,0.32,0.32,0.9,12.8);
GlMaterial * nspace::GlMaterial::bronze=new GlMaterial(0.21,0.13,0.05,0.71,0.43,0.18,0.39,0.27,0.17,1,25.6);



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

void nspace::glScale(const Real x, const Real y, const Real z)
{
  glScaled(x, y, z);
}

void nspace::glTranslate(const Real x, const Real y, const Real z)
{
  glTranslated(x, y, z);
}

void nspace::glTranslate(const Vector3D& v)
{
  glTranslated(v.x(), v.y(), v.z());
}

void nspace::glNormal(const Vector3D& v)
{
  glNormal3d(v(0), v(1), v(2));
}

void nspace::glVertex(const Vector3D& v)
{

  glVertex3d(v(0), v(1), v(2));
}

void nspace::glMultMatrix(const Matrix3x3& R, const Vector3D& r)
{
  double m[16];
  m[0] = R(0, 0);
  m[4] = R(0, 1);
  m[8] = R(0, 2);
  m[12] = r(0);
  m[1] = R(1, 0);
  m[5] = R(1, 1);
  m[9] = R(1, 2);
  m[13] = r(1);
  m[2] = R(2, 0);
  m[6] = R(2, 1);
  m[10] = R(2, 2);
  m[14] = r(2);
  m[3] = 0;
  m[7] = 0;
  m[11] = 0;
  m[15] = 1;
  glMultMatrixd(m);
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
    

void GlMaterial
  ::set(){
    //GlMaterial::setup();
    glMaterial(*this);
}
void nspace::renderCube(){
  //http://www.morrowland.com/apron/tutorials/gl/gl_rotating_cube.php
   glBegin(GL_QUADS);		// Draw The Cube Using quads
    glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Top)
    glNormal3f(0.0f,1.0f,0.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Top)
    glNormal3f(0.0f,1.0f,0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);	// Bottom Left Of The Quad (Top)
    glNormal3f(0.0f,1.0f,0.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);	// Bottom Right Of The Quad (Top)
    glNormal3f(0.0f,1.0f,0.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);	// Top Right Of The Quad (Bottom)
    glNormal3f(0.0f,-1.0f,0.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);	// Top Left Of The Quad (Bottom)
    glNormal3f(0.0f,-1.0f,0.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Bottom)
    glNormal3f(0.0f,-1.0f,0.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Bottom)
    glNormal3f(0.0f,-1.0f,0.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Front)
    glNormal3f(0.0f,0.0f,1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Front)
    glNormal3f(0.0f,0.0f,1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Front)
    glNormal3f(0.0f,0.0f,1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Front)
    glNormal3f(0.0f,0.0f,1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);	// Top Right Of The Quad (Back)
    glNormal3f(0.0f,0.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);	// Top Left Of The Quad (Back)
    glNormal3f(0.0f,0.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);	// Bottom Left Of The Quad (Back)
    glNormal3f(0.0f,0.0f,-1.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);	// Bottom Right Of The Quad (Back)
    glNormal3f(0.0f,0.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);	// Top Right Of The Quad (Left)
    glNormal3f(-1.0f,0.0f,0.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);	// Top Left Of The Quad (Left)
    glNormal3f(-1.0f,0.0f,0.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);	// Bottom Left Of The Quad (Left)
    glNormal3f(-1.0f,0.0f,0.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);	// Bottom Right Of The Quad (Left)
    glNormal3f(-1.0f,0.0f,0.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);	// Top Right Of The Quad (Right)
    glNormal3f(1.0f,0.0f,0.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);	// Top Left Of The Quad (Right)
    glNormal3f(1.0f,0.0f,0.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);	// Bottom Left Of The Quad (Right)
    glNormal3f(1.0f,0.0f,0.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);	// Bottom Right Of The Quad (Right)
    glNormal3f(1.0f,0.0f,0.0f);
  glEnd();			// End Drawing The Cube

}

