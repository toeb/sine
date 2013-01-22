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
#include <utility.reader.mesh.h>
#include <memory>
#include <simulation.geometry/mesh/basic/BasicMesh.h>
namespace nspace {

  /**
   * \brief Basic mesh builder.  Creates a basic mesh from trough the IMeshBuilder interface
   */
  struct BasicMeshBuilder : public IMeshBuilder {
    std::shared_ptr<BasicMesh> mesh;
    std::queue<Vector3D> vertices;
    std::queue<FaceType> faces;

    void position(Vector3D && position);
    void face(FaceType && face);
    void end();
  };
}