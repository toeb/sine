#pragma once

#include <Simulation/Core/ISimulationObject.h>
#include <Math/Vector3D.h>
#include <Math/Quaternion.h>
#include <Math/Matrix3x3.h>
#include <Simulation/Kinematics/Position.h>
#include <Simulation/Kinematics/Orientation.h>

namespace IBDS{

/**
 * \brief Coordinate system. 
 * 				A Coordinate system consists of a position in and an orientation
 *
 * \author Tobi
 * \date 24.05.2012
 */
class CoordinateSystem : public virtual ISimulationObject{
private:

  Matrix3x3 * _R;
  Matrix3x3 * _RT;
public:
  Position position;
  Orientation orientation;

  void mirror(CoordinateSystem & original){
    position.mirror(original.position);
    orientation.mirror(original.orientation);
  }
  void unshare(){
    position.unshare();
    orientation.unshare();
  }

  static const CoordinateSystem & identity();

  CoordinateSystem(const Vector3D & p, const Quaternion & q);
  CoordinateSystem();
  ~CoordinateSystem();
  
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