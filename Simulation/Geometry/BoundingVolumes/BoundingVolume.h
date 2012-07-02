#pragma once
#include <Simulation/Kinematics/CoordinateSystem.h>
namespace IBDS{
  
enum Classification{
  UNCLASSIFIED=0,
  INSIDE=1,
  OUTSIDE=2,
  BOTH=3
};

class BoundingVolume{
private:
  bool _colliding;
  bool _updated;
  const CoordinateSystem & _coordinateSystem;
public:
  BoundingVolume(const CoordinateSystem & parentObject);

  bool isColliding()const;
  void setColliding(bool val);
  void update();
  void reset();
  bool isUpToDate()const;
  const CoordinateSystem & parentCoordinates()const;
protected:
  virtual void updateBoundingVolume()=0;
};


class BoundingVolumeFactory{
public:

  /**
   * \brief Creates a BoundingVolume that includes min and max and all points in between.
   *
   * \param min          The minimum point.
   * \param max          The maximum point.
   * \param parentObject The parent object.
   *
   * \return null if it fails, else.
   */
  virtual BoundingVolume * create(const Vector3D & min, const Vector3D & max,const CoordinateSystem & parentObject)=0;
};

}