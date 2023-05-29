/*****************************************************************************
 * HBase.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Basic definitions for HALCON, HALCON/C, HALCON/C++
 *              and other language interfaces
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************/

#ifndef HBASE_H
#define HBASE_H

#include <stdlib.h> /* NULL */
#include "HIntDef.h"

typedef   void*   VOIDP;

/*****************************************************************************/
/* Parameter passing (Control parameters)                                    */
/*****************************************************************************/
#define UNDEF_PAR        0       /* Parameter type: no defined type          */
#define LONG_PAR         1       /* Parameter type: long                     */
#define FLOAT_PAR        2       /* Parameter type: float                    */
#define STRING_PAR       4       /* Parameter type: string                   */
#define HANDLE_PAR       16      /* Parameter type: handle (arbitrary data)  */
#define INT_PAR          LONG_PAR    /* Parameter type: int                  */
#define DOUBLE_PAR       FLOAT_PAR   /* Parameter type: double               */
#define MIXED_PAR        8           /* Parameter type: Hcpar                */
#define MAX_TUPLE_TYPE   HANDLE_PAR  /* maximum type number                  */
/* Possible parameter types for a single element: */
#define ANY_ELEM         (LONG_PAR|FLOAT_PAR|STRING_PAR|HANDLE_PAR)
/* Possible parameter types for a tuple: */
#define ANY_TUPLE        (ANY_ELEM|MIXED_PAR)
/*                       32          reserved */
#define POINTER_PAR      64        /* Parameter type: pointer to any type    */
#define TUPLE_PAR        128       /* Parameter type: pointer to tuple       */
#define MAX_PAR          HANDLE_PAR


/*****************************************************************************/
/* Constants and basic types                                                 */
/*****************************************************************************/
#define MAX_TUPLE_LENGTH 1000000   /* max. length of a tuple                 */
#define MAX_STRING       1024      /* max. length of a string                */

typedef UINT4            Herror;   /* Type function values (error messages)  */

typedef  long *Hkey;               /* primary key in DB (for iconic objects) */
#define  UNDEF_KEY   (Hkey)(0)     /* Undefined iconic object                */


/*****************************************************************************/
/* Structures for passing parameters between language interface and core     */
/*****************************************************************************/
#ifndef HC_NO_STRUCT_MEMBER_ALIGNMENT
/* sets the struct member alignment to avoid problems if
 * the settings of the user differ to those of the HALCON
 * version. (8 is the default alignment, generally) */
# pragma pack(push,8)
#endif


/*****************************************************************************/
/* HALCON procedure (operator) handle                                        */
/*****************************************************************************/
/* This data structure contains all informations about an instance of an     */
/* HALCON operator or an HALCON thread derived from an HALCON operator       */
/* instance. The contained information describes the processing context of   */
/* HALCON operators (e.g. parameter values, debugging information, etc.).    */
/*****************************************************************************/
typedef void *Hproc_handle;


/*****************************************************************************/
/* Structures, Functions and Defines for Handles                             */
/*****************************************************************************/

struct HStreamBufferT;
struct _HhandleList;

/****************************************************************************/
/** HSignalTypeEnum: List of signals that can be sent to handles
 ****************************************************************************
 * This enum defines a set of signals that can be sent to the
 * signalling callback of handles.  Note that the callback functions must
 * ignore any signal that they do not understand.
 ****************************************************************************/
typedef enum {
  eSignalNone = 0,   /**< No signal */
  eSignalStartAbort, /**< Initiate abort: stop running, abort mutexes etc. */
  eSignalAbort,      /**< Finalize abort, wait for resources to finish */
  eSignalRestore,    /**< After abortion is complete, restore mutexes etc. */
} HSignalTypeEnum;

typedef Herror (*HHandleSerializeFunc)(Hproc_handle, struct HStreamBufferT *,
                                       void *);
typedef Herror (*HHandleDeserializeFunc)(Hproc_handle, struct HStreamBufferT *,
                                         void **);
typedef Herror (*HHandleDestructorFunc)(Hproc_handle, void *);
typedef Herror (*HHandleSignalFunc)(HSignalTypeEnum signal, void *);

/****************************************************************************/
/** HHandleInfo holds handle type information.
 ****************************************************************************
 * This structure exists once per handle type (usually per sem_type).
 * It contains basic, static, constant information about that type.
 * Most notably, it contains pointers to the functions that operate on the
 * handles (clear, serialize, deserialize and signal).
 *
 * Handles (instances) of types where the cb_signal callback is not NULL are
 * stored in a list that allows calling the signal callback for each of them.
 *
 * All serialized items must have a unique header, usually a string, that
 * identifies them. 'header' contains a pointer to that header, allowing
 * other functions to identify a serialized item based on its header.
 * If no (de)serialization function is set, header must be NULL.
 *
 * \ingroup data_structures_handles
 ****************************************************************************/
typedef struct H_HANDLE_TYPE {
  INT4_8                 type_id;        /**< Type ID */
  const char *           sem_type;       /**< sem_type of the handle */
  HHandleSerializeFunc   cb_serialize;   /**< Serialize this handle type */
  HHandleDeserializeFunc cb_deserialize; /**< Deserialize this handle type */
  const char *           header;         /**< Serialization header */
  HHandleDestructorFunc  cb_clear;       /**< Clear this handle type */
  HHandleSignalFunc      cb_signal;      /**< Signal (for semaphores etc.) */
  struct _HhandleList *  list;           /**< List of handles, or NULL */
} HHandleInfo;


/****************************************************************************/
/** HANDLE_INFO_INITIALIZER: Convenience macro for initializing HHandleInfo
 ****************************************************************************/
#  define HANDLE_INFO_INITIALIZER(TYPE_ID, SEM_TYPE, FUN_SERIALIZE,           \
                                  FUN_DESERIALIZE, HEADER_STRING, FUN_CLEAR,  \
                                  FUN_SIGNAL, LIST)                           \
    {                                                                         \
      (INT4_8)(TYPE_ID), (SEM_TYPE), (HHandleSerializeFunc)(FUN_SERIALIZE),   \
          (HHandleDeserializeFunc)(FUN_DESERIALIZE), HEADER_STRING,           \
          (HHandleDestructorFunc)(FUN_CLEAR),                                 \
          (HHandleSignalFunc)(FUN_SIGNAL), (LIST)                             \
    }

/****************************************************************************/
/** HANDLE_INFO_INITIALIZER_NOSER: Convenience macro for init. HHandleInfo
 ****************************************************************************
 * Use this macro for handles that cannot be (de)serialized.
 ****************************************************************************/
#  define HANDLE_INFO_INITIALIZER_NOSER(TYPE_ID, SEM_TYPE, FUN_CLEAR,         \
                                        FUN_SIGNAL, LIST)                     \
    {                                                                         \
      (INT4_8)(TYPE_ID), (SEM_TYPE), (HHandleSerializeFunc)NULL,              \
          (HHandleDeserializeFunc)NULL, (const char *)NULL,                   \
          (HHandleDestructorFunc)(FUN_CLEAR),                                 \
          (HHandleSignalFunc)(FUN_SIGNAL), (LIST)                             \
    }

typedef struct _Hhandle *Hphandle;

typedef union
{
  INT4_8   l;             /* 4/8 byte integer                       (input)  */
  double   d;             /* 8 byte real                            (input)  */
  char     *s;            /* pointer to strings                     (input)  */
  double   f;             /* 8 byte real (legacy 11.0)              (input)  */
  Hphandle h;             /* Pointer to handle                      (input)  */
} Hpar;                   /* parameter passing for the C interface           */

typedef union
{
  INT4_8  *l;             /* 4/8 byte integer                       (output) */
  double  *d;             /* 8 byte real,                           (output) */
  char    *s;             /* pointer to strings                     (output) */
  void   *p;              /* pointer to var. of any type (e.g. tuple)(output)*/
  double  *f;             /* 8 byte real, (legacy 11.0)             (output) */
} Hvar;                   /* parameter passing for the C interface           */

typedef struct
{
  Hpar   par;             /* values                                          */
  HINT   type;            /* type flag                                       */
} Hcpar;                  /* parameter passing for the C interface           */

typedef struct
{
  Hvar   var;             /* values                                          */
  HINT   type;            /* type flag                                       */
} Hcvar;                  /* parameter passing for the C interface           */

typedef union {
  INT4_8   *l;
  double   *d;
  char     **s;
  Hcpar    *cpar;
  Hphandle *h;
} Hcelem; /* pure type array */


typedef struct HCTUPLE
{
  Hpar  val;
  HINT  type;
  /*
   * Add manual padding here so that a Hcpar can be mapped to a Hctuple exactly,
   * including the padding compilers insert at the end of data structures to
   * align the entire structure to the largest alignment of any structure
   * member. Note that on 32 bit Linux for Intel, Hcpar is aligned to 4 bytes,
   * so no manual padding is necessary on that architecture (only).
   */
#if !(defined(__linux__) && defined(__i386__))
  char   pad[sizeof(Hcpar)-sizeof(Hpar)-sizeof(HINT)];
#endif
  INT4_8 num;                   /* number of set array elements */
  INT4_8 capacity;              /* allocated array length */
  HINT  free;                   /* free array elem when destroying tuple? */
  Hcelem elem;                  /* the actual array */
} Hctuple;
#define HCTUPLE_INITIALIZER {{0},UNDEF_PAR,{0},0,0,0,{NULL}}

typedef struct
{
  Hcvar   *variables;     /* variables (of application) to write back values */
  Hcpar   *element;       /* tuple element(s)                                */
  INT4_8  num_el;         /* number of used elements                         */
  INT4_8  length;         /* total length of array (incl. unused elements)   */
} Hcvtuple;               /* for passing control parameter variables from    */
                          /* the language to the core interface              */
#ifndef HC_NO_STRUCT_MEMBER_ALIGNMENT
# pragma pack(pop)
#endif

/*****************************************************************************/
/* Bool constants                                                            */
/*****************************************************************************/
#ifdef TRUE
#undef TRUE
#endif
#define TRUE             true

#ifdef FALSE
#undef FALSE
#endif
#define FALSE            false


/*****************************************************************************/
/* Pixel types of HALCON images                                              */
/*****************************************************************************/
#define UNDEF_IMAGE   (HINT)0
#define BYTE_IMAGE    (HINT)(1<<0)
#define INT4_IMAGE    (HINT)(1<<1)
#define LONG_IMAGE    INT4_IMAGE
#define FLOAT_IMAGE   (HINT)(1<<2)
#define DIR_IMAGE     (HINT)(1<<3)
#define CYCLIC_IMAGE  (HINT)(1<<4)
#define INT1_IMAGE    (HINT)(1<<5)
/* (1<<6) omitted so far -> use it for next new image type */
#define COMPLEX_IMAGE (HINT)(1<<7)
/* (1<<8) omitted so far -> use it for next new image type */
#define INT2_IMAGE    (HINT)(1<<9)
#define UINT2_IMAGE   (HINT)(1<<10)
#define VF_IMAGE      (HINT)(1<<11)
#define INT8_IMAGE    (HINT)(1<<12)

/*****************************************************************************/
/* Type of HALCON vector field images                                        */
/*****************************************************************************/
#define VF_ABSOLUTE   (INT4)0
#define VF_RELATIVE   (INT4)(1<<0)


/*****************************************************************************/
/* data types for handling pthreads (POSIX threads) and mutex variables      */
/*****************************************************************************/
typedef void*          H_pthread_t;            /* pthread handle             */
typedef void*          H_pthread_mutex_t;      /* pthread mutex data type    */
typedef void*          H_pthread_cond_t;       /* pthread condition variable */
typedef void*          H_pthread_barrier_t;    /* pthread barrier variable */


/*****************************************************************************/
/* signature of the callback functions for drawing objects                   */
/*****************************************************************************/

#ifndef _WIN32
#define __stdcall
#endif
typedef Herror (__stdcall *HDrawObjectCallback)(Hphandle DrawHandle,
                                                Hphandle WindowHandle,
                                                char* type);

/*****************************************************************************/
/* signature of the callback functions for buffer window content updates     */
/*****************************************************************************/
typedef Herror (__stdcall *HUpdateContentCallback)(void *context);

/*****************************************************************************/
/* signature of the callback function for license recheck failure callbacks  */
/*****************************************************************************/
typedef void (__stdcall *HLicenseRecheckFailedCallback)(void *context,
                                                        Herror error);

/* A define for the restrict qualifier */
#if !defined(H_RESTRICT)
# if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
   /* Compiler is in C99 mode and should know about the restrict qualifier */
#  define H_RESTRICT restrict
# else
#  if (defined(_WIN32) && defined(_MSC_VER) && _MSC_VER >= 1400) || defined(__INTEL_COMPILER)
    /* Intel Compilers and grown-up Microsoft Compilers always know a __restrict */
#   define H_RESTRICT __restrict
#  elif (defined(__linux) || defined(__APPLE__)) && defined(__GNUC__)
    /* Gcc knows about __restrict__ since at least gcc 3.0 */
#   define H_RESTRICT __restrict__
#  elif defined(__TI_COMPILER_VERSION__)
    /* TI's cgtools know about restrict. */
#   define H_RESTRICT restrict
#  else
#   define H_RESTRICT
#  endif
# endif /* __STDC_VERSION__ */
#endif /* H_RESTRICT */


/* A define for the inline qualifier */
#if !defined(H_INLINE)
#ifdef __cplusplus
#define H_INLINE inline
#else
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* compiler is in C99 mode and should know about the inline qualifier */
#  define H_INLINE inline
#else
#if defined(_WIN32) || defined(__alpha) || defined(__sgi)
#  define H_INLINE __inline
#else
#if defined(__linux) || defined(__APPLE__)
#  define H_INLINE __inline__
#else
#if defined(__sun)
#  define H_INLINE inline
#else
#  define H_INLINE
#endif
#endif
#endif
#endif /* __STDC_VERSION__ */
#endif /* #ifdef __cplusplus .. else */
#endif /* H_INLINE */

/* A define to force functions to be inlined */
#if defined(_WIN32)
#define H_FORCEINLINE __forceinline
#elif (defined(__linux) || defined(__APPLE__)) && defined(__GNUC__)
#define H_FORCEINLINE H_INLINE __attribute__((always_inline))
#else
#define H_FORCEINLINE H_INLINE
#endif

#endif /* ifndef HBASE_H */

