#pragma once

#include <map>
#include <string>
#include <sstream>
#include <math/core.h>
#include <core/Reflection.h>
namespace nspace{
  // RGB is a vector
  typedef Vector3D RGB;
  // YUV is a vector
  typedef Vector3D YUV;

  // represents a color which has a name a rgb value and and alpha value. 
  // static color class contains a map of all collors : a color palette
  class Color : public virtual PropertyChangingObject{
    REFLECTABLE_OBJECT(Color);
  private:
    // the name of the color
    std::string * _colorName;
    // rgb value
    RGB _rgb;
    // alpha
    Real _alpha;
    // static map of all loaded colors
    static std::map<std::string, Color*> & _palette;
    // the unknow color value (default : black)
    static const  Color& unknown;
    static std::string _defaultname;
  public:
    static const Color & UnknownColor(){return unknown;}

    // constructor sets the color to the color represented by name
    // if it does not exists it sets it to the default: black
    Color(const std::string & name);

    // setTo assigns this color the value of the color represented by name (or black if the name was not found)
    void setTo(const std::string & name);
    // sets the color to the color represented by name or if not found : black
    void operator()(const std::string & name);

    // assigns this color the value of the other color
    Color & operator=(const Color  & newValue);
    // assigns this color the value of the color specified by name
    Color & operator=(const std::string & name);


    //not thread safe
    operator const float*()const;
    friend bool operator==(const Color& a, const Color & b);
    friend bool operator!=(const Color & a, const Color & b);

    
    // loads all colors from the color file specified by filename
    static int loadColors(const std::string & filename);
    // returns the color from the palette by name
    static const Color & getColorByName(const std::string & name);

    // returns the current color but with an alpha value of al
    Color alpha(Real al);

    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, const std::string & name);
    Color();
    Color(const RGB & rgb, Real alpha);
    Color(const Vector3D &  col);
    Color(Real r, Real g, Real b, Real alpha=0);
    Color(const Color & color){
      *this = color;
    }


    // normalizes the color (sets all color channels to between zero and one)
    void normalize();
    
    // byte value of the red channel (0-255)
    unsigned char r8bit()const;
    // byte value of the green channel (0-255)
    unsigned char g8bit()const;
    // byte value of the blue channel (0-255)
    unsigned char b8bit()const;
    // byte value of the alpha channel (0-255)
    unsigned char a8bit()const;

    // returns the grayscale value of this color (not implemented yet)
    Real grayscale();

    void setColorName(const std::string& name);
    void setColorNameNull(){_colorName=0;}
    const std::string & colorName()const;

    bool hasName()const;

    // copies the color value into the float array (length 4)
    void colorArray(float * color)const;

    // read/write access to the  color vector
    RGB & rgb();
    // read access to the color vector
    const RGB & rgb()const;    

    // read/write access to the color values
    Real & r();
    Real & g();
    Real & b(); 
    Real & a();

    // read access to the color values
    const Real & r()const;
    const Real & g()const;
    const Real & b()const;
    const Real & a()const;

    Color operator * (Real val)const{
      Color c = *this;
      c.rgb() *= val;
      return c;
    }

    // writes the color to the output stream
    friend std::ostream & operator <<(std::ostream & o, const Color & color);
  };
  TYPEDATAPROVIDER(Color);


  
SERIALIZERS(Color,{
  if(value->hasName())stream << value->colorName();
  else stream << value->r() << " "<<value->g() <<" "<<value->b()<<" " <<value->a();
  return true;
},{
  std::string colorname;
  stream>>colorname;
  auto color = Color::getColorByName(colorname);
  if(&color!=&Color::UnknownColor()){
    *value = color;
    return true;
  }  
  std::stringstream ss(colorname);
  stream>>value->r()>>value->g()>>value->b()>>value->a();
  value->setColorNameNull();
  return true;
});
}