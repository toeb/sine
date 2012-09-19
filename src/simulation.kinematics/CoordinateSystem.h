#pragma once

#include <simulation/ISimulationObject.h>
#include <math/definitions.h>
#include <simulation.kinematics/Position.h>
#include <simulation.kinematics/Orientation.h>

namespace nspace{

/**
 * \brief Coordinate system. 
 * 				A Coordinate system consists of a position in and an orientation
 * 				
 * 				it is shareable
 *
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


  
  friend std::ostream & operator << (std::ostream & o, const CoordinateSystem & coordinates);

  void fromObjectCoordinates(const CoordinateSystem & coords_ocs,CoordinateSystem & result)const;
  void toObjectCoordinates(const CoordinateSystem & coords_wcs,CoordinateSystem & result)const;

};
}