/*****************************************************************************
 * HalconCOM.h
 ***************************************************************************** 
 *
 * Project:     HALCON/COM
 * Description: Defines, types, and declarations for HALCON/COM,
 *              required for building COM extension packages
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *               www.mvtec.com 
 * 
 *****************************************************************************/

#ifndef HALCON_COM_H
#define HALCON_COM_H

#include <windows.h>
#include "HIntDef.h"
#include "HBase.h"
#include "HDeclSpec.h"
#include "HConst.h"
#include "IPType.h"
#include "HCtype.h"

/* FindText, CreateMutex, CreateEvent, and DeleteFile are also functions of
 * the Windows API. They are defines on FindTextW, CreateMutexW, CreateEventW,
 * and DelteFileW if UNICODE is defined, otherwise they are defines on
 * FindTextA, CreateMutexA, CreateMutexA, and DeleteFileA.
 * These defines are undefined here. If you want to use the corresponding
 * Windows API calls, you must use FindTextA, FindTextW, CreateMutexA,
 * CreateMutexW, CreateEventA, CreateEventW, DeleteFileA, or DeleteFileW
 * directly. */
#undef FindText
#undef CreateMutex
#undef CreateEvent
#undef DeleteFile

/* Error codes */

#define HALCONX_ERR_BASE (0x80040000UL + 2048UL)
#define HALCONX_COMINT_ERR_BASE (0x80040000UL + 1024UL)

#define HXC_WRONG_INTERFACE (HALCONX_COMINT_ERR_BASE + 1UL)
#define HXC_CANT_ACCESS_HANDLE (HALCONX_COMINT_ERR_BASE + 2UL)
#define HXC_SRC_OBJECT_NOT_INITIALIZED (HALCONX_COMINT_ERR_BASE + 3UL)
#define HXC_TUPLE_CONVERSION_ERROR (HALCONX_COMINT_ERR_BASE + 4UL)
#define HXC_NULL_POINTER (HALCONX_COMINT_ERR_BASE + 5UL)

#ifndef HALCON_C_H

typedef Hkey     Hobject;     /* ID of iconic HALCON objects    */

typedef struct                /* Tuple representation           */
{
  Hcpar   *tuple;
  INT_PTR length;
} Htuple;

#define UNDEF_TYPE  (-1)      /* Uninitialized tuple type       */

#endif

#ifdef __cplusplus
extern "C" {
#endif


/* Prototypes of interface functions */

extern LIntExport char *HMessage_COMInt(Herror message) ;

extern LIntExport Herror 
HcomPreCall(INT proc_index, Hproc_handle *proc_handle);

extern LIntExport Herror 
HcomCall(Hproc_handle proc_handle);

extern LIntExport Herror 
HcomPostCall(Hproc_handle proc_handle,Herror err);

extern LIntExport Herror 
HcomStoreIO(Hproc_handle proc_handle,INT par,Hobject inObjVar);

extern LIntExport Herror 
HcomStoreICL(Hproc_handle proc_handle,INT par,Hlong value);

extern LIntExport Herror 
HcomStoreICD(Hproc_handle proc_handle,INT par,double value);

extern LIntExport Herror 
HcomStoreICT(Hproc_handle proc_handle,INT par,Htuple value);

extern LIntExport Herror 
HcomStoreICTOOL(Hproc_handle proc_handle, INT par, Htuple value);

extern LIntExport Herror 
HcomStoreOO(Hproc_handle proc_handle,INT par,Hobject *outObjVar,Herror err);

extern LIntExport Herror 
HcomStoreOCL(Hproc_handle proc_handle,INT par, Hlong *outCtrlVar,Herror err);

extern LIntExport Herror 
HcomStoreOCD(Hproc_handle proc_handle,INT par,double *outCtrlVar,Herror err);

extern LIntExport Herror 
HcomStoreOCT(Hproc_handle proc_handle,INT par,Htuple *outCtrlVar,Herror err);

extern LIntExport Herror 
HcomStoreOCTOOL(Hproc_handle proc_handle, INT par, Htuple *outCtrlVar, 
                Herror err);

/* Higher level signatures based on COM types */

extern LIntExport Herror 
HcomStoreIOHandleAccess(Hproc_handle proc_handle, INT par, 
                        CComQIPtr<IHandleAccess, &IID_IHandleAccess> piha);

extern LIntExport Herror 
HcomStoreOOHandleAccess(Hproc_handle proc_handle, INT par, 
                       CComQIPtr<IHandleAccess, &IID_IHandleAccess> piha,
                       Herror errorStatus);

extern LIntExport Herror 
HcomStoreITOOLHandleAccess(Hproc_handle proc_handle, INT par, 
                           CComQIPtr<IHandleAccess, &IID_IHandleAccess> piha);

extern LIntExport Herror 
HcomStoreOTOOLHandleAccess(Hproc_handle proc_handle, INT par,
                           CComQIPtr<IHandleAccess, &IID_IHandleAccess> piha,
                           Herror errorStatus);

extern LIntExport Herror 
HcomStoreICV(Hproc_handle proc_handle, INT par, VARIANT value);

extern LIntExport Herror 
HcomStoreOCV(Hproc_handle proc_handle, INT par, VARIANT *value, Herror err);

extern LIntExport Herror 
HcomStoreICBSTR(Hproc_handle proc_handle, INT par, BSTR value);

extern LIntExport Herror 
HcomStoreOCBSTR(Hproc_handle proc_handle, INT par, BSTR *value, Herror err);


#ifdef __cplusplus
}
#endif


/* Conversions between tuples and COM data types */

#define VARCONVERT varconvert
#define TUPLECONVERT tupleconvert

extern LIntExport 
void varconvert(Htuple *dest, const INT_PTR arg, const char *par_name);

extern LIntExport 
void varconvert(Htuple *dest, const double arg, const char *par_name);

extern LIntExport 
void varconvert(Htuple *dest, const BSTR arg, const char *par_name);

extern LIntExport 
void varconvert(Hctuple *dest, const BSTR arg, const char *par_name);

extern LIntExport 
void varconvert(Htuple *dest, const VARIANT &arg, const char *par_name);

extern LIntExport 
void varconvert(Hctuple *dest, const VARIANT &arg, const char *par_name);

extern LIntExport 
void tupleconvert(Htuple &val, INT_PTR *lVal, char *par_name);

extern LIntExport 
void tupleconvert(Htuple &val, VARIANT_BOOL *bVal, char *par_name);

extern LIntExport 
void tupleconvert(Htuple &val, double *dVal, char *par_name);

extern LIntExport 
void tupleconvert(Htuple &val, BSTR *bstrVal, char *par_name);

extern LIntExport 
void tupleconvert(Hctuple *val, BSTR *bstrVal, char *par_name);

extern LIntExport 
void tupleconvert(Htuple &val, VARIANT *varVal, char *par_name);

extern LIntExport 
void tupleconvert(Hctuple *val, VARIANT *varVal, char *par_name);

class ConversionException
{
public:
  char *msg;
  ConversionException(char *m)
  {
    msg = ::new char [strlen(m)+1];
    strcpy(msg, m);
  }
  ConversionException(const ConversionException &src)
  {
    msg = ::new char [strlen(src.msg)+1];
    strcpy(msg, src.msg);
  }
  ~ConversionException(void)
  {
    delete [] msg;
  }
};

/* Macros for storing object parameters */

#define HCOMSTOREIO(INDEX,NAME) \
  if (NAME == NULL) \
    errorStatus = HXC_NULL_POINTER - HALCONX_ERR_BASE; \
  else \
  { \
    CComQIPtr<IHandleAccess, &IID_IHandleAccess> piha(NAME); \
    errorStatus = HcomStoreIOHandleAccess(ph,INDEX,piha); \
  }

#ifndef HALCON_COM_INTERNAL_H

#define HCOMSTOREOO(INDEX,NAME,TYPE) \
  CComQIPtr<I##TYPE, &IID_I##TYPE> p##NAME;                             \
  p##NAME.CoCreateInstance(L"HalconX." L#TYPE);                         \
  CComQIPtr<IHandleAccess, &IID_IHandleAccess> pi##NAME(p##NAME);       \
  errorStatus = HcomStoreOOHandleAccess(ph,INDEX,pi##NAME,errorStatus); \
  p##NAME->QueryInterface(IID_I##TYPE, (void**)NAME)

#endif

#endif
