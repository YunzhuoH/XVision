/*****************************************************************************
 * HalconCpp.h
 *****************************************************************************
 *
 * Project:     HALCON/C++
 * Description: Defines / types / extern declarations for HALCON/C++ interface
 *
 * (c) 2010-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 *****************************************************************************/


#ifndef HALCON_CPP_H
#define HALCON_CPP_H


// Architecture limitations

#if !defined(HCPP_NO_INT_OVERLOADS)
#  define HCPP_INT_OVERLOADS
#endif

#if !defined(HCPP_NO_USE_IOSTREAM)
#  define HCPP_USE_IOSTREAM
#endif

// HALCON library includes
#include "Halcon.h"

// interface version
// do not define a number because it can be loaded in parallel to version 10
#define HCPP_INTERFACE_VERSION_11


// Standard C++ library includes

#ifdef HCPP_USE_IOSTREAM
#  include <iostream>
#endif


// Resolve known macro name collisions

#if defined(_WIN32)
 /* include windows.h here, as Halcon.h does not include it anymore */
#  define _WINSOCKAPI_ /* use winsock2 */
#include <Windows.h>

//
// FindText, CopyFile, CreateMutex, CreateEvent, and DeleteFile are also
// functions of the Windows API. There are defines on FindTextW, CopyFileW,
// CreateMutexW, CreateEventW, and DeleteFileW if UNICODE is defined,
// otherwise there are defines on FindTextA, CopyFileA, CreateMutexA,
// CreateMutexA, and DeleteFileA. These defines are undefined here. If you
// want to use the corresponding Windows API calls, you must use FindTextA,
// FindTextW, CopyFileA, CopyFileW, CreateMutexA, CreateMutexW, CreateEventA,
// CreateEventW, DeleteFileA, or DeleteFileW directly.
//
#undef CopyFile
#undef CreateMutex
#undef CreateEvent
#undef DeleteFile
#undef FindText
#endif

// Macro to deprecate a method
#if defined __GNUC__ &&  !defined HC_NO_LEGACY_WARNING
#  define GCC_VERSION (__GNUC__ * 10 + __GNUC_MINOR__)
#  if defined __INTEL_COMPILER || GCC_VERSION < 45
#    define HDEPRECATED( OBJ, MSG)   OBJ __attribute__ ((deprecated))
#  else
#    define HDEPRECATED( OBJ, MSG)   OBJ __attribute__ ((deprecated(MSG)))
#  endif
#elif defined(_MSC_VER)  &&  !defined HC_NO_LEGACY_WARNING
#  define HDEPRECATED( OBJ, MSG)   __declspec(deprecated(MSG)) OBJ
#else
// no mechanism implemented for this compiler
#  define HDEPRECATED( OBJ, MSG)   OBJ
#endif

#if defined(HCPP_LEGACY_API)
// Allow usage of legacy exception handler
#  define HCPP_LEGACY_EXCEPTION
#endif

// HALCON/C++ types
#include "halconcpp/HalconCppForwards.h"

// HALCON/C++ includes
#include "halconcpp/HTuple.h"
#include "halconcpp/HVector.h"
#include "halconcpp/HString.h"
#include "halconcpp/HException.h"
#include "halconcpp/HDevWindowStack.h"
#include "halconcpp/HObjectBase.h"
#include "halconcpp/HHandleBase.h"
#include "halconcpp/HHandle.h"
#include "halconcpp/HDataBase.h"
#include "halconcpp/HOperatorOverloads.h"

// Fully generated classes
#include "halconcpp/HalconCppIncludes.h"

// Include inline functions for streaming operations
#include "halconcpp/HIOStream.h"


/*****************************************************************************
 ** String Encoding for the HALCON/C++ interface
 ** This effects all char* strings used by HTuple, HString and the operators
 **---------------------------------------------------------------------------
 ** The global functions are for setting and requesting the string encoding
 ** used in the HALCON/C++ interface.
 *****************************************************************************/
namespace HalconCpp
{
  LIntExport void SetHcppInterfaceStringEncodingIsUtf8(bool is_utf8);
  LIntExport bool IsHcppInterfaceStringEncodingUtf8();
}


// Defining the following two preprocessor constants
// enables a restricted source code compatibility mode
// for procedural legacy code

// Definining HCPP_LEGACY_API provides declarations for
// Hobject and HTuple members that are

#if defined(HCPP_LEGACY_API)

// Allow to resolve obsolete class Hobject
namespace HalconCpp
{
  typedef HalconCpp::HObject Hobject;
}

// Allow to use global operator signatures with Herror return values */
#include "halconcpp/HOperatorSetLegacy.h"

// Defining HCPP_LEGACY_NAMESPACE will textually
// replace all references to the Halcon namespace with
// HalconCpp, with potential for name conflicts.

#if defined(HCPP_LEGACY_NAMESPACE)
// Remap namespace Halcon to HalconCpp
#define Halcon HalconCpp
#endif

#endif // HCPP_LEGACY_API

#endif // HALCON_CPP_H
