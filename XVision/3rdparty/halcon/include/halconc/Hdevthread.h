/*****************************************************************************
 * Hdevthread.h
 *****************************************************************************
 *
 * Project:     HALCON/C
 * Description: generic HALCON/C thread interface for hdevelop's HALCON/C
 *              export (for internal use only, signatures and functionality 
 *              may change )
 *
 * (c) 2014-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 ****************************************************************************/

#ifndef HDEVTHREAD_H
#define HDEVTHREAD_H

#if defined(__cplusplus)
extern "C" {
#endif

typedef Hlong Hdevthread;
typedef Hlong Hdevthread_context;
#define HDEVTHREAD_UNDEF          0
#define HDEVTHREAD_CONTEXT_UNDEF  0

/**************************************************************************
 * HALCON/C Hdevthread interface
 * This interface is for HDevelop C-Export only!
 **************************************************************************/

/* A thread context marks for the started thread the period the father
 * (=caller) thread stays within the function in which the thread was
 * started. This period is equivalent to the period the output parameters of
 * procedure started within a thread are valid. I.e., a thread has to be
 * joined in the function where it was started if the output parameters
 * should be used.
 * The procedure that is starting a thread has to call create_hdevthread_context
 * after entering (at least before starting the first thread).
 * clear_hdevthread_contex must be called before leaving the calling procedure,
 * but at least after the last join call within this procedure (if present).
 */
LIntExport Herror
create_hdevthread_context( Hdevthread_context *H_RESTRICT context_handle);
LIntExport Herror
clear_hdevthread_context( Hdevthread_context context_handle);

/* create_hdevthread allocates and initializes a HALCON/C thread handle
 * 'hthread_handle'. This handle will hold the input and output parameters
 * of the procedure that should be called as thread. Therefore, the basic
 * address of this procedure is passed in 'proc' (arbitrary sequence of
 * input/output HALCON/C types, return type void). Accordingly, the total
 * number of input object parameters (iop_num), output object parameters
 * (oop_num), input vector parameters (ivp_num), output vector parameters
 * (ovp_num), input control parameters (icp_num) and output control
 * parameters (ocp_num) of the procedure is passed. The thread instance will
 * be owned  by the started thread and needn't be cleared by the calling
 * thread. */
LIntExport Herror
create_hdevthread( Hdevthread_context const context_handle, void const *proc,
                   Hlong ip_num, Hlong op_num,
                   Hdevthread *H_RESTRICT hthread_handle);

/* exit thread is called at the end of the thread's execution and clears
 * the hthread handle. */
LIntExport Herror
exit_hdevthread( Hdevthread hthread_handle);

/* clear_hdevthread frees all data hold by the hthread handle. Generally,
 * it will be called by exit_hdevthread implicitly and needn't be called
 * explicitly. */
LIntExport Herror
clear_hdevthread( Hdevthread hthread_handle);

/* -------------------------------------------------------------------
 * Functions to set the input/output parameters of the procedure 'proc'
 * within the father thread before starting the new (child) thread:
 * -------------------------------------------------------------------*/
/* set_hdevthread_iop sets a input object parameter of the procedure that should
 * be started as a thread. The object parameter
 * is copied (lazy copy). parpos denotes the x-th occurrence of an input
 * object parameter within the signature of proc, starting with 0.*/
LIntExport Herror
set_hdevthread_iop( Hdevthread hthread_handle, Hlong parpos, Hobject const obj);

/* set_hdevthread_oop sets a reference on a output object parameter of the
 * procedure that should be started as a thread. parpos denotes the x-th
 * occurrence of an output object parameter within the signature of proc,
 * starting with 0.*/
LIntExport Herror
bind_hdevthread_oop( Hdevthread hthread_handle, Hlong parpos, HBOOL glb_flag,
                     Hobject *obj);

/* set_hdevthread_ivp sets a input vector parameter (Hvector) of the procedure
 * that should be started as a thread. The input parameter is copied
 * (deep copy). parpos denotes the x-th occurrence of the input vector
 * parameter within the signature of proc, starting with 0.*/
LIntExport Herror
set_hdevthread_ivp( Hdevthread hthread_handle, Hlong parpos, 
                    Hvector const vector);

/* set_hdevthread_ovp sets the reference on a output vector parameter (Hvector*)
 * of the procedure that should be started as a thread. If a sub vector
 * should be set, the reference of the original vector is passed in  vector,
 * the indices of the sub vector are passed in vec_idx.
 * parpos denotes the x-th occurrence of the output vector
 * parameter within the signature of proc, starting with 0.*/
LIntExport Herror
bind_hdevthread_ovp( Hdevthread hthread_handle, Hlong parpos, HBOOL glb_flag,
                     Hvector *vector, Htuple const vec_idx);

/* set_hdevthread_icp sets a input control parameter (Htuple) of the procedure
 * that should be started as a thread. The control parameter is copied
 * (deep copy). parpos denotes the x-th occurrence of the input
 * control parameter within the signature of proc, starting with 0.*/
LIntExport Herror
set_hdevthread_icp( Hdevthread hthread_handle, Hlong parpos,
                    Htuple const tpl);

/* bind_hdevthread_ocp sets a reference on a output control parameter (Htuple*)
 * of the procedure that should be started as a thread.
 * parpos denotes the x-th
 * occurrence of an output control parameter within the signature of proc,
 * starting with 0.*/
LIntExport Herror
bind_hdevthread_ocp( Hdevthread hthread_handle, Hlong parpos, HBOOL glb_flag,
                     Htuple *H_RESTRICT tpl);

/* -------------------------------------------------------------------
 * Functions to set the input/output parameters of the procedure 'proc'
 * within the child thread:
 * -------------------------------------------------------------------*/
/* get_hdevthread_iop returns a reference on the copied object set with
 * set_hdevthread_iop. */
LIntExport Herror
get_hdevthread_iop( Hdevthread const hthread_handle, Hlong parpos,
                    Hobject *H_RESTRICT* obj);

/* overwrite_hdevthread_oop writes back the output object parameter on the
 * reference passed in set_hdevthread_oop. */
LIntExport Herror
store_hdevthread_oop( Hdevthread hthread_handle,Hlong parpos,Hobject const obj);

/* get_hdevthread_ivp returns a reference on the copied vector parameter
 * set with set_hdevthread_ivp. */
LIntExport Herror
get_hdevthread_ivp( Hdevthread const hthread_handle,
                    Hlong parpos, Hvector *H_RESTRICT* vec);

/* store_hdevthread_ovp writes back the output (sub) vector parameter
 * (generated with create_hdevthread_ovp) on the reference passed in
 * set_hdevthread_ovp. */
LIntExport Herror
store_hdevthread_ovp( Hdevthread hthread_handle, Hlong parpos,
                      Hvector const vector);

/* get_hdevthread_icp returns a reference on the copied tuple control parameter
 * set with set_hdevthread_icp. */
LIntExport Herror
get_hdevthread_icp( Hdevthread const hthread_handle,
                    Hlong parpos, Htuple *H_RESTRICT* tpl);

/* store_hdevthread_ocp writes back the output control parameter on the
 * reference passed in set_hdevthread_ocp. */
LIntExport Herror
store_hdevthread_ocp( Hdevthread hthread_handle, Hlong parpos,
		      Htuple const tpl);

/* start_hdevthread is called by the father thread to start the thread after
 * the parameters are set. Contrary to par_start_hdevthread, start_hdevthread can
 * be used when no thread has to join with the started thread. No thread id
 * is returned, therefore.
 * Attention: Different to HDevelop, the child thread must not run anymore
 * when exiting the program or unloading the HALCON library. Violating this
 * rule might lead to a segmentation fault on exit/unload,
 *  especially on unix systems. */
LIntExport Herror
start_hdevthread( Hdevthread const hthread_handle);

/* par_start_hdevthread is called by the father thread to start the thread after
 * the parameters are set. Contrary to start_thread, a thread id (par_handle)
 * is returned that can be used by par_join to wait for the started thread
 * exiting.
 * Attention: Different to HDevelop, the child thread must not run anymore
 * when exiting the program or unloading the HALCON library. Violating this
 * rule might lead to a segmentation fault on exit/unload,
 *  especially on unix systems. */
LIntExport Herror
par_start_hdevthread( Hdevthread const hthread_handle,
                      Htuple *H_RESTRICT par_handle);

/* call_hdevthread_proc calls the procedure specified in create_hdevthread
 * synchronously. This must be used for synchronous procedure calls, when
 * the procedure was started as thread with the same output parameters within
 *  the same hthread context.  */
LIntExport Herror
call_hdevthread_proc( Hdevthread const hthread_handle);

/* T_par_join_hdevthread waits until all threads addressed by their thread id in
 * par_handle finished. */
LIntExport Herror
T_par_join_hdevthread( Htuple const par_handles);

#if defined(__cplusplus)
}
#endif

#endif
