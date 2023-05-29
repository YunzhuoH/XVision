/*****************************************************************************
 * CORE1.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Mid level procedure interface
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *               www.mvtec.com
 *
 *****************************************************************************
 *
 *
 */

#ifndef CORE1_H
#define CORE1_H

#include "hlib/DBNew.h" /* -> DBFreeProc */

#if defined(__cplusplus)
extern "C" {
#endif

/* HPAllocStringMem - allocate memory for StringMem                          */
extern HLibExport Herror HPAllocStringMem(Hproc_handle proc_handle,
                                          size_t       size);

/* HFreeStringMem - give free memory of StringMem                            */
extern HLibExport Herror HFreeStringMem(Hproc_handle proc_handle);

/* HNoInpObj - returns TRUE, if any input object parameter is empty          */
extern HLibExport Herror HNoInpObj(Hproc_handle proc_handle, HBOOL* b);

/* HPGetObj - get key of a input object                                      */
extern HLibExport Herror HPGetObj(Hproc_handle proc_handle, HINT par_num,
                                  INT4_8 obj_num, Hkey* key);

/* HPGetOutpObj - get key of a output object */
extern HLibExport Herror HPGetOutpObj(Hproc_handle proc_handle, HINT par_num,
                                      INT4_8 obj_num, Hkey* key);


/* HPGetObjNum - get number of objects of input object parameter             */
extern HLibExport Herror HPGetObjNum(Hproc_handle proc_handle, HINT par_num,
                                     INT4_8* num);


/* HPTestObj - test, whether key specifies a valid database object           */
extern HLibExport HBOOL HPTestObj(Hkey obj);

/* HPCountTuple - count number of managed data base objects                  */
extern HLibExport Herror HPCountTuple(char* relation, INT4_8* num);

/* HPGetComp - get key of a component of an object                           */
extern HLibExport Herror HPGetComp(Hproc_handle proc_handle, Hkey obj_key,
                                   HINT comp, Hkey* key);

/* HPGetFRL - get runlength code of a region (no copy; just pointer to data) */
extern HLibExport Herror HPGetFRL(Hproc_handle proc_handle, Hkey rl_key,
                                  Hrlregion** region);

/* HPGetFRL - get runlength code of a region (region is copied!)             */
extern HLibExport Herror HPGetRL(Hproc_handle proc_handle, Hkey rl_key,
                                 Hrlregion* rl);

/* HPGetFDRL - get runlength code of a region (no copy; just pointer to data)*/
extern HLibExport Herror HPGetFDRL(Hproc_handle proc_handle, Hkey obj_key,
                                   Hrlregion** rl);

/* HPGetDRL - get chord coding of a region (region gets copied!)             */
extern HLibExport Herror HPGetDRL(Hproc_handle proc_handle, Hkey obj_key,
                                  Hrlregion* rl);

/* HPGetURL - merge all regions of an object into a new one                  */
extern HLibExport Herror HPGetURL(Hproc_handle proc_handle, HINT par_num,
                                  Hrlregion* region);

/* HPGetURLLocal - merge all regions of an object into a new one             */
extern HLibExport Herror HPGetURLLocal(Hproc_handle proc_handle, HINT par_num,
                                       Hrlregion** region);


/* HPGetCParNum - get number of values of input control parameter            */
extern HLibExport Herror HPGetCParNum(Hproc_handle proc_handle, HINT par_num,
                                      INT4_8* num);

/* HPGetPPar - get array of pointers to value structures of inp. ctrl. par.  */
extern HLibExport Herror HPGetPPar(Hproc_handle proc_handle, HINT par_num,
                                   Hcpar* H_RESTRICT* val, INT4_8* num);

/* HPGetPar - get values of input control parameter                          */
extern HLibExport Herror HPGetPar(Hproc_handle proc_handle, HINT par_num,
                                  HINT kind_in, HINT* kind, Hpar Val[],
                                  INT4_8 min, INT4_8 max, INT4_8* num);

/* HPGetCPar - get values of input control parameter                         */
extern HLibExport Herror HPGetCPar(Hproc_handle proc_handle, HINT par_num,
                                   HINT kind_in, Hcpar Val[], INT4_8 min,
                                   INT4_8 max, INT4_8* num);

/* HPPutPElem - store output control parameter values by reference           */
extern HLibExport Herror HPPutPElem(Hproc_handle proc_handle, HINT parnr,
                                    void* Val, INT4_8 num, HINT type);

/* HPPutElem - store output control parameter values by copy                 */
extern HLibExport Herror HPPutElem(Hproc_handle proc_handle, HINT parnr,
                                   void const* Val, INT4_8 num, HINT type);

/* HPPutPar - store output control parameter values                          */
extern HLibExport Herror HPPutPar(Hproc_handle proc_handle, HINT par_num,
                                  HINT kind, Hpar* Elem, INT4_8 num);

/* HPPutPPar - store output control parameter values (by using pointers)     */
extern HLibExport Herror HPPutPPar(Hproc_handle proc_handle, HINT par_num,
                                   Hcpar* Val, INT4_8 num);

/* HPPutCPar - store output control parameter values                         */
extern HLibExport Herror HPPutCPar(Hproc_handle proc_handle, HINT par_num,
                                   Hcpar* Val, INT4_8 num);

/* HPFreeAllParStrings - free all strings in parameter array                 */
extern HLibExport Herror HPFreeAllParStrings(Hproc_handle proc_handle,
                                             Hcpar* par, INT4_8 num);

/* HPPutRL - copy region into region object, return its key */
extern HLibExport Herror HPPutRL(Hproc_handle proc_handle, Hrlregion* region,
                                 Hkey* key);
/* HPPutPRL - store region into region object, return its key */
extern HLibExport Herror HPPutPRL(Hproc_handle proc_handle, Hrlregion** region,
                                  Hkey* key);

/* HPPutDRL - copy region into component object and return its region
 * object key..*/
extern HLibExport Herror HPPutDRL(Hproc_handle proc_handle, Hkey obj_key,
                                  Hrlregion* rl, Hkey* key);
/* HPPutPRLComp - store region into component object and return its region
 * object key.           */
extern HLibExport Herror HPPutPRLComp(Hproc_handle proc_handle, Hkey obj_key,
                                      Hrlregion** reg, Hkey* key);

/* HPPutRect - insert rectangular region in output object                    */
extern HLibExport Herror HPPutRect(Hproc_handle proc_handle, Hkey obj,
                                   HINT width, HINT height);

/* HPGetImage - fetch key of image object from database (including spy)      */
extern HLibExport Herror HPGetImage(Hproc_handle proc_handle, Hkey key,
                                    Himage* image);

/* HP0GetImage - fetch key of image object from database (without spy)       */
extern HLibExport Herror HP0GetImage(Hproc_handle proc_handle, Hkey key,
                                     Himage* image);

extern HLibExport Herror HPGetImageManip(Hproc_handle proc_handle, Hkey key,
                                         Himage* image);

/* HPGetImage - fetch key of image object from database (including spy)      */
extern HLibExport Herror HPGetCDImage(Hproc_handle proc_handle, Hkey key,
                                      Himage* image);

/* HP0GetImage - fetch key of image object from database (without spy)       */
extern HLibExport Herror HP0GetCDImage(Hproc_handle proc_handle, Hkey key,
                                       Himage* image);

/* HPGetDImage - fetch gray value channel of image object (without key)      */
extern HLibExport Herror HPGetDImage(Hproc_handle proc_handle, Hkey obj_key,
                                     HINT comp, Himage* image);

/* HPDelObj - delete an object                                               */
extern HLibExport Herror HPDelObj(Hproc_handle proc_handle, Hkey obj_key);

/* HCrIObj - create new image object                                         */
extern HLibExport Herror HCrIObj(Hproc_handle proc_handle, Hkey* key);

/* HPCrObj - create new image object and insert it into output object list   */
extern HLibExport Herror HPCrObj(Hproc_handle proc_handle, HINT par_num,
                                 Hkey* key);

/* HPCopyIObj - copy image object                                            */
extern HLibExport Herror HPCopyIObj(Hproc_handle proc_handle, Hkey obj_key,
                                    Hkey* tuple);

/* HPCopyObj - copy image object and insert it into output object list       */
extern HLibExport Herror HPCopyObj(Hproc_handle proc_handle, Hkey obj_key,
                                   HINT par_num, Hkey* key);

/* HPPutImage - store image data as image object in database                 */
extern HLibExport Herror HPPutImage(Hproc_handle proc_handle, Himage* image,
                                    HBOOL copy, Hkey* key);

/* HPDefObj - build up new object from already created objhects/components   */
extern HLibExport Herror HPDefObj(Hproc_handle proc_handle, Hkey obj_key,
                                  Hkey comp_key, HINT comp);

/* HPPutDImage - store image data in database and assign it to object        */
extern HLibExport Herror HPPutDImage(Hproc_handle proc_handle, Hkey obj_key,
                                     HINT comp, Himage* image, HBOOL copy,
                                     Hkey* key);

/* HPNewRegion - create new output object with copied region                 */
extern HLibExport Herror HPNewRegion(Hproc_handle proc_handle,
                                     Hrlregion*   region);

/* HPPushRegion - create new output object with defined region               */
extern HLibExport Herror HPPushRegion(Hproc_handle proc_handle,
                                      Hrlregion*   region);

/* HPPushGlobalRegion - create new output object with defined region         */
extern HLibExport Herror HPPushGlobalRegion(Hproc_handle proc_handle,
                                            Hrlregion*   region);

/* HPDupObj - duplicate object and insert it into output object list         */
extern HLibExport Herror HPDupObj(Hproc_handle proc_handle, INT4_8 obj_index);

/* HPAllSegm - loop over all components of all objects of first input par.   */
extern HLibExport Herror HPAllSegm(Hproc_handle proc_handle, INT4_8 obj_index,
                                   Hrlregion** region, Himage* images,
                                   HINT max_channels);

/* HPAllReg - loop over all region components of all obj.s of first inp. par.*/
extern HLibExport Herror HPAllReg(Hproc_handle proc_handle, INT4_8 obj_index,
                                  Hrlregion** region);

/* HPAllFilter - loop over all image obj.s of 1. inp. par. & create new obj.*/
extern HLibExport Herror HPAllFilter(Hproc_handle proc_handle,
                                     INT4_8 obj_index, Hrlregion** region,
                                     Himage* images_in, Himage* images_out,
                                     HINT max_channels);

/* HPAllFilter2 - loop over all image obj.s of 1. inp. par. & create new obj.*/
extern HLibExport Herror HPAllFilter2(Hproc_handle proc_handle,
                                      INT4_8 obj_index, Hrlregion* region,
                                      Himage* images_in1, Himage* images_in2,
                                      Himage* images_out, HINT max_channels);

/* HPNumOfChannels - check number of channels of input object                */
extern HLibExport Herror HPNumOfChannels(Hproc_handle proc_handle,
                                         HINT par_num, INT4_8 obj_num,
                                         HINT* chn_num);

/* HPCheckSingleInputObject - check if it is a single input object */
extern HLibExport Herror HPCheckSingleInputObject(Hproc_handle ph,
                                                  INT4_8       obj_num);

/* HPCrXLD - create XLD object                                               */
extern HLibExport Herror HPCrXLD(Hproc_handle proc_handle, HINT Par, void* XLD,
                                 HINT Type, Hkey* Uses, HINT NumUses,
                                 DBFreeProc free_proc, Hkey* key);

/* HPGetXLD - fetch XLD object  (in fact void **XLD)                         */
extern HLibExport Herror HPGetXLD(Hproc_handle proc_handle, Hkey Key,
                                  HINT* Type, void* XLD, Hkey** Uses,
                                  HINT* NumUses);

/* HPNumOfObjChannels - return number of defined channels of an object.      */
extern HLibExport Herror HPNumOfObjChannels(Hproc_handle proc_handle, Hkey obj,
                                            HINT* chn_num);

/* HNumOfOutpObj - return number of objects of an output object parameter    */
extern HLibExport Herror HNumOfOutpObj(Hproc_handle proc_handle, HINT par_num,
                                       HINT* outp_objs);

/* HGetInputKeyByPtr - get input object key containing ptr */
extern HLibExport Herror HGetInputKeyByPtr(Hproc_handle proc_id, void* ptr,
                                           Hkey* key);

/* HGetOutputKeyByPtr - get output object key containing ptr */
extern HLibExport Herror HGetOutputKeyByPtr(Hproc_handle proc_id, void* ptr,
                                            Hkey* key);

/* HGetInputRegionKeyByPtr - get input object key containing ptr */
extern HLibExport Herror HGetInputRegionKeyByPtr(Hproc_handle proc_id,
                                                 Hrlregion* ptr, Hkey* key);

extern HLibExport Herror HPAllocOutpCtrl(Hproc_handle ph, HINT par, HINT type,
                                         INT4_8 length,
                                         void* H_RESTRICT* elem);
#define HAllocOutpCtrl(ph, par, type, length, elem)                           \
  HPAllocOutpCtrl(ph, par, type, length, (void* H_RESTRICT*)elem)

extern HLibExport Herror HFreeOutpCtrl(Hproc_handle ph, HINT par);

extern HLibExport Herror HPReallocOutpCtrl(Hproc_handle ph, HINT par,
                                           HINT newtype, INT4_8 newlength,
                                           void* H_RESTRICT* elem);
#define HReallocOutpCtrl(ph, par, type, newlength, elem)                      \
  HPReallocOutpCtrl(ph, par, type, newlength, (void* H_RESTRICT*)elem)

extern HLibExport void HSetNumOutpCtrl(Hproc_handle ph, HINT par, INT4_8 num);

extern HLibExport void HPGetPElem(Hproc_handle ph, HINT par,
                                  void const* H_RESTRICT* elem, INT4_8* num,
                                  HINT* type);

/* definition of conversion flags to pass to convert slot of HPGetPElemx: */
/* no conversion;do only consider original element types */
#define CONV_NONE 0
#define CONV_CAST 1 /* <INT4_8>=(INT4_8)<double>; <double>=(double)<INT4_8>*/
#define CONV_IDNT 2 /* convert double->INT4_8 if double has no fraction */
#define CONV_RND 3  /* <INT4_8>=(INT4_8)(<double>+0.5) */
/* direct access input ctrl arrays */
extern HLibExport Herror HPGetPElemL(Hproc_handle ph, HINT par, HINT convert,
                                     INT4_8 const* H_RESTRICT* elem,
                                     INT4_8*                   num);
extern HLibExport Herror HPGetPElemD(Hproc_handle ph, HINT par, HINT convert,
                                     double const* H_RESTRICT* elem,
                                     INT4_8*                   num);
extern HLibExport Herror HPGetPElemS(Hproc_handle ph, HINT par, HINT convert,
                                     char const* const* H_RESTRICT* elem,
                                     INT4_8*                        num);
extern HLibExport Herror HPGetPElemH(Hproc_handle ph, HINT par,
                                     const HHandleInfo* expected_type,
                                     INT4_8 expected_num, void** elem,
                                     INT4_8* num, HBOOL alloc);

/* copy variant */
extern HLibExport Herror HPGetElemL(Hproc_handle ph, HINT par, HINT convert,
                                    HINT memtype, INT4_8* H_RESTRICT* elem,
                                    INT4_8* num);
extern HLibExport Herror HPGetElemD(Hproc_handle ph, HINT par, HINT convert,
                                    HINT memtype, double* H_RESTRICT* elem,
                                    INT4_8* num);
extern HLibExport Herror HPGetElemS(Hproc_handle ph, HINT par, HINT convert,
                                    HINT  memtype,
                                    char* H_RESTRICT* H_RESTRICT* elem,
                                    INT4_8*                       num);

/* copy variant with preallocated arrays */
extern HLibExport Herror HPCopyElemL(Hproc_handle ph, HINT par, HINT convert,
                                     INT4_8* H_RESTRICT lelem, INT4_8* num);
extern HLibExport Herror HPCopyElemD(Hproc_handle ph, HINT par, HINT convert,
                                     double* H_RESTRICT delem, INT4_8* num);
extern HLibExport Herror HPCopyElemF(Hproc_handle ph, HINT par, HINT convert,
                                     float* H_RESTRICT delem, INT4_8* num);

/* returning handles */
extern HLibExport Herror HAllocOutputHandles(Hproc_handle ph, HINT parnr,
                                             Hphandle** elem, INT4_8 num,
                                             const HHandleInfo* type);
extern HLibExport Herror HXAllocOutputHandle(Hproc_handle ph, HINT parnr,
                                             void***            elem,
                                             const HHandleInfo* type);

#if defined(__cplusplus)
}
#endif


#endif
