#include "opengl.h"
#include "Utility.h"
#include <math/core.h>



using namespace nspace;

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
void nspace::glDisableLights(){
  const uint lightId = GL_LIGHT0;
  for(uint i=0; i < 8;i++){
    glDisable(lightId+i);
  }  
}

void nspace::glLight(uint lightNumber, const Light & light){  
  glPushMatrix();
  glTransformation(light.Coordinates());
  const uint lightId = GL_LIGHT0+lightNumber;
  glLightfv(lightId,GL_AMBIENT  ,(light.AmbientColor()  * light.AmbientIntensity() ));
  glLightfv(lightId,GL_DIFFUSE  ,(light.DiffuseColor()  * light.DiffuseIntensity() ));
  glLightfv(lightId,GL_SPECULAR ,(light.SpecularColor() * light.SpecularIntensity()));
  float pos[4]={0,0,0,1};
  glLightfv(lightId,GL_POSITION,pos);
  glEnable(lightId);
  glPopMatrix();
}

void nspace::glMaterial(
  const Vector3D & color
  ,  Real ambient
  ,  Real diffuse
  ,  Real specular
  ,  Real shininess
  ,  Real alpha)
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



void nspace::glMaterial(const nspace::Material & material){
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.Ambient());
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.Diffuse());
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.Diffuse());
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material.Emission());
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.Shininess());
  glColor(material.Diffuse());
};
    
void nspace::glQuad(const Vector3D & a,const Vector3D & b,const Vector3D & c,const Vector3D & d, const Vector3D * normal){
    glBegin(GL_QUADS);

    if(!normal){
      Vector3D n;
      vectorop::crossProduct(n, b-a, c-a);
      n.normalize();
      glNormal(n);
    }else{
      glNormal(*normal);
    }

		// Das untere QUAD
		glTexCoord2d(0, 1); glVertex(a); 
		glTexCoord2d(1, 1); glVertex(b);
		glTexCoord2d(1, 0); glVertex(c); 
		glTexCoord2d(0, 0); glVertex(d); 
	  glEnd();
}

void nspace::glQuad(const Vector3D & position, const Quaternion & normal, Real a){
  auto matrix = normal.toRotationMatrix();
  auto ux = matrix.row(0);
  auto uy = matrix.row(1);
  auto uz = matrix.row(2);

  auto a2 = a /2;
  auto va = position-ux * a2-uy*a2;
  auto vb = position+ux * a2-uy*a2;
  auto vc = position+ux * a2+uy*a2;
  auto vd = position-ux * a2-uy*a2;
  
  uz.normalize();
  glQuad(va,vb,vc,vd,&uz);

}


void nspace::glSphere(double r, int lats, int longs) {
    int i, j;
    for(i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
}


void nspace::glLine(const Vector3D & a, const Vector3D & b){  
	glBegin (GL_LINES);
  glVertex3d(a(0),a(1),a(2));
  glVertex3d(b(0),b(1),b(2));
	glEnd ();  
}
void nspace::glVector(const Vector3D & start, const Vector3D & direction){
  glLine(start,start+direction);
}

