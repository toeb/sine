#include "Color.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using namespace nspace;
map<string, Color*> & Color::_palette = *new map<string, Color*>();
const Color & Color::unknown= *new Color(0,0,0,1,"unknown");


int Color::loadColors(const std::string &filename ){
  ifstream file(filename,ifstream::in);
  if(!file.good())return 0;
  int colorsLoaded = 0;
  while(file.good()){
    int r,g,b;
    std::string name;
    file >> r >>g>>b;

    getline(file,name);

    name = name.substr(1);

    _palette[name]=new Color(r,g,b,255,name);
    colorsLoaded++;
  }  
  return colorsLoaded;
}


const Color & Color::getColorByName(const std::string & name){
  auto color = _palette[name];
  if(color)return *color;
  return unknown;
}


namespace nspace{
  std::ostream & operator <<(std::ostream & o, const Color & color){
    o << "[" << (int)color.r8bit() << ", " << (int)color.g8bit()<<", "<< (int)color.b8bit() << "] " << color.colorName().c_str();  
    return o;
  }

  bool operator==(const Color& a, const Color & b){
      if(a.r()!=b.r())return false;
      if(a.g()!=b.g())return false;
      if(a.b()!=b.b())return false;
      if(a.a()!=b.a())return false;
      return true;
  }
  bool operator!=(const Color & a, const Color & b){
    return !(a==b);
  }
}




Color::Color(const std::string & name){
  setTo(name);
}
void Color::setTo(const std::string & name){
  auto color = getColorByName(name);
  *this = color;
}
void Color::operator()(const std::string & name){
  setTo(name);
}
Color & Color::operator=(const Color  & newValue){
  if(!newValue.hasName()){
    setColorNameNull();
  }else{
    setColorName(newValue.colorName());
  }
  _rgb = newValue.rgb();
  _alpha =newValue.a();
  return *this;
}

Color::operator const float*()const{
  static float color[4];
  colorArray(color);
  return color;
} 



Color Color::alpha(Real al){
  return Color(_rgb,al);
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, const std::string & name):
  _rgb(r/255.0, g/255.0, b/255.0), _alpha(alpha/255.0),_colorName(new std::string(name)){

}
Color::Color():_rgb(0,0,0),_alpha(0),_colorName(0) {

}
Color::Color(const RGB & rgb, Real alpha):_rgb(rgb),_alpha(alpha),_colorName(0){

}
Color::Color(const Vector3D &  col):_alpha(1),_colorName(0),_rgb(col){
  normalize();
}
Color::Color(Real r, Real g, Real b, Real alpha):_rgb(r,g,b),_alpha(alpha),_colorName(0){

}
void Color::normalize(){
  if(_alpha<0)_alpha=0;
  if(_alpha>1)_alpha=1;
  _rgb = _rgb * (1.0/ matrix::maximum(_rgb));
}


unsigned char Color::r8bit()const{
  return (unsigned char)(255*r());
}
unsigned char Color::g8bit()const{
  return (unsigned char)(255*g());
}
unsigned char Color::b8bit()const{
  return (unsigned char)(255*b());
}
unsigned char Color::a8bit()const{
  return (unsigned char)(255*a());
}


Real Color::grayscale(){
  return 0;
}
void Color::colorArray(float * color)const{
  color[0] = (float)r();
  color[1] = (float)g();
  color[2] = (float)b();
  color[3] = (float)a();
}
void Color::setColorName(const std::string& name){
  _colorName = new std::string(name);
}
std::string Color::_defaultname="<NONAME>";
const std::string & Color::colorName()const{
 
  if(_colorName)return *_colorName;
  return _defaultname;
}


bool Color::hasName()const{
  if(_colorName)return true;
  return false;
}

RGB & Color::rgb(){ return _rgb;}
const RGB & Color::rgb()const{return _rgb;}     
Real & Color::a(){return _alpha;}
const Real & Color::a()const{return _alpha;}
Real & Color::r(){return _rgb(0);}  
Real & Color::g(){return _rgb(1);}  
Real & Color::b(){return _rgb(2);}
const  Real & Color::r()const{return _rgb(0);}  
const Real & Color::g()const{return _rgb(1); }  
const Real & Color::b()const{return _rgb(2); }  
