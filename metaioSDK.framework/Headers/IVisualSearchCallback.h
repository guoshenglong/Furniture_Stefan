// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef __AS_VISUALSEARCH_CALLBACK__
#define __AS_VISUALSEARCH_CALLBACK__

#include <metaioSDK/MobileStructs.h>
#include <metaioSDK/STLCompatibility.h>

#include <vector>

namespace metaio
{

/**
 * Enumeration of all possible states of the visual search engine
 */
enum EVISUAL_SEARCH_STATE
{
	EVSS_IDLE = 0,				///< The visual search engine is idle and waiting for a new search request.
	EVSS_DEVICE_MOVING,			///< The device is currently moving, so we have not started the communication yet
	EVSS_SERVER_COMMUNICATION	///< The visual search request is running and it is waiting for the server response.
								///< and is checking if any of the delivered results is trackable.
};

/**
 * The Visual Search Callback Interface.
 *
 * These functions should be implemented for handling events triggered by the visual search engine.
 * \sa IMetaioSDK::registerVisualSearchCallback
 */
class IVisualSearchCallback
{
public:

	/** 
	 * Virtual destructor 
	 */
	virtual ~IVisualSearchCallback() {};

	/**
	* This method is always called after you successfully started a new visual search
	* (with IMetaioSDK::requestVisualSearch) and received the result from the server.
	*
	* \param response All found results. If response.size() > 0 the search has found something.
	* \param errorCode if > 0, then an error has occured. 
	* \sa IMetaioSDK::requestVisualSearch
	*/
	virtual void onVisualSearchResult(const stlcompat::Vector<metaio::VisualSearchResponse>& response, int errorCode) {}

	/**
	* This method is called whenever the state of the visual search engine changes
	* \param state the new state
	* \sa EVISUAL_SEARCH_STATE
	*/
	virtual void onVisualSearchStatusChanged(metaio::EVISUAL_SEARCH_STATE state) {};

private:

	/**
	 * \deprecated You must use the method signature with stlcompat::Vector instead. The other method
	 *             replaces this one!
	 */
	virtual void onVisualSearchResult(const std::vector<metaio::VisualSearchResponse>& response, int errorCode) METAIOSDK_CPP11_FINAL {}
};

}

#endif
