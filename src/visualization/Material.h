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
#include <config.h>
#include <visualization/Color.h>
#include <core.h>

namespace nspace {

  
    // illumination model as defined in http://web.archive.org/web/20080813073052/http://local.wasp.uwa.edu.au/~pbourke/dataformats/mtl/
  enum IlluminationModel{
    ColorOnly=0	,//	Color on and Ambient off
    ColorAmbient = 1	,//	Color on and Ambient on
    Highlight = 2	,//	Highlight on
    ReflectionRayTrace = 3	,//	Reflection on and Ray trace on
    GlassRayTraceOn=4	,//	Transparency: Glass on
    //  Reflection: Ray trace on
    FresnelRayTrace=5	,//	Reflection: Fresnel on and Ray trace on
    RefractionRayTrace=6	,//	Transparency: Refraction on
    //  Reflection: Fresnel off and Ray trace on
    RefractionFresnelRayTrace=7	,//	Transparency: Refraction on
    //  Reflection: Fresnel on and Ray trace on
    Reflection=8	,//	Reflection on and Ray trace off
    Glass=9	,//	Transparency: Glass on
    //  Reflection: Ray trace off
    Shadows=10	,//	Casts shadows onto invisible surfaces
  };
  META(IlluminationModel);
  /**
  * \brief Material.  Represents a visual material containing Properties the typical (OpenGL Material)
  */
  class Material : public virtual PropertyChangingObject {
    REFLECTABLE_OBJECT(Material);
  public:
  
    /**
    * \brief Ambient Color property.
    */
    PROPERTY(Color,Ambient){}
    REFERENCES(public, Color, Ambient);

    PROPERTY(IlluminationModel, Model){}
    REFERENCES(public,IlluminationModel,Model);

    /**
    * \brief Diffuse Color property.
    */
    PROPERTY(Color,Diffuse){}
    REFERENCES(public, Color, Diffuse);
    /**
    * \brief Specular Color property.
    */
    PROPERTY(Color,Specular){}
    REFERENCES(public, Color, Specular);
    /**
    * \brief Emission Color property.
    */
    PROPERTY(Color,Emission){}
    REFERENCES(public, Color, Emission);


    /**
    * \brief Shininess property.
    */
    PROPERTY(Real,Shininess){}
    REFERENCES(public, Real, Shininess);

    PROPERTY(std::string, MaterialName){}
    REFERENCES(public, std::string, MaterialName);
  private:

    /**
    * \brief The palette. contains a list of Materials
    */
    static std::map<std::string, Material*> & _palette;
  public:

    /**
    * \brief Sets the material to the Materials identified by name in the palette.
    *
    * \param name  The name.
    */
    void setTo(const std::string & name);

    /**
    * \brief The unknown material.
    */
    static const Material& unknown;

    /**
     * \brief Sets the transparency for this material.
     *
     * \param value The value.
     */
    void setTransparency(Real value){
      //@TODO check if this is the correct way to set transparency
      Diffuse().a()=value;
      Specular().a()=value;
      Ambient().a()=value;
    }

      

    /**
    * \brief Loads the materials from a file and stores them in the palette.
    *
    * \param filename  Filename of the file.
    *
    * \return  The materials.
    */
    static int loadMaterials(const std::string & filename);

    /**
    * \brief Gets material by name.
    *
    * \param name  The name.
    *
    * \return  The material by name.
    */
    static const Material & getMaterialByName(const std::string & name);

    /**
    * \brief Default constructor.
    */
    Material();

    /**
    * \brief Constructs a material from the specified color
    *
    * \param color The color.
    */
    Material(const Color &color);

    /**
    * \brief Constructs the material from the passed parameters
    *
    * \param name      The name.
    * \param ambient   The ambient.
    * \param diffuse   The diffuse.
    * \param specular  The specular.
    * \param emission  The emission.
    * \param shininess The shininess.
    */
    Material(const std::string &name, const Color &ambient, const Color &diffuse, const Color &specular, const Color &emission, Real shininess);

    /**
    * \brief Constructs the material by searching in the palette for a material known by name
    *
    * \param name  The name.
    */
    Material(const std::string & name);

    Material(const char * name);

    Material(const Material &material);
    Material & operator =(const Material &material);
  };
}
