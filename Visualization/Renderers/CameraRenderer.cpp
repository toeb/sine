
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



void CameraRenderer::setInputHandler(InputHandler * handler){
  _input = handler;
}
void CameraRenderer::onBeforeRenderering(){
      MiniGL::setViewport (40.0f, 1.0f, 100.0f, Vector3D (15.0, 1.0, 20.0), Vector3D (5.0, -4, 0.0));
}
void CameraRenderer::render(){
  setMovementToZero();
  calculateRotationMatrices();
  const Matrix3x3 & R=getRotationMatrix(); 
  Vector3D dir, normal, binormal;
  R.getCoordinateVectors(dir,normal,binormal);

  if(_input->isKeyDown(Keys::KEY_W)){
    setVelocity(dir);
  }
  if(_input->isKeyDown(Keys::KEY_S)){
    setVelocity(-dir);
  }
  if(_input->isKeyDown(Keys::KEY_A)){
    setVelocity(-binormal);
  }
  if(_input->isKeyDown(Keys::KEY_D)){
    setVelocity(binormal);
  }
  if(_input->isKeyDown(Keys::KEY_C)){
    setVelocity(-normal);
  }
  if(_input->isKeyDown(Keys::KEY_SPACE)){
    setVelocity(normal);
  }
  if(_input->isKeyDown(Keys::KEY_F)){
    setAngularVelocity(normal);
  }

  
	Matrix4x4 transform;
	Vector3D scale(1, 1, 1);
  transform.setTransformation(getPosition(), R, scale);
	Real transformMatrix[16];
	transform.get(&transformMatrix[0]);
  glMultMatrix(&transformMatrix[0]);
    

  MiniGL::drawVector(Vector3D(0,0,-100),Vector3D(0,0,100),1,MiniGL::black);
  MiniGL::drawVector(Vector3D(0,-100,0),Vector3D(0,100,0),1,MiniGL::black);
  MiniGL::drawVector(Vector3D(-100,0,0),Vector3D(100,0,0),1,MiniGL::black);
}
