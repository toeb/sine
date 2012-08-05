#include <math/definitions.h>
#include <map>
#include <string>
#pragma once


namespace nspace{
  typedef Vector3D RGB;
  typedef Vector3D YUV;
  class Color{
  private:
    std::string * _colorName;
    RGB _rgb;
    Real _alpha;
    static std::map<std::string, Color*> & _palette;
  public:
    Color(const std::string & name){
      setTo(name);
    }
    void setTo(const std::string & name){
      auto color = getColorByName(name);
      *this = color;
    }
    void operator()(const std::string & name){
      setTo(name);
    }
    Color & operator=(const Color  & newValue){
      setColorName(newValue.colorName());
      _rgb = newValue.rgb();
      _alpha =newValue.a();
      return *this;
    }

    static const  Color& unknown;
    //not thread safe
    operator const float*()const{
      static float color[4];
      colorArray(color);
      return color;
    } 
    friend bool operator==(const Color& a, const Color & b){
      if(&a==&b)return true;
      return false;
    }
    friend bool operator!=(const Color & a, const Color & b){
      return !(a==b);
    }
    static int loadColors(const std::string & filename);
    static const Color & getColorByName(const std::string & name){
      auto color = _palette[name];
      if(color)return *color;
      return unknown;
    }
    
    Color alpha(Real al){
      return Color(_rgb,al);
    }

    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, const std::string & name):
    _rgb(r/255.0, g/255.0, b/255.0), _alpha(alpha/255.0),_colorName(new std::string(name)){

    }
    Color():_rgb(0,0,0),_alpha(0),_colorName(0) {

    }
    Color(const RGB & rgb, Real alpha):_rgb(rgb),_alpha(alpha),_colorName(0){
         
    }
    Color(const Vector3D &  col):_alpha(1),_colorName(0),_rgb(col){
      normalize();
    }
    Color(Real r, Real g, Real b, Real alpha=0):_rgb(r,g,b),_alpha(alpha),_colorName(0){
      
    }
    void normalize(){
      if(_alpha<0)_alpha=0;
      if(_alpha>1)_alpha=1;
      _rgb = _rgb * (1.0/ _rgb.maxValue());
    }


    unsigned char r8bit()const{
      return (unsigned char)(255*r());
    }
    unsigned char g8bit()const{
      return (unsigned char)(255*g());
    }
    unsigned char b8bit()const{
      return (unsigned char)(255*b());
    }
    unsigned char a8bit()const{
      return (unsigned char)(255*a());
    }


    Real grayscale(){
      return 0;
    }
    void colorArray(float * color)const{
      color[0] = (float)r();
      color[1] = (float)g();
      color[2] = (float)b();
      color[3] = (float)a();
    }
    void setColorName(const std::string& name){
      _colorName = new std::string(name);
    }
    const std::string & colorName()const{
      static std::string defaultName ="<NONAME>";
      if(_colorName)return *_colorName;
      return defaultName;
    }
    RGB & rgb(){ return _rgb;}
    const RGB & rgb()const{return _rgb;}     
    Real & a(){return _alpha;}
    const Real & a()const{return _alpha;}
    Real & r(){return _rgb(0);}  
    Real & g(){return _rgb(1);}  
    Real & b(){return _rgb(2);}
    const  Real & r()const{return _rgb(0);}  
    const Real & g()const{return _rgb(1); }  
    const Real & b()const{return _rgb(2); }  
    friend std::ostream & operator <<(std::ostream & o, const Color & color);
  };
}