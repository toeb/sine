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
#include <core.collection.h>

#include <visualization/Renderer.h>
#include <visualization/Material.h>
#include <visualization/Color.h>

#include <simulation.geometry/primitives/Sphere.h>

namespace nspace {

/**
 * \brief Sphere renderer.   SphereRenderer is a Set of spheres. every sphere added will be rendered in the material.
 */
  class SphereRenderer : public Renderer, virtual PropertyChangingObject, public Set<Sphere*>, public virtual NamedObject{
    REFLECTABLE_OBJECT(SphereRenderer);
    SUBCLASSOF(Renderer);

    /**
     * \brief Property Material - the material the spheres are rendered in
     */
    PROPERTY(Material, Material){}

    /**
     * \brief Color Property - the creates sets copies the Materialsproperty changing its color
     *
     * \param parameter1  The first parameter.
     * \param parameter2  The second parameter.
     */
    PROPERTY(Color, Color){
      setMaterial(Material(newvalue));
    }

    /**
     * \brief LatitudeSegments property. specifies how many latitudal segments the sphere is to be rendered with
     *
     */
    PROPERTY(int, LatitudeSegments){}

    /**
     * \brief LatitudeSegments property. specifies how many longitudal segments the sphere is to be rendered with
     *
     */
    PROPERTY(int, LongitudeSegments){}

public:

    /**
     * \brief Default constructor.
     */
    SphereRenderer();

    /**
     * \brief Renders this object.
     */
    void render();
  }; //SphereMesh
}
