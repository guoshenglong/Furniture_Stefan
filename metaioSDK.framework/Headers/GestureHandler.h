// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef __GESTURE_HANDLER_H__
#define __GESTURE_HANDLER_H__

#include <metaioSDK/IMetaioSDK.h>
#include <metaioSDK/GeometryExtension.h>
#include <metaioSDK/IGestureHandlerCallback.h>
#include <metaioSDK/STLCompatibility.h>

namespace metaio
{

/**
 * GestureHandler base class, the applications should use platform specific
 * implementations, i.e. GestureHandlerAndroid or GestureHandlerIOS
 */
class METAIO_DLL_API GestureHandler 
{
    // a vector of GeometryExtension objects that contain the geometries and their states
    stlcompat::Vector<GeometryExtension*> m_geometryExt;
    
    // Pointer to the metaio SDK instance
    metaio::IMetaioSDK* m_pMetaioSDK;
    
    // Gestures that are enabled.
    int m_gesturesEnabled;
    
    // Whether the geometries can be controlled individually
    bool m_singleControl;
    
    // Rotation axis that is enabled.
    char m_rotationAxis;
    
	// callback pointer to the class
	IGestureHandlerCallback* m_pCallback;

	// Gesture state
	EGESTURE_STATE m_currentGestureState;

public:

	static const int GESTURE_NONE =		0<<0;		///< No gesture flag
    static const int GESTURE_DRAG =		1<<0;		///< Drag gesture flag
    static const int GESTURE_ROTATE =	1<<1;		///< Rotate gesture flag
    static const int GESTURE_PINCH =	1<<2;		///< Pinch gesture flag
    static const int GESTURE_ALL =		0xFF;		///< All gestures flag
    

    /**
     * Create new gesture handler by specifying gestures to enable.
	 *
     * \param metaioSDK metaio SDK instance
     * \param gestureMask Gesture mask to enable gestures
	 * \sa GESTURE_DRAG
     * \sa GESTURE_ROTATE
     * \sa GESTURE_PINCH
     * \sa GESTURE_ALL
     */
    GestureHandler(metaio::IMetaioSDK* metaioSDK, int gestureMask = GESTURE_ALL);
    
    
    /**
     * Destructor for the class.
     */
    ~GestureHandler();

    
	/**
     * Register callback for the gesture handler
	 * \param callback An implementation of metaio::IGestureHandlerCallback
	 * \sa metaio::IGestureHandlerCallback
     */
	void registerCallback(metaio::IGestureHandlerCallback* callback );
    

	/**
     * Enable gestures that should be handled.
     * \param gestureMask Gestures that should be enabled.
	 * \sa getGestures
	 * \sa GESTURE_NONE
	 * \sa GESTURE_DRAG
     * \sa GESTURE_ROTATE
     * \sa GESTURE_PINCH
     * \sa GESTURE_ALL
     */
    void enableGestures(int gestureMask);

    /**
     * Get the gestures that are enabled.
     * \return Gesture mask
	 * \sa enableGestures
	 * \sa GESTURE_NONE
	 * \sa GESTURE_DRAG
     * \sa GESTURE_ROTATE
     * \sa GESTURE_PINCH
     * \sa GESTURE_ALL
     */
    int getGestures();
    
	/**
     * Specify if the geometries can be controlled individually.
     * \param singleControl True if can be controlled individually, false otherwise.
	 * \sa getSingleControl
     */
    void enableSingleControl(bool singleControl);
    
    /**
     * Test if the geometries can be controlled individually.
     * \return True if geometries are controlled individually, false otherwise.
	 * \sa enablePickability
     */
    bool getSingleControl();
    
	/**
     * Set the rotation axis that the rotation gesture applies to.
     * \param axis axis that should be enabled, i.e. 'x', 'y' or 'z' (default).
	 * \sa getRotationAxis
     */
    void setRotationAxis(char axis);

    /**
     * Get the rotation axis that rotation gestures can be applied to.
     * \return The rotation axis that is enabled, i.e. 'x', 'y' or 'z'
	 * \sa setRotationAxis
     */
    char getRotationAxis();
    
    /**
     * Add an object to the gesture handler with an option to group them.
     * \param geometry A pointer to the geometry to be added.
     * \param group The group which geometry should belong to.
	 * \sa removeObject, removeObjects
	 * \sa getAllObjects
     */
    void addObject(metaio::IGeometry* geometry, int group);
    

	/**
     * Remove an object from the gesture handler.
     * \param geometry The geometry to be removed.
	 * \sa addObject
	 * \sa getAllObjects
     */
    void removeObject(metaio::IGeometry* geometry);
	
	/**
     * Remove all objects from gesture handler.
     */
    void removeObjects();

	/**
     * Reset all objects to not selected.
     */
    void resetSelected();
	
	/** 
	 * Get a list of objects added to the gesture handler.
	 * \return A vector of geometries
	 * \sa addObject
	 */
	stlcompat::Vector<metaio::IGeometry*> getAllObjects();

    
    /**
     * Select all the objects in the same group and record their initial states.
     * \param group The group number of the selected object.
     * \param x The x coordinate of the touch point.
     * \param y The y coordinate of the touch point.
     */
    void selectAllObjectsInGroup(int group, int x, int y);
    
    
    /**
     * Select all the objects record their initial states.
     * \param x The x coordinate of the touch point.
     * \param y The y coordinate of the touch point.
     */
    void selectAllObjects(int x, int y);
    
    
    /**
     * Go through the vector to select all touched objects if they are controlled individually, and select all objects if they are not.
     * \param x The x coordinate of the touch point.
     * \param y The y coordinate of the touch point.
     */
    void touchesBegan(int x, int y);
    
    
    /**
     * Move all the objects if they are selected.
     * \param x The x coordinate of the touch point.
     * \param y The y coordinate of the touch point.
     */
    void touchesMoved(int x, int y);
    
    
    /**
     * Reset all the objects in the vector to not selected.
     * \param x The x coordinate of the touch point.
     * \param y The y coordinate of the touch point.
     */
    void touchesEnded(int x, int y);
    
    
    /**
     * Go through the vector to change the scale of the geometries if they are selected.
     * \param scale The new scale of the geometry.
     */
    void handlePinchGesture(float scale);
    
    
    /**
     * Go through the vector to change the rotation of the geometries if they are selected.
     * \param rotation The new rotation that should be applied to the axis.
     */
    void handleRotateGesture(float rotation);
	
	
	/**
	 * Set the metaio SDK.
	 * \param metaioSDK Pointer to the metaio SDK instance.
	 */
	void setSDK( metaio::IMetaioSDK* metaioSDK );

};

} // namespace metaio

#endif // defined(__GESTURE_HANDLER_H__)

