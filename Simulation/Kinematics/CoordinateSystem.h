#pragma once

#include <Simulation/Core/ISimulationObject.h>
#include <Math/Vector3D.h>
#include <Math/Quaternion.h>
#include <Math/Matrix3x3.h>

namespace IBDS{

/**
 * \brief Coordinate system. 
 * 				A Coordinate system consists of a position in and an orientation
 *
 * \author Tobi
 * \date 24.05.2012
 */
class CoordinateSystem : public virtual ISimulationObject{
protected:
  Vector3D _p;
  Quaternion _orientation;
  Matrix3x3 * _R;
  Matrix3x3 * _RT;
public:
  static const CoordinateSystem & identity();
  CoordinateSystem(const Vector3D & p, const Quaternion & q);
  CoordinateSystem();
  ~CoordinateSystem();
  
  const Vector3D & getPosition()const;
  void setPosition(const Vector3D & p_wcs);
  Vector3D & position();

  const Quaternion & getOrientation()const;
  Quaternion & orientation();

  /**
   * \brief Sets an orientation.
   *    orientation is normalized after setting
   * \param orientation The orientation.
   */
  void setOrientation(const Quaternion & orientation);
  
  void calculateRotationMatrices();

  const Matrix3x3 * getCachedRotationMatrix()const;
  const Matrix3x3 * getCachedTransposedRotationMatrix()const;
  
  const Matrix3x3 & getRotationMatrix();
  const Matrix3x3 & getTransposedRotationMatrix();

  
  void toObjectCoordinates(const Vector3D & p_wcs, Vector3D & p_ocs);
  void fromObjectCoordinates(const Vector3D & p_ocs, Vector3D & p_wcs);

  void toObjectCoordinates(const Vector3D & p_wcs, Vector3D & p_ocs)const;
  void fromObjectCoordinates(const Vector3D & p_ocs, Vector3D & p_wcs)const;

  void toObjectCoordinatesCached(const Vector3D & p_wcs, Vector3D & p_ocs)const;
  void fromObjectCoordinatesCached(const Vector3D & p_ocs, Vector3D & p_wcs)const;

  
  

};
}