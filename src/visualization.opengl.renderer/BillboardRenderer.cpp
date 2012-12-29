#include "BillboardRenderer.h"
#include <visualization.opengl/opengl.h>
#include <visualization.opengl/Utility.h>
#include <simulation/Simulation.h>
#include <lodepng.h>
using namespace std;
using namespace nspace;

bool BillboardRenderer::initializeObject(){
  PngImage * image = new PngImage("resources/images/testimage.png");
  Image * result = new Image;
  filter(*result,*image,1,1,[](Pixel & res, const PixelWindow & window){
    const Pixel & currentPixel = window(0,0);
    res = currentPixel;
    res.fromGrayscale(res.toGrayscale());
    //res.color.g = 0;
    //res.color.b = 255;
    //res.color.a =128;
    return;/*
           byte val = currentPixel.toGrayscale();
           //  std::cout<<(Real)val<<endl;
           if(currentPixel.color.a>127){
           res.fromGrayscale(255);
           }else{
           res.fromGrayscale(0);
           }
           res.fromGrayscale(255);*/
  });
  _texture = new Texture(*result);
  //<TODO *hub()<<_texture;
  return true;
}
void BillboardRenderer::cleanupObject(){
}
void BillboardRenderer::render(){
  _texture->bind();

  glBegin (GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f (0.0, 0.0);
  glVertex3f (0.0, 0.0, 0.0);
  glTexCoord2f (1.0, 0.0);
  glVertex3f (10.0, 0.0, 0.0);
  glTexCoord2f (1.0, 1.0);
  glVertex3f (10.0, 10.0, 0.0);
  glTexCoord2f (0.0, 1.0);
  glVertex3f (0.0, 10.0, 0.0);
  glEnd ();
  _texture->unbind();
}

BillboardRenderer::BillboardRenderer(){
}