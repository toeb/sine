#pragma once
#include <config.h>
#include <simulation/ISimulationObject.h>
#include <utility.imaging/Pixel.h>
#include <string>
#include <iostream>
#include <functional>
namespace nspace{
  

  class Image : public virtual ISimulationObject{
  private:
    uint _width;
    uint _height;
    Pixel * _data;
  public:  
    Image();
    Image(uint width, uint height);
    Image(uint width, uint height,Pixel * data);
    ~Image();

    inline uint width()const{return _width;}
    inline uint height()const{return _height;}
    inline uint size()const{return width()*height();}
    inline uint byteSize()const{return sizeof(Pixel)*size();}
    inline Pixel * data(){return _data;}
    inline const Pixel * data()const{return _data;}

    void resize(uint width, uint height);
    void loadData(const void * dataPtr);
    void load(uint width, uint height, const void * dataPtr);
    
    Pixel & operator()(uint i, uint j){
      return _data[_width*i+j];
    }
    const Pixel & operator()(uint i, uint j)const{
      return _data[_width*i+j];
    }
  };  
  class PixelWindow{
  public:
    PixelWindow(Image & img , uint x, uint y, uint width, uint height):_image(img),_width(width),_height(height),_x(x),_y(y){

    }
    Image & _image;
    uint _x;
    uint _y;
    uint _width;
    uint _height;

    const Pixel & operator()(int i, int j)const{
      return _image(_x+i,_y+j);
    }
    const Pixel & operator()(uint i)const{
      return this->operator()(i / _width, i % _width);
    }
  };
  static void filter(Image & output, const Image & input, uint width, uint height, std::function<void (Pixel &, const PixelWindow & )> f){
   output.resize(input.width()-2*width,input.height()-2*height);
   PixelWindow current(const_cast<Image &>(input),width,height,width,height);
    for(uint i=0; i < output.width(); i++){
      for(uint j=0; j < output.height();j++){
        current._x=width+i;
        current._y=height+j;
       // std::cout << i << " " << j  << " ";
        f(output(i,j), current);
      }
    }
  }
  

  class PngImage : public Image{
  public:
    PngImage();
    PngImage(const std::string & filename);
    bool load(const std::string & filename);
  };

}