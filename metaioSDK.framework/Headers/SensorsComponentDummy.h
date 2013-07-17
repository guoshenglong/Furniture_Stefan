// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef __AS_SENSORSCOMPONENTWIN32_H__
#define __AS_SENSORSCOMPONENTWIN32_H__

#include <metaioSDK/STLCompatibility.h>
#include <metaioSDK/MobileStructs.h>
#include <metaioSDK/ISensorsComponent.h>

#include <Common/AS_Matrix.h>


namespace metaio
{

/**
 * \brief Interface for sensors (Location, Accelerometer and Compass
 *
 * \anchor ISensorsComponentDummy
 */
class SensorsComponentDummy: virtual public ISensorsComponent
{
public:

	/**
	 * @brief Default constructor.
	 */
	SensorsComponentDummy();

	/**
	 * @brief Destructor.
	 */
	virtual ~SensorsComponentDummy();

	virtual int start(int sensors);
	virtual int stop(int sensors = SENSOR_ALL);
	virtual void setManualLocation(const metaio::LLACoordinate& location);
	virtual void resetManualLocation();
	virtual LLACoordinate getLocation() const;
	virtual Vector3d getGravity() const;
	virtual float getHeading() const;
	virtual SensorValues getSensorValues() const;
	virtual stlcompat::Vector<metaio::UserAcceleration> getUserAcceleration() const METAIOSDK_CPP11_OVERRIDE;

	/**
	* \brief: sets a simulated location
	*
	* \param coordinate LLA Coordinate
	*/
	void setLocation(LLACoordinate& coordinate);

	/**
	* \brief: Sets a simulated gravity vector
	*
	* \param vector the gravity vector
	* \return
	*/
	void setGravity(const Vector3d& vector);

	/**
	* \brief: Sets a simulated device heading (compass direction)
	*
	* \param heading The compass direction
	*/
	void setHeading(float heading);

	/**	Computes the camera pose in the metaio camera coordinate system based on stored
	*	gravity, GPS and compass values relative to the given location of origin. The height
	*	of the handheld device/camera is approxiamted to 1800.0 millimeters.
	*
	*	\param originLat	latitute of the origin location to which the cameras pose will
	*						be computed
	*	\param originLong	longitute of the origin location to which the cameras pose will
	*						be computed
	*	\param outPose		4x4 matrix in which the resulting camera pose will be stored
	*
	*	\return false if no gravity value is stored, otherwise true
	*/
	bool computePoseInMetaioCameraCOS(double originLat, double originLong,
	                                  core::Matrix<float>& outPose);
	
private:

	float m_heading;
	Vector3d m_gravity;
	metaio::LLACoordinate m_location;
	metaio::LLACoordinate m_manualLocation;
	int m_activeSensors;
};

}

#endif
