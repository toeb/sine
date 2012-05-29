
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
    q = q * getOrientation();
    q.normalize();
    setOrientation(q);
  
    q.setFromAxisAngle(binormal,dy/20.0);
    q = q * getOrientation();
    q.normalize();
    setOrientation(q);
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
  R.v[0] = Vector3D(5,-4,0)-getPosition();
  R.v[0].normalize();
  R.v[1]=Vector3D(0,1,0);
  R.v[2] = R.v[0] ^ R.v[1];
  R.v[2].normalize();

  q.setFromMatrix3x3(&R);
  //setOrientation(q);
}
void CameraRenderer::render(){
  
  setMovementToZero();
  calculateRotationMatrices();
  const Matrix3x3 & R=getRotationMatrix(); 
  Vector3D dir, normal, binormal;
  R.getCoordinateVectors(dir,normal,binormal);

  if(_input->isKeyDown(Keys::KEY_W)){
    setVelocity(getVelocity()+dir);
  }
  if(_input->isKeyDown(Keys::KEY_S)){
    setVelocity(getVelocity()-dir);
  }
  if(_input->isKeyDown(Keys::KEY_A)){
    setVelocity(getVelocity()-binormal);
  }
  if(_input->isKeyDown(Keys::KEY_D)){
    setVelocity(getVelocity()+binormal);
  }
  if(_input->isKeyDown(Keys::KEY_C)){
    setVelocity(getVelocity()-normal);
  }
  if(_input->isKeyDown(Keys::KEY_SPACE)){
    setVelocity(getVelocity()+normal);
  }
  if(_input->isKeyDown(Keys::KEY_J)){
    setAngularVelocity(getAngularVelocity()+Vector3D(0,1,0)*0.1);
  }
  if(_input->isKeyDown(Keys::KEY_L)){
    setAngularVelocity(getAngularVelocity()-Vector3D(0,1,0)*0.1);
  }

  if(_input->isKeyDown(Keys::KEY_I)){
    setAngularVelocity(getAngularVelocity()+binormal*0.1);
  }
  if(_input->isKeyDown(Keys::KEY_K)){
    setAngularVelocity(getAngularVelocity()-binormal*0.1);
  }

  MiniGL::multMatrix(R);

  
  MiniGL::drawVector(Vector3D(0,0,-100),Vector3D(0,0,100),1,MiniGL::black);
  MiniGL::drawVector(Vector3D(0,-100,0),Vector3D(0,100,0),1,MiniGL::black);
  MiniGL::drawVector(Vector3D(-100,0,0),Vector3D(100,0,0),1,MiniGL::black);

  MiniGL::translate(-getPosition());
  

  


  
}
