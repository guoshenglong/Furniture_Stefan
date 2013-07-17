// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef __AS_IGEOMETRY_H_INCLUDED__
#define __AS_IGEOMETRY_H_INCLUDED__

#include <metaioSDK/MobileStructs.h>
#include <metaioSDK/ColorFormat.h>
#include <metaioSDK/Rotation.h>
#include <metaioSDK/STLCompatibility.h>

namespace metaio
{

/// Enumeration to encode the type of a geometry
enum EGEOMETRY_TYPE
{
    EGEOMETRY_TYPE_3D,					///< A 3D model
    EGEOMETRY_TYPE_BILLBOARD,			///< Billboard
    EGEOMETRY_TYPE_PLANE,				///< A 3D plane
	EGEOMETRY_TYPE_RADAR,				///< Radar
    EGEOMETRY_TYPE_UNKNOWN				///< Unknown geometry type
};

/**
 * Movie texture playback status
 */
enum EPLAYBACK_STATUS
{
	EPLAYBACK_STATUS_ERROR = 0,			///< not a movie texture or failed to load/play
	EPLAYBACK_STATUS_PLAYING = 1,		///< currently playing
	EPLAYBACK_STATUS_PAUSED = 2,		///< playing, but currently paused
	EPLAYBACK_STATUS_STOPPED = 3		///< playback stopped
};

/**
 * Movie texture status
 */
struct MovieTextureStatus
{
	EPLAYBACK_STATUS playbackStatus;	///< Playback status
	float currentPosition;				///< Current playback position in seconds
	bool looping;						///< Whether playback should loop

	/**
	 * Constructor
	 */
	MovieTextureStatus(): playbackStatus(EPLAYBACK_STATUS_ERROR), currentPosition(0.f), looping(false) {}
};


/**
 * General interface for a geometry that can be loaded within the system
 *
 */
class IGeometry
{

public:

	static const int ANCHOR_NONE =			0<<0;			///< No anchor, i.e. not relative-to-screen (0)
	static const int ANCHOR_LEFT =			1<<0;			///< Anchor to the left edge (1)
	static const int ANCHOR_RIGHT =			1<<1;			///< Anchor to the right edge (2)
	static const int ANCHOR_BOTTOM =		1<<2;			///< Anchor to the bottom edge (4)
	static const int ANCHOR_TOP =			1<<3;			///< Anchor to the top edge (8)
	static const int ANCHOR_CENTER_H =		1<<4;			///< Anchor to the horizontal center (16)
	static const int ANCHOR_CENTER_V =		1<<5;			///< Anchor to the vertical center (32)

	static const int ANCHOR_TL = ANCHOR_LEFT|ANCHOR_TOP;				///< Anchor to the Top-Left (9)
    static const int ANCHOR_TC = ANCHOR_TOP|ANCHOR_CENTER_H;			///< Anchor to the Top-Center (24)
    static const int ANCHOR_TR = ANCHOR_TOP|ANCHOR_RIGHT;				///< Anchor to the Top-Right (10)
    static const int ANCHOR_CL = ANCHOR_CENTER_V|ANCHOR_LEFT;			///< Anchor to the Center-Left (33)
    static const int ANCHOR_CC = ANCHOR_CENTER_H|ANCHOR_CENTER_V;		///< Anchor to the Center (48)
    static const int ANCHOR_CR = ANCHOR_CENTER_V|ANCHOR_RIGHT;			///< Anchor to the Center-Right (34)
    static const int ANCHOR_BL = ANCHOR_BOTTOM|ANCHOR_LEFT;				///< Anchor to the Bottom-Left (5)
    static const int ANCHOR_BC = ANCHOR_BOTTOM|ANCHOR_CENTER_H;			///< Anchor to the Bottom-Center (20)
    static const int ANCHOR_BR = ANCHOR_BOTTOM|ANCHOR_RIGHT;			///< Anchor to the Bottom-Right (6)

	static const int FLAG_NONE =						0<<0;		///< No flag, all geometric transforms are considered
	static const int FLAG_IGNORE_ROTATION =				1<<0;		///< ignore rotation of the geometry
	static const int FLAG_IGNORE_ANIMATIONS =			1<<1;		///< ignore animations of the geometry
	/**
	 * The geometry will be scaled automatically to match the physical display, regardless of its pixel density
	 * and resolution. This means that geometry will have same physical size on every display. 
	 * The scaling is relative to the baseline density which is 160ppi.
	 * If this flag is not defined, the one unit of the geometry will exactly match 1 pixel
	 * on the screen. It will also match 1 pixel on a display with 160ppi.
	 */
	static const int FLAG_MATCH_DISPLAY =				1<<2;

	/**
	 * Autoscale geometries according to the screen resolution and/or display density.
	 * if flag FLAG_MATCH_DISPLAY is also defined, the baseline will be 4-inch
	 * display, other wise it will be screen with width = 640 pixels.
	 */
	static const int FLAG_AUTOSCALE =					1<<3;


	virtual ~IGeometry() {};

	/**
	 * Set geometry relative to an anchor point on screen.
	 *
	 * \param anchor one or combination of screen anchors (use ANCHOR_NONE to stop rendering geometry as relative to screen)
	 * \param flags additional flags to ignore some geometric transforms.
	 * Can be combination of FLAG_IGNORE_ROTATION, FLAG_IGNORE_ANIMATIONS, FLAG_MATCH_DISPLAY or FLAG_AUTOSCALE.
	 * Default is FLAG_NONE.
	 *
	 * \sa ANCHOR_NONE
	 * \sa ANCHOR_LEFT, ANCHOR_RIGHT, ANCHOR_BOTTOM, ANCHOR_TOP, ANCHOR_CENTER_H, ANCHOR_CENTER_V
	 * \sa ANCHOR_TL, ANCHOR_TC, ANCHOR_TR, ANCHOR_CL, ANCHOR_CC, ANCHOR_CR, ANCHOR_BL, ANCHOR_BC, ANCHOR_BR
	 * \sa FLAG_NONE
	 * \sa FLAG_IGNORE_ROTATION, FLAG_IGNORE_ANIMATIONS
	 * \sa FLAG_MATCH_DISPLAY, FLAG_AUTOSCALE
	 * \sa getRelativeToScreen
	 */
	virtual void setRelativeToScreen(int anchor, int flags=FLAG_NONE) = 0;

	/**
	 * Get relative-to-screen anchor.
	 * \return One or combination of screen anchors.
	 * \sa setRelativeToScreen
	 */
	virtual int getRelativeToScreen() const = 0;

	/**
	 * Set the translation of the geometry.
	 * \param translation The 3D translation vector in millimeters.
	 * \param concat If true, the new translation is added to the existing one, otherwise it is overwritten.
	 * \sa getTranslation
	 */
	virtual void setTranslation(const Vector3d& translation, bool concat = false) = 0;


	/**
	 * Get the current translation of the geometry.
	 * \return A 3D vector containing the translation in millimeters.
	 * \sa setTranslation
	 */
	virtual Vector3d getTranslation() = 0;


	/**
	 * Set the translation of the geometry to an LLA coordinate.
	 *	The system will then adjust its Cartesian offset in the renderer accordingly.
	 *	Note: The altitude is ignored, if you want adjust the height use setTranslation
	 *
	 * \param llaCoorindate The LLA (latitude, longitude, altitude) to set as translation.
	 * \sa setTranslation and getTranslation
	 * \sa getTranslationLLA
	 * \sa getTranslationLLACartesian
	 */
	virtual void setTranslationLLA(LLACoordinate llaCoorindate)  = 0;


	/**
	 * Get the translation of the geometry as LLA coordinate.
	 * \return The LLA (latitude, longitude, altitude) coordinate of the geometry.
	 * \sa setTranslation and getTranslation
	 * \sa setTranslationLLA
	 * \sa getTranslationLLACartesian
	 */
	virtual LLACoordinate getTranslationLLA() = 0;


	/**
	 * Get the Cartesian translation of the geometry with an LLA coordinate.
	 * It returns absolute translation of the geometry relative to current LLA coordinates
	 * provided by the sensors' component. 
	 *
	 * \return A 3D vector containing the translation in millimeters 
	 * \sa setTranslation and getTranslation
	 * \sa setTranslationLLA and getTranslationLLA
	 */
	virtual Vector3d getTranslationLLACartesian() = 0;


	/**
	 * Set the scale of the geometry.
	 * \param scale Scaling vector (x,y,z).
	 * \param concat If true, the new scale is multiplied with existing scale.
	 * \sa getScale
	 */
	virtual void setScale(const Vector3d& scale, bool concat = false)  = 0;

	/**
	 * Set the scale of the geometry.
	 * \param scale scale factor for all dimensions
	 * \param concat If true, the new scale is multiplied with existing scale.
	 * \sa getScale
	 */
	virtual void setScale(const float scale, bool concat = false) = 0;

	/**
	 * Get the current scale of the geometry.
	 * \return The scaling vector (x,y,z).
	 * \sa setScale
	 */
	virtual Vector3d getScale() = 0;


	/**
	 * Set the rotation of the geometry in axis angle representation.
	 *
	 * \param rotation The rotation object specifying the rotation.
	 * \param concat If true, the new rotation is concatenated with an existing rotation.
	 * \sa getRotation
	 */
	virtual void setRotation(const metaio::Rotation& rotation, bool concat = false)  = 0;


	/**
	 * Get the current rotation of the geometry in axis angle representation.
	 * \return The current rotation as Rotation object.
	 * \sa setRotation
	 */
	virtual metaio::Rotation getRotation() = 0;


	/**
	 * Determine if the geometry is currently being rendered based on camera frustum,
	 * and geometry visibiliy. It only works when target is being tracked.
	 * \return True if the geometry is being rendered, false otherwise.
	 */
	virtual bool getIsRendered() = 0;


	/**
	 * Determine the visibility of the geometry.
	 * \return True if the geometry is set visible, false otherwise.
	 * \sa setVisible
	 */
	virtual bool isVisible() = 0;

	/**
	 * Triggers application pause actions
	 *
	 * You don't need to call this directly, use IMetaioSDK::pause() instead!
	 */
	virtual void onApplicationPause() {};

	/**
	 * Triggers application resume actions
	 *
	 * You don't need to call this directly, use IMetaioSDK::resume() instead!
	 */
	virtual void onApplicationResume() {};

	/**
	 * Set the visibility of the geometry.
	 * \param visible True if the geometry should be visible, false if it should be hidden.
	 * \sa isVisible
	 * \sa setOcclusionMode
	 * \sa setTransparency
	 * \sa setRenderAsXray
	 * \sa setPickingEnabled
	 */
	virtual void setVisible(bool visible) = 0;


	/**
	 * Set the rendering mode of a geometry to "x-ray".
	 *
	 * This method shall be used if a model should be drawn on top of
	 * all others and therefore ignore the z-buffer.
	 * It is only available with OpenGL ES 2.0 rendering.
	 *
	 * \param xray If true, the geometry will be rendered with the x-ray effect, otherwise it will be displayed normally.
	 * \sa setVisible and isVisible
	 * \sa setOcclusionMode
	 * \sa setTransparency
	 * \sa setPickingEnabled
	 */
	virtual void setRenderAsXray(bool xray) = 0;

	/**
	 * Set the rendering order of the geometry
	 *
	 * This method should be used for compositing, e.g. if a geometry should be drawn before or after other geometries.
	 * The ordering depends on the value of the level that is passed, the lower levels are drawn before higher levels,
	 * which means that a geometry with higher level will be on top of a geometry with lower level.
	 *
	 * The z-buffer (depth) check can be optionaly disabled so that geomrteis are rendered independant of their
	 * real distance from the camera. This is usefull when more than one geometries are positioned at same depth (z), or
	 * a geometry with greater depth needs to be rendered in front of a geometry with less depth. Note that it works only
	 * for simple geometries, e.g a plane or sphere.
	 *
	 * For complex geometries, clear depth (z-buffer) can be enabled instead of disabling z-buffer check. This would ensure
	 * that geometries are rendered in correct order, however, it is an expensive operation and can significantly reduce
	 * rendering performance.
	 * 
	 * Note that geometry picking is always based on real distance from the camera. It means that even though a geometry
	 * is forced to rendered on top of another geometry (i.e. by disabling z-buffer check and/or enabling clear depth), the
	 * background geometry may be picked because it is closer to the camera in reality.
	 *
	 * \param level render order, the higher value means front, default is 0
	 * \param disableDepth true to disable depth test, false to enable (default)
	 * \param clearDepth true to clear depth before rendering, false to disable this (default)
	 * \sa getRenderOrder
	 */
	virtual void setRenderOrder(int level, bool disableDepth=false, bool clearDepth=false) = 0;

	/**
	 * Retrieve the rendering order of the geometry.
	 *
	 * \return the level
	 * \sa setRenderOrder
	 */
	virtual int getRenderOrder() = 0;

	/**
	 * Set the occlusion mode of the geometry.
	 *
	 * \param occlude If true, the geometry is not displayed but only used to occlude other geometrys,
	 * otherwise it will be displayed normally.
	 * \sa setVisible and isVisible
	 * \sa setTransparency
	 * \sa setRenderAsXray
	 * \sa setPickingEnabled
	 */
	virtual void setOcclusionMode(bool occlude) = 0;


    /**
	 * Get the occlusion mode of the geometry.
	 * \return boolean If true geometry is occluded, otherwise false
	 * \sa isVisible
	 */
	virtual bool isOccluded() = 0;
    
	/**
	 * Set the transparency of the geometry.
	 *
	 * \param transparency The transparency value, where 0 corresponds to a non-transparent model, 1 to a fully transparent model.
	 * \sa getTransparency
	 * \sa setVisible and isVisible
	 * \sa setOcclusionMode
	 * \sa setRenderAsXray
	 * \sa setPickingEnabled
	 */
	virtual void setTransparency(float transparency) = 0;


	/**
	 * Get the transparency of the geometry.
	 *
	 * \return transparency The transparency value, where 0 corresponds to a non-transparent model, 1 to a fully transparent model.
	 * \sa setTransparency
	 */
	virtual float getTransparency() = 0;

	/**
	 * Start a specific animation of the geometry.
	 * \param animationName Identifier of the animation.
	 * \param loop If true, the animation is looped, otherwise it is only played once.
	 * \sa setAnimationSpeed
	 */
	virtual void startAnimation(const stlcompat::String& animationName = "", bool loop = false) = 0;

	/**
	 * Stops the current animation of the geometry.
	 * \sa startAnimation
	 */
	virtual void stopAnimation() = 0;

	/**
	 * Set the animation speed of the model.
	 * \param fps Desired animation speed in frames per second.
	 */
	virtual void setAnimationSpeed(float fps) = 0;

	/**
	 * Pause the currently started animation
	 */
	virtual void pauseAnimation() = 0;

	/**
	 * Returns all possible animation names.
	 * \return all animation names.
	 * \sa startAnimation
	 */
	virtual stlcompat::Vector<stlcompat::String> getAnimationNames() = 0;

	/**
	 * Get the (axis-aligned) bounding box of the geometry.
	 * \param inObjectCoordinates If true (default behaviour) the bounding box
	          will be returned in the coordinate system of the object, if false
			  it will be returned in the camera coordinate system
	 * \return The bounding box of the geometry.
	 */
	virtual BoundingBox getBoundingBox(bool inObjectCoordinates = true) = 0;


	/**
	 * Assign the geometry to a specific coordinate system (COS).
	 * \param coordinateSystemID The (one based) index of the coordinate system.
	 * \sa getCoordinateSystemID
	 */
	virtual void setCoordinateSystemID(int coordinateSystemID) = 0;


	/**
	 * Get the index of the coordinate system (COS) the geometry is assigned.
	 * \return The (one based) index of the coordinate system.
	 * \sa setCoordinateSystemID
	 */
	virtual int getCoordinateSystemID() = 0;


	/**
	 * Set a name of the geometry
	 * \param name Name of the geometry
	 * \sa getName
	 */
	virtual void setName(const stlcompat::String& name) = 0;

	/**
	 * Get the name of the geometry previously set by calling setName.
	 * \return Name of the geometry
	 * \sa setName
	 */
	virtual stlcompat::String getName() = 0;


	/**
	 * Get the type of the geometry.
	 * \return EGEOMETRY_TYPE value
	 * \sa EGEOMETRY_TYPE
	 */
	virtual EGEOMETRY_TYPE getType()  = 0;


	/**
	 * Activate or deactivate the usage of LLA rendering limits.
	 *
	 * If disabled, the geometry will ignore the near and far LLA limit
	 * and always render the object the the real location. The default
	 * is always enabled.
	 *
	 * \param enabled True to enable, false to disable.
	 * \sa IMetaioSDK::setLLAObjectRenderingLimits
	 */
	virtual void setLLALimitsEnabled(bool enabled) = 0;


	/**
	 * Enable or disable picking for the geometry.
	 *
	 * \param enabled True to enable picking of this geometry, false to disable it.
	 * \sa isPickingEnabled
	 * \sa setVisible and isVisible
	 * \sa setOcclusionMode
	 * \sa setTransparency
	 * \sa setPickingEnabled
	 * \sa setRenderAsXray
	 */
	virtual void setPickingEnabled(bool enabled)  = 0;


	/** 
	 * Determine if picking is enabled or disabled for the geometry
	 * \return true, if enabled, false otherwise
	 * \sa setPickingEnabled
	 */
	virtual bool isPickingEnabled() = 0;


	/**
	 * Set image from given file path as texture for the geometry.
	 *
	 * Supported formats are PNG and JPG.
	 *
	 * \param texturePath Path to the texture image file.
	 * \return true on success
	 */
	virtual bool setTexture(const stlcompat::String& texturePath) = 0;

	/**
	 * Set image from memory as texture for the geometry.
	 *
	 * \param textureName A name that should be assigned to the texture (for reuse).
	 * \param image The actual image.
	 * \param updateable Flag to signal, that this image will be frequently updated.
	 * \return true on success
	 */
	virtual bool setTexture(const stlcompat::String& textureName, const ImageStruct& image, const bool updateable = false) = 0;

	/**
	 * Set movie texture for the geometry.
	 *
	 * If the movie texture is transparent, the left side should have colored part,
	 * and right side should have alpha transparency (red channel).
	 *
	 * \param filename Filename of the movie.
	 * \param transparent If true, the movie file will be rendererd as transparent texture.
	 * \sa removeMovieTexture
	 * \return true if successful, false otherwise (e.g. file not found or not loadable).
	 */
	virtual bool setMovieTexture(const stlcompat::String& filename,
	                             const bool transparent = false) = 0;

	/**
	 * Remove the movie texture of the geometry.
	 * \sa setMovieTexture
	 */
	virtual void removeMovieTexture() = 0;

	/**
	 * Stop the playback of a movie texture.
	 * \sa startMovieTexture
	 * \sa pauseMovieTexture
	 */
	virtual void stopMovieTexture() = 0;

	/**
	 * Start the playback of a movie texture.
	 * If the movie texture was stopped, it will start from begining. If it was paused,
	 * it will resume playback from same frame.
	 * \param loop If true, the movie will play in a loop, otherwise it is played only once.
 	 * \sa pauseMovieTexture
	 * \sa stopMovieTexture
	 */
	virtual void startMovieTexture(const bool loop = false) = 0;


	/**
	 * Pause the playback of a movie texture. Call startMovieTexture to
	 * resume again.
	 * \sa startMovieTexture
	 * \sa stopMovieTexture
	 */
	virtual void pauseMovieTexture() = 0;

	/**
	 * Retrieves the current playback status and position of the movie texture.
	 *
	 * Note that the timestamp does not immediately get reset to zero when stopMovieTexture is
	 * called, so you should take playbackStatus into account.
	 *
	 
	 * \return Current playback status of the movie texture
	 * \sa metaio::MovieTextureStatus
	 */
	virtual metaio::MovieTextureStatus getMovieTextureStatus() const = 0;
	
	/** 
	 * Determine if the geometry should be displayed on the radar
	 * \return true, if it should be displayed on the radar, false otherwise
	 * \sa setRadarVisibility to set the visiblity on radar
	 */
	virtual bool getRadarVisibility() const = 0;
	
	
	/** 
	 * Define if a geometry should be displayed on the radar
	 * \param visible if false, the geometry is never displayed on
	 * the radar, else it may be displayed depending on its visibility.
	 */
	virtual void setRadarVisibility(bool visible) = 0;

};
}
#endif //__AS_IGEOMETRY_H_INCLUDED__

