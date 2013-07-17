// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef _AS_SENSORVALUES_H_
#define _AS_SENSORVALUES_H_

#include <metaioSDK/MobileStructs.h>
#include <metaioSDK/Rotation.h>
#include <metaioSDK/STLCompatibility.h>

namespace metaio
{

/** SensorValues combines a snapshot of different sensor parameters
 */
struct SensorValues
{

	LLACoordinate location;							///< Device location.			Needed: SENSOR_LOCATION
	Vector3d gravity;								///< Normalized gravity vector.	Needed: SENSOR_GRAVITY
	double gravityTimestamp;						///< timestamp in ms

	float heading;									///< Heading in degrees, 0=North, 90=East, 180=South	Needed: SENSOR_HEADING
	double headingTimestamp;						///< timestamp in ms

	metaio::Rotation attitude;						///< device attitude based on running sensors	Needed: SENSOR_ATTITUDE
	double attitudeTimestamp;						///< timestamp in ms

	bool	deviceIsMoving;							///< Indicates if device is moving.				Needed: SENSOR_DEVICE_MOVEMENT

	stlcompat::Vector<metaio::UserAcceleration>	userAcceleration;		///< measured user acceleration with timestamps. Needed: SENSOR_USER_ACCELERATION

	/** SensorValues combines a snapshot of different sensor parameters
	 */
	SensorValues(): gravityTimestamp(0.0), heading(-1.0), headingTimestamp(0.0), attitudeTimestamp(0.0), deviceIsMoving(false)
	{
	}

};
}


#endif // _AS_SENSORVALUES_H_
