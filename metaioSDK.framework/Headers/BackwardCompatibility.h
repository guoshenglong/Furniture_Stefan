// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef __AS_BACKWARDCOMPATIBILITY_H_INCLUDED__
#define __AS_BACKWARDCOMPATIBILITY_H_INCLUDED__

// You may define either of the following in your project to change C++11 behavior:
// - #define METAIOSDK_COMPAT_NO_CPP11
//   in order to not use any C++11 features. You don't have to explicitly define this if your
//   compiler doesn't support C++11 at all.
// - #define METAIOSDK_COMPAT_NO_CPP11_STL_FEATURES
//   to disable usage of new STL features like std::move. Use this if you only want to use C++11
//   syntax features like override/final (for checking backward compatibility), but not library
//   features of C++11 (e.g. if you're still linking against an old standard library).

// Use C++11 features if available for move semantics and to check backward compatibility problems.
// Unfortunately, with C++ standards before 2011, private virtual methods can be overridden and thus
// there is no way to find out whether you're overriding a deprecated function.
#if !defined(METAIOSDK_COMPAT_NO_CPP11) && ( (defined(__cplusplus) && __cplusplus >= 201103L) || (defined(_MSC_VER) && _MSC_VER >= 1600) )
	#define METAIOSDK_COMPAT_HAVE_CPP11

	#define METAIOSDK_CPP11_OVERRIDE override

	#if defined(_MSC_VER) && _MSC_VER < 1700
		// Pre Visual Studio 2012
		#define METAIOSDK_CPP11_FINAL sealed
	#else
		#define METAIOSDK_CPP11_FINAL final
	#endif

	// Visual Studio 2010 complains about use of override/sealed keyword with
	// "warning C4481: nonstandard extension used: override specifier 'override'"
	#if defined(_MSC_VER)
		#pragma warning(disable:4481)
	#endif
#else
	#define METAIOSDK_CPP11_OVERRIDE
	#define METAIOSDK_CPP11_FINAL
#endif

#endif //__AS_BACKWARDCOMPATIBILITY_H_INCLUDED__
