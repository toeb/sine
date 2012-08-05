#pragma once
#include <common/Config.h>
#include <simulation/core/ISimulationObject.h>
#include <visualization/core/Pixel.h>
#include <string>
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
  };
  class PngImage : public Image{
  public:
    PngImage();
    PngImage(const std::string & filename);
    bool load(const std::string & filename);
  };

}