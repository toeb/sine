
#ifdef WIN32
#include "windows.h"
#endif
#include "GL/gl.h"
#include "GL/glu.h"
#include <iostream>
#include "CameraRenderer.h"
#include <Visualization/MiniGL.h>
#include <Math/Matrix4x4.h>
using namespace std;
using namespace IBDS;

void CameraRenderer::onMouseMove(int x, int y , int dx, int dy){
  
  calculateRotationMatrices();
  const Matrix3x3 & R=getRotationMatrix(); 
  Vector3D dir, normal, binormal;
  R.getCoordinateVectors(dir,normal,binormal);

  if(_input->isKeyDown(Keys::KEY_F3)){
    Quaternion q;
    q.setFromAxisAngle(normal,dx/20.0);
    q = q * orientation();
    q.normalize();
    orientation() = q;
  
    q.setFromAxisAngle(binormal,dy/20.0);
    q = q * orientation();
    q.normalize();
    orientation() = q;
  }

}

void CameraRenderer::setInputHandler(InputHandler * handler){
  _input = handler;
}
void CameraRenderer::onBeforeRenderering(){
  //(15 1 20)t  (5,-4,0)
  MiniGL::setViewport (40.0f, 1.0f, 100.0f, Vector3D (0, 0, 0), Vector3D (1,0,0));
 // setPosition(Vector3D(15,1,20));
  Quaternion q;
  Matrix3x3 R;
  R.v[0] = Vector3D(5,-4,0)-position();
  R.v[0].normalize();
  R.v[1]=Vector3D(0,1,0);
  R.v[2] = R.v[0] ^ R.v[1];
  R.v[2].normalize();

  q.setFromMatrix3x3(&R);
  //setOrientation(q);
}
void CameraRenderer::camera(){
  
  setMovementToZero();
  Matrix3x3 R;
  orientation().getMatrix3x3(R);
  Vector3D dir, normal, binormal;
  R.getCoordinateVectors(dir,normal,binormal);

  if(_input->isKeyDown(Keys::KEY_W)){
    velocity() = velocity()+dir;
  }
  if(_input->isKeyDown(Keys::KEY_S)){
    velocity() = velocity()-dir;
  }
  if(_input->isKeyDown(Keys::KEY_A)){
    velocity() = (velocity()-binormal);
  }
  if(_input->isKeyDown(Keys::KEY_D)){
    velocity()=(velocity()+binormal);
  }
  if(_input->isKeyDown(Keys::KEY_C)){
    velocity()=(velocity()-normal);
  }
  if(_input->isKeyDown(Keys::KEY_SPACE)){
    velocity()=(velocity()+normal);
  }
  if(_input->isKeyDown(Keys::KEY_J)){
    angularVelocity()=(angularVelocity()+Vector3D(0,1,0)*0.1);
  }
  if(_input->isKeyDown(Keys::KEY_L)){
    angularVelocity()=(angularVelocity()-Vector3D(0,1,0)*0.1);
  }

  if(_input->isKeyDown(Keys::KEY_I)){
    angularVelocity()=(angularVelocity()+binormal*0.1);
  }
  if(_input->isKeyDown(Keys::KEY_K)){
    angularVelocity()=(angularVelocity()-binormal*0.1);
  }

  MiniGL::multMatrix(R);

  
  MiniGL::drawVector(Vector3D(0,0,-100),Vector3D(0,0,100),1,MiniGL::black);
  MiniGL::drawVector(Vector3D(0,-100,0),Vector3D(0,100,0),1,MiniGL::black);
  MiniGL::drawVector(Vector3D(-100,0,0),Vector3D(100,0,0),1,MiniGL::black);

  MiniGL::translate(-position());
  
}
