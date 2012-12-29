#pragma once

#include <simulation.kinematics/CoordinateSystem.h>
#include <simulation.geometry/boundingVolumes/BoundingBox.h>
namespace nspace{
  class Geometry : public ISimulationObject{
  private:
    CoordinateSystem _coordinateSystem;
  public:
    inline CoordinateSystem & coordinates(){return _coordinateSystem;}
    inline const CoordinateSystem & coordinates()const{return _coordinateSystem;}

    /**
    * \brief Project the Geometry on a local axis.
    *
    *
    *
    * \param axis_ocs        The axis ocs.
    * \param [in,out] result The result.
    */
    virtual void projectOCS(const Axis & axis_ocs, Interval & result)const{};

    /**
    * \brief Projects the object on the wordl axis
    *
    *
    * \param axis_wcs        The axis in world coordinates.
    * \param [in,out] result The result.
    */
    virtual void project(const Axis & axis_wcs, Interval & result)const;

    /**
    * \brief Get the bounding box in local coordinates
    *
    *
    * \param [in,out] aabb_ocs The aabb ocs.
    */
    virtual void getBoundingBoxOCS(BoundingBox & aabb_ocs)const;
    virtual void getBoundingBox(BoundingBox & aabb_wcs)const;

    virtual Real calculateBoundingSphereRadius()const;

    virtual Classification classify(const BoundingVolume & volume)const{return Classification::UNCLASSIFIED;}
  };
}