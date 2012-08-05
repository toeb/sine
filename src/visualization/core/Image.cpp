#include "Image.h"
#include <common/patterns/ArrayPool.h>
#include <lodepng.h>
using namespace std;
using namespace nspace;

Image::~Image(){
  ArrayPool<Pixel>::freeArray(&_data, _width*_height);}
void Image::resize(uint width, uint height){  
  ArrayPool<Pixel>::freeArray(&_data,_width*_height);
  _width=width;
  _height=height;
  ArrayPool<Pixel>::createArray(&_data,width*height);
}
void Image::loadData(const void * dataPtr){
  memcpy(_data,dataPtr,byteSize());
}
void Image::load(uint width, uint height, const void * dataPtr){
  resize(width,height);
  loadData(dataPtr);
}

Image::Image():_data(0),_width(0),_height(0){}
Image::Image(uint width, uint height):_data(0),_width(0),_height(0){resize(width,height);}
Image::Image(uint width, uint height,Pixel * data):_data(0),_width(0),_height(0){load(width,height,data);}


bool PngImage::load(const std::string & filename){
  vector<unsigned char> imageBuffer;
  vector<unsigned char> image;
  lodepng::State state;
  unsigned int width;
  unsigned int height;

  lodepng::load_file(imageBuffer,"resources/images/testimage2.png");
  unsigned int error = lodepng::decode(image,width,height,state,imageBuffer);
  if(error)return false;
  Image::load(width,height,image.data());
  return true;
}

PngImage::PngImage(){}
PngImage::PngImage(const string & filename){load(filename);}