/*****************************************************************************
 * CIOIIDeviceDefines.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Defines for the integration interface for IO Devices
 *
 * (c) 2013-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 *****************************************************************************/

#ifndef CIO_IIDEVICE_DEFINES_H
#define CIO_IIDEVICE_DEFINES_H

#ifndef HC_NO_IOIINTERFACE

#  define HIOII_VERSION 1300

#  define HIOGET_IOII_VERSION(IOI_VERSION) ((IOI_VERSION) >> 16)
#  define HIOGET_IOII_HMAJOR(IOI_VERSION)                                     \
    (HIOGET_IOII_VERSION(IOI_VERSION) / 100)
#  define HIOGET_IOII_HMINOR(IOI_VERSION)                                     \
    (HIOGET_IOII_VERSION(IOI_VERSION) % 100)
#  define HIOGET_IOI_REVISION(IOI_VERSION) (((IOI_VERSION) >> 8) & 0xFF)
#  define HIOGET_IOI_BUILD(IOI_VERSION) ((IOI_VERSION)&0xFF)
#  define HIOI_VERSION(IOI_REVISION, IOI_BUILD)                               \
    (((HIOII_VERSION) << 16) | ((IOI_REVISION) << 8) | (IOI_BUILD))

#  if !defined HIOI_PREFIX
#    if defined H_PARALLEL
#      define HIOI_PREFIX "hio"
#    else
#      define HIOI_PREFIX "seqhio"
#    endif
#  endif

#  if !defined HIOI_SUFFIX
#    if defined HC_LARGE_IMAGES
#      define HIOI_SUFFIX "xl"
#    else
#      define HIOI_SUFFIX ""
#    endif
#  endif


#  if defined(__cplusplus)
extern "C" {
#  endif

#  ifndef HC_NO_STRUCT_MEMBER_ALIGNMENT
/* sets the struct member alignment to avoid problems if
 * the settings of the user differ to those of the HALCON
 * version. (8 is the default alignment, generally) */
#    pragma pack(push, 8)
#  endif

/* HIOInstance holds the general data of a (virtual) device instance */
typedef struct _HIOInstance
{
  struct _HIOClass* ioclass;    /* backward reference to the interface
                                 * class handle */
  char* H_RESTRICT name;        /* name of opened device */
  void*            iochnl_list; /* list of opened device channels */
  void* H_RESTRICT usrinst;     /* holds the device specific data, set by
                                 * the device interface. */
} HIOInstance;

/* HIOChannel holds the general data of a (virtual) channel */
typedef struct _HIOChannel
{
  char* H_RESTRICT     name;   /* name of opened channels */
  struct _HIOInstance* ioinst; /* backward reference to the interface
                                * device instance */
  void* H_RESTRICT usrchnl;    /* holds the channel specific data, set by
                                * the device interface. */
} HIOChannel;

/* HIOClass holds the class information of a io device interface */
typedef struct _HIOClass
{
  /* -------------------------- internal ---------------------------------- */
  char*    interface_name;    /* name of io class                           */
  void*    lib_handle;        /* handle of interface library                */
  INT4     interface_version; /* current HALCON io device interface version */
  INT4     flags;             /* interface flags                            */
  void*    ioinst_list;       /* list of instantiated device interfaces     */
  Hphandle handle;            /* pointer to (shared) HALCON handle          */
  HBOOL    keep_open;         /* If true, do not close the interface if no  */
                              /* instances are open.                        */
  /* ----------------- interface-specific functions ----------------------- */
  Herror (*Cleanup)(Hproc_handle ph, struct _HIOClass* ioclass);
  Herror (*QueryInterface)(Hproc_handle ph);
  Herror (*OpenDevice)(Hproc_handle ph, HIOInstance* const* ioinst,
                       INT4_8* inst_num);
  Herror (*CloseDevice)(Hproc_handle ph, HIOInstance* const* ioinst,
                        INT4_8 inst_num);
  Herror (*SetDeviceParam)(Hproc_handle ph, HIOInstance* H_RESTRICT ioinst);
  Herror (*GetDeviceParam)(Hproc_handle ph, HIOInstance const* ioinst);
  Herror (*QueryDevice)(Hproc_handle ph, HIOInstance const* ioinst);
  Herror (*OpenChannel)(Hproc_handle ph, HIOInstance const* ioinst,
                        HIOChannel* const* iochnls, INT4_8* chnlnum);
  Herror (*CloseChannel)(Hproc_handle ph, HIOChannel* const* iochnls,
                         INT4_8 chnlnum);
  Herror (*SetChannelParam)(Hproc_handle ph, HIOChannel* const* iochnls,
                            INT4_8 chnlnum);
  Herror (*GetChannelParam)(Hproc_handle ph, HIOChannel const* const* iochnls,
                            INT4_8 chnlnum);
  Herror (*ReadChannel)(Hproc_handle ph, HIOChannel const* const* iochnls,
                        INT4_8 chnlnum);
  Herror (*WriteChannel)(Hproc_handle ph, HIOChannel* const* iochnls,
                         INT4_8 chnlnum);

  /* These are optional */
  Herror (*ControlInterface)(Hproc_handle ph);
  Herror (*ControlDevice)(Hproc_handle ph, HIOInstance const* ioinst);
  Herror (*ControlChannel)(Hproc_handle ph, HIOChannel* const* iochnls,
                           INT4_8 chnlnum);
} HIOClass;


typedef Herror (*HIOI_INIT_FUNC)(Hproc_handle, HIOClass*);
#  define HIOI_INIT_NAME "HIOIInit"
#  define HIOI_FLAGS_NAME "HIOIFlags"

/*
 * Special IO interface flags. Tp set the flags, the interface should export
 * the symbol HIOI_FLAGS_NAME, which must be an INT4.
 *
 * The following flags are defined:
 *
 * HIO_FLAG_THREAD_INIT: if set, the interface cleanup function is called
 * from the same thread as the init function.
 */
#  define HIO_FLAG_THREAD_INIT (1 << 0)

#  ifndef HC_NO_STRUCT_MEMBER_ALIGNMENT
#    pragma pack(pop)
#  endif


#  if defined(__cplusplus)
}
#  endif


#endif /* ifndef HC_NO_IOIINTERFACE */

#endif /* ifndef CIO_IIDEVICE_DEFINES_H */
