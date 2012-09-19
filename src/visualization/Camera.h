#pragma once

#include <simulation/ISimulationObject.h>
#include <simulation/kinematics/CoordinateSystem.h>
#include <math/definitions.h>



namespace nspace{
 void cartesianToHomogeneousCoordinates(Vector4D & hom3d, const Vector3D & cart3d){};
 void homogeneousToCartesianCoordinates(Vector3D & cart3d, const Vector4D & hom3d){};
 void cartesianToHomogeneousCoordinates(Vector3D & hom2d, const Vector2D & cart2d){};
 void homogeneousToCartesianCoordinates(Vector2D & cart2d, const Vector3D & hom2d){};
 
  class Camera : public virtual ISimulationObject{
  TYPED_OBJECT;
  private:
	Matrix4x4 _worldToCameraCoordinates;
	Matrix3x4 _perspectiveProjectionMatrix;
	Matrix3x3 _cameraToPixelCoordinates;
	
	
	///< The world coordinates of the camera
    CoordinateSystem _coordinates;
    ///< The principal point (in z direction of camera coordinate system)
    Real _principalPoint;
    
    ///< Width of a pixel in m
    Real _pixelWidth;
    ///< Height of the pixel in m
    Real _pixelHeight;
    ///< The width in pixel
    uint _width;
    ///< The height in pixle
    uint _height;

public:
    void transform(Vector2D & p_image, const Vector3D & p_wcs )const;
	void transform(Axis & ray, const Vector2D & image)const;
    void getTransformationMatrix(Matrix4x4 & transformation)const;
	
  };
}