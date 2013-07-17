// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef __AS_METAIOSDK_CALLBACK__
#define __AS_METAIOSDK_CALLBACK__

#include <string>
#include <vector>
#include <metaioSDK/STLCompatibility.h>
#include <metaioSDK/TrackingValues.h>

namespace metaio
{
// forward declarations
class IGeometry;


/**
 * The metaio SDK Callback interface.
 *
 * These functions should be implemented for handling events triggered by the metaio SDK.
 */
class IMetaioSDKCallback
{
public:

	/** 
	 * Virtual destructor 
	 */
	virtual ~IMetaioSDKCallback() {};

	/**
	 * This is triggered as soon as the SDK is ready, e.g. splash screen is finished.
	 */
	virtual void onSDKReady() {};

	/**
	 * This function will be triggered, if an animation has ended
	 *
	 * \param geometry the geometry which has finished animating
	 * \param animationName the name of the just finished animation or in case of movie-playback the filename of the movie
	 */
	virtual void onAnimationEnd(metaio::IGeometry* geometry, const stlcompat::String& animationName) {};

	/**
	 * This function will be triggered, if an animation/movietexture-playback has ended
	 *
	 * \param geometry the geometry which has finished animating/movie-playback
	 * \param movieName the name of the just finished animation or in case of movie-playback the filename of the movie
	 * \return void
	 */
	virtual void onMovieEnd(metaio::IGeometry* geometry, const stlcompat::String& movieName) {};

	/**
	 * Callback that delivers the next camera image.
	 *
	 * The image will have the dimensions of the current capture resolution.
	 * To request this callback, call requestCameraFrame()
	 *
	 * \param cameraFrame the latest camera image
	 *
	 * \note you must copy the ImageStuct::buffer, if you need it for later.
	 */
	virtual void onNewCameraFrame(metaio::ImageStruct* cameraFrame) {};


	/**
	 * Callback that notifies that camera image has been saved
	 *
	 * To request this callback, call requestCameraFrame(filepath, width, height)
	 *
	 * \param filepath File path in which image is written, or empty string in case of a failure
	 *
	 */
	virtual void onCameraImageSaved(const stlcompat::String& filepath) {};

	/**
	 * Callback that delivers screenshot as new ImageStruct.
	 * The ImageStruct and its' buffer must be released by the caller.
	 * Note: This callback is called on the render thread.
	 * 
	 * \param image Screenshot image
	 * \sa IMetaioSDK::requestScreenshot
	 */
	virtual void onScreenshotImage(metaio::ImageStruct* image) {};

	/**
	 * Callback that notifies that screenshot has been saved to a file.
	 * If the screenshot is not written to a file, the filepath will be
	 * an empty string.
	 * Note: This callback is called on the render thread.
	 * 
	 * \param filepath File path where screenshot image has been written
	 * \sa IMetaioSDK::requestScreenshot
	 */
	virtual void onScreenshotSaved(const stlcompat::String& filepath) {};

	/**
	* Callback that informs new trackingValues (tracked, detected or lost)
	*
	* This is called automatically as soon as trackingValues have been updated. The vector
	* contains all the valid poses.
	* The invalid trackingValues is only returned for first frame as soon as target is lost
	* to inform this event.
	* Note that this function is called in rendering thread, thus it would block
	* rendering. It should be returned as soon as possible without any expensive
	* processing.
	*
	* \param trackingValues current tracking values
	*
	*/
	virtual void onTrackingEvent(const metaio::stlcompat::Vector<metaio::TrackingValues>& trackingValues) {};

	/**
	* Callback to notify the application about an instant tracker event
	*
	*	If "success" is true, "file" will contain a file name you either specified
	*	when starting the instant tracking or a temporarily result.
	*
	* \param success true on success
	* \param file path to the tracking configuration
	*/
	virtual void onInstantTrackingEvent(bool success, const stlcompat::String& file) {};

private:
	/**
	 * \deprecated You must use the method signature with stlcompat::String instead. The other method
	 *             replaces this one!
	 */
	virtual void onAnimationEnd(metaio::IGeometry* geometry, std::string animationName) METAIOSDK_CPP11_FINAL {};

	/**
	 * \deprecated You must use the method signature with stlcompat::String instead. The other method
	 *             replaces this one!
	 */
	virtual void onCameraImageSaved(const std::string& filepath) METAIOSDK_CPP11_FINAL {};

	/**
	 * \deprecated You must use the method signature with stlcompat::String instead. The other method
	 *             replaces this one!
	 */
	virtual void onInstantTrackingEvent(bool success, const std::string& file) METAIOSDK_CPP11_FINAL {};

	/**
	 * \deprecated You must use the method signature with stlcompat::String instead. The other method
	 *             replaces this one!
	 */
	virtual void onMovieEnd(metaio::IGeometry* geometry, std::string movieName) METAIOSDK_CPP11_FINAL {};

	/**
	 * \deprecated You must use the method signature onScreenshotSaved with stlcompat::String
	 *             instead. The other method replaces this one!
	 */
	virtual void onScreenshot(const std::string& filepath) METAIOSDK_CPP11_FINAL {};

	/**
	 * \deprecated You must use the method signature with stlcompat::Vector instead. The other method
	 *             replaces this one!
	 */
	virtual void onTrackingEvent(std::vector<metaio::TrackingValues> trackingValues) METAIOSDK_CPP11_FINAL {}
};

}

#endif
