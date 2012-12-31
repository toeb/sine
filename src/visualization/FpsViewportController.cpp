#include "FpsViewportController.h"
#include <simulation.interaction/InputHandler.h>
using namespace nspace;
using namespace std;

#define iftype(type,object) if(dynamic_cast<type*>(object))dynamic_cast<type*>(object)

void FpsViewportController::onViewportAdded(Viewport * viewport){
  auto v = dynamic_cast<PerspectiveViewport*>(viewport);
  if(!v)return;
  body.position.mirror(v->Coordinates().position);
  body.orientation.mirror(v->Coordinates().orientation);
}
void FpsViewportController::onViewportRemoved(Viewport * viewport){
  auto v = dynamic_cast<PerspectiveViewport*>(viewport);
  if(!v)return;
  // v->coordinates().unshare();
}
Real degToRad(Real deg){
  return deg*scalar::pi<Real>()/180;
}
Real radToDeg(Real deg){
  return 180*deg/scalar::pi<Real>();
}
Real clampToPeriod(Real x, Real range){
  Real p = floor(x/range)*range;
  return x-p;
}
Real clampTo2Pi(Real x){
  return clampToPeriod(x,2*scalar::pi<Real>());
}
void deserializeDeg2Rad(Real & val,std::istream & in){
  in >> val;
  val = degToRad(val);
  val = clampTo2Pi(val);
}
void serializeRad2Deg(std::ostream & out, Real val){
  val = clampTo2Pi(val);
  val = radToDeg(val);
  out << val;
}
bool FpsViewportController::deserializeProperty(Real,Roll){
  deserializeDeg2Rad(*value,stream);
  return true;
}
bool FpsViewportController::serializeProperty(Real,Roll){
  serializeRad2Deg(stream,*value);
  return true;
}
bool FpsViewportController::deserializeProperty(Real,Yaw){
  deserializeDeg2Rad(*value,stream);
  return true;
}
bool FpsViewportController::serializeProperty(Real,Yaw){
  serializeRad2Deg(stream,*value);
  return true;
}

bool FpsViewportController::deserializeProperty(Real,Pitch){
  deserializeDeg2Rad(*value,stream);
  return true;
}
bool FpsViewportController::serializeProperty(Real,Pitch){
  serializeRad2Deg(stream,*value);
  return true;
}

FpsViewportController::FpsViewportController():_Roll(0),_Pitch(0),_Yaw(0){
  setName("FpsViewportController");
  setIsOneTimeTask(false);
  setInterval(0.01);

  setMovementSpeed(4);
  setRotationSpeed(0.1);

  eulerIntegrator.setLowerBound(0.0);
  eulerIntegrator.setUpperBound(0.0);
  eulerIntegrator.setEvaluator(new Evaluator(kinematicBody()));
  Components()|=&eulerIntegrator;
}

void FpsViewportController::timeout(Time timePassed,Time time){
  auto handler = currentHandler();
  if(!handler)return;

  Real speed = getMovementSpeed();

  body.velocity().setZero();
  body.angularVelocity().setZero();

  calculateRotation();
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

 // logInfo(body.velocity());

  eulerIntegrator.setUpperBound(eulerIntegrator.getUpperBound()+timePassed);
  eulerIntegrator.integrate();
}

void FpsViewportController::onMouseMove(InputHandler * inputhandler, int x , int y, int dx, int dy){
  if(abs(dx)>40 || abs(dy)>40){
    return;
  }
  Real speed = getRotationSpeed();
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
  if(inputhandler->isKeyDown(KEY_R)){
    _Roll += dx*speed*0.1;
    notifyRollChanged();
  }

  if(inputhandler->isMouseButtonDown(BUTTON_LEFT) || inputhandler->isKeyDown(KEY_Q)){
    debugMessage("left mouse button down --> rotating view (yaw: "<<(int)(getYaw()/scalar::pi<Real>()*360)<<", roll: "<<(int)(getRoll()/scalar::pi<Real>()*360)<<")",9);
    _Yaw += -dx*speed*0.1;
    notifyYawChanged();
    _Pitch += -dy*speed*0.1;
    notifyPitchChanged();
    calculateRotation();
  }
}

void FpsViewportController::calculateRotation(){
  Quaternion qx;
  Quaternion qy;
  Quaternion qz;

  qx.fromAxisAngle(Vector3D::UnitX(),_Pitch);
  qy.fromAxisAngle(Vector3D::UnitY(),_Yaw);
  qz.fromAxisAngle(Vector3D::UnitZ(),_Roll);
  qx.normalize();
  qy.normalize();
  qz.normalize();
  body.orientation() = qy*qx*qz;
  body.orientation().normalize();
}