#include "FpsViewportController.h"
#include <simulation.interaction/InputHandler.h>
using namespace nspace;
using namespace std;

#define iftype(type,object) if(dynamic_cast<type*>(object))dynamic_cast<type*>(object)

void FpsCamera::onViewportAdded(Viewport * viewport){
  auto v = dynamic_cast<PerspectiveViewport*>(viewport);
  if(!v)return;
  body.position.mirror(v->Coordinates().position);
  body.orientation.mirror(v->Coordinates().orientation);
}
void FpsCamera::onViewportRemoved(Viewport * viewport){
  auto v = dynamic_cast<PerspectiveViewport*>(viewport);
  if(!v)return;
  // v->coordinates().unshare();


}

FpsCamera::FpsCamera():roll(0),pitch(0),yaw(0){
  isOneTimeTask()=false;
  interval()=0.01;

  eulerIntegrator.setLowerBound(0.0);
  eulerIntegrator.setUpperBound(0.0);
  eulerIntegrator.setEvaluator(new Evaluator(kinematicBody()));
}

void FpsCamera::timeout(Time timePassed,Time time){
  auto handler = currentHandler();
  if(!handler)return;

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



  if(handler->isKeyDown(KEY_W))body.velocity() += direction * speed;
  if(handler->isKeyDown(KEY_S))body.velocity() -= direction * speed;
  if(handler->isKeyDown(KEY_A))body.velocity() += binormal * speed;
  if(handler->isKeyDown(KEY_D))body.velocity() -= binormal * speed;
  if(handler->isKeyDown(KEY_CTRL))body.velocity() += normal * speed;
  if(handler->isKeyDown(KEY_SPACE))body.velocity() -= normal * speed;
  eulerIntegrator.setUpperBound(eulerIntegrator.upperBound()+timePassed);
  eulerIntegrator.integrate();

  

}

void FpsCamera::onMouseMove(InputHandler * inputhandler, int x , int y, int dx, int dy){
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

  if(!inputhandler)return;
  if(inputhandler->isMouseButtonDown(BUTTON_RIGHT)||inputhandler->isKeyDown(KEY_SHIFT)){
    body.position() += -direction*ySpeed;
    body.position() += -binormal*xSpeed;
  }
  if(inputhandler->isMouseButtonDown(BUTTON_MIDDLE)||inputhandler->isKeyDown(KEY_ALT)){
    body.position() += -normal*ySpeed;
    body.position() += -binormal*xSpeed;
  }

  if(inputhandler->isKeyDown(KEY_1)){    
    body.position() += binormal*length*speed;
  } 
  if(inputhandler->isKeyDown(KEY_2)){    
    body.position() +=normal*length*speed;
  }
  if(inputhandler->isKeyDown(KEY_3)){    
    body.position() +=direction* length*speed;
  }
  if(inputhandler->isMouseButtonDown(BUTTON_LEFT) || inputhandler->isKeyDown(KEY_Q)){

      logInfo("left mouse button down --> rotating view");

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
