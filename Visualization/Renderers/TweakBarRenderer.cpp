#include "TweakBarRenderer.h"
#include <AntTweakBar/AntTweakBar.h>
#include <GL\glut.h>

#include <iostream>
using namespace IBDS;

bool TweakBarRenderer::initialize(){
  // Initialize AntTweakBar
  // (note that AntTweakBar could also be initialized after GLUT, no matter)
/*	if( !TwInit(TW_OPENGL, NULL) )
  {
    // A fatal error occured    
    fprintf(stderr, "AntTweakBar initialization failed: %s\n", TwGetLastError());
    return false;
  }
  //TwWindowSize(width, height);
  //after GLUT initialization
  // directly redirect GLUT events to AntTweakBar
  glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT); // same as MouseMotion
  */
  // send the ''glutGetModifers'' function pointer to AntTweakBar
  //TwGLUTModifiersFunc(glutGetModifiers);
  //_tweakBar = TwNewBar("TweakBar");
  // 	// turn wireframe mode on
  //int val = 1;
  //setWireframeCB(&val,NULL);

  // Create a tweak bar
/*	_tweakBar = TwNewBar("TweakBar");
  TwDefine(" GLOBAL help='TweakBarRenderer TweakBar.' "); // Message added to the help bar.
  TwDefine(" TweakBar size='250 250' position='5 5' color='96 200 224' text=dark "); // change default tweak bar size and color
  /*
  TwAddVarRO(m_tweakBar, "Time", TW_TYPE_FLOAT, &m_time, " label='Time' precision=5");

  TwAddVarCB(m_tweakBar, "Rotation", TW_TYPE_QUAT4F, setRotationCB, getRotationCB, &m_quat, 
    " label='Rotation' open help='Change the rotation.' ");

  // Add callback to toggle auto-rotate mode (callback functions are defined above).
  TwAddVarCB(m_tweakBar, "Wireframe", TW_TYPE_BOOL32, setWireframeCB, getWireframeCB, NULL, 
    " label='Wireframe' key=w help='Toggle wireframe mode.' ");
    */
  return true;
}
void TweakBarRenderer::cleanup(){
  TwTerminate();
}

void TweakBarRenderer::render(){
 // TwRefreshBar(_tweakBar);

  TwDraw();  // draw the tweak bar(s)
}