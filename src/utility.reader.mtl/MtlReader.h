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

#include <utility.reader.h>

namespace nspace {

  class Color;
  class Material;

/**
 * \brief Material reader (MTL format).
 *       specification of mtl:  http://web.archive.org/web/20080813073052/http://local.wasp.uwa.edu.au/~pbourke/dataformats/mtl/
 */
  class MtlReader : public Reader {
    REFLECTABLE_OBJECT(MtlReader);
    SUBCLASSOF(Reader);

    /**
     * \brief resulting vector of materials
     *
     */
    std::vector<std::shared_ptr<Material> > _materials;

    /**
     * \brief map of parsers for line beginnings.
     */
    std::map<std::string, std::function<void (std::istream & stream)> > parsers;

    /**
     * \brief The current material being read.
     */
    std::shared_ptr<Material> currentMaterial;
private:
    void parseNewMaterial(std::istream &stream);
    Color parseColor(std::istream & stream);
    void parseSpecular(std::istream & stream);
    void parseDiffuse(std::istream & stream);
    void parseAmbient(std::istream & stream);
    void parseIlluminationModel(std::istream & stream);
    void parseShininess(std::istream & stream);
    void parseSharpness(std::istream  &stream);
    void parseRefractionIndex(std::istream & stream);
    void parseDissolve(std::istream & stream);
    void parseTransmissionFilter(std::istream & stream);

public:

    /**
     * \brief Default constructor.
     */
    MtlReader();

    /**
     * \brief Gets the materials that were read.
     *
     * \return  the reference to the material pointer vector.
     */
    const std::vector<std::shared_ptr<Material> > & Materials();
protected:

    /**
     * \brief Executes the read operation.
     *
     * \return  true if it succeeds, false if it fails.
     */
    bool doRead();
  };
}