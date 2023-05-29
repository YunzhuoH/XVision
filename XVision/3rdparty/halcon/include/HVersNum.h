/*****************************************************************************
 * HVersNum.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Current version of the HALCON library
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************/

#ifndef HLIB_MAJOR_NUM
# define HLIB_MAJOR_NUM         19
#endif

#ifndef HLIB_MINOR_NUM
# define HLIB_MINOR_NUM         11
#endif

#ifndef HLIB_REVISION_NUM
# define HLIB_REVISION_NUM       0
#endif

#ifndef HLIB_BUILD_NUM
# define HLIB_BUILD_NUM          0
#endif


#ifndef HLIB_PRODUCT_VERSION
/* major_number.minor_number.maintenance_number.build_number */
# define HLIB_PRODUCT_VERSION   HVERSNUM_STR(HLIB_MAJOR_NUM) "."        \
  HVERSNUM_STR(HLIB_MINOR_NUM) "." HVERSNUM_STR(HLIB_REVISION_NUM)      \
    "." HVERSNUM_STR(HLIB_BUILD_NUM)
#endif

#ifndef HLIB_FILE_VERSION
# define HLIB_FILE_VERSION  HLIB_PRODUCT_VERSION
#endif

#if HLIB_REVISION_NUM == 0
# define HC_PROGRESS_EDITION
# define HALCON_PRODUCT_NAME "HALCON Progress Edition"
#else
# define HALCON_PRODUCT_NAME "HALCON Steady Edition"
#endif

/* --- Derived version numbers (with according helper macros) --- */
#ifndef HVERSNUM_STR
# define HVERSNUM_STR(S) HVERSNUM_STRX(S)
# define HVERSNUM_STRX(S) #S
#endif

#ifndef HVERSNUM_GLUE
# define HVERSNUM_GLUE(A,B)  HVERSNUM_GLUEX(A,B)
# define HVERSNUM_GLUEX(A,B) A ## B
#endif

#ifndef HLIB_VERSION
# define HLIB_VERSION       HVERSNUM_STR(HLIB_MAJOR_NUM) "." HVERSNUM_STR(HLIB_MINOR_NUM)
#endif

#ifndef HLIB_HEX_VERSION
# define HLIB_HEX_VERSION    (((HLIB_MAJOR_NUM)<<8) + ((HLIB_MINOR_NUM)<<0))
#endif

#ifndef HLIB_VERSION_NUM
/* deprecated: */
# define HLIB_VERSION_NUM        HVERSNUM_GLUE(HLIB_MAJOR_NUM,HVERSNUM_GLUE(.,HLIB_MINOR_NUM))
#endif


#ifndef HLIB_REVISION
# if HLIB_REVISION_NUM > 0
#  define HLIB_REVISION         HVERSNUM_STR(HLIB_REVISION_NUM)
# else

#  define HLIB_REVISION         ""
# endif
#endif


#ifndef HALCON_VERSION
# define HALCON_VERSION(major,minor,revision)   \
  HALCON_VERSIONX(major,minor,revision)
# define HALCON_VERSIONX(major,minor,revision)  \
  (((major)<<16) + ((minor)<<8) + (revision))
#endif

#ifndef HALCON_VERSION_CODE
# define HALCON_VERSION_CODE  HALCON_VERSION(HLIB_MAJOR_NUM,HLIB_MINOR_NUM,\
                                             HLIB_REVISION_NUM)
#endif
