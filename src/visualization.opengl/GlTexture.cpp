#include "GlTexture.h"
#include <visualization.opengl/opengl.h>
#include <simulation/Simulation.h>
using namespace nspace;

Texture::Texture(Image & image):_image(image),_id(_nextId++){

}
uint Texture::id()const{
  return _id;
}
void Texture::bind()const{
  glEnable (GL_TEXTURE_2D);
  glBindTexture (GL_TEXTURE_2D, _id);
}
void Texture::unbind()const{
  glDisable(GL_TEXTURE_2D);
}

bool Texture::initializeObject(){
  glEnable (GL_TEXTURE_2D);
  //glGenTextures(1,&_id);

  glBindTexture(GL_TEXTURE_2D, _id);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, _image.width(), _image.height(), 0, GL_RGBA, 
					 GL_UNSIGNED_BYTE, _image.data());
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  /*
  glBindTexture(GL_TEXTURE_2D, _id);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, _image.width(), _image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _image.data());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);*/
  return true;
}

uint Texture::_nextId=13;