/*****************************************************************************
 * hclib_types.h
 *****************************************************************************
 *
 * Project:     HCLib
 * Description: Type definitions for HCLib
 *
 * (c) 2019-2019 by MVTec Software GmbH
 *             www.mvtec.com
 *
 * This file provides parts of C99's stdint.h and stdbool.h for compilers that
 * do not provide those headers (i.e. MSVC prior to cl 10.0 / Visual Studio 2010
 * for stdint.h, and MSVC prior to cl 12.0 / Visual Studio 2013 for stdbool.h)
 *
 * Note: if you are using a version of MSVC that does not provide stdint.h or
 * stdbool.h and have definitions of these types from some other header, define
 * the preprocessor macro EXTERNAL_STDINT_TYPES and/or EXTERNAL_STDBOOL_TYPES
 * to supress the definitions in this header. However, in this case you must
 * ensure that the external types have the exact same sizes as those defined
 * here to ensure ABI compatibility.
 ****************************************************************************/
/*
 * For some bizarre reason clang-format does not recognize the construct
 * below as an include guard for this file only, so turn clang-format off.
 */
/* clang-format off */
#ifndef HCLIB_TYPES_H_INCLUDED
#define HCLIB_TYPES_H_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER < 1600)
#  ifndef EXTERNAL_STDINT_TYPES
typedef __int8           int8_t;
typedef __int16          int16_t;
typedef __int32          int32_t;
typedef __int64          int64_t;
typedef unsigned __int8  uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

/* Get the minimum and maximum integral types from the limits.h header */
#    include <limits.h>
#    define INT8_MIN SCHAR_MIN
#    define INT8_MAX SCHAR_MAX
#    define INT16_MIN SHRT_MIN
#    define INT16_MAX SHRT_MAX
#    define INT32_MIN INT_MIN
#    define INT32_MAX INT_MAX
#    define INT64_MIN LLONG_MIN
#    define INT64_MAX LLONG_MAX

#    define UINT8_MAX UCHAR_MAX
#    define UINT16_MAX USHRT_MAX
#    define UINT32_MAX UINT_MAX
#    define UINT64_MAX ULLONG_MAX

#    ifdef _WIN64
typedef __int64          intptr_t;
typedef unsigned __int64 uintptr_t;
typedef __int64          intmax_t;
typedef unsigned __int64 uintmax_t;
#      define INTPTR_MIN LLONG_MIN
#      define INTPTR_MAX LLONG_MAX
#      define UINTPTR_MAX ULLONG_MAX
#    else
typedef __int32          intptr_t;
typedef unsigned __int32 uintptr_t;
typedef __int32          intmax_t;
typedef unsigned __int32 uintmax_t;
#      define INTPTR_MIN INT_MIN
#      define INTPTR_MAX INT_MAX
#      define UINTPTR_MAX UINT_MAX
#    endif
#  endif
#else
#  include <stdint.h>
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1800)
#  ifndef EXTERNAL_STDBOOL_TYPES
#    ifndef __cplusplus
       /*
        * The MSVC compiler treats 'bool' as a reserved keyword in C code,
        * even though it does not define it as a type. As a result, use the
        * preprocessor to #define 'bool' instead.
        */
#      define bool char
#      define true 1
#      define false 0
#    endif
#  endif
#else
#  include <stdbool.h>
#endif

#endif /* !HCLIB_TYPES_H_INCLUDED */
