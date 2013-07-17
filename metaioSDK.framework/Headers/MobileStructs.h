// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef _AS_TYPEDEFS_H_
#define _AS_TYPEDEFS_H_

#if !defined(METAIO_DLL_API)
#if !defined(AS_USE_METAIOSDKDLL)
	#define METAIO_DLL_API	// we don't have a dll file
#else
#ifdef AS_METAIOSDKDLL_EXPORTS
	#ifdef AS_ANDROID
		#define METAIO_DLL_API __attribute__ ((visibility("default")))
	#else
		#define METAIO_DLL_API __declspec(dllexport)
	#endif
#else
	#define METAIO_DLL_API __declspec(dllimport)
#endif
#endif
#endif

#include <metaioSDK/ColorFormat.h>
#include <metaioSDK/STLCompatibility.h> // for METAIO_DLL_API and stlcompat types

#include <cassert>
#include <math.h>

namespace metaio
{
/**
 * Screen rotations
 *
 * This enumeration is used to inform Mobile SDK about
 * camera image rotation needed to compensate for current screen
 * rotation w.r.t. it's natural rotation.
 *
 * For example if the screen is naturally set to Landscape orientation,
 * and device is rotated to Portrait inverted orientation, then an angle
 * of 90 degrees is required to compensate this.
 */
enum METAIO_DLL_API ESCREEN_ROTATION
{
	/// No rotation, natural screen orientation (Landscape (Left) by default)
	ESCREEN_ROTATION_0,

	/// 90 degrees, by default Portrait Inverted orientation
	ESCREEN_ROTATION_90,

	/// 180 degrees, by default Landscape Inverted (Right) orientation
	ESCREEN_ROTATION_180,

	/// 270 degrees, by default Portrait orientation
	ESCREEN_ROTATION_270,
};

/**
 * Structure that defines a 2D float vector 
 */
struct METAIO_DLL_API Vector2d
{
	float x;	///< x component of the vector
	float y;	///< y component of the vector

	/**
	 * Create Vector2d and initializes all components to 0
	 */
	Vector2d();

	/**
	 * Create Vector2d and intialize all components to the given scalar value
	 * \param _n x and y components of the vector
	 */
	explicit Vector2d(float _n);

	/**
	 * Create Vector2d with given values
	 * \param _x x component of the vector
	 * \param _y y component of the vector
	 */
	Vector2d(float _x, float _y);

	/** 
	 * Coefficient-wise sum of two vectors
	 *
	 * \param[in] rhs Vector to be added
	 * \return Coefficient-wise sum of the vectors
	 */
	Vector2d operator +(const Vector2d& rhs) const;

	/** 
	 * Coefficient-wise difference of two vectors
	 *
	 * \param[in] rhs Vector to be subtracted
	 * \return Coefficient-wise difference of the vectors
	 */
	Vector2d operator -(const Vector2d& rhs) const;

	/** 
	 * Coefficient-wise product of two vectors
	 *
	 * \param[in] rhs Vector to be multiplied
	 * \return Coefficient-wise product of the vectors
	 */
	Vector2d cwiseProduct(const Vector2d& rhs) const;

	/** 
	 * Coefficient-wise quotient of two vectors
	 *
	 * \param[in] rhs Denominator Vector
	 * \return Coefficient-wise quotient of the vectors
	 */
	Vector2d cwiseQuotient(const Vector2d& rhs) const;

	/** 
	 * Scale the vector by a scalar
	 *
	 * \param[in] rhs Scalar which scales the vector
	 * \return Scaled vector
	 */
	Vector2d operator *(float rhs) const;

	/** 
	 * In-place coefficient-wise sum of two vectors
	 *
	 * \param[in] rhs Vector to be added
	 * \return Resultant vector (Reference to *this)
	 */
	Vector2d& operator +=(const Vector2d& rhs);

	/** 
	 * In-place coefficient-wise difference of two vectors
	 *
	 * \param[in] rhs Vector to be subtracted
	 * \return Resultant vector (Reference to *this)
	 */
	Vector2d& operator -=(const Vector2d& rhs);

	/** 
	 * Scale the vector in-place by a given scalar
	 *
	 * \param[in] rhs Scalar which scales the vector
	 * \return Resultant vector (Reference to *this)
	 */
	Vector2d& operator *=(float rhs);

	/** 
	 * In-place coefficient-wise quotient of two vectors
	 *
	 * \param[in] rhs Denominator Vector
	 * \return Resultant vector (Reference to *this)
	 */
	Vector2d& operator /=(float rhs);

	/** 
	 * Dot-product (or scalar-product or inner-product) of the two vectors
	 *
	 * \param[in] rhs Second vector for the dot product
	 * \return Dot product of the two vectors
	 */
	float dot(const Vector2d& rhs) const;

	/** 
	 * Euclidean-norm (L2-norm) of this vector
	 *
	 * \return Euclidean norm
	 * \sa squaredNorm
	 */
	float norm() const;

	/** 
	 * Squared-norm of this vector
	 *
	 * \return Squared norm
	 * \sa norm
	 */
	float squaredNorm() const;

	/**
	* Determine if the vector is null
	* \return true if null vector, else false
	*/
	bool isNull() const;

	/** 
	 * Check if two vectors are coefficient-wise equal
	 *
	 * \param other Vector2d to compare with
	 * \return true if vectors are coefficient-wise equal, otherwise false.
	 */
	bool operator ==(const Vector2d& other) const;

	/** 
	 * Check if two vectors differ in at least one coefficient
	 *
	 * \param other Vector2d to compare with
	 * \return true if vectors are unequal, otherwise false.
	 */
	bool operator !=(const Vector2d& other) const;

	/** 
	 * Check if a vector is lexicographically smaller than another vector
	 *
	 * \param other Vector2d to compare with
	 * \return true if this vector is smaller than the other, otherwise false.
	 */
	bool operator <(const Vector2d& other) const;
};

/**
 * Structure that defines an integer 2D vector 
 */
struct METAIO_DLL_API Vector2di
{
	int x;	///< x component of the vector
	int y;	///< y component of the vector

	/**
	 * Create Vector2di and initializes all components to 0
	 */
	Vector2di();

	/**
	 * Create Vector2di and initializes all components to the given scalar value
	 * \param _n x and y components of the vector
	 */
	Vector2di(int _n);

	/**
	 * Create Vector2di and initializes all components to the given values
	 * \param _x x component of the vector
	 * \param _y y component of the vector
	 */
	Vector2di(int _x, int _y);

	/**
	 * Determine if the vector is null
	 * \return true if null vector, else false
	 */
	bool isNull() const;

};

/**
 * Structure that defines a 3D float vector 
 */
struct METAIO_DLL_API Vector3d
{
	float x;	///< x component of the vector
	float y;	///< y component of the vector
	float z;	///< z component of the vector

	/**
	 * Create Vector3d and initializes all components to 0
	 */
	Vector3d();

	/**
	 * Create Vector3d and initializes all components to the given scalar value
	 * \param _n x, y and z components of the vector
	 */
	Vector3d(float _n);

	/**
	 * Create Vector3d and initializes all components to the given values
	 * \param _x x component of the vector
	 * \param _y y component of the vector
	 * \param _z z component of the vector
	 */
	Vector3d(float _x, float _y, float _z);

	/** 
	 * Sets all coefficients to 0
	 *
	 * \post norm() == 0
	 */
	void setZero();

	/** 
	 * Negative of this vector
	 *
	 * \return Resultant vector
	 */
	Vector3d operator -() const;

	/** 
	 * Add two vectors coefficient-wise
	 *
	 * \param[in] rhs Vector to add
	 * \return Resultant vector after addition
	 */
	Vector3d operator +(const Vector3d& rhs) const;

	/** 
	 * Subtracts two vectors coefficient-wise
	 *
	 * \param[in] rhs Vector to subtract
	 * \return Resultant vector after subtraction
	 */
	Vector3d operator -(const Vector3d& rhs) const;

	/** 
	 * Multiply the given scalar with the vector
	 *
	 * \param[in] rhs Scalar to multiply
	 * \return Resultant vector after multiplication
	 */
	Vector3d operator *(float rhs) const;

	/** 
	 * Divide the vector by a scalar
	 *
	 * \param[in] rhs Denominator scalar value
	 * \return Resultant vector after division
	 * \pre rhs != 0
	 */
	Vector3d operator /(float rhs) const;

	/** 
	 * Add coefficient-wise two vector in place
	 *
	 * \param[in] rhs Vector to add
	 * \return Resultant vector (reference to *this)
	 */
	Vector3d& operator +=(const Vector3d& rhs);

	/** 
	 * Subtract coefficient-wise two vector in place
	 *
	 * \param[in] rhs Vector to subtract
	 * \return Resultant vector (reference to *this)
	 */
	Vector3d& operator -=(const Vector3d& rhs);

	/** 
	 * Multiply the vector with a scalar in place
	 *
	 * \param[in] rhs Vector to multiply
	 * \return Resultant vector (reference to *this)
	 */
	Vector3d& operator *=(float rhs);

	/** 
	 * Divide this vector by a scalar
	 *
	 * \param[in] rhs Denominator scalar value
	 * \return Resultant vector (reference to *this)
	 * \pre rhs != 0
	 */
	Vector3d& operator /=(float rhs);

	/** 
	 * Compute the dot product (or scalar product, inner product) of this and the
	 * given vector
	 *
	 * \param[in] rhs Second vector
	 * \return Dot product of two vectors
	 */
	float dot(const Vector3d& rhs) const;

	/** 
	 * Computes the cross-product of this and the gien vector
	 *
	 * \param[in] rhs Second vector
	 * \return Cross product of two vectors
	 */
	Vector3d cross(const Vector3d& rhs) const;

	/** 
	 * Squared norm of this vector
	 *
	 * \return Squared norm of this vector
	 */
	float squaredNorm() const;

	/** 
	 * Euclidean norm of this vector
	 *
	 * \return Euclidean norm of this vector
	 */
	float norm() const;

	/**
	 * Determine if the vector is null
	 * \return true if null vector, else false
	 */
	bool isNull() const;

    /** 
	 * Lexicographical compare of two vectors
     *
     * \param other Vector3d to compare with
     * \return True if this vector is less than the other, otherwise false
     */
    bool operator <(const Vector3d& other) const;

    /** 
	 * Equality operator
     *
     * \param other Vector3d to compare with
     * \return True if vectors are coefficient-wise equal, otherwise false
     */
	bool operator ==(const Vector3d& other) const;
};

/** 
 * Structure that defines a 4D float vector 
 */
struct METAIO_DLL_API Vector4d
{
	float x;	///< x component of the vector
	float y;	///< y component of the vector
	float z;	///< z component of the vector
	float w;	///< w component of the vector

	Vector4d();

	/** 
	 * Create Vector4d and initialize all components to 0
	 * \param _x x component of the vector
	 * \param _y y component of the vector
	 * \param _z z component of the vector
	 * \param _w w component of the vector
	 */
	Vector4d(float _x, float _y, float _z, float _w);

	/** 
	 * Sets all the components to 0
	 *
	 * \post norm() == 0
	 */
	void setZero();

	/** 
	 * Negative of this vector
	 *
	 * \return Resultant vector
	 */
	Vector4d operator -() const;

	/** 
	 * Add two vectors coefficient-wise
	 *
	 * \param[in] rhs Vector to add
	 * \return Resultant vector after addition
	 */
	Vector4d operator +(const Vector4d& rhs) const;

	/** 
	 * Subtract two vectors coefficient-wise
	 *
	 * \param[in] rhs Vector to be subtracted
	 * \return Resultant vector after subtraction
	 */
	Vector4d operator -(const Vector4d& rhs) const;

	/** 
	 * Multiplies a scalar coefficient-wise with the vector
	 *
	 * \param[in] rhs Scalar value to multiple
	 * \return Resultant vector after multiplication
	 */
	Vector4d operator *(float rhs) const;

	/** 
	 * Divide coefficient-wise with the vector by a scalar
	 *
	 * \param[in] rhs Denominator scalar value
	 * \return Resultant vector
	 * \pre rhs != 0
	 */
	Vector4d operator /(float rhs) const;

	/** 
	 * Add coefficient-wise two vector in place
	 *
	 * \param[in] rhs Vector to be added
	 * \return Resultant vector (Reference to *this)
	 */
	Vector4d& operator +=(const Vector4d& rhs);

	/** 
	 * Subtract coefficient-wise two vector in place
	 *
	 * \param[in] rhs Vector to subtract
	 * \return Resultant vector (Reference to *this)
	 */
	Vector4d& operator -=(const Vector4d& rhs);

	/** 
	 * Multiply the vector with a scalar in place
	 *
	 * \param[in] rhs Scalar to multiple
	 * \return Resultant vector (Reference to *this)
	 */
	Vector4d& operator *=(float rhs);

	/** 
	 * Divide the vector by a scalar
	 *
	 * \param[in] rhs Denominator scalar value
	 * \return Resultant vector (Reference to *this)
	 * \pre rhs != 0
	 */
	Vector4d& operator /=(float rhs);

	/** 
	 * Compute dot product (or scalar product, inner product) of this and the
	 * given vector.
	 *
	 * \param[in] rhs Second vector
	 * \return Dot product of the vectors
	 */
	float dot(const Vector4d& rhs) const;
	
	/** 
	 * Squared norm of the vector
	 *
	 * \return Squared norm of the vector
	 */
	float squaredNorm() const;

	/** 
	 * Euclidean norm of the vector
	 *
	 * \return Euclidean norm of the vector
	 */
	float norm() const;

	/**
	 * Determine if the vector is null
	 * \return true if null vector, else false
	 */
	bool isNull() const;
	
};

/** 
 * Struct for corresponding 2D and 3D points 
 */
struct METAIO_DLL_API Correspondence2D3D
{
	Vector2d observedPoint;		///< observed 2D point (e.g. on the image screen)
	Vector3d referencePoint;	///< reference 3D point (e.g. point in world coordinates)

	Correspondence2D3D();

	/**
	 * Sets the initial coordinates of the correspondence
	 *
	 * \param[in] observed_x Coordinate in x of the 2D point
	 * \param[in] observed_y Coordinate in y of the 2D point
	 * \param[in] reference_x Coordinate in x of the 3D point
	 * \param[in] reference_y Coordinate in y of the 3D point
	 * \param[in] reference_z Coordinate in z of the 3D point
	 */
	Correspondence2D3D(float observed_x, float observed_y, float reference_x, float reference_y, float reference_z);

	/**
	 * Sets the initial coordinates of the correspondence
	 *
	 * \param[in] observed Observed point in 2D
	 * \param[in] reference Reference point in 3D
	 */
	Correspondence2D3D(const Vector2d& observed, const Vector3d& reference);
	
};

/** 
 * Structure that defines a GPS coordinate. 
 */
struct METAIO_DLL_API LLACoordinate
{
	double latitude;	///< Latitude in decimal
	double longitude;	///< Longitude in decimal
	double altitude;	///< Altitude in meters
	double accuracy;	///< Accuracy of the GPS position
	double timestamp;	///< Timestamp in milliseconds when the coordinates were valid

	/**
	 * Default constructor
	 */
	LLACoordinate();

	/**
	 * Create and initialize LLACoordinate to the given values
	 * \param _lat	latitude component
	 * \param _long	longitude component
	 * \param _alt	altitude component
	 * \param _acc	accuracy component
	 */
	LLACoordinate(double _lat, double _long, double _alt, double _acc);

	/**
	 * Create and initialize LLACoordinate to the given values
	 * \param _lat	latitude component
	 * \param _long	longitude component
	 * \param _alt	altitude component
	 * \param _acc	accuracy component
	 * \param _tms	timestamp
	 */
	LLACoordinate(double _lat, double _long, double _alt, double _acc, double _tms);

	/**
	 * Determine if location is invalid (null)
	 * \return true if invalid, else false
	 * \sa setNull
	 */
	bool isNull() const;

	/**
	 * Set location to invalid, i.e. all fields to zero
	 * \sa isNull
	 */
	void setNull();

	/**
	 * Determine if the two LLACoordinates are equal, this does not compare
	 * timestamps
	 *
	 * \param rhs LLACoordinates to compare with
	 * \return true if they are equal
	 */
	bool operator==(const LLACoordinate& rhs) const;

	/**
	 * Determine if the two LLACoordinates are not equal, this does not compare
	 * timestamps
	 *
	 * \param rhs LLACoordinates to compare with
	 * \return true if they are not equal
	 */
	bool operator!=(const LLACoordinate& rhs) const;
};

/** 
 * BoundingBox of the geometry.
 */
struct METAIO_DLL_API BoundingBox
{
	Vector3d min;	///< Vector containing the minimum x,y,z values
	Vector3d max;	///< Vector containing the maximum x,y,z values
};


/** 
 * A byte buffer with its length
 */
struct METAIO_DLL_API ByteBuffer
{
	unsigned char* buffer;		///< pointer to a binary buffer
	int length;					///< legnth of the buffer

	/**
	 * Default constructor for ByteBuffer struct
	 */
	ByteBuffer();

	/**
	 * Constructor for ByteBuffer struct
	 *
	 * \param _buffer pointer to the binary data
	 * \param _length length of the buffer
	 */
	ByteBuffer(unsigned char* _buffer, int _length);

	/**
	 * Release the memory used by the buffer.
	 * All the members are reset to their default values after this call.
	 */
	void release();

};

/** 
 * Image structure used by metaio SDK
 */
struct METAIO_DLL_API ImageStruct
{
	unsigned char* buffer;						///< Pointer to the pixels' buffer
	int width;									///< Image width
	int height; 								///< Image height
	metaio::common::ECOLOR_FORMAT colorFormat;	///< Image color format
	bool originIsUpperLeft;						///< true if the origin is in the upper left corner (default); false, if lower left
	double timestamp;							///< timestamp when the image was created

    /**
     *  On iOS and especially iPhone5 captured YUV420SP-images may have an offset between Y and UV plane.
     *  To not omit this information after capturing the frame it should be stored here.
     *  On iOS this information can be retrieved using CVPixelBufferGetBaseAddressOfPlane()
     *
     */
    unsigned int planePaddingOffset;
    
	/**
	 * Platform-specific capturing context object
	 *
	 * On iOS, this is a CVImageBufferRef
	 * (https://developer.apple.com/library/mac/#documentation/QuartzCore/Reference/CVImageBufferRef/Reference/reference.html)
	 * which you can optionally use for faster texture upload of the camera image, for example. If
	 * you store this object yourself, don't forget to use CFRetain/CFRelease for reference
	 * counting.
	 *
	 * On other platforms, this is NULL at the moment.
	 */
	void* capturingContext;
    
	/**
	 * Stride of the image in bytes
	 *
	 * This defines the number of bytes between the first and second row in the image. Use this in
	 * case an image has extra padding bytes at the end of each row. If this field is zero, a
	 * packed alignment will be assumed - for example, a 12 pixels wide RGB image has a stride of 36
	 * bytes if it's packed, i.e. without any padding.
	 */
	unsigned int stride;

	/**
	 * Create an empty ImageStruct
	 */
	ImageStruct();

	/**
	 * Create ImageStruct with the given data
	 *
	 * \param _buffer pointer to the image data
	 * \param _width width of the image
	 * \param _height height of the image
	 * \param _colorFormat the color format
	 * \param _originIsUpperLeft true if the origin is upper left corner, false if lower left
	 * \param _timestamp timestamp when the image was created
	 * \param _capturingContext platform-specific capturing context object
	 * \param _stride stride of the image
	 */
	ImageStruct(unsigned char* _buffer, int _width, int _height,
				metaio::common::ECOLOR_FORMAT _colorFormat, bool _originIsUpperLeft, double _timestamp = 0,
				void* _capturingContext = 0, unsigned int _stride = 0);

	/**
	 * Get buffer size that is based on image dimensionsn and color format
	 * \return Image buffer size
	 */
	unsigned int getBufferSize() const;

	/**
	 *	Compress the image contents into a new buffer. 
	 * This function currently supports JPEG compression only. 
	 * It is the responsibility of the caller to delete returned ByteBuffer structure and its contents.
	 *
	 *	\param	quality JPEG quality (1-100, 0 will pick the default quality)
	 *
	 *	\return	ByteBuffer containing compressed data on success, NULL on failure.
	 */
	ByteBuffer* compress(unsigned int quality=0) const;

	/**
	 * Release the memory used by the buffer.
	 * All the members are reset to their default values after this call.
	 */
	void release();

};

/**
 * User-defined acceleration vector with timestamp
 */
struct UserAcceleration
{
	double				timestamp; ///< Timestamp

	metaio::Vector3d	acceleration; ///< Acceleration vector
};

/**
 * The Visual Search response from the server.
 */
struct METAIO_DLL_API VisualSearchResponse
{
	stlcompat::String trackingConfigurationName;	///< The name of the tracking configuration that is found
	stlcompat::String trackingConfiguration;		///< The tracking configuration of the found target that can be directly loaded into metaioSDK
	float visualSearchScore;						///< Visual search score

	/**
	 * Default constructor of VisualSearchResponse
	 */
	VisualSearchResponse();
	
};

} // namespace metaio

#endif
