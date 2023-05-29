/*****************************************************************************
 * HMessageQueue.h
 *****************************************************************************
 *
 * Projekt:     Halcon/libhalcon
 * Description: implements a programming interface to HALCONs Message Queues.
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *               www.mvtec.com
 *
 *****************************************************************************/

#ifndef HMESSAGEQUEUE_H
#define HMESSAGEQUEUE_H

#if defined(__cplusplus)
extern "C" {
#endif


/* Message data structure typedef pushed to the header
 * to allow use from the message-queue unit. */
typedef struct H_MESSAGE_DATA  h_message_data_t;
typedef struct H_MESSAGE_QUEUE h_message_queue_t;

/* Helper struct used to encapsulate the object tuple which is passed
 * through operator interface as a simple Hkey array.
 * Analogy to Hctuple for control data tuples... */
typedef struct HOTUPLE
{
  INT4_8 num;
  Hkey*  objects;
  HBOOL  owns_objects;
} Hotuple;


/*
 * Functions exported for use by e.g. extension packages. This should probably
 * go into its own header file.
 */

extern HLibExport Herror HotCreate(Hproc_handle proc_handle,
                                   Hotuple** obj_tuple, INT4_8 num_obj,
                                   const Hkey* objects, HINT memtype);
extern HLibExport Herror HotClear(Hproc_handle proc_handle,
                                  Hotuple*     obj_tuple);

extern HLibExport Herror HDestroyMessageData(Hproc_handle      proc_handle,
                                             h_message_data_t* msg_data);
extern HLibExport Herror HAllocMessageData(Hproc_handle       proc_handle,
                                           h_message_data_t** pmsg_data);
extern HLibExport Herror HSetMessageDataTuple(Hproc_handle      proc_handle,
                                              h_message_data_t* msg_data,
                                              char const*       key,
                                              Hctuple const*    ctrl_tuple);
extern HLibExport Herror HSetMessageDataObject(Hproc_handle      proc_handle,
                                               h_message_data_t* msg_data,
                                               char const*       key,
                                               Hotuple const*    ctrl_tuple);
extern HLibExport Herror HQueueMessageData(Hproc_handle proc_handle,
                                           Hphandle     queue,
                                           h_message_data_t* const* msgs,
                                           INT4_8                   num_msgs);
extern HLibExport HBOOL HIsMessageQueue(Hphandle handle);


#if defined(__cplusplus)
}
#endif

#endif /* HMESSAGEQUEUE_H */
