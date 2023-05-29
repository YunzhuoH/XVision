/*****************************************************************************
 * HInstance.h
 *****************************************************************************
 *
 * Project:      HALCON/HLib
 * Description:  handling of HALCON operator instances and HALCON threads;
 *               provides procedural access to global context variables;
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************/


#ifndef HINSTANCE_H
#define HINSTANCE_H


#if defined(__cplusplus)
extern "C" {
#endif


#include "hlib/HInstanceDefines.h"


/* HALCON library already initialized? */
extern HLibExport HBOOL IsInitHlib(void);

/* HAccessGlVar - access to global HALCON context variables                  */
extern HLibExport Herror HAccessGlVar(Hproc_handle proc_handle, HINT element,
                                      HBYTE to_do, void* r_value,
                                      double w_value, char* w_string,
                                      Hkey w_key, INT4_8 index);

/* HWriteGlUtf8Var - write a string with encoding to the global HALCON
 * context and convert it if necessary from hlib encoding to utf-8 */
extern HLibExport Herror HWriteGlUtf8Var(Hproc_handle ph, HINT element,
                                         char const* str_hlib);

/* HReadGlUtf8Var - read a string with encoding from the global HALCON
 *  context and convert if necessary from utf-8 to hlib encoding
 *  when do_free is set to true by the called function, the result string was
 *  allocated in local memory and must be freed by the caller,
 *  if the caller passes NULL for do_free, it must always be freed */
extern HLibExport Herror HReadGlUtf8Var(Hproc_handle ph, HINT element,
                                        char** str_p, HBOOL* do_free);

/* HCheckInpObjNum - check whether specified object number is in range       */
extern HLibExport HBOOL HCheckInpObjNum(Hproc_handle proc_handle, HINT par_num,
                                        INT4_8 obj_num);
extern HLibExport HBOOL HCheckObjNum(Hproc_handle proc_handle, HINT par_num,
                                     INT4_8 obj_num);
extern HLibExport HBOOL HCheckOutpObjNum(Hproc_handle proc_handle,
                                         HINT par_num, INT4_8 obj_num);
extern HLibExport Hproc_handle HTSProcHandle(void);
extern HLibExport Hproc_handle HTSHProcIndepend(HINT op_id);

extern HLibExport void* HCreateTSPSysInfoHandle(void);
extern HLibExport Herror HPushTSPSysInfoHandle(void* handle);
extern HLibExport void*  HPopTSPSysInfoHandle(void);
extern HLibExport Herror HClearTSPSysInfoHandle(void* handle);

/* HGetHProc - get a thread specific HALCON operator call instance (no full
 * use) */
extern HLibExport Herror HGetHProc(INT4 proc_index, Hproc_handle* ph);
/* HPutHProc - return a thread specific HALCON operator call instance to Core*/
extern HLibExport Herror HPutHProc(Hproc_handle proc_handle);
/* HGetRecHProc - get a thread specific HALCON operator call instance, able
 * to handle recursive calls  (no full use)  */
extern HLibExport Herror HGetRecHProc(INT4 proc_index, Hproc_handle* ph);
/* HPutRecHProc - return a thread specific (recursiveable) HALCON operator
 * call instance */
extern HLibExport Herror HPutRecHProc(Hproc_handle proc_handle);
/* HPutRecHProcErr - return a thread specific (recursiveable) HALCON operator
 * call instance, where the operator returned with the given error */
extern HLibExport Herror HPutRecHProcErr(Hproc_handle ph, Herror err);
/* HCreateHProc - create a new HALCON operator call instance                 */
extern HLibExport Herror HCreateHProc(INT4          current_idx,
                                      Hproc_handle* proc_handle);
/* HDeleteHProc - delete a HALCON operator call instance                     */
extern HLibExport Herror HDeleteHProc(Hproc_handle proc_handle, HBOOL last,
                                      Herror proc_result);

extern HLibExport HBOOL HOpIdIsValid(HINT opid);

extern HLibExport HINT HGVGet_NumSysOp(void); /* number of system operators*/
extern HLibExport HINT HGVGet_NumOp(void);    /* total number of operators */
extern HLibExport char const* HGVGet_Language(void);
extern HLibExport HINT HGVGet_locale_filename_encoding(void);
extern HLibExport UINT4 HGVGet_parallel(void);
extern HLibExport HBOOL HGVGet_CPUFeature(HINT feature);
extern HLibExport void  HGVSet_CPUFeature(HINT feature, HBOOL value);
extern HLibExport INT4_8 HGVGet_CPUCache(HINT level);

extern HLibExport char const* HOIGet_InpCtrlParType(HINT opid);
extern HLibExport char const* HOIGet_OutpCtrlParType(HINT opid);

extern HLibExport HINT HOIGet_NumInpCtrlPar(HINT opid);
extern HLibExport HINT HOIGet_NumOutpCtrlPar(HINT opid);
extern HLibExport HINT HOIGet_NumInpObjPar(HINT opid);
extern HLibExport HINT        HOIGet_NumOutpObjPar(HINT opid);
extern HLibExport char const* HOIGet_LogicalName(HINT opid);

extern HLibExport HINT HPHGet_NumInpCtrlPar(Hproc_handle ph);
extern HLibExport HINT HPHGet_NumOutpCtrlPar(Hproc_handle ph);
extern HLibExport HINT HPHGet_NumInpObjPar(Hproc_handle ph);
extern HLibExport HINT HPHGet_NumOutpObjPar(Hproc_handle ph);
extern HLibExport INT4        HPHGet_proc_index(Hproc_handle ph);
extern HLibExport const char* HPHGet_LogicalName(Hproc_handle ph);
extern HLibExport INT4 HPHGet_check(Hproc_handle ph);
extern HLibExport INT4_8 HPHGet_PreviousMaxAlloc(Hproc_handle ph);

extern HBOOL  HGetInstanceMemCacheMode(void);
extern Herror HSetInstanceMemCacheMode(Hproc_handle ph, HBOOL mode);

/* HProcSetStop sets a stop-flag for all running operator instances
 * (asynchonously). Opertors supporting this flag will break execution and
 * return (without an error) */
extern HLibExport Herror HProcSetStop(HINT mode);

/* HProcBreak sets a beak flag for all running operator instances
 * (asynchonously) */
extern HLibExport Herror HProcBreak(void);

#if defined(__cplusplus)
}
#endif


#endif
