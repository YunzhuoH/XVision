/*****************************************************************************
 * IOSpy.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Spy procedures
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 */


#ifndef IOSPY_H
#define IOSPY_H


#if defined(__cplusplus)
extern "C" {
#endif


extern HLibExport Herror IOSetSpyByEnv(Hproc_handle proc_id, char* env);

extern HLibExport Herror IOSetSpy(Hproc_handle proc_id, char const* task,
                                  Hpar const* par, HINT type);

extern HLibExport Herror IOSetSpyTime(Hproc_handle proc_id, HBOOL mode);

extern HLibExport Herror IOGetSpyTime(Hproc_handle proc_id, HBOOL* mode);

extern HLibExport Herror IOSpyDB(Hproc_handle proc_handle);

extern HLibExport Herror IOSetSpyNumPar(Hproc_handle proc_id, HINT num);

extern HLibExport Herror IOGetSpyNumPar(Hproc_handle proc_id, HINT* num);

extern HLibExport Herror IOSetSpyPredecessor(Hproc_handle proc_id,
                                             HBOOL        state);

extern HLibExport Herror IOGetSpyPredecessor(Hproc_handle proc_id,
                                             HBOOL*       state);

extern HLibExport Herror IOSpyPrintPredecessor(Hproc_handle proc_id,
                                               const char* kind, HINT pred,
                                               HINT curr);

extern HLibExport Herror IOSetSpyProcCall(Hproc_handle proc_id, HBOOL state);

extern HLibExport Herror IOGetSpyProcCall(Hproc_handle proc_id, HBOOL* state);
extern HLibExport HBOOL IOGetSpyProcCallSwitch(void);

extern HLibExport Herror IOSetSpyFile(Hproc_handle proc_handle,
                                      Hphandle     file_id);

extern HLibExport Herror IOGetSpyFile(Hproc_handle proc_handle,
                                      Hphandle*    file_id);

extern HLibExport Herror IOGetSpyProc(Hproc_handle proc_id, HBOOL* proc,
                                      HBOOL* input_ctrl, HBOOL* output_ctrl);

extern HLibExport Herror IOSetSpyProc(Hproc_handle proc_id, HBOOL proc,
                                      HBOOL input_ctrl, HBOOL output_ctrl);

extern HLibExport Herror IOSpyProcEnd(void);

extern HLibExport Herror IOSpyProc(Hproc_handle proc_id, const char* name);

extern HLibExport Herror IOSpyPar(Hproc_handle proc_handle, HINT par,
                                  HINT type, Hpar const* val, INT4_8 num,
                                  HBOOL input);

extern HLibExport Herror IOSpyCPar(Hproc_handle proc_handle, HINT par,
                                   Hcpar const* val, INT4_8 num, HBOOL input);

extern HLibExport Herror IOSpyElem(Hproc_handle proc_handle, HINT par,
                                   void const* val, INT4_8 num, HINT type,
                                   HBOOL input);

extern HLibExport Herror IOSpyCTuple(Hproc_handle proc_handle, HINT par,
                                     Hctuple const* val, HBOOL input);

extern HLibExport Herror IOSetSpyError(Hproc_handle proc_id, HBOOL state);

extern HLibExport Herror IOGetSpyError(Hproc_handle proc_id, HBOOL* state);

extern HLibExport Herror HProcessErr(const char* proc, Herror err, INT4_8 line,
                                     const char* file);

extern HLibExport void IOSpyProcCall(const char* proc, INT4_8 line,
                                     const char* file);


#if defined(__cplusplus)
}
#endif


#endif
