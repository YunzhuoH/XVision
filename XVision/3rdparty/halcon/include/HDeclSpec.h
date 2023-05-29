/*****************************************************************************
 * HDeclSpec.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Windows DLL specifications
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************/

#ifndef HALCON_DECL_SPEC_H
#define HALCON_DECL_SPEC_H

#if defined(_WIN32) && !defined (_NODLL)
/* HALCON Library: */
#  if defined(_HLibDLL)
#    define HLibExport __declspec(dllexport)
#  elif !defined(_HLibStatic)
#    define HLibExport __declspec(dllimport)
#  else
#    define HLibExport
#  endif
/* Language Interfaces: */
#  if defined(_LIntDLL)
#    define LIntExport __declspec(dllexport)
#  elif !defined(_LIntStatic)
#    define LIntExport __declspec(dllimport)
#  else
#    define LIntExport
#  endif
/* Extension Packages: */
#  define HUserExport __declspec(dllexport)
#  define HUserImport __declspec(dllimport)
#else
#  if defined(__GNUC__) && (__GNUC__ >= 4)
#    define HLibExport __attribute__ ((visibility("default")))
#    define LIntExport __attribute__ ((visibility("default")))
#    define HUserExport __attribute__ ((visibility("default")))
#  elif defined(__sun) && (defined(__SUNPRO_C) || defined(__SUNPRO_CC))
#    define HLibExport __global
#    define LIntExport __global
#    define HUserExport __global
#  else  /* Any other Unix */
#    define HLibExport
#    define LIntExport
#    define HUserExport
#  endif /* Any other Unix */
#  define HUserImport
#endif /* not _WIN32 */

#endif
