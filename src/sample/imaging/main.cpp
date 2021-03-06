#include <lodepng/lodepng.h>
#include <math/core.h>
#include <string>
#include <config.h>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <simulation.timing/Timeable.h>
#include <core.logging.h>
#include <math.matrix.dslib/DynamicMatrix.h>
using namespace nspace;
using namespace nspace::matrix2;
using namespace std;

union Pixel{
  Pixel(){value[0]=0;value[1]=0; value[2]=0; value[3]=0;}
  struct{
    byte r;
    byte g;
    byte b;
    byte a;
  }color;
  byte value[4];
};

struct PixelRed{
  operator Pixel(){
    Pixel result;
    result.color.r = (byte)value;
    return result;
  }
  PixelRed(const Pixel & pixel){
    value = pixel.color.r;
  }
  Real value;
};


struct PixelGreen{
  operator Pixel(){
    Pixel result;
    result.color.g = (byte)value;
    return result;
  }
  PixelGreen(const Pixel & pixel){
    value = pixel.color.g;
  }
  Real value;
};

struct PixelBlue{
  operator Pixel(){
    Pixel result;
    result.color.b=(byte)value;
    return result;
  }
  PixelBlue(const Pixel & pixel){
    value = pixel.color.b;
  }
  Real value;
};

struct PixelAlpha{
  operator Pixel(){
    Pixel result;
    result.color.a=(byte)value;
    return result;
  }
  PixelAlpha(const Pixel & pixel){
    value = pixel.color.a;
  }
  Real value;
};




namespace nspace{
  std::ostream & operator << (std::ostream & o, const Pixel & pixel){
    o << "("<<(int)pixel.color.r<<"r, "<<(int)pixel.color.g<<"g, "<<(int)pixel.color.b<<"b, "<<(int)pixel.color.a<<"a)";
    return o;
  }

}



class Image{
  uint _width;
  uint _height;
  DynamicMatrix<Real> _red;
  DynamicMatrix<Real> _green;
  DynamicMatrix<Real> _blue;
  DynamicMatrix<Real> _alpha;
public:
  Image():_width(0),_height(0){}
  template<typename T>
  void toGrayscale(DynamicMatrix<T> & g)const{
    g= 0.2126 * _red + 0.7152 * _green + 0.0722 * _blue;  
  }
  template<typename T>
  void fromGrayscale(const DynamicMatrix<T> & g){
    resize(g.cols(),g.rows());
    _red = g;
    _green = g;
    _blue = g;
    _alpha.setConstant(255.0);
  }

  friend class ImageLoader;
  const DynamicMatrix<Real> & red()const{
    return _red;
  }
  const DynamicMatrix<Real> & green()const{
    return _green;
  }
  const DynamicMatrix<Real> & blue()const{
    return _blue;
  }
  const DynamicMatrix<Real> & alpha()const{
    return _alpha;
  }
   DynamicMatrix<Real> & red(){
    return _red;
  }
   DynamicMatrix<Real> & green(){
    return _green;
  }
   DynamicMatrix<Real> & blue(){
    return _blue;
  }
   DynamicMatrix<Real> & alpha(){
    return _alpha;
  }
  void resize(uint width, uint height){
    _width = width;
    _height = height;
    _red.resize(height,width);
    _green.resize(height,width);
    _blue.resize(height,width);
    _alpha.resize(height,width);
  }
  inline uint size()const{
    return _width*_height;
  }
  inline uint width()const{
    return _width;
  }
  inline uint height()const{
    return _height;
  }

};



class ImageLoader : public virtual Log{
public:
  
  virtual void load(Image & image, std::istream & i)=0;
  virtual void store(std::ostream & o, const Image & image)=0;
  void loadFromFile(Image & img, const std::string & filename){
    ifstream stream(filename.c_str(),  std::ios::in|std::ios::binary|std::ios::ate);
    if(!stream.good()){
      logError("could not open file "<< filename);
    }
    load(img,stream);
    stream.close();
  }
  void storeToFile(const std::string & filename, const Image & img){
    ofstream stream(filename.c_str(),std::ios::out|std::ios::binary);
    if(!stream){
      logError("could not open file "<< filename);
    }
    store(stream,img);
    stream.close();
  }
  
};



class PngLoader : public ImageLoader{
public:
  virtual void load( Image & image, std::istream & stream ) 
  {
    std::streamsize size = 0;
    if(stream.seekg(0, std::ios::end).good()) size = stream.tellg();
    if(stream.seekg(0, std::ios::beg).good()) size -= stream.tellg();
    vector<byte> imageBuffer;
    imageBuffer.resize(size_t(size));
    if(size >0)stream.read((char*)&imageBuffer[0],size);
    else return;

    vector<byte> imageDecoded;
    lodepng::State state;
    unsigned int width;
    unsigned int height;

    unsigned int error = lodepng::decode(imageDecoded,width,height,state,imageBuffer);
    if(error)return;

    image.resize(width,height);
    Pixel * data =(Pixel*)imageDecoded.data();
    for(int i=0; i < image.red().size();i++){
      image.red()(i)=data[i].color.r;
      image.green()(i)=data[i].color.g;
      image.blue()(i)=data[i].color.b;
      image.alpha()(i)=data[i].color.a;
    }


  }



  virtual void store( std::ostream & o, const Image & image ) 
  {    
    std::vector<Pixel> data;
    //normalize image first
    for(int i=0; i < image.size();i++){
      Pixel p;
      p.color.r = (byte)image.red()(i);
      p.color.g = (byte)image.green()(i);
      p.color.b = (byte)image.blue()(i);
      p.color.a = (byte)image.alpha()(i);
      data.push_back(p);
    }


    vector<byte> enc;
    lodepng::State state;
    unsigned error = lodepng::encode(enc,(byte*)data.data(),image.width(),image.height(),state);
    if(error)return;
    o.write((char*)enc.data(),enc.size());

    o.write(data.empty() ? 0 : (char*)&data[0], std::streamsize(data.size()));
  }

};




int main(int argc, char ** argv){
  /*
  DynamicMatrix<Real> I(4,4);
  DynamicMatrix<Real> k(2,2);
  I.setFunction([](Real & v, int i, int j){v=i==j;});
  k.setConstant(1.0);
  DynamicMatrix<Real> res;
  MatrixOps::convolveSame(res, I,k);

  I.toStream(cout);
  k.toStream(cout);
  res.toStream(cout);

  *///*
  PngLoader pngLoader;
  Image img;
  pngLoader.loadFromFile(img,"resources/images/testHuge.png");


  DynamicMatrix<Real> I;
  img.toGrayscale(I);

  //I.setFunction([](Real & v, int i, int j){v = i==j;});
  
  DynamicMatrix<Real> Ix,Iy,IxIy,IxIx, IyIy;
  DynamicMatrix<Real> dx(1,3);
  dx(0)=-0.5;
  dx(1)=0;
  dx(2)=0.5;
  DynamicMatrix<Real> dy = dx.transpose(); 
  
  matrix::convolveSame(Ix,I,dx);
  matrix::convolveSame(Iy,I,dy);


  matrix::elementWiseMultiply(IxIy, Ix,Iy);
  matrix::elementWiseMultiply(IxIx, Ix,Ix);
  matrix::elementWiseMultiply(IyIy, Iy,Iy);

  I.toUnitInterval();
  I *= 255.0;
  img.fromGrayscale(I);
  pngLoader.storeToFile("I.png",img);
  Ix.toUnitInterval();
  Ix *= 255.0;
  img.fromGrayscale(Ix);
  pngLoader.storeToFile("Ix.png",img);
  Iy.toUnitInterval();
  Iy *= 255.0;
  img.fromGrayscale(Iy);
  pngLoader.storeToFile("Iy.png",img);

  IxIx.toUnitInterval();
  IxIx *= 255.0;
  img.fromGrayscale(IxIx);
  pngLoader.storeToFile("IxIx.png",img);

  IyIy.toUnitInterval();
  IyIy *= 255.0;
  img.fromGrayscale(IyIy);
  pngLoader.storeToFile("IyIy.png",img);

  IxIy.toUnitInterval();
  IxIy *= 255.0;
  img.fromGrayscale(IxIy);
  pngLoader.storeToFile("IxIy.png",img);

  return 0;
}
