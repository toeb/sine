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
#include <math.matrix.h>
#include <utility.reader.mtl.h>
#include <utility.reader.mesh.h>
namespace nspace {


/**
 * \brief Mesh Reader for Wavefront obj files.
 *        specification for obj file format: http://www.martinreddy.net/gfx/3d/OBJ.spec
 */
  class ObjReader : public MeshReader {
    REFLECTABLE_OBJECT(ObjReader);
    SUBCLASSOF(MeshReader);

    typedef std::function<void (std::istream & )> Parser;
    typedef nspace::Vector3D Vector3D;
    typedef nspace::Vector2D TextureVector;
    typedef MeshFace Face;
    typedef MeshElement::Index Index;
    
    std::map<std::string, Parser> parsers;
    std::vector<std::string> comments;
   
    Set<std::string> groups;
    Set<std::string> objects;
    Set<std::string> materials;
    
    Set<Index> currentGroups;
    Index currentMaterial;
    Index currentObject;
    Index currentSmoothingGroup;

public:
    ObjReader();
private:
    void parseVertex(std::istream & stream);
    void parseTextureCoordinates(std::istream & stream);
    void parseNormal(std::istream & stream);
    void parseFace(std::istream & stream);
    void parseComment(std::istream & stream);
    void parseGroup(std::istream& stream);
    void parseObject(std::istream & stream);
    void parseMaterialLibrary(std::istream & stream);
    void parseUseMaterial(std::istream &stream);
    void parseSmoothingGroup(std::istream &stream);
protected:
    bool readMesh(IMeshBuilder & meshBuilder);
  };

}