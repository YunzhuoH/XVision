/*****************************************************************************
 * DBNew.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Object handling and storing in memory
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 */

#ifndef HDBNEW_H
#define HDBNEW_H


#if defined(__cplusplus)
extern "C" {
#endif

#include <stdio.h>

/*===========================================================================*/
/*                                 Defines                                   */
/*===========================================================================*/

#define DB_MAGIC_OK 1234567890
#define DB_MAGIC_REGION (DB_MAGIC_OK + REGION_ID)
#define DB_MAGIC_IMAGE (DB_MAGIC_OK + IMAGE_ID)
#define DB_MAGIC_OBJECT (DB_MAGIC_OK + OBJECT_ID)
#define DB_MAGIC_OBJECT_TUPLE (DB_MAGIC_OK + TUPLE_ID)

#define DB_MAGIC_CLEARED 1987654320
#define DB_CLEARED_REGION (DB_MAGIC_CLEARED + REGION_ID)
#define DB_CLEARED_IMAGE (DB_MAGIC_CLEARED + IMAGE_ID)
#define DB_CLEARED_OBJECT (DB_MAGIC_CLEARED + OBJECT_ID)
#define DB_CLEARED_OBJECT_TUPLE (DB_MAGIC_CLEARED + TUPLE_ID)
#define DB_MIN_CLEARED (DB_MAGIC_CLEARED + 1)
#define DB_MAX_CLEARED (DB_MAGIC_CLEARED + MAX_XLD_ID)

/*===========================================================================*/
/*                            'Global' Makros                                */
/*===========================================================================*/


/* -------- work on data identifiers --------------------------------------- */
#define DB_ID(PTR) ((INT4)(((DBImage*)PTR)->magic) - DB_MAGIC_OK)
#define DB_ERROR_ID(PTR) ((INT4)(((DBImage*)PTR)->magic) - DB_MAGIC_CLEARED)

#define DB_IS_XLD(PTR)                                                        \
  ((DB_ID(PTR) >= MIN_XLD_ID) && (DB_ID(PTR) <= MAX_XLD_ID))

/* -------- work on doubly linked lists ------------------------------------ */
/*****************************************************************************/
/* DB_INSERT - insert element in doubly linked list                          */
/*****************************************************************************/
#define DB_INSERT(ROOT, PTR, H)                                               \
  H = (ROOT)->succ;                                                           \
  if (H != NULL)                                                              \
    (H)->pred = PTR;                                                          \
  (ROOT)->succ = PTR;                                                         \
  (PTR)->succ  = H;                                                           \
  (PTR)->pred  = ROOT

/*****************************************************************************/
/* DB_REMOVE - remove element from doubly linked list                        */
/*****************************************************************************/
#define DB_REMOVE(PTR)                                                        \
  (PTR)->pred->succ = (PTR)->succ;                                            \
  if ((PTR)->succ != NULL)                                                    \
  (PTR)->succ->pred = (PTR)->pred

/*****************************************************************************/
/* HPAR_DATASIZE_XXX                         */
/*****************************************************************************/
#ifdef H_PARALLEL
#  define HPAR_DATASIZE_IMG(DOMAIN, CHANNELS, DATASIZE)                       \
    if (HTestF(DOMAIN, center_area))                                          \
    {                                                                         \
      (DATASIZE) = HGetFVal(DOMAIN, area) * (CHANNELS);                       \
    }                                                                         \
    else if (0 < (DOMAIN)->num)                                               \
    {                                                                         \
      (DATASIZE) = (CHANNELS) * (DOMAIN)->num *                               \
                   ((DOMAIN)->rl[0].ce - (DOMAIN)->rl[0].cb + 1);             \
    }                                                                         \
    else                                                                      \
    {                                                                         \
      (DATASIZE) = 0;                                                         \
    }

#  define HPAR_DATASIZE_REG(REGION, DATASIZE) (DATASIZE) = (REGION)->num;


#  define HPAR_DATASIZE_XLD(XLD, TYPE, DATASIZE)                              \
    switch (TYPE)                                                             \
    {                                                                         \
    case XLD_CONTOUR_ID:                                                      \
      (DATASIZE) = ((Hcont*)(XLD))->num;                                      \
      break;                                                                  \
    case XLD_POLYGON_ID:                                                      \
      (DATASIZE) = ((Hpoly*)(XLD))->num_line;                                 \
      break;                                                                  \
    case XLD_PARALLEL_ID:                                                     \
    case XLD_MOD_PARALLEL_ID: /* Hmod_para struct up to last2 member identic  \
                               * to Hpara_poly */                             \
    case XLD_EXT_PARALLEL_ID: /* Hext_para struct up to last2 member identic  \
                               * to Hpara_poly  */                            \
      (DATASIZE) =                                                            \
          ((Hpara_poly*)(XLD))->last1 - ((Hpara_poly*)(XLD))->first1 +        \
          ((Hpara_poly*)(XLD))->last2 - ((Hpara_poly*)(XLD))->first2 + 2;     \
      break;                                                                  \
    default:                                                                  \
      return H_ERR_XLDWT;                                                     \
    }

#  define HPAR_READ_DATASIZE_OBJ(POBJ, NUM, DATASIZE)                         \
    {                                                                         \
      UINT4_8 idx;                                                            \
      (DATASIZE) = 0;                                                         \
      if (64 > (NUM))                                                         \
      {                                                                       \
        for (idx = 0; idx < NUM; idx++)                                       \
        {                                                                     \
          (DATASIZE) += ((DBObject*)(POBJ)[idx])->datasize;                   \
        }                                                                     \
      }                                                                       \
      /* approximation for bigger object arrays ...*/                         \
      else if (256 > NUM)                                                     \
      {                                                                       \
        for (idx = 0; idx < NUM; idx += 4)                                    \
        {                                                                     \
          (DATASIZE) += (((DBObject*)(POBJ)[idx])->datasize << 2);            \
        }                                                                     \
      }                                                                       \
      else if (512 > NUM)                                                     \
      {                                                                       \
        for (idx = 0; idx < NUM; idx += 8)                                    \
        {                                                                     \
          (DATASIZE) += (((DBObject*)(POBJ)[idx])->datasize << 3);            \
        }                                                                     \
      }                                                                       \
      else                                                                    \
      {                                                                       \
        for (idx = 0; idx < NUM; idx += 16)                                   \
        {                                                                     \
          (DATASIZE) += (((DBObject*)(POBJ)[idx])->datasize << 4);            \
        }                                                                     \
      }                                                                       \
    }

#  define HPAR_READ_DATASIZE(OBJ, DATASIZE)                                   \
    switch (*(UINT4*)(OBJ))                                                   \
    { /* switch on magig number */                                            \
    case DB_MAGIC_OBJECT_TUPLE:                                               \
      HPAR_READ_DATASIZE_OBJ(((DBObjectTuple*)(OBJ))->object,                 \
                             ((DBObjectTuple*)(OBJ))->num, DATASIZE);         \
      break;                                                                  \
    default:                                                                  \
      DATASIZE = ((DBObject*)(OBJ))->datasize;                                \
      break;                                                                  \
    }


#else

#  define HPAR_DATASIZE_IMG(DOMAIN, CHANNELS, DATASIZE) (DATASIZE) = 0
#  define HPAR_DATASIZE_REG(REGION, DATASIZE) (DATASIZE) = 0
#  define HPAR_DATASIZE_XLD(XLD, TYPE, DATASIZE) (DATASIZE) = 0
#  define HPAR_READ_DATASIZE_OBJ(POBJ, NUM, DATASIZE) (DATASIZE) = 0
#  define HPAR_READ_DATASIZE(OBJ, DATASIZE) (DATASIZE) = 0

#endif


/*===========================================================================*/
/*                                Data Types                                 */
/*===========================================================================*/
#ifndef HC_NO_STRUCT_MEMBER_ALIGNMENT
/* sets the struct member alignment to avoid problems if
 * the settings of the user differ to those of the HALCON
 * version. (8 is the default alignment, generally) */
#  pragma pack(push, 8)
#endif

typedef Herror (*DBFreeProc)(Hproc_handle proc_handle, void* mem);


/*****************************************************************************/
/*                                  Regions                                  */
/*****************************************************************************/

typedef struct DB_REGION
{
  UINT4             magic;
  Hrlregion*        region;  /* region data inn runlength encoding     */
  UINT2             creator; /* operator index (see HProcInfo)         */
  INT4_8            counter; /* references > 0; if == 0 delete it      */
  H_pthread_mutex_t mutex_counter;
  struct DB_REGION* pred;
  struct DB_REGION* succ;
  DBFreeProc        clear;
  void*             list;  /* associated management list             */
  HBOOL             filed; /* is object stored in data base?         */
} DBRegion;


typedef DBRegion* DBRegionPtr;


/*****************************************************************************/
/*                                   Images                                  */
/*****************************************************************************/


#ifndef HC_NO_COMPUTE_DEVICES

/* 2d dimensions */
typedef struct
{
  HIMGDIM width;
  HIMGDIM height;
} HCDDimension;


/* linear and 2d memory size */
typedef union
{
  HCDDimension dim;
  UINT4_8      bytes;
} HCDSize;


/* compute device memory ptr */
typedef struct HCD_PTR
{
  void*           ptr;
  INT2            type;
  HINT            image_kind;
  HCDSize         size;
  void*           device_handle;
  struct HCD_PTR* next;
  struct HCD_PTR* prev;
} HCDPtrT;


typedef HCDPtrT* HCDPtr;

/* HCD_PTR::type values */
#  define HCD_BUFFER (INT2)0
#  define HCD_IMAGE (INT2)1


/* page locked host memory ptr */
typedef struct HCD_PINNED_PTR
{
  void*                  handle;
  void*                  ptr;
  UINT4_8                size;
  void*                  device_handle;
  HBOOL                  is_pinned;
  struct HCD_PINNED_PTR* next;
  struct HCD_PINNED_PTR* prev;
} HCDPinnedPtrT;

typedef HCDPinnedPtrT* HCDPinnedPtr;

/* compute devices associated function ptr types */
typedef Herror (*DeviceHandleFreeProc)(Hproc_handle proc_handle);
typedef Herror (*HImageTransferProc)(Hproc_handle, Hkey);
typedef Herror (*HImageFreeDeviceMemProc)(Hproc_handle, HCDPtr);
typedef Herror (*HImageSynchProc)(Hproc_handle, void*);
typedef Herror (*HCleanupProc)(Hproc_handle, void*);

/* identical header for all compute device handles */
#  ifdef H_PARALLEL
#    define DEVICE_HANDLE_HEADER                                              \
      INT2                 device_kind; /* e.g. COMPUTE_DEVICE_OPENCL */      \
      UINT4_8              device_id;   /* device identifier */               \
      UINT4_8              platform;                                          \
      H_pthread_mutex_t    sync_mutex;                                        \
      DeviceHandleFreeProc free_proc;                                         \
      HBOOL                asynchronous_execution;                            \
      HBOOL                alloc_pinned;                                      \
      void*                next_handle;
#  else
#    define DEVICE_HANDLE_HEADER                                              \
      INT2                 device_kind; /* e.g. COMPUTE_DEVICE_OPENCL */      \
      UINT4_8              device_id;   /* device identifier */               \
      UINT4_8              platform;                                          \
      DeviceHandleFreeProc free_proc;                                         \
      HBOOL                asynchronous_execution;                            \
      HBOOL                alloc_pinned;                                      \
      void*                next_handle;
#  endif


typedef struct
{
  DEVICE_HANDLE_HEADER
} Hdevice_handle_header;

/* macros to access Hdevice_handle_header */
#  define HCDGetDeviceKind(DEVICE_HANDLE_PTR)                                 \
    (((Hdevice_handle_header*)(DEVICE_HANDLE_PTR))->device_kind)
#  define HCDGetDeviceID(DEVICE_HANDLE_PTR)                                   \
    (((Hdevice_handle_header*)(DEVICE_HANDLE_PTR))->device_id)
#  define HCDGetDeviceFreeProc(DEVICE_HANDLE_PTR)                             \
    (((Hdevice_handle_header*)(DEVICE_HANDLE_PTR))->free_proc)
#  ifdef H_PARALLEL
#    define HCDGetDeviceSyncMutex(DEVICE_HANDLE_PTR)                          \
      (((Hdevice_handle_header*)(DEVICE_HANDLE_PTR))->sync_mutex)
#    define HGetDeviceSyncMutex(PROC_HANDLE)                                  \
      HCDGetDeviceSyncMutex(HGetGV_compute_device_handle(DEVICE_HANDLE_PTR))
#  endif


typedef struct
{
  UINT4                   state;                /* state bitfield          */
  HImageTransferProc      transfer_proc;        /* image->host transfer    */
  HImageFreeDeviceMemProc free_device_mem_proc; /* frees decvice memory    */
  HCDPtr                  device_ptr;           /* ptr to device memory    */
  void*                   event_handle;         /* device computation event*/
  HImageSynchProc         sync_proc;            /* wait for event          */
  HImageSynchProc         release_event_proc;   /* free event (no wait)    */
  HCleanupProc            cleanup_proc;         /* frees cleanup_data      */
  void*                   cleanup_data;         /* blocks to free after
                                                   computation has finished*/
  DBRegionPtr  domain;                          /* associated domain       */
  HCDPinnedPtr pinned_mem_ptr;                  /* associated pinned mem   */
} HCDImageInfo;

#endif

#ifndef HC_NO_STRUCT_MEMBER_ALIGNMENT
#  pragma pack(pop)
#endif


/* HCDImageInfo::state flags */
#define HCD_HOST_MEM_ALLOCATED (UINT4)(1 << 0)
#define HCD_DEVICE_MEM_ALLOCATED (UINT4)(1 << 1)
#define HCD_IMAGE_IN_HOST_MEM (UINT4)(1 << 2)
#define HCD_IMAGE_IN_DEVICE_MEM (UINT4)(1 << 3)
#define HCD_IMAGE_IN_IMAGE_2D (UINT4)(1 << 4)
#define HCD_HOST_IS_PINNED (UINT4)(1 << 5)
#define HCD_HAS_COMPUTE_EVENT (UINT4)(1 << 6)
#define HCD_HAS_UPLOAD_EVENT (UINT4)(1 << 7)
#define HCD_STD_FLAGS ((HCD_HOST_MEM_ALLOCATED) | (HCD_IMAGE_IN_HOST_MEM))

/* macros to access HCDImageInfo::state */
#define HCD_TEST_FLAG(KEY, FLAG) (((DBImage*)KEY)->device_data.state & FLAG)
#define HCD_SET_FLAG(KEY, FLAG) ((DBImage*)KEY)->device_data.state |= FLAG
#define HCD_UNSET_FLAG(KEY, FLAG) ((DBImage*)KEY)->device_data.state &= ~(FLAG)

/* macros to access HCDImageInfo */
#define HCD_SET_DEVICE(KEY, DEVICE)                                           \
  ((DBImage*)KEY)->device_data.device_ptr->device_kind = DEVICE;
#define HCD_SET_DEVICE_ID(KEY, DEVICE_ID)                                     \
  ((DBImage*)KEY)->device_data.device_ptr->device_id = DEVICE_ID;
#define HCD_GET_DEVICE(KEY)                                                   \
  HCDGetDeviceKind((((DBImage*)KEY)->device_data.device_ptr->device_handle))
#define HCD_GET_DEVICE_ID(KEY)                                                \
  HCDGetDeviceID((((DBImage*)KEY)->device_data.device_ptr->device_handle))
#define HCD_DEVICE_DATA(KEY) (((DBImage*)KEY)->device_data)
#define HCD_SET_PINNED_MEM_HANDLE(KEY, HANDLE)                                \
  (((DBImage*)KEY)->device_data.pinned_mem_ptr) = HANDLE;
#define HCD_GET_PINNED_MEM_HANDLE(KEY)                                        \
  (((DBImage*)KEY)->device_data.pinned_mem_ptr)

#ifndef HC_NO_STRUCT_MEMBER_ALIGNMENT
/* sets the struct member alignment to avoid problems if
 * the settings of the user differ to those of the HALCON
 * version. (8 is the default alignment, generally) */
#  pragma pack(push, 8)
#endif
typedef struct DB_IMAGE
{
  UINT4             magic;
  Himage            image;   /* image data                             */
  UINT2             creator; /* operator index (see HProcInfo)         */
  INT4_8            counter; /* references > 0; if == 0 delete it      */
  H_pthread_mutex_t mutex_counter;
  struct DB_IMAGE*  pred;
  struct DB_IMAGE*  succ;
  void*             list;  /* associated management list             */
  HBOOL             filed; /* is object stored in data base?         */
#ifndef HC_NO_COMPUTE_DEVICES
  HCDImageInfo device_data;
#endif
} DBImage;

typedef DBImage* DBImagePtr;


/*****************************************************************************/
/*                                 Objects                                   */
/*****************************************************************************/

typedef struct DB_OBJECT
{
  UINT4       magic;         /* specific magic number for tests        */
  INT4_8      datasize;      /* for AOP relevant size information      */
  DBRegion*   region;        /* pointer to region                      */
  DBImagePtr* image;         /* pointer to array of image matrices     */
                             /* (undefined components are set to NULL) */
  UINT2             num;     /* num. of gray value matrices; not fixed!*/
  UINT2             creator; /* operator index (see HProcInfo)         */
  struct DB_OBJECT* pred;
  struct DB_OBJECT* succ;
  void*             list;  /* associated management list             */
  HBOOL             filed; /* is object stored in data base?         */
} DBObject;

typedef DBObject* DBObjectPtr;


/*****************************************************************************/
/*                                 XLD                                       */
/*****************************************************************************/


typedef struct DB_XLD
{
  UINT4             magic;
  INT4_8            datasize; /* for AOP relevant size information      */
  void*             xld;      /* pointer to data                        */
  Hkey*             uses;     /* XLD objects that are used              */
  UINT2             num_uses;
  UINT2             creator; /* operator index (see HProcInfo)         */
  INT4_8            counter;
  H_pthread_mutex_t mutex_counter;
  struct DB_XLD*    pred;
  struct DB_XLD*    succ;
  DBFreeProc        clear;
  void*             list;  /* associated management list             */
  HBOOL             filed; /* is object stored in data base?         */
} DBXLD;

typedef DBXLD* DBXLDPtr;


/*****************************************************************************/
/*                             Object Tuple                                  */
/*****************************************************************************/

typedef struct DB_TUPLE
{
  UINT4            magic;   /* specific magic number for tests        */
  DBObjectPtr*     object;  /* array of pointers to DBObjects         */
  UINT4            num;     /* length of object                       */
  UINT2            creator; /* operator index (see HProcInfo)         */
  struct DB_TUPLE* pred;
  struct DB_TUPLE* succ;
  void*            list;  /* associated management list             */
  HBOOL            filed; /* is object stored in data base?         */
} DBObjectTuple;

/*****************************************************************************/
/*                Data Structure for Management Lists and Counters           */
/*****************************************************************************/
typedef struct DB_HANDLE
{
  /* singly linked object lists */
  DBObjectTuple*    DBObjectTupleRoot;       /* entry of obj. tuple list */
  DBObjectTuple*    DBObjectTupleSave;       /* memory to recycle        */
  H_pthread_mutex_t mutex_DBObjectTupleRoot; /* to lock obj. tuple list  */
  H_pthread_mutex_t mutex_DBObjectTupleSave; /* to lock recycle-list     */

  DBObject*         DBObjectRoot;       /* entry of object list     */
  DBObject*         DBObjectSave;       /* memory to recycle        */
  H_pthread_mutex_t mutex_DBObjectRoot; /* to lock object list      */
  H_pthread_mutex_t mutex_DBObjectSave; /* to lock recycle-list     */

  DBRegion*         DBRegionRoot;       /* entry of region list     */
  DBRegion*         DBRegionSave;       /* memory to recycle        */
  H_pthread_mutex_t mutex_DBRegionRoot; /* to lock region list      */
  H_pthread_mutex_t mutex_DBRegionSave; /* to lock recycle-list     */

  DBImage*          DBImageRoot;       /* Bildobjekt-Liste-Anker   */
  DBImage*          DBImageSave;       /* memory to recycle        */
  H_pthread_mutex_t mutex_DBImageRoot; /* to lock image list       */
  H_pthread_mutex_t mutex_DBImageSave; /* to lock recycle-list     */

  DBXLD*            DBXLDRoot;       /* XLD-Objekt-Liste-Anker   */
  DBXLD*            DBXLDSave;       /* memory to recycle        */
  H_pthread_mutex_t mutex_DBXLDRoot; /* to lock XLD object list  */
  H_pthread_mutex_t mutex_DBXLDSave; /* to lock recycle-list     */

  /* counters for managed objects                                            */
  INT4_8 CountObjectTuple; /* number of object tuples  */
  INT4_8 CountObject;      /* number of objects        */
  INT4_8 CountRegion;      /* number of regions        */
  INT4_8 CountImage;       /* number of image objects  */
  INT4_8 CountXLD;         /* number of XLD objects    */
  /* counter for living image objects (independent of working state of
   * HALCON data base): */
  INT4_8 NumImgObjs;

  /* mutex variables for changing an object reference pointer                */
  H_pthread_mutex_t mutex_DBRegionCount; /* lock writing to reference*/
  H_pthread_mutex_t mutex_DBImageCount;  /* counter on primary iconic*/
  H_pthread_mutex_t mutex_DBXLDCount;    /* objects                  */
} DBHandle;

typedef DBHandle* DBhandle;

#ifndef HC_NO_STRUCT_MEMBER_ALIGNMENT
#  pragma pack(pop)
#endif

/*===========================================================================*/
/*                             External Interface                            */
/*===========================================================================*/
extern HLibExport Herror HDataBaseSwitch(HBOOL db_on);
extern HLibExport Herror HDataBaseState(HBOOL* db_on);
extern HLibExport Herror HDBIsInitial(HBOOL* is_initial);
extern HLibExport Herror HNumImgObjs(INT4_8* num_img_objs);
extern HLibExport Herror DBFreeCaches(void);
extern HLibExport Herror DBInitRoots(Hproc_handle proc_handle);
extern HLibExport Herror DBInitHandle(Hproc_handle proc_handle, HBOOL shared);
extern HLibExport Herror DBCloseRoots(Hproc_handle proc_handle);
extern HLibExport Herror DBCloseHandle(Hproc_handle proc_handle);
extern HLibExport Herror DBWriteBackHandle(Hproc_handle proc_handle);
extern HLibExport void   HPrintPixelType(FILE* file, HINT kind);
extern HLibExport Herror DBSpy(FILE* file);
extern HLibExport void   DBInfoCleared(void* ptr);
extern HLibExport Herror HIsCompact(Hproc_handle proc_handle, Hkey key,
                                    HBOOL* res);
extern HLibExport Herror DBCountImage(INT4_8* num);
extern HLibExport Herror DBCountXLD(INT4_8* num);
extern HLibExport Herror DBStoreImage(Hproc_handle proc_handle, Himage* image,
                                      Hkey* id);
extern HLibExport Herror DBFetchImage(Hproc_handle proc_handle, Hkey id,
                                      Himage** image);
extern HLibExport Herror DBGetImageCreator(Hproc_handle proc_handle, Hkey obj,
                                           HINT comp, HINT* proc_num);
extern HLibExport Herror DBCountRegion(INT4_8* num);
extern HLibExport Herror DBStoreRegion(Hproc_handle proc_handle,
                                       Hrlregion* region, Hkey* id);
extern Herror DBStoreRegionLocal(Hproc_handle proc_handle, Hrlregion* region,
                                 Hkey* id);
extern HLibExport Herror DBFetchDRegion(Hproc_handle proc_handle, Hkey id,
                                        Hrlregion** region);
extern HLibExport Herror DBFetchRegion(Hproc_handle proc_handle, Hkey id,
                                       Hrlregion** region);
extern HLibExport Herror DBGetRegionCreator(Hproc_handle proc_handle, Hkey obj,
                                            HINT* proc_num);
extern HLibExport Herror DBGetObjectCreator(Hproc_handle proc_handle, Hkey obj,
                                            HINT* proc_num);
extern HLibExport Herror DBCountObject(INT4_8* num);
extern HLibExport Herror DBTestObjektID(Hkey id);
extern HLibExport Herror DBStoreObject(Hproc_handle proc_handle,
                                       Hkey region_id, Hkey* image_ids,
                                       HINT num, HBOOL copy, Hkey* id);
extern Herror     DBStoreObjectLocal(Hproc_handle proc_handle, Hkey region_id,
                                     Hkey* image_ids, HINT num, HBOOL copy,
                                     Hkey* id);
extern HLibExport Herror DBFetchObject(Hproc_handle proc_handle, Hkey id,
                                       Hkey* region_id, Hkey** image_ids,
                                       HINT* num);
extern HLibExport Herror DBCopyObject(Hproc_handle proc_handle, Hkey id,
                                      Hkey* new_id);
extern HLibExport Herror DBDelObject(Hproc_handle proc_handle, Hkey id);
extern Herror            DBDelObjectLocal(Hproc_handle proc_handle, Hkey id);
extern HLibExport Herror DBDelRegion(Hproc_handle proc_handle, DBRegion* ptr);
extern HLibExport Herror DBDelImage(Hproc_handle proc_handle, DBImage* ptr);
extern HLibExport Herror DBRetainImage(Hproc_handle proc_handle, DBImage* ptr);
extern HLibExport Herror DBRequestRegion(Hproc_handle proc_handle,
                                         DBRegion*    ptr);
extern HLibExport Herror DBObjectNewRegion(Hproc_handle proc_handle, Hkey id,
                                           Hkey region_id);
extern HLibExport Herror DBObjectNewImage(Hproc_handle proc_handle, Hkey id,
                                          Hkey image_id, HINT comp);
extern HLibExport Herror DBStoreXLD(Hproc_handle proc_handle, void* data,
                                    HINT type, Hkey* uses, INT4 num,
                                    DBFreeProc free_proc, Hkey* id);
extern HLibExport Herror DBFetchXLD(Hproc_handle proc_handle, Hkey id,
                                    HINT* type, void* data, Hkey** uses,
                                    INT4* num); /* in fact void **data */
extern HLibExport Herror DBCopyXLD(Hkey id, Hkey* new_id);
extern HLibExport Herror DBDelXLD(Hproc_handle proc_handle, Hkey id);
extern HLibExport Herror DBGetXLDCreator(Hkey obj, HINT* proc_num);
extern HLibExport Herror DBCountObjectTuple(INT4_8* num);
extern HLibExport Herror DBStoreTuple(Hproc_handle proc_handle,
                                      Hkey const* ids, INT4_8 num, Hkey* id);
extern HLibExport Herror DBFetchTuple(Hproc_handle proc_handle, Hkey id,
                                      Hkey** ids, INT4_8* num);
extern HLibExport Herror DBDelTuple(Hproc_handle proc_handle, Hkey id);
extern Herror            DBFreeObjectTuple(Hproc_handle, DBObjectTuple*);
extern HLibExport Herror DBDelObjectId(Hproc_handle proc_handle, Hkey id);
extern HLibExport Herror DBCopyObjectId(Hproc_handle proc_handle, Hkey id,
                                        Hkey* new_id);
extern HLibExport Herror DBNumImaRefs(Hkey id, INT4_8* num);
extern HLibExport Herror HGetCreator(Hproc_handle proc_handle, Hkey obj,
                                     HINT comp, HINT* proc_num);
extern HLibExport Herror DBGetRLPtr(Hproc_handle proc_handle, Hkey id,
                                    Hrlregion** rl);
extern HLibExport Herror DBGetXLDPtr(Hkey id, void** xld);

#if defined(__cplusplus)
}
#endif


#endif
