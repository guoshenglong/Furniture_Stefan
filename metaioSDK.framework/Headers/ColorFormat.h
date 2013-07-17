// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef _AS_COLORFORMAT_H_
#define _AS_COLORFORMAT_H_

namespace metaio
{
namespace common
{

/**
* Enumeration of the different color formats
*/
enum ECOLOR_FORMAT
{
    ECF_A1R5G5B5 = 0,	///< 16 bit color format with one alpha bit
    ECF_R5G6B5 = 1,		///< 16 bit color format.
    ECF_R8G8B8 = 2,		///< 24 bit color, no alpha channel, but 8 bit for red, green and blue.
    ECF_B8G8R8 = 3,		///< 24 bit color, no alpha channel, but 8 bit for red, green and blue.
    ECF_A8R8G8B8 = 4,	///< Default 32 bit color format. 8 bits are used for every component: red, green, blue and alpha (in this byte order).

	/**
	 The meaning is BGRA (byte order, endianness-independent).
	 */
    ECF_A8B8G8R8 = 5,
	
    /**
    YUV4:2:2(YCbCr)
    Bits 31-24	Bits 23-16	Bits 15-8	Bits 7-0
    	 V (Cr)	Y [n+1 pixel]	U (Cb)	Y [n pixel]
    */
    ECF_V8Y8U8Y8 = 6,
    ECF_V8A8U8Y8 = 7,		///< same as ECF_V8Y8U8Y8 except for second Y is used for 8bit alpha value
	ECF_YUV420SP = 8,		///< 12 bit semi-planar YUV image format (4:2:0 Yplane + UVplane)
	ECF_YV12 = 9,			///< 12 bit YV12 planar YUV image format
    ECF_GRAY = 10,			///< 8 bit gray image format
    ECF_HSV = 11,			///< HSV color format
	ECF_UNKNOWN = 999		///< unknown image format
};


}
}
#endif

