// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef _AS_IARELINTERPRETER_
#define _AS_IARELINTERPRETER_

#include <metaioSDK/MobileStructs.h>
#include <metaioSDK/IARELInterpreterCallback.h>
#include <metaioSDK/STLCompatibility.h>

//forward declaration
class QGraphicsWebView;
class QGraphicsScene;

namespace metaio
{

// forward declarations
class IMetaioSDK;
class IARELInterpreterIOS;
class GestureHandler;

/**
* The main Interface to AREL
*
*	AREL (Augmented Reality Experience Language) is platform indented framework based on javascript and HTML.
*	It is an extension the Mobile SDK. This interface provides functions to load a AREL scene and handle user input.
*	For for information, best see examples accompanied with the metaio SDK
*/
class METAIO_DLL_API IARELInterpreter
{

public:

	/**
	* Destructor
	*/
	virtual ~IARELInterpreter() {};


	/**
	* Update the AREL layer
	*
	*	Update should be called each render cycle, it will capture, track, render and handle other events within
	*	this loop.
	*/
	virtual void update() = 0;

	/**
	* Initialize with an existing metaio SDK
	*
	* \param metaioSDK the metaio SDK instance
	* \param pGestureHandler Pointer to the gesture handler
	*/
	virtual void initialize(metaio::IMetaioSDK* metaioSDK, metaio::GestureHandler* pGestureHandler) = 0;

	/**
	* Load a AREL file
	* \param file the filename to load
	*/
	virtual void loadARELFile(const stlcompat::String& file) = 0;

	/**
	* Load an AREL by junaio channel ID
	*
	* Note: This function is not included in the SDK release
	*
	* \param channelID the channel to load
	*/
	virtual void loadChannel(const int channelID) = 0;

	/**
	* Notify that a web page has been loaded.
	*
	*	Some platforms handle web page callbacks on application side (e.g. for Qt)
	*/
	virtual void loadFinished() = 0;

    /**
     * Set Radar properties
     *
     * \param anchor position relative to screen from metaio::IGeometry
     * \param translation metaio::Vector3d translation vector
     * \param scale metaio::Vector3d scale vector
     */
    virtual void setRadarProperties( int anchor, metaio::Vector3d translation, metaio::Vector3d scale) = 0;
    
	/**
	* Register a callback class
	*
	* \param callback the pointer to the implementation of the IARELInterpreterCallback
	*/
	virtual void registerCallback(IARELInterpreterCallback* callback) {};
};



/**
* Constructor for Qt
*
* \param webView the Qt WebView which should be used for initialization
* \return IARELInterpreter returns a reference to the newly created ARELInterpreter
*/
METAIO_DLL_API IARELInterpreter* CreateARELInterpreterQT(QGraphicsScene* scene,  QGraphicsWebView* webView);


} // end of namespace metaio




#endif
