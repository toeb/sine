#include <visualization.opengl/opengl.h>
#include "LightRenderer.h"
using namespace nspace;

void LightRenderer::doLights(){
    
	float t = 0.9f;
	float a = 0.2f;
	float amb0 [4] = {a,a,a,1};
	float diff0 [4] = {t,0,0,1};
	float spec0 [4] = {1,1,1,1};
	float pos0 [4] = {-10,10,10,1};
	glLightfv(GL_LIGHT0, GL_AMBIENT,  amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  diff0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos0);
	glEnable(GL_LIGHT0);

	float amb1 [4] = {a,a,a,1};
	float diff1 [4] = {0,0,t,1};
	float spec1 [4] = {1,1,1,1};
	float pos1 [4] = {10,10,10,1};
	glLightfv(GL_LIGHT1, GL_AMBIENT,  amb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  diff1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glEnable(GL_LIGHT1);

	float amb2 [4] = {a,a,a,1};
	float diff2 [4] = {0,t,0,1};
	float spec2 [4] = {1,1,1,1};
	float pos2 [4] = {0,10,10,1};
	glLightfv(GL_LIGHT2, GL_AMBIENT,  amb2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  diff2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, spec2);
	glLightfv(GL_LIGHT2, GL_POSITION, pos2);
	glEnable(GL_LIGHT2);


	glEnable(GL_LIGHTING);
	glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
}
void LightRenderer::render(){
  //doLights();
}
void LightRenderer::onBeforeRendering(){
  doLights();
}