/*****************************************************************************
 * HpThread.h
 *****************************************************************************
 *
 * Projekt:     Halcon/libhalcon
 * Description: implements a programming interface to Posix or DCE
 *              thread-packages for different operating systems.
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *               www.mvtec.com
 *
 *****************************************************************************/

#ifndef HPTHREAD_H
#define HPTHREAD_H

#if defined(__cplusplus)
extern "C" {
#endif


/*===========================================================================*/
/*                        Prototypes of Functions                            */
/*===========================================================================*/

/* --- Thread Synchronization --------------- */
/* type of dynamically set synchronisation functions */
typedef Herror (*H_THREAD_MUTEX_FCT)(H_pthread_mutex_t* hmutex);
typedef HBOOL (*H_THREAD_MUTEX_BFCT)(H_pthread_mutex_t* hmutex);

/* general mutex                                                             */
extern HLibExport Herror HpThreadMutexInit(H_pthread_mutex_t* hmutex);
/* dynamically set synchronisation functions */
extern HLibExport H_THREAD_MUTEX_FCT HpThreadMutexLock;
extern HLibExport H_THREAD_MUTEX_FCT HpThreadMutexUnlock;
extern HLibExport H_THREAD_MUTEX_BFCT HpThreadMutexTrylock;

extern HLibExport Herror HpThreadMutexDestroy(H_pthread_mutex_t* hmutex);


/* --- Threads -------------------------------*/
/* HpThreadHandleAlloc - allocate pthread handle (identifier of pthread)     */
extern HLibExport Herror HpThreadHandleAlloc(H_pthread_t* handle);
/* HpThreadHandleFree - give pthread handle (identifier of pthread) free     */
extern HLibExport Herror HpThreadHandleFree(H_pthread_t handle);
/* HpThreadCreate - create pthread object and start pthread asynchronously   */
extern HLibExport Herror HpThreadCreate(H_pthread_t handle, void** parameters,
                                        Herror (*function)(void**));
/* HpThreadClear - frees resources allocated by HpThreadCreate  */
extern HLibExport Herror HpThreadClear(H_pthread_t handle);
/* HpThreadSelf - get calling thread's identifier (UNIX) or handle (Windows) */
extern HLibExport Herror HpThreadSelf(H_pthread_t* my_handle);
/* HpThreadSelfId - get calling thread's identifier                          */
extern HLibExport Herror HpThreadSelfId(void* thread_id);
/* HpThreadEqualToSelf - compare a thread identifier to current thread       */
extern HLibExport Herror HpThreadEqualToSelf(H_pthread_t t_handle,
                                             HINT*       result_val);
/* HpThreadJoin - wait for termination of specified pthread                  */
extern HLibExport Herror HpThreadJoin(H_pthread_t handle);
/* HpThreadDetach - detach pthread, mark the pthread object for deletion     */
extern HLibExport Herror HpThreadDetach(H_pthread_t handle);


#if defined(__cplusplus)
}
#endif

#endif
