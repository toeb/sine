#include "GlTexture.h"
#include <visualization.opengl/opengl.h>
#include <simulation/Simulation.h>
using namespace nspace;

Texture::Texture(Image & image):_image(image),_id(0){
}
uint Texture::id()const{
  return _id;
}
void Texture::bind()const{
  if(!_id){
    Texture * ohoh = const_cast<Texture*>(this);

    glGenTextures(1,&ohoh->_id);
    glEnable (GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    glTexImage2D(GL_TEXTURE_2D, 0, _image.pixelSize(), _image.width(), _image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _image.data());
  }
  glEnable (GL_TEXTURE_2D);
  glBindTexture (GL_TEXTURE_2D, _id);
}
void Texture::unbind()const{
  glDisable(GL_TEXTURE_2D);
}

bool Texture::initializeObject(){
  /*
  glBindTexture(GL_TEXTURE_2D, _id);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, _image.width(), _image.height(), 0, GL_RGBA,
  GL_UNSIGNED_BYTE, _image.data());
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);*/

  /*
  glBindTexture(GL_TEXTURE_2D, _id);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, _image.width(), _image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _image.data());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);*/
  return true;
}