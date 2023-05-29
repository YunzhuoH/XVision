/*****************************************************************************
 * hclib_inttypes.h
 *****************************************************************************
 *
 * Project:     HCLib
 * Description: Format conversion of integer types for HCLib
 *
 * (c) 2019-2019 by MVTec Software GmbH
 *             www.mvtec.com
 *
 * This file provides parts of C99's inttypes.h for compilers that do not
 * provide that header (i.e. MSVC prior to cl 11.0 / Visual Studio 2012).
 * Note: Visual Studio 2010 does have stdint.h but no inttypes.h.
 ****************************************************************************/
#ifndef HCLIB_INTTYPES_H_INCLUDED
#define HCLIB_INTTYPES_H_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER < 1700)

#  define PRId8 "d"
#  define PRId16 "hd"
#  define PRId32 "I32d"
#  define PRId64 "I64d"

#  define PRIu8 "u"
#  define PRIu16 "hu"
#  define PRIu32 "I32u"
#  define PRIu64 "I64u"

#  define PRIx8 "x"
#  define PRIx16 "hx"
#  define PRIx32 "I32x"
#  define PRIx64 "I64x"

#  ifdef _WIN64
#    define PRIdPTR PRId64
#    define PRIuPTR PRIu64
#    define PRIxPTR PRIx64
#  else
#    define PRIdPTR PRId32
#    define PRIuPTR PRIu32
#    define PRIxPTR PRIx32
#  endif

#else
#  include <inttypes.h>
#endif

#endif /* HCLIB_INTTYPES_H_INCLUDED */