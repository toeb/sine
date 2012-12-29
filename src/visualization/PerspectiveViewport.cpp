#include "PerspectiveViewport.h"

using namespace nspace;

PerspectiveViewport::PerspectiveViewport():
  _FieldOfViewAngle(M_PI/ 4),
  _NearCutOffPlane(0.1),
  _FarCutOffPlane(200.0),
  _ZoomFactor(1.0){}