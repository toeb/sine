#include "FpsCamera.h"
#include <simulation.interaction/InputHandler.h>
using namespace nspace;
using namespace std;

#define iftype(type,object) if(dynamic_cast<type*>(object))dynamic_cast<type*>(object)

void FpsCamera::onViewportAdded(Viewport * viewport){

}
void FpsCamera::onViewportRemoved(Viewport * viewport){
}

FpsCamera::FpsCamera():roll(0),pitch(0),yaw(0){
  eulerIntegrator.setLowerBound(0.0);
  eulerIntegrator.setEvaluator(new Evaluator(kinematicBody()));
  interval()=0.01;
}

void FpsCamera::timeout(Time timePassed,Time time){
  if(!_handler)return;

  Real speed = 4;

  body.velocity().setZero();
  body.angularVelocity().setZero();  

  Matrix3x3 R = body.orientation().toRotationMatrix();


  Vector3D direction;
  Vector3D normal;
  Vector3D binormal;
  direction =  R.col(2);
  normal=  R.col(1);
  binormal=  R.col(0);



  if(_handler->isKeyDown(KEY_W))body.velocity() += direction * speed;
  if(_handler->isKeyDown(KEY_S))body.velocity() -= direction * speed;
  if(_handler->isKeyDown(KEY_A))body.velocity() += binormal * speed;
  if(_handler->isKeyDown(KEY_D))body.velocity() -= binormal * speed;
  if(_handler->isKeyDown(KEY_CTRL))body.velocity() += normal * speed;
  if(_handler->isKeyDown(KEY_SPACE))body.velocity() -= normal * speed;
  eulerIntegrator.setUpperBound(eulerIntegrator.upperBound()+timePassed);
  eulerIntegrator.integrate();


}

void FpsCamera::onMouseMove(int x , int y, int dx, int dy){
  if(abs(dx)>40 || abs(dy)>40){
    return;
  }
  Real speed = 0.1;
  Real length =dx+dy;// sqrt((Real)dx*dx+dy*dy);
  Real xSpeed = speed*dx;
  Real ySpeed = speed*dy;

  Matrix3x3 R = body.orientation().toRotationMatrix();


  Vector3D direction;
  Vector3D normal;
  Vector3D binormal;
  direction =  R.col(2);
  normal=  R.col(1);
  binormal=  R.col(0);

  if(!_handler)return;
  if(_handler->isMouseButtonDown(BUTTON_RIGHT)||_handler->isKeyDown(KEY_SHIFT)){
    body.position() += -direction*ySpeed;
    body.position() += -binormal*xSpeed;
  }
  if(_handler->isMouseButtonDown(BUTTON_MIDDLE)||_handler->isKeyDown(KEY_ALT)){
    body.position() += -normal*ySpeed;
    body.position() += -binormal*xSpeed;
  }

  if(_handler->isKeyDown(KEY_1)){    
    body.position() += binormal*length*speed;
  } 
  if(_handler->isKeyDown(KEY_2)){    
    body.position() +=normal*length*speed;
  }
  if(_handler->isKeyDown(KEY_3)){    
    body.position() +=direction* length*speed;
  }

  if(_handler->isMouseButtonDown(BUTTON_LEFT) || _handler->isKeyDown(KEY_Q)){
    yaw += -dx*speed*0.1;
    pitch += -dy*speed*0.1;
    Quaternion qx;
    Quaternion qy;

    qx.fromAxisAngle(Vector3D::UnitX(),pitch);
    qy.fromAxisAngle(Vector3D::UnitY(),yaw);
    qx.normalize();
    qy.normalize();
    body.orientation() = qy*qx;
    body.orientation().normalize();
  }

}