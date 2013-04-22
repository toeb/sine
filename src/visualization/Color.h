/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#pragma once

#include <map>
#include <string>
#include <sstream>
#include <math/core.h>
#include <core.h>
namespace nspace {

  /**
   * \brief RGB is a vector.
   */
  typedef Vector3D RGB;

  /**
   * \brief YUV is a vector.
   */
  typedef Vector3D YUV;

  /**
   * \brief represents a color which has a name a rgb value and and alpha value. static color class
   *        contains a map of all collors : a color palette.
   */
  class Color : public virtual PropertyChangingObject {
    reflect_type(Color);
private:

    /**
     * \brief the name of the color.
     */
    std::string * _colorName;

    /**
     * \brief rgb value.
     */
    RGB _rgb;

    /**
     * \brief alpha.
     */
    Real _alpha;

    /**
     * \brief static map of all loaded colors.
     */
    static std::map<std::string, Color*> & _palette;

    /**
     * \brief the unknown color value (default : black)
     */
    static const Color& unknown;

    /**
     * \brief The defaultname.
     */
    static std::string _defaultname;
public:

  /**
   * \brief Gets the color array as a shared pointer so that its memory is freed when not used anymore.
   *
   * \return  .
   */
  std::shared_ptr<float> colorArray()const{
    std::shared_ptr<float> result(new float[4]);
    colorArray(result.get());
    return result;
  }
    /**
     * \brief Gets the unknown color.
     *
     * \return  .
     */
    static const Color & UnknownColor(){
      return unknown;
    }

    /**
     * \brief constructor sets the color to the color represented by name if it does not exists it sets
     *        it to the default: black.
     *
     * \param name  The name.
     */
    Color(const std::string & name);

    Color(const char * name);

    /**
     * \brief setTo assigns this color the value of the color represented by name (or black if the name
     *        was not found)
     *
     * \param name  The name.
     */
    void setTo(const std::string & name);

    /**
     * \brief sets the color to the color represented by name or if not found : black.
     */
    void operator() (const std::string & name);

    /**
     * \brief assigns this color the value of the other color.
     *
     * \param newValue  The new value.
     *
     * \return  A shallow copy of this object.
     */
    Color & operator=(const Color &newValue);

    /**
     * \brief assigns this color the value of the color specified by name.
     *
     * \param name  The name.
     *
     * \return  A shallow copy of this object.
     */
    Color & operator=(const std::string & name);

    /**
     * \brief not thread safe.
     *
     * \return  .
     */
    operator const float*() const;

    /**
     * \brief Equality operator.
     *
     * \param a The first instance to compare.
     * \param b The second instance to compare.
     *
     * \return  true if the parameters are considered equivalent.
     */
    friend bool operator==(const Color &a, const Color &b);

    /**
     * \brief Inequality operator.
     *
     * \param a The first instance to compare.
     * \param b The second instance to compare.
     *
     * \return  true if the parameters are not considered equivalent.
     */
    friend bool operator!=(const Color &a, const Color &b);

    /**
     * \brief loads all colors from the color file specified by filename.
     *
     * \param filename  Filename of the file.
     *
     * \return  The colors.
     */
    static int loadColors(const std::string & filename);

    /**
     * \brief returns the color from the palette by name.
     *
     * \param name  The name.
     *
     * \return  The color by name.
     */
    static const Color & getColorByName(const std::string & name);

    /**
     * \brief returns the current color but with an alpha value of al.
     *
     * \param al  The al.
     *
     * \return  .
     */
    Color alpha(Real al);

    /**
     * \brief Constructor.
     *
     * \param r     The unsigned char to process.
     * \param g     The unsigned char to process.
     * \param b     The unsigned char to process.
     * \param alpha The alpha.
     * \param name  The name.
     */
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha, const std::string & name);

    /**
     * \brief Default constructor.
     */
    Color();

    /**
     * \brief Constructor.
     *
     * \param rgb   The RGB.
     * \param alpha The alpha.
     */
    Color(const RGB &rgb, Real alpha);

    /**
     * \brief Constructor.
     *
     * \param col The col.
     */
    Color(const Vector3D &col);

    /**
     * \brief Constructor.
     *
     * \param r     The Real to process.
     * \param g     The Real to process.
     * \param b     The Real to process.
     * \param alpha (optional) the alpha.
     */
    Color(Real r, Real g, Real b, Real alpha=0);

    /**
     * \brief Copy constructor.
     *
     * \param color The color.
     */
    Color(const Color &color){
      *this = color;
    }

    /**
     * \brief normalizes the color (sets all color channels to between zero and one)
     */
    void normalize();

    /**
     * \brief byte value of the red channel (0-255)
     *
     * \return  .
     */
    unsigned char r8bit() const;

    /**
     * \brief byte value of the green channel (0-255)
     *
     * \return  .
     */
    unsigned char g8bit() const;

    /**
     * \brief byte value of the blue channel (0-255)
     *
     * \return  .
     */
    unsigned char b8bit() const;

    /**
     * \brief byte value of the alpha channel (0-255)
     *
     * \return  .
     */
    unsigned char a8bit() const;

    /**
     * \brief returns the grayscale value of this color (not implemented yet)
     *
     * \return  .
     */
    Real grayscale();

    /**
     * \brief Sets color name.
     *
     * \param name  The name.
     */
    void setColorName(const std::string& name);

    /**
     * \brief Sets color name null.
     */
    void setColorNameNull(){
      _colorName=0;
    }

    /**
     * \brief Gets the color name.
     *
     * \return  .
     */
    const std::string & colorName() const;

    /**
     * \brief Query if this object has name.
     *
     * \return  true if name, false if not.
     */
    bool hasName() const;

    /**
     * \brief copies the color value into the float array (length 4)
     *
     * \param [in,out]  color If non-null, the color.
     */
    void colorArray(float * color) const;

    /**
     * \brief read/write access to the  color vector.
     *
     * \return  .
     */
    RGB & rgb();

    /**
     * \brief read access to the color vector.
     *
     * \return  .
     */
    const RGB & rgb() const;

    /**
     * \brief read/write access to the color values.
     *
     * \return  .
     */
    Real & r();

    /**
     * \brief Gets the g.
     *
     * \return  .
     */
    Real & g();

    /**
     * \brief Gets the b.
     *
     * \return  .
     */
    Real & b();

    /**
     * \brief Gets a.
     *
     * \return  .
     */
    Real & a();

    /**
     * \brief read access to the color values.
     *
     * \return  .
     */
    const Real & r() const;

    /**
     * \brief Gets the g.
     *
     * \return  .
     */
    const Real & g() const;

    /**
     * \brief Gets the b.
     *
     * \return  .
     */
    const Real & b() const;

    /**
     * \brief Gets a.
     *
     * \return  .
     */
    const Real & a() const;

    /**
     * \brief Multiplication operator.
     *
     * \param val The value.
     *
     * \return  The result of the operation.
     */
    Color operator * (Real val)const {
      Color c = *this;
      c.rgb() *= val;
      return c;
    }

    /**
     * \brief writes the color to the output stream.
     *
     * \param [in,out]  o The std::ostream &amp; to process.
     * \param color       The color.
     *
     * \return  The shifted result.
     */
    friend std::ostream & operator <<(std::ostream & o, const Color &color);
  };

  SERIALIZERS(Color,{
                if(value->hasName()) stream << value->colorName();
                else stream << value->r() << " "<<value->g() <<" "<<value->b()<<" " <<value->a();
                return true;
              },{
                std::string colorname;
                stream>>colorname;
                auto color = Color::getColorByName(colorname);
                if(&color!=&Color::UnknownColor()) {
                  *value = color;
                  return true;
                }
                std::stringstream ss(colorname);
                stream>>value->r()>>value->g()>>value->b()>>value->a();
                value->setColorNameNull();
                return true;
              });
}