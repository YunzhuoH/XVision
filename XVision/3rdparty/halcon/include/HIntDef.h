/*****************************************************************************
 * HIntDef.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Definition of HALCON data types
 *              These definitions can be controlled by the compiler
 *              The size of the data type is always in byte _not_ in bits
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************/

#ifndef HINTDEF_H
#define HINTDEF_H

#ifndef __midl
#  include <float.h>  /* FLT_MAX, DBL_MAX, ... */
#  include <limits.h> /* LONG_MAX, INT_MAX, ... */
#  include <stdlib.h> /* RAND_MAX */
#endif

#include "hclib/hclib_inttypes.h" /* C99 integer format conversion */
#include "hclib/hclib_types.h"    /* C99 standard integer types    */

typedef int HINT;           /* Signed integer. HALCON assumes at least
                               4 bytes */
typedef unsigned int HUINT; /* Unsigned integer. HALCON assumes at least
                               4 bytes */
#define HUINT_MIN 0

#ifndef _DOUBLE8
typedef double DOUBLE8;
#else
typdef _DOUBLE8 DOUBLE8;
#endif

#ifdef __vxworks
#  include <types/vxTypesBase.h>
#  ifndef DBL_MAX
#    define DBL_MAX _ARCH_DBL_MAX
#  endif
#  ifndef DBL_MIN
#    define DBL_MIN _ARCH_DBL_MIN
#  endif
#  ifndef FLT_MAX
#    define FLT_MAX _ARCH_FLT_MAX
#  endif
#  ifndef FLT_MIN
#    define FLT_MIN _ARCH_FLT_MIN
#  endif
#endif

/* float and double epsilons: These are the differences between 1 and
   the smallest floating point number of type float/double that is
   greater than 1. As we assume IEEE 754 floating point arithmetic,
   the following values are used. */
#ifndef FLT_EPSILON
#  define FLT_EPSILON 1.19209290e-07F
#endif

#ifndef DBL_EPSILON
#  define DBL_EPSILON 2.2204460492503131e-16
#endif

#ifndef RAND_MAX
#  define RAND_MAX MAXINT
#endif

typedef int8_t INT1; /* signed integer, 1 byte */
#define INT1_MIN INT8_MIN
#define INT1_MAX INT8_MAX

typedef uint8_t UINT1; /* unsigned integer, 1 byte */
#define UINT1_MIN 0
#define UINT1_MAX UINT8_MAX

typedef int16_t INT2; /* signed integer, 2 bytes */
#define INT2_MIN INT16_MIN
#define INT2_MAX INT16_MAX

typedef uint16_t UINT2; /* unsigned integer, 2 bytes */
#define UINT2_MIN 0
#define UINT2_MAX UINT16_MAX

typedef int32_t INT4; /* signed integer, 4 bytes */
#define INT4_MIN INT32_MIN
#define INT4_MAX INT32_MAX

typedef uint32_t UINT4; /* unsigned integer, 4 bytes */
#define UINT4_MIN 0
#define UINT4_MAX UINT32_MAX

/*
 * Defining HINT4_8 and UINT4_8 to be 64 bits on 64 bit systems and 32 bits on
 * 32 bit systems is a bit tricky. The obvious solution would be to use
 * intptr_t and uintptr_t, but this causes problems on platforms where
 * 'intptr_t' is ultimately derived from 'int'. Our C++ language interface has
 * overloaded functions with variants taking both 'int' and 'Hlong' parameters,
 * which is only allowed if 'int' and 'Hlong' are distinct types. Since typedef
 * does not create distinct types in C++, we must make sure 'Hlong' is
 * ultimately derived from a different type. The 'long' type nicely fits our
 * requirements, as it is 64 bits on all our supported platforms except for 64
 * bit Windows, and 32 bits on all 32 bit platforms (except for TI C6X DSPs
 * using COFF object format - which is obsolete - where it is 40 bits).
 */
#if defined(_WIN64)
typedef __int64 HINT4_8;
typedef __int64 INT4_8;
#  define INT4_8_FORMAT "I64"
#  define INT4_8_MIN _I64_MIN
#  define INT4_8_MAX _I64_MAX

typedef unsigned __int64 UINT4_8;
#  define UINT4_8_MIN 0UL
#  define UINT4_8_MAX _UI64_MAX
#  define UINT4_8_FORMAT INT4_8_FORMAT

#else
typedef long    HINT4_8;
typedef long    INT4_8;
#  define INT4_8_MIN LONG_MIN
#  define INT4_8_MAX LONG_MAX
#  define INT4_8_FORMAT "l"

typedef unsigned long UINT4_8;
#  define UINT4_8_MIN 0UL
#  define UINT4_8_MAX ULONG_MAX
#  define UINT4_8_FORMAT INT4_8_FORMAT
#endif

/* Hlong/Hulong is the same as INT4_8/UINT4_8 */
typedef INT4_8 Hlong;
#define HLONG_MIN INT4_8_MIN
#define HLONG_MAX INT4_8_MAX
#define HLONG_FORMAT INT4_8_FORMAT
#define LONG_FORMAT INT4_8_FORMAT /* deprecated, use HLONG_FORMAT     */

typedef UINT4_8 Hulong;
#define HULONG_MIN UINT4_8_MIN
#define HULONG_MAX UINT4_8_MAX

typedef int64_t HINT8; /* signed integer, 8 bytes */
#define HINT8_MIN INT64_MIN
#define HINT8_MAX INT64_MAX
#if defined(_WIN32)
#  define HINT8_FORMAT "I64"
#else
#  define HINT8_FORMAT "ll"
#endif

typedef uint64_t HUINT8; /* unsigned integer, 8 bytes */
#define HUINT8_MIN 0U
#define HUINT8_MAX UINT64_MAX

#if !defined(HC_LARGE_IMAGES)
#  define HIMGCOOR_MIN INT2_MIN
#  define HIMGCOOR_MAX INT2_MAX
#  define HITEMCNT_MIN INT4_MIN
#  define HITEMCNT_MAX INT4_MAX
#  define HSUBCOOR_MIN FLT_MIN
#  define HSUBCOOR_MAX FLT_MAX
#  define HSUBCOOR_EPS FLT_EPSILON
#  define HSUBATTR_MIN FLT_MIN
#  define HSUBATTR_MAX FLT_MAX
#else
#  define HIMGCOOR_MIN INT4_MIN
#  define HIMGCOOR_MAX INT4_MAX
#  define HITEMCNT_MIN INT4_8_MIN
#  define HITEMCNT_MAX INT4_8_MAX
#  define HSUBCOOR_MIN DBL_MIN
#  define HSUBCOOR_MAX DBL_MAX
#  define HSUBCOOR_EPS DBL_EPSILON
#  define HSUBATTR_MIN DBL_MIN
#  define HSUBATTR_MAX DBL_MAX
#endif

/*
 * Define the largest double that can be safely casted to INT4_8 without
 * turning negative.
 */
#if INT4_8_MAX == INT4_MAX
#  define INT_4_8_MAXDOUBLE (double)INT4_MAX
#else
#  define INT_4_8_MAXDOUBLE (double)(HINT8_MAX - 1023)
#endif

/* At least an address must fit into MACHINE_WORD */
typedef intptr_t MACHINE_WORD;

#endif /* !HINTDEF_H */
