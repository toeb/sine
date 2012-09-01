#pragma once
#include <simulation/dynamics/DynamicBody.h>
#include <math/definitions.h>
#include <simulation/dynamics/connection/Connector.h>
namespace nspace{
  class ConnectorFactory{
  private:
  static ConnectorFactory * _instance;
  public:

    /**
     * \brief Gets the instance. (singleton access
     *
     *
     * \return .
     */
    static inline ConnectorFactory & instance(){
      return *_instance;
    }

    /**
     * \brief Creates a with connector wiht  connection point in local coordinates.
     * 				
     * \return null if it fails, else.
     */
    DynamicConnector * createWithLocalConnectionPoint(DynamicBody& body, const Vector3D & p_ocs = Vector3D::Zero());

    /**
     * \brief Creates a connector with connection point in world coordinates.
     * 				
     * \param [in,out] body The body.
     * \param p_wcs         (optional) the wcs.
     *
     * \return null if it fails, else.
     */
    DynamicConnector * createWithWorldConnectionPoint(DynamicBody& body, const Vector3D & p_wcs = Vector3D::Zero());

    /**
     * \brief Frees a  connector. (be sure to not use it anymore afterwards because it might be reused elswhere
     *
     * 
     *
     * \param [in,out] connector If non-null, the connector.
     */
    void freeConnector(DynamicConnector * connector);
  
  };

}