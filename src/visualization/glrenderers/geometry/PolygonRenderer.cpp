#include "PolygonRenderer.h"
#include <visualization/opengl/MiniGL.h>
#include <algorithm>
#include <sstream>
using namespace nspace;
using namespace std;



PolygonRenderer::PolygonRenderer(Polygon & poly):_polygon(poly),
  faceColor("gray"),
  vertexColor("navy"),edgeColor("yellow"),normalColor("blue"){
  drawEdges = true;
  drawHalfEdges = true;
  drawLabels = true;
  drawNormals = true;
  drawFaces = true;
  
}

void PolygonRenderer::render(){
  MiniGL::pushMatrix();
  
  
  Matrix3x3  R;
  _polygon.coordinates().orientation().getMatrix3x3T(R);

  //cout << _polygon.coordinates().position() <<endl;

  MiniGL::drawPoint(_polygon.coordinates().position(),10,MiniGL::blue);

  MiniGL::translate(_polygon.coordinates().position());
  MiniGL::multMatrix(R);



  if(drawVertices){
    for_each(_polygon.vertices().begin(), _polygon.vertices().end(),[this](Vertex * v){
      MiniGL::drawPoint(v->p_ocs,6,vertexColor);
      if(drawLabels){
        Vector3D pnew = v->p_ocs * 1.3;
        stringstream ss;
        ss << "v" <<v->index ;
        MiniGL::drawStrokeText(pnew,0.0007,ss.str().c_str(),ss.str().size(),MiniGL::black);
      }
    });
  }
  if(drawNormals||drawFaces){
    for_each(_polygon.faces().begin(), _polygon.faces().end(),[this](Face * f){
      if(drawNormals){
        Vector3D p;
        f->getCenter(p);
        MiniGL::drawVector(p,p+(0.5*f->n_ocs),2,normalColor);
      }
      if(drawFaces){
        vector<Vertex * > vertices;
        
        f->getVertices(vertices);
        switch(f->vertexCount){
        case 3:
          MiniGL::drawTriangle(
            vertices.at(0)->p_ocs+f->n_ocs*0.001,
            vertices.at(1)->p_ocs+f->n_ocs*0.001,
            vertices.at(2)->p_ocs+f->n_ocs*0.001,
            f->n_ocs,MiniGL::gray);
          break;
        case 4:
          MiniGL::drawQuad(
            vertices.at(0)->p_ocs+f->n_ocs*0.001,
            vertices.at(1)->p_ocs+f->n_ocs*0.001,
            vertices.at(2)->p_ocs+f->n_ocs*0.001,
            vertices.at(3)->p_ocs+f->n_ocs*0.001,
            f->n_ocs,faceColor);
          break;
        }
      }
    });
  }
  if(drawEdges){
    for_each(_polygon.edges().begin(),_polygon.edges().end(),[this](Edge *e){
      MiniGL::drawVector(e->A->p_ocs,e->B->p_ocs,1,MiniGL::yellow);
      if(drawLabels){ 
        Vector3D pnew = (e->A->p_ocs+e->B->p_ocs) * 0.5 * 1.3;
        stringstream ss;
        ss << "e" <<e->index ;
        MiniGL::drawStrokeText(pnew,0.0007,ss.str().c_str(),ss.str().size(),MiniGL::black);
      }
    });
  }


  if(drawHalfEdges){
    for_each(_polygon.halfEdges().begin(), _polygon.halfEdges().end(), [this](const HalfEdge * he){
     Vector3D center;
     if(!he->face)return;
      he->face->getCenter(center);
      Vector3D a = he->edge->A->p_ocs;
      Vector3D b = he->edge->B->p_ocs;
      a = a - 0.1 *( a - center) + 0.03 * he->face->n_ocs;
      b = b - 0.1 *( b - center)+ 0.03 * he->face->n_ocs;

      float width = 1;
      if(he->isFirstHalfEdgeOfFace())width =4;
      if(he->isForwardHalfEdge()){
        MiniGL::drawVector(a,b,width,MiniGL::green);
      }else{
          MiniGL::drawVector(a,b,width,MiniGL::red);
      }
    });
  }
  MiniGL::popMatrix();
}