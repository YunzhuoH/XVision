/*****************************************************************************
 * CIOFrameGrab.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Image acquisition integration interface
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 *****************************************************************************
 *
 * See also:  "Image Acquisition Integration Programmer's Manual"
 *
 *****************************************************************************
 */


#ifndef CIOFRAMEGRAB_H
#define CIOFRAMEGRAB_H

#ifndef HC_NO_FRAMEGRABBER

#  include "CIOFrameGrabDefines.h"

#  if defined(__cplusplus)
extern "C" {
#  endif

/* function for integrating image acquisition devices into the system using
   a linked interface (instead of a dynamic object accessed online) */
extern HLibExport Herror HAddFgClass(Hproc_handle proc_id, char* name,
                                     FG_INIT_FUNC init_func);

/* function for writing the interface specific default values into an
   Hcpar array */
extern HLibExport Herror HFgGetDefaults(Hproc_handle proc_id, FGClass* fgClass,
                                        Hcpar** values, HINT* numValues);

#  if defined(__cplusplus)
}
#  endif

#endif /* ifndef HC_NO_FRAMEGRABBER */

#endif /* ifndef CIOFRAMEGRAB_H */
