// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef _ARELSCENEOPTIONS_H_
#define _ARELSCENEOPTIONS_H_

#include <metaioSDK/MobileStructs.h>
#include <metaioSDK/STLCompatibility.h>

namespace metaio
{
namespace common
{

// See IARELInterpreterCallback::onSceneOptionsParsed. Note that all values are strings that have
// to be parsed according to the descriptions below.

enum EAREL_SCENE_OPTION
{
	/**
	 * Defines the desired camera index, e.g. 0 (back facing camera on mobile devices), 1 (front
	 * facing camera on mobile devices, else second camera), etc.
	 */
	EARELSO_CAMERA_INDEX = 0,

	/**
	 * Defines the desired camera resolution for capturing, e.g. "640x480"
	 */
	EARELSO_CAMERA_RESOLUTION = 1,

	/**
	 * Path to the environment map to load (directory)
	 *
	 * \sa IMetaioSDK::loadEnvironmentMap
	 */
	EARELSO_ENVIRONMENT_MAP = 2,
	
	/**
	 * Defines whether the application should run in fullscreen mode. Possible associated values:
	 * "true", "false"
	 */
	EARELSO_FULLSCREEN = 3,

	/**
	 * Defines how many frames per second the application should render, as integer string: e.g. "25"
	 */
	EARELSO_RENDER_FPS = 4
};

} // end of namespace metaio::common


struct ARELSceneOption
{
	/**
	 * Defines which option is described by the value field
	 */
	common::EAREL_SCENE_OPTION	key;

	/**
	 * Trimmed string value of the option as defined in the AREL file
	 *
	 * This must be parsed according to the type of option (e.g. integer for EARELSO_CAMERA_INDEX).
	 *
	 * \sa EAREL_SCENE_OPTION
	 */
	stlcompat::String			value;
};


} // end of namespace metaio

#endif
