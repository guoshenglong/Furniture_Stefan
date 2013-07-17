// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef __AS_IRADAR_H_INCLUDED__
#define __AS_IRADAR_H_INCLUDED__

#include <metaioSDK/MobileStructs.h>
#include <metaioSDK/IGeometry.h>
#include <metaioSDK/STLCompatibility.h>

namespace metaio
{


/**
 * Interface for the radar
 */
class IRadar
{
public:

	/**
	 * Destructor
	 */
	virtual ~IRadar() {};


	/**
	 * Add a geometry to radar
	 *
	 * \param geometry Pointer to the geometry to add
	 * \return true if the geometry has been added, else false
	 */
	virtual bool add(IGeometry* geometry) = 0;

	/**
	 * Remove a geometry from radar
	 *
	 * \param geometry Pointer to the geometry to remove
	 * \return true if the geometry has been removed, else false
	 */
	virtual bool remove(IGeometry* geometry) = 0;

	/**
	 * Remove all geometries from radar
	 */
	virtual void removeAll() = 0;

	/**
	 * Set background texture of the radar from then given file path
	 *
	 *	Supported formats are PNG and JPG.
	 *
	 * \param texturePath Path to the texture image file.
	 * \return true on success
	 */
	virtual bool setBackgroundTexture(const stlcompat::String& texturePath) = 0;

	/**
	 * Set background texture of the radar from the given image structure
	 *
	 * \param textureName A name that should be assigned to the texture (for reuse).
	 * \param image The actual image.
	 * \param updateable Flag to signal, that this image will be frequently updated.
	 * \return true on success
	 */
	virtual bool setBackgroundTexture(const stlcompat::String& textureName, const ImageStruct& image,
	                                  const bool updateable = false) = 0;

	/**
	 * Set default texture of the radar objects from then given file path.
	 * The new texture is applied to all radar objects in case of success.
	 *
	 *	Supported formats are PNG and JPG.
	 *
	 * \param texturePath Path to the texture image file.
	 * \return true on success
	 */
	virtual bool setObjectsDefaultTexture(const stlcompat::String& texturePath) = 0;

	/**
	 * Set default texture of the radar objects from the given image structure
	 * The new texture is applied to all radar objects in case of success.
	 *
	 * \param textureName A name that should be assigned to the texture (for reuse).
	 * \param image The actual image.
	 * \param updateable Flag to signal, that this image will be frequently updated.
	 * \return true on success
	 */
	virtual bool setObjectsDefaultTexture(const stlcompat::String& textureName, const ImageStruct& image,
	                                      const bool updateable = false) = 0;


	/**
	 * Set default texture of the radar objects from then given file path.
	 * The new texture is applied to all radar objects in case of success.
	 *
	 *	Supported formats are PNG and JPG.
	 *
	 * \param geometry Geometry for which corresponding object's texture is set
	 * \param texturePath Path to the texture image file.
	 * \return true on success
	 */
	virtual bool setObjectTexture(IGeometry* geometry, const stlcompat::String& texturePath) = 0;

	/**
	 * Set default texture of the radar objects from the given image structure
	 * The new texture is applied to all radar objects in case of success.
	 *
	 * \param geometry Geometry for which corresponding object's texture is set
	 * \param textureName A name that should be assigned to the texture (for reuse).
	 * \param image The actual image.
	 * \param updateable Flag to signal, that this image will be frequently updated.
	 *        It should always be true on Android.
	 * \return true on success
	 */
	virtual bool setObjectTexture(IGeometry* geometry, const stlcompat::String& textureName,
	                              const ImageStruct& image, const bool updateable = false) = 0;

	/**
	 * Set size of the radar objects
	 * \param size new size
	 * \sa getObjectSize
	 */
	virtual void setObjectsSize(float size) = 0;


	/**
	 * Get size of the radar objects
	 * \return size of the radar objects
	 * \sa setSize
	 */
	virtual float getObjectsSize() const = 0;

	/**
	 * Get default scale of the radar objects
	 *
	 * \return a vector containing relative scale of the object.
	 * \sa setObjectsScale
	 */
	virtual Vector3d getObjectsScale() const = 0;

	/**
	 * Set default relative scale of the radar objects
	 *
	 * \param scale a vector containing relative scale
	 * \sa getObjectsScale
	 */
	virtual void setObjectsScale(Vector3d scale) = 0;

	/**
	 * Set default relative scale of the radar objects
	 *
	 * \param scale relative scale
	 * \sa getObjectsScale
	 */
	virtual void setObjectsScale(float scale) = 0;

	/**
	 * Get scale of the radar object that represents given geometry.
	 *
	 * \param geometry Geometry for which the corresponding object scale is returned
	 * \return a vector containing relative scale of the object, if geometry
	 * is not found, the scale will be invalid, i.e. (-1,-1,-1).
	 * \sa setObjectScale
	 */
	virtual Vector3d getObjectScale(IGeometry* geometry) const = 0;

	/**
	 * Set relative scale of the object that represents the given geometry
	 *
	 * \param geometry Geometry that has been added to the radar
	 * \param scale a vector containing relative scale
	 * \sa getObjectScale
	 */
	virtual void setObjectScale(IGeometry* geometry, Vector3d scale) = 0;

	/**
	 * Set relative scale of the object that represents the given geometry
	 *
	 * \param geometry Geometry that has been added to the radar
	 * \param scale relative scale
	 * \sa getObjectScale
	 */
	virtual void setObjectScale(IGeometry* geometry, float scale) = 0;

	/**
	 * Get size of the radar
	 * \return size of the radar
	 * \sa setSize
	 */
	virtual float getSize() const = 0;

	/**
	 * Set size of the radar
	 * \param size new size
	 * \sa getSize
	 */
	virtual void setSize(float size) = 0;


	/**
	 * Set width of the border to exclude from drawable area
	 *
	 * \param border width of the border
	 * \sa getBorder
	 */
	virtual void setBorder(float border) = 0;

	/**
	 * Get width of the border that is excluded from drawable area
	 * \return width of the border
	 * \sa setBorder
	 */
	virtual float getBorder() const = 0;

	/**
	 * Set the radar relative to one of the anchor points on screen
	 *
	 * \param anchor one of the screen anchor points
	 * \param flags additional flags to ignore some geometric transforms, default is
	 * IGeometry::FLAG_MATCH_DISPLAY
	 * \sa IGeometry::setRelativeToScreen
	 */
	virtual void setRelativeToScreen(int anchor, int flags=IGeometry::FLAG_MATCH_DISPLAY) = 0;

	/**
	 * Get relative-to-screen anchor.
	 * \return One or combination of screen anchors.
	 * \sa setRelativeToScreen
	 */
	virtual int getRelativeToScreen() const = 0;


	/**
	 * Set the translation of the radar geometry.
	 * \param translation The 3D translation vector in millimeters.
	 * \param concat If true, the new translation is added to the existing one, otherwise it is overwritten.
	 * \sa getTranslation
	 */
	virtual void setTranslation(const Vector3d& translation, bool concat = false) = 0;


	/**
	 * Get the current translation of the radar geometry.
	 * \return A 3D vector containing the translation in millimeters.
	 * \sa setTranslation
	 */
	virtual Vector3d getTranslation() = 0;

	/**
	 * \brief Set the scale of the radar.
	 * \param scale Scaling vector (x,y,z).
	 * \sa getScale
	 */
	virtual void setScale(const Vector3d& scale)  = 0;

	/**
	 * Set the scale of the radar.
	 * \param scale scale factor for all dimensions
	 * \sa getScale
	 */
	virtual void setScale(const float scale) = 0;

	/**
	 * Get the current scale of the radar.
	 * \return The scaling vector (x,y,z).
	 * \sa setScale
	 */
	virtual Vector3d getScale() = 0;

	/**
	 * Determine the visibility of the radar.
	 * \return True if the radar is set visible, false otherwise.
	 * \sa setVisible
	 */
	virtual bool isVisible() = 0;

	/**
	 * Set the visibility of the radar.
	 * \param visible True if the radar should be visible, false if it should be hidden.
	 * \sa isVisible
	 */
	virtual void setVisible(bool visible) = 0;

	/**
	 * Set the transparency of the radar.
	 *
	 * \param transparency The transparency value, where 0 corresponds to a non-transparent radar,
	 *                     1 to a fully transparent radar.
	 * \sa getTransparency
	 * \sa setVisible and getIsVisible
	*/
	virtual void setTransparency(float transparency) = 0;


	/**
	 * Get the transparency of the radar.
	 *
	 * \return transparency The transparency value, where 0 corresponds to a non-transparent radar,
	 *                      1 to a fully transparent radar.
	 * \sa setTransparency
	 */
	virtual float getTransparency() = 0;

	/**
	 * Enable or disable picking for the radar geometry.
	 *
	 * \param enabled true to enable picking of the radar, false to disable it.
	 * \sa isPickingEnabled
	 */
	virtual void setPickingEnabled(bool enabled)  = 0;


	/** Determine if picking is enabled or disabled for the radar geometry.
	 * \return true, if enabled, false otherwise
	 * \sa setPickingEnabled
	 */
	virtual bool isPickingEnabled() = 0;


};	// end interface IRadar
}	// end namespace metaio

#endif //__AS_IRADAR_H_INCLUDED__

