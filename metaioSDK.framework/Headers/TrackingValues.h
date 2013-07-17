// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef _AS_TRACKINGVALUES_H_
#define _AS_TRACKINGVALUES_H_

#include <metaioSDK/MobileStructs.h>
#include <metaioSDK/Rotation.h>
#include <metaioSDK/STLCompatibility.h>

namespace metaio
{
/**
 * Tracking states
 */
enum ETRACKING_STATE
{
	ETS_UNKNOWN,			///< Tracking state is unknown
    ETS_NOT_TRACKING,		///< Not tracking
	ETS_TRACKING,			///< Tracking
	ETS_LOST,				///< Target lost
	ETS_FOUND,				///< Target found
	ETS_EXTRAPOLATED,		///< Tracking by extrapolating
	ETS_INITIALIZED			///< The tracking has just been loaded
};


/** 
 * This class encapsulates complete tracking state of the system.
 */
class METAIO_DLL_API TrackingValues
{
public:

	/**
	 * Create with default values
	 */
	TrackingValues();

	/**
	 * Destructor
	 */
	~TrackingValues();

	/** 
	 * Create TrackingValues with given translation, rotation, quality,
	 * coordinate system ID and name.
	 *
	 * \param tx Translation in x direction
	 * \param ty Translation in y direction
	 * \param tz Translation in z direction
	 * \param q1 First component of the rotation quaternion
	 * \param q2 Second component of the rotation quaternion
	 * \param q3 Third component of the rotation quaternion
	 * \param q4 Fourth component of the rotation quaternion
	 * \param quality Value between 0 and 1 defining the tracking
	 *	quality. (1=tracking, 0=not tracking)
	 * \param cosID the coordinate system ID
	 * \param cosName Name of the coordinate system.
	 */
	TrackingValues(float tx, float ty, float tz, float q1, float q2,
	               float q3, float q4, float quality, int cosID, const stlcompat::String& cosName);


	ETRACKING_STATE			state;			///< The state of the tracking values

	Vector3d                translation;	///< Translation component of the pose
	Rotation                rotation;		///< Rotation component of the pose
	LLACoordinate           llaCoordinate;	///< Set if the sensors provides a geo position

	/** 
	 * Quality of the tracking values.
	 * Value between 0 and 1 defining the tracking quality.
	 * A higher value means better tracking results. More specifically:
	 * - 1 means the system is tracking perfectly.
	 * - 0 means that we are not tracking at all.
	 *
	 * In the case of marker-based tracking, the quality values behave a bit
	 * different:
	 * - If tracking is unsuccessful, the quality will be 0.
	 * - If tracking results are coming from a fuser, the quality will be 0.5.
	 * - If the system is tracking successfully, the quality will be between
	 *   0.5 and 1.
	 */
	float				quality;

	float				timeElapsed;				///< Time elapsed (in ms) since last state change of the tracking system
	int					coordinateSystemID;			///< The ID of the coordinate system
	stlcompat::String	cosName;                    ///< The name of the coordinate system (configured via Connection/COS/Name)
	stlcompat::String	additionalValues;           ///< Extra space for information provided by a sensor that cannot be expressed with translation and rotation properly.
	stlcompat::String	sensor;                     ///< The sensor that provided the values

	/** 
	 * Determine if a state means that its tracking or not
	 * \return true, if the current state represents a state, that is tracking
	 */
	bool isTrackingState() const;

	/**
	 * Get inverse translation based on current pose
	 * \return Inverse translation vector
	 */
	metaio::Vector3d getInverseTranslation() const;

	/** 
	 * Determine if a state means that its tracking or not
	 *
	 * \param state the state to check for
	 * \return true, if the state represents a state, that is tracking
	 */
	static inline bool isTrackingState(ETRACKING_STATE state)
	{
		return (state == ETS_FOUND || state == ETS_TRACKING || state == ETS_EXTRAPOLATED);
	}
};
}


#endif
