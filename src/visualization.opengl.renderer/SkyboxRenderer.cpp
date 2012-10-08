#include "SkyboxRenderer.h"
#include <visualization.opengl/opengl.h>
#include <visualization.opengl/Utility.h>
#include <utility.imaging/Image.h>
using namespace nspace;



SkyboxRenderer::SkyboxRenderer(const std::string & filebase){
  setName("SkyboxRenderer");
  Textures()|=new Texture(*new PngImage(filebase+"0.png"));
  Textures()|=new Texture(*new PngImage(filebase+"1.png"));
  Textures()|=new Texture(*new PngImage(filebase+"2.png"));
  Textures()|=new Texture(*new PngImage(filebase+"3.png"));
  Textures()|=new Texture(*new PngImage(filebase+"4.png"));
  Textures()|=new Texture(*new PngImage(filebase+"5.png"));
  Textures().foreachElement([this](Texture * t){
    components()|=t;
    t->initialize();
  });
}

void SkyboxRenderer::render(){
    glDisable(GL_DEPTH_TEST);
		//glCallList(2412);

     Real sz=10.0f;
	glDisable(GL_LIGHTING);
	  glEnable(GL_TEXTURE_2D);
    Textures().at(0)->bind();
	  glBegin(GL_QUADS);	
		glColor3f (1,1,1);
		// Das vordere QUAD
		glNormal3f(0,0,1);
		glTexCoord2d(0, 0); glVertex3f(-sz, -sz, sz); 
		glTexCoord2d(1, 0); glVertex3f( sz, -sz, sz); 
		glTexCoord2d(1, 1); glVertex3f( sz, sz, sz); 
		glTexCoord2d(0, 1); glVertex3f(-sz, sz, sz); 
	  glEnd();

	 
    Textures().at(1)->bind();
	  glBegin(GL_QUADS);	
		// Das rechte QUAD
		glNormal3f(1,0,0);
		glTexCoord2d(1, 0); glVertex3f( sz, -sz, -sz); 
		glTexCoord2d(1, 1); glVertex3f( sz, sz, -sz); 
		glTexCoord2d(0, 1); glVertex3f( sz, sz, sz); 
		glTexCoord2d(0, 0); glVertex3f( sz, -sz, sz); 
	  glEnd();
    
    Textures().at(2)->bind();
	  glBegin(GL_QUADS);	
		// Das hintere QUAD
		glNormal3f(0,0,-1);
		glTexCoord2d(1, 0); glVertex3f(-sz, -sz, -sz);
		glTexCoord2d(1, 1); glVertex3f(-sz, sz, -sz);
		glTexCoord2d(0, 1); glVertex3f( sz, sz, -sz);
		glTexCoord2d(0, 0); glVertex3f( sz, -sz, -sz);
	  glEnd();
    
    Textures().at(3)->bind();
	  glBegin(GL_QUADS);	
		// Das linke QUAD
		glNormal3f(-1,0,0);
		glTexCoord2d(0, 0); glVertex3f(-sz, -sz, -sz); 
		glTexCoord2d(1, 0); glVertex3f(-sz, -sz, sz); 
		glTexCoord2d(1, 1); glVertex3f(-sz, sz, sz); 
		glTexCoord2d(0, 1); glVertex3f(-sz, sz, -sz); 
	  glEnd();
    
    Textures().at(4)->bind();
	  glBegin(GL_QUADS);	
		// Das obere QUAD
		glNormal3f(0,1,0);
		glTexCoord2d(0, 1); glVertex3f(-sz, sz, -sz); 
		glTexCoord2f(0, 0); glVertex3f(-sz, sz, sz); 
		glTexCoord2f(1, 0); glVertex3f( sz, sz, sz); 
		glTexCoord2f(1, 1); glVertex3f( sz, sz, -sz); 
	  glEnd();
    
    Textures().at(5)->bind();
	  glBegin(GL_QUADS);	
		// Das untere QUAD
		glNormal3f(0,-1,0);
		glTexCoord2d(1, 1); glVertex3f( sz, -sz, sz); 
		glTexCoord2d(0, 1); glVertex3f(-sz, -sz, sz);
		glTexCoord2d(0, 0); glVertex3f(-sz, -sz, -sz); 
		glTexCoord2d(1, 0); glVertex3f( sz, -sz, -sz); 
	  glEnd();

	  glDisable(GL_TEXTURE_2D);
	
		glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

bool SkyboxRenderer::initializeObject(){
  

  Real sz=10.0f;
	glNewList (2412, GL_COMPILE);
	  glEnable(GL_TEXTURE_2D);
    Textures().at(0)->bind();
	  glBegin(GL_QUADS);	
		glColor3f (1,1,1);
		// Das vordere QUAD
		glNormal3f(0,0,1);
		glTexCoord2d(0, 0); glVertex3f(-sz, -sz, sz); 
		glTexCoord2d(1, 0); glVertex3f( sz, -sz, sz); 
		glTexCoord2d(1, 1); glVertex3f( sz, sz, sz); 
		glTexCoord2d(0, 1); glVertex3f(-sz, sz, sz); 
	  glEnd();

	 
    Textures().at(1)->bind();
	  glBegin(GL_QUADS);	
		// Das rechte QUAD
		glNormal3f(1,0,0);
		glTexCoord2d(1, 0); glVertex3f( sz, -sz, -sz); 
		glTexCoord2d(1, 1); glVertex3f( sz, sz, -sz); 
		glTexCoord2d(0, 1); glVertex3f( sz, sz, sz); 
		glTexCoord2d(0, 0); glVertex3f( sz, -sz, sz); 
	  glEnd();
    
    Textures().at(2)->bind();
	  glBegin(GL_QUADS);	
		// Das hintere QUAD
		glNormal3f(0,0,-1);
		glTexCoord2d(1, 0); glVertex3f(-sz, -sz, -sz);
		glTexCoord2d(1, 1); glVertex3f(-sz, sz, -sz);
		glTexCoord2d(0, 1); glVertex3f( sz, sz, -sz);
		glTexCoord2d(0, 0); glVertex3f( sz, -sz, -sz);
	  glEnd();
    
    Textures().at(3)->bind();
	  glBegin(GL_QUADS);	
		// Das linke QUAD
		glNormal3f(-1,0,0);
		glTexCoord2d(0, 0); glVertex3f(-sz, -sz, -sz); 
		glTexCoord2d(1, 0); glVertex3f(-sz, -sz, sz); 
		glTexCoord2d(1, 1); glVertex3f(-sz, sz, sz); 
		glTexCoord2d(0, 1); glVertex3f(-sz, sz, -sz); 
	  glEnd();
    
    Textures().at(4)->bind();
	  glBegin(GL_QUADS);	
		// Das obere QUAD
		glNormal3f(0,1,0);
		glTexCoord2d(0, 1); glVertex3f(-sz, sz, -sz); 
		glTexCoord2f(0, 0); glVertex3f(-sz, sz, sz); 
		glTexCoord2f(1, 0); glVertex3f( sz, sz, sz); 
		glTexCoord2f(1, 1); glVertex3f( sz, sz, -sz); 
	  glEnd();
    
    Textures().at(5)->bind();
	  glBegin(GL_QUADS);	
		// Das untere QUAD
		glNormal3f(0,-1,0);
		glTexCoord2d(1, 1); glVertex3f( sz, -sz, sz); 
		glTexCoord2d(0, 1); glVertex3f(-sz, -sz, sz);
		glTexCoord2d(0, 0); glVertex3f(-sz, -sz, -sz); 
		glTexCoord2d(1, 0); glVertex3f( sz, -sz, -sz); 
	  glEnd();

	  glDisable(GL_TEXTURE_2D);
	glEndList();	
  return true;
}