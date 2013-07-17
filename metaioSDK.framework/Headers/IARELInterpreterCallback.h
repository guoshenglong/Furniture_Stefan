// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef _IAREL_INTERPRETER_CALLBACK_H_
#define _IAREL_INTERPRETER_CALLBACK_H_

#include <metaioSDK/ARELSceneOptions.h>
#include <metaioSDK/STLCompatibility.h>

#include <map>
#include <string>

namespace metaio
{

/**
 * Interface to receive the callbacks form the ARELInterpreter
 */
class IARELInterpreterCallback
{
public:

	/**
	* Destructor.
	*/
	virtual ~IARELInterpreterCallback() {};

	/**
	 * The implementation should play a video from a given URL
	 * \param videoURL the url to the video
	 * \return true if handled by the callback, false to use the default implementation
	 */
	virtual bool playVideo(const stlcompat::String& videoURL) { return false; }

	/**
	 * Open the URL
	 * \param url the url to the website
	 * \param openInExternalApp true to open in external app, false otherwise
	 * \return true if handled by the callback, false to use the default implementation
	 */
	virtual bool openWebsite(const stlcompat::String& url, bool openInExternalApp = false) { return false; }

	/**
	 * This is triggered as soon as the SDK is ready, e.g. splash screen is finished.
	 */
	virtual void onSDKReady() {};

	/**
	 * Called after scene options were loaded from AREL XML file (always called even if there are no
	 * scene options)
	 *
	 * \param sceneOptions map that receives options from the XML file (see ARELSceneOptions.h for
	 *                     possible keys and their values)
	 */
	virtual void onSceneOptionsParsed(const stlcompat::Vector<metaio::ARELSceneOption>& sceneOptions) {};

	/**
	 * This is triggered as soon as the AREL is ready, including the loading of XML geometries.
	 */
	virtual void onSceneReady() {};

private:
	/**
	 * \deprecated You must use the method signature with stlcompat::Vector instead. The other method
	 *             replaces this one!
	 */
	virtual void onSceneOptionsParsed(const std::map<std::string, std::string>& sceneOptions) METAIOSDK_CPP11_FINAL {};

	/**
	 * \deprecated You must use the method signature with stlcompat::String instead. The other method
	 *             replaces this one!
	 */
	virtual bool openWebsite(const std::string& url, bool openInExternalApp = false) METAIOSDK_CPP11_FINAL { return false; }

	/**
	 * \deprecated You must use the method signature with stlcompat::String instead. The other method
	 *             replaces this one!
	 */
	virtual bool playVideo(const std::string& videoURL) METAIOSDK_CPP11_FINAL { return false; }
};

}

#endif
