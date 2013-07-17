// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef _AS_ROTATIONMATRIX_H_
#define _AS_ROTATIONMATRIX_H_

#include <metaioSDK/MobileStructs.h>

#include <assert.h>
#include <memory>
#include <math.h>
#include <string.h>

namespace metaio
{
/**
* \brief This class contains some basic operations on rotations in the 3D space.
*	Basic conversions to different representations of an rotation are also implemented
*/
class METAIO_DLL_API Rotation
{
public:

	/**
	* \brief Standard constructor. Initialized with no rotation
	*/
	Rotation();


	/**
	* \brief Copy constructor
	*
	* \param rotation This rotation will be used for initialization
	*/
	Rotation(const Rotation& rotation);

	/**
	* \brief Constructor with initialization from a (3x3) rotation matrix
	*
	* \param rotationMatrix Rotation matrix (3x3) array row major
	*/
	explicit Rotation(const float rotationMatrix[9]);

	/**
	 * \brief Constructor with initialization from a quaternion
	 *
	 * \param quaternion rotation as quaternion
	 */
	explicit Rotation(const Vector4d& quaternion);

	/**
	 * \brief Constructor with initialization from euler angles (radians)
	 *
	 * \param eulerAngle rotation as euler angles in radians
	 */
	explicit Rotation(const Vector3d& eulerAngle);

	/**
	 * \brief Constructor with initialization from euler angles (radians)
	 *
	 * \param x Euler angle (radians) around x-axis
	 * \param y Euler angle (radians) around y-axis
	 * \param z Euler angle (radians) around z-axis
	 */
	explicit Rotation(const float x, const float y, const float z);


	/**
	* \brief Access to the element (i,j) of this rotation as (3x3) rotation matrix.
	*
	* \param i row index
	* \param j column index
	* \return element at (i,j)
	*/
	inline float& operator()(int i, int j)
	{
		assert(i >= 0 && i < 3 && j >= 0 && j < 3);
		return m_data[i * 3 + j];
	}


	/**
	* \brief Access to the element (i,j) of this rotation as (3x3) rotation matrix.
	*	Overloaded const function
	*
	* \param i row index
	* \param j column index
	* \return element at (i,j)
	*/
	inline const float& operator()(int i, int j) const
	{
		assert(i >= 0 && i < 3 && j >= 0 && j < 3);
		return m_data[i * 3 + j];
	}


	/**
	* \brief	Assignment operator
	*
	* \param	rotation The rotation that should be assigned to this one.
	* \return 	This rotation
	*/
	inline const Rotation& operator = (const Rotation& rotation)
	{
		if (this != &rotation)
			memcpy(m_data, rotation.m_data, sizeof(m_data));
		return *this;
	}


	/**
	* \brief Combines two rotations. The right factor rotation is performed first, then this rotation.
	*
	* \param factor The right factor rotation
	* \return Combination of the two rotations
	*/
	Rotation operator*(const Rotation& factor) const;


	/**
	 * \brief Equals operator
	 *
	 * \param rotation The rotation that should be compared with.
	 * \return true if equal, false otherwise
	 */
	bool isEqual(const Rotation& rotation) const;

	/**
	* \brief Sets this rotation by a (3x3) matrix representation
	*
	* \param rotationMatrix Rotation matrix (3x3) array row major
	*/
	void setFromRotationMatrix(const float rotationMatrix[9]);

	/**
	* \brief Returns the (3x3) matrix representation of this rotation
	*
	* \param rotationMatrix Rotation matrix (3x3) array row major
	*/
	void getRotationMatrix(float rotationMatrix[9]) const;

	/**
	* \brief Sets this rotation by the rotational part of a (4x4) modelview matrix
	*
	* \param modelviewMatrix Modelview matrix (4x4) array row major
	*/
	void setFromModelviewMatrix(const float modelviewMatrix[16]);

	/**
	* \brief Sets this rotation by a quaternion representation
	*
	* \param quaternion Quaternion. Imaginary part: quaternion.x, quaternion.y, quaternion.z Real part: quaternion.w
	*/
	void setFromQuaternion(const Vector4d& quaternion);


	/**
	* \brief Computes the quaternion representation of this rotation
	*
	* \return Vector4d representing a quaternion. Imaginary part: x, y, z Real part: w
	*/
	Vector4d getQuaternion() const;


	/**
	* \brief Sets this rotation by an axis angle representation
	*
	* \param axisAngle Axis angle. Rotation axis (length == 1): axisAngle.x, axisAngle.y, axisAngle.z Rotation right handed: axisAngle.w in radians
	*/
	void setFromAxisAngle(const Vector4d& axisAngle);


	/**
	* \brief Computes the axis angle representation of this rotation
	*
	* \return Vector4d representing an axis angle. Rotation axis (length == 1): x, y, z Rotation right handed: w in radians
	*/
	Vector4d getAxisAngle() const;


	/**
	* \brief Sets this rotation by an Euler angle representation
	*
	* \param eulerAngleRadians Euler angle. Rotation order: x-axis, y-axis, z-axis in radians
	*/
	void setFromEulerAngleRadians(const Vector3d& eulerAngleRadians);


	/**
	* \brief Computes the Euler angle representation of this rotation
	*
	* \return Vector3d representing an Euler angle. Rotation order: x-axis, y-axis, z-axis in radians
	*/
	Vector3d getEulerAngleRadians() const;


	/**
	* \brief Sets this rotation by an Euler angle representation
	*
	* \param eulerAngleDegree Euler angle. Rotation order: x-axis, y-axis, z-axis in degrees
	*/
	void setFromEulerAngleDegrees(const Vector3d& eulerAngleDegree);


	/**
	* \brief Computes the Euler angle representation of this rotation
	*
	* \return Vector3d representing an Euler angle. Rotation order: x-axis, y-axis, z-axis in degrees
	*/
	Vector3d getEulerAngleDegrees() const;


	/**
	* \brief Returns a rotated point, rotated by this rotation
	*
	* \param point 3D point
	* \return The rotated point
	*/
	Vector3d rotatePoint(const Vector3d& point) const;


	/**
	* \brief Sets this rotation to not rotate at all
	*/
	void setNoRotation();


	/**
	* \brief Returns an inverted copy of this rotation. This inverse corresponds to a rotation in the opposite direction
	*		rotation*rotation.inverse() == rotation.setNoRotation()
	*
	* \return The inverse of the rotation
	*/
	Rotation inverse() const;


	/**
	* \brief Returns the angle that is needed to rotate the input rotation to this rotation
	*	suitable to compare two rotations. If they are similar this angle should be small
	*
	* \param rotation Input rotation
	* \return Angle difference in radians. Always >= 0
	*/
	float getAngleToRotation(const Rotation& rotation) const;


	/**
	* \brief Interpolates a rotation between this rotation and the input rotation
	*
	* \param rotation The input rotation, that will be interpolated
	* \param weight of the input rotation.
	*	weight == 0: Returns this rotation
	*	weight == 1: Returns the input rotation
	*	weight[0;1]: Returns interpolated rotation
	* \return Interpolated rotation
	*/
	Rotation interpolateRotation(const Rotation& rotation, float weight) const;

private:

	float m_data[9]; //!< Rotation matrix representation
};
}


#endif
