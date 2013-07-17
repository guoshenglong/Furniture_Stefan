// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef __AS_I_AUDIOCALLBACK__
#define __AS_I_AUDIOCALLBACK__

#include <metaioSDK/MobileStructs.h>

namespace metaio
{
// forward declarations
class IGeometry;

/**
* The metaio SDK Audio Callback interface.
*
* These functions should be implemented for handling events triggered by the SDK.
*/
class IAudioCallback
{
public:

	/**
	* \brief Destructor
	*/
	virtual ~IAudioCallback() {};

	/**
	* \brief New audio sample arrived
	* \param soundBuffer struct containing the audio buffer
	*/
	virtual void onAudioSample(metaio::ByteBuffer* soundBuffer) = 0;

	/**
	* \brief Audio playback should be paused
	*/
	virtual void onAudioPause() = 0;

	/**
	* \brief Audio playback should continue (after pause)
	*/
	virtual void onAudioRestart() = 0;

	/**
	* \brief Audio playback should be stopped and all cached samples removed
	*/
	virtual void onAudioStop() = 0;

};


}


#endif