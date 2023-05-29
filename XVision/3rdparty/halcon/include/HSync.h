/*****************************************************************************
 * HSync.h
 ***************************************************************************** 
 *
 * Project:     HALCON/libhalcon
 * Description: Synchronisation macros for Windows
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************/

#ifndef _HSYNC_H

/* WIN32 */
#if defined (_WIN32)

#include <Windows.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if defined (_MAKE_H_THREAD_SAFE) && ! defined (_NODLL)
extern HLibExport CRITICAL_SECTION    csHalcon;
#define H_SYNC_ENTER_CRITICAL_SECTION EnterCriticalSection(&csHalcon);
#define H_SYNC_LEAVE_CRITICAL_SECTION LeaveCriticalSection(&csHalcon);
#define H_SYNC_CRITICAL_SECTION_DEF   CRITICAL_SECTION csHalcon;
#define H_SYNC_DEF_INT(VARIABLE)      int VARIABLE
#define H_SYNC_LEAVE_ALL_CS_LOCKS(GetNumLocks)                          \
{                                                                       \
  int idx;                                                              \
                                                                        \
  (GetNumLocks) = 0;                                                    \
  RTL_CRITICAL_SECTION *cs = (RTL_CRITICAL_SECTION *)&csHalcon;         \
                                                                        \
  /* Rem: according to the article "Break Free of Code Deadlocks in Critical \
   * Sections Under Windows" from Matt Pietrek and Russ Osterlund of MSDN,   \
   * the field OwningThread is incorrectly defined in WINNT.H. It should be  \
   * a DWORD instead of a HANDLE and it contains the thread id. */      \
  if(GetCurrentThreadId() == (DWORD)(INT4_8)(cs->OwningThread))         \
  {                                                                     \
    (GetNumLocks) = cs->RecursionCount;                                 \
    for(idx=cs->RecursionCount; idx>0; idx--)                           \
    {                                                                   \
      H_SYNC_LEAVE_CRITICAL_SECTION;                                    \
    }                                                                   \
  }                                                                     \
}

#define H_SYNC_REENTER_ALL_CS_LOCKS(NumLocks)                   \
{                                                               \
  int idx;                                                      \
  for(idx=0; idx<(NumLocks); idx++)                             \
  {                                                             \
    H_SYNC_ENTER_CRITICAL_SECTION;                              \
  }                                                             \
}

#else
#define H_SYNC_ENTER_CRITICAL_SECTION
#define H_SYNC_LEAVE_CRITICAL_SECTION
#define H_SYNC_CRITICAL_SECTION_DEF
#define H_SYNC_DEF_INT(VARIABLE)
#define H_SYNC_LEAVE_ALL_CS_LOCKS(GetNumLocks)
#define H_SYNC_REENTER_ALL_CS_LOCKS(NumLocks)
#endif

#if defined(__cplusplus)
}
#endif
#else  /* end of part WIN32 */

/* SUN Solaris, SGI-Irix, HP-UX (10.30 or higher), Linux: */
#if defined (__sgi) || defined(__sun) || defined(__linux) || \
  defined(__APPLE__)|| defined(HPPA2) || defined(__alpha) || defined(__vxworks)

#if defined(__cplusplus)
extern "C" {
#endif

#if defined (_MAKE_H_THREAD_SAFE) && ! defined (_NODLL)
#include "hlib/system/HCriticalSection.h"
#define H_SYNC_LEAVE_CRITICAL_SECTION  HLeaveCriticalSectionG();
#define H_SYNC_ENTER_CRITICAL_SECTION  HEnterCriticalSectionG();
#define H_SYNC_CRITICAL_SECTION_DEF
#define H_SYNC_DEF_INT(VARIABLE) int (VARIABLE)
#define H_SYNC_LEAVE_ALL_CS_LOCKS(GetNumLocks)                  \
{                                                               \
  GetNumLocks = 0;                                              \
  while(HLeaveCriticalSectionG()==H_MSG_OK)                     \
  {                                                             \
    GetNumLocks++;                                              \
  }                                                             \
}
#define H_SYNC_REENTER_ALL_CS_LOCKS(NumLocks)                   \
{                                                               \
  int idx;                                                      \
  for(idx=0; idx<NumLocks; idx++)                               \
  {                                                             \
    HEnterCriticalSectionG();                                   \
  }                                                             \
}

#else
#define H_SYNC_LEAVE_CRITICAL_SECTION
#define H_SYNC_ENTER_CRITICAL_SECTION
#define H_SYNC_CRITICAL_SECTION_DEF
#define H_SYNC_DEF_INT(VARIABLE)
#define H_SYNC_LEAVE_ALL_CS_LOCKS(GetNumLocks)
#define H_SYNC_REENTER_ALL_CS_LOCKS(NumLocks)
#endif

#if defined(__cplusplus)
}
#endif

/* HP-UX 9.xx  and all others: */
#else
#define H_SYNC_LEAVE_CRITICAL_SECTION
#define H_SYNC_ENTER_CRITICAL_SECTION
#define H_SYNC_CRITICAL_SECTION_DEF
#define H_SYNC_DEF_INT(VARIABLE)
#define H_SYNC_LEAVE_ALL_CS_LOCKS(GetNumLocks)
#define H_SYNC_REENTER_ALL_CS_LOCKS(NumLocks) 
#endif

#endif /* end of section: not Windows OS */

#endif /* _HSYNC_H */
