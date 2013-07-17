// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef __AS_SENSORSCOMPONENTIOS_H__
#define __AS_SENSORSCOMPONENTIOS_H__

#include <metaioSDK/MobileStructs.h>
#include <metaioSDK/ISensorsComponent.h>
#import <CoreMotion/CoreMotion.h>
#import <CoreLocation/CoreLocation.h>

#include <map>

#define kASLocationServicesDeactivatedNotification @"ASLocationServicesDeactivatedNotification"
#define kASHeadingNotAvailableNotification @"ASHeadingNotAvailableNotification"


/** Actual Objective-C implementation of the SensorsComponent
 */
@interface SensorsComponentImpl : NSObject <CLLocationManagerDelegate>
{
	NSOperationQueue *		m_motionQueue;			//!< Pointer to a motion queue that processes the user acceleration readings
	int						m_activeSensors;		//!< Which sensors are currenlty running?
	metaio::stlcompat::Vector<metaio::UserAcceleration> m_userAccelerationSamples;	//!< Samples of the user acceleration <timestamp, acceleration>
	CLLocation*			overwriteLocation;		//!< Can be used to overwrite the real location
	
	metaio::SensorValues	m_sensorValues;		//!< Holds the current state of all sensor values
	
	float					m_deviceMovementStatus;	//!< Low-pass filter for devicemovement
}

@property (nonatomic, retain) CMMotionManager*		motionManager;			//!< Pointer to our motionManager instance (for SENSOR_ACCELEROMETER)
@property (nonatomic, retain) CLLocationManager*	locationManager;		//!< Pointer to our location manager instance
@property (nonatomic, retain) CLLocation*			currentLocation;		//!< Contains the current location
@property (assign)		float						currentCompassAngle;	//!< The current compass angle
@property (nonatomic, retain) CLLocation*			lastRealLocation;       //!< If the location overwrite is active, here we can access the last real location



@property (assign)	BOOL shouldDisplayHeadingCalibration;		//!< Indicates of the heading calibration message should be displayed
@property (assign)  BOOL locationIsDisabled;					//!< Property you can set to make sure no location objects are accessed
@property (assign)  BOOL ignoreResetLocationOverwrite;			//!< If this is set, resetLocationOverride calls will be ignored
@property (assign)  CLLocationDistance				locationDistanceFilter;	//!< Distancefilter
@property (nonatomic, retain)	NSString*			purposeLocation;	//!< If set, this will indicate the purpose of the location usage

@property (nonatomic, assign)	NSObject<CLLocationManagerDelegate>*		locationManagerDelegate;	//!< You can set this delegate to be also informed about changes




/** Start the given sensors
 *
 * \param sensors Sensors to start (see ESENSOR)
 * \return sensors that are actually started
 * \sa ESENSOR, stop
 */
- (int) start: (int) sensors;

/** Stop the given sensors
 *
 * \param sensors Sensors to stop (default is all sensors, i.e. SENSOR_ALL)
 * \return sensors that are actually stopped
 * \sa start
 */
- (int) stop: (int) sensors;

/** Overwrite the current location with a predefined one
 *
 * \param location the location to overwrite with. pass nil to deactivate
 */
- (void) setManualLocation:(CLLocation* ) location;


/** Get user acceleration samples with timestamps
 *
 * \return	User acceleration samples in a map <timestamp, acceleration>.
 * \note	We return a copy, not a reference, to make sure it is not modified!
 */
- (metaio::stlcompat::Vector<metaio::UserAcceleration>) getUserAcceleration;


/** Get the current gravity vector
 * \return gravity vector
 */
- (metaio::Vector3d) getGravity;


/** Return the current Sensor values structure
 * \return the current sensor values
 */
- (metaio::SensorValues) getSensorValues;


/** Return the current location.
 * This will return the manual location if set, otherwise the real one
 * \return location
 */
- (metaio::LLACoordinate) getLocation;

@end

namespace metaio
{

	/** Interface for sensors (Location, Accelerometer and Compass) on iOS
	 *
	 * \anchor ISensorsComponentIOS
	 */
	class SensorsComponentIOS: virtual public ISensorsComponent
	{
	public:

		/** Default constructor.
		 */
		SensorsComponentIOS();

		/** Destructor.
		 */
		~SensorsComponentIOS();
		
        virtual int start(int sensors);
        virtual int stop(int sensors = SENSOR_ALL);
        virtual void setManualLocation(const metaio::LLACoordinate& location);
        virtual void resetManualLocation();
        virtual LLACoordinate getLocation() const;
        virtual Vector3d getGravity() const;
        virtual float getHeading() const;
        virtual SensorValues getSensorValues() const;
       	virtual stlcompat::Vector<metaio::UserAcceleration> getUserAcceleration() const;
		
		/** Return a pointer to the objective C object that you can work with
		 * \return pointer to obj-c object
		 */
		SensorsComponentImpl* getSensorComponentImpl();
		
		
		/** Setter for the distance filter.
		 */
		void setDistanceFilter(CLLocationDistance distanceFilter);

	

	private:
		SensorsComponentImpl*		m_pSensorsComponent;	//!<	Objective-C object that contains all code
    };
	
}

#endif
