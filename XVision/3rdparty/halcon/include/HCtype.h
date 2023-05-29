/*****************************************************************************
 * HCtype.h
 *****************************************************************************
 *
 * Project:      HALCON/libhalcon
 * Description:  (Global) data structures defining the processing context
 *               for HALCON operator instances and HALCON operator threads
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *               www.mvtec.com
 *
 *****************************************************************************/

#ifndef HCTYPE_H
#define HCTYPE_H

#include "HErrorDef.h" /* -> H_MSG_OK */
#include "IPType.h" /* -> HBOOL */

#if defined(__cplusplus)
extern "C" {
#endif


#ifndef HC_NO_STRUCT_MEMBER_ALIGNMENT 
/* sets the struct member alignment to avoid problems if 
 * the settings of the user differ to those of the HALCON
 * version. (8 is the default alignment, generally) */
# pragma pack(push,8) 
#endif

/*---------------------------------------------------------------------------
 * aop_split_t defines CORE-AOP levels 
 *---------------------------------------------------------------------------*/
typedef enum {split_tuple=0, split_channel, split_domain, split_num} 
  aop_split_t;


/*---------------------------------------------------------------------------*/
/* ATTENTION! Increase H_OPERATOR_INFO_VERSION/DERIVATE whenever you change
 *            or add operator info identifyers
 *            The version number is composed as follows:
 *            Version#32 := [Major#8 Minor#8 OptionalInfo16]
 *            whereas major#8 denotes a 1 byte coded mojor version number,
 *            Minor#8 denotes a 1 byte coded minor version number,
 *            OptionalInfo16 denotes a 16 bit coded bitfield of optional coded
 *            operator information 
 *---------------------------------------------------------------------------*/
#define H_OPERATOR_INFO_VERSION  0x0400  /* 4.0 */

#ifndef HC_NO_COMPUTE_DEVICES
# define HOI_COMPUTE_DEVICES (1<<0)  /* Bit0: information for compute device
                                      * support available */
#else
# define HOI_COMPUTE_DEVICES 0
#endif

#define H_OPERATOR_INFO_DERIVATE ( (H_OPERATOR_INFO_VERSION<<16) |  \
                                   HOI_COMPUTE_DEVICES)

/* HALCON operator info identifyers: */
#define HOIID_NumInpObjPar        0
#define HOIID_NumOutpObjPar       1
#define HOIID_NumInpCtrlPar       2
#define HOIID_NumOutpCtrlPar      3
#define HOIID_LogicalName         4
#define HOIID_PhysicalName        5
#define HOIID_ParameterName       6
#define HOIID_ParameterType       7   /* [2] */
#define HOIID_process_excl_local  8 
#define HOIID_parallelization     9
#define HOIID_splitIOPmask       10   /*[split_num]*/
#define HOIID_tupleIOPmask       11   /*[split_num]*/
#define HOIID_splitIOPref        12   /*[split_num]*/
#define HOIID_RegionPost         13
#define HOIID_ParameterCosts     14   /*[MAX_INP_CTRL_PAR]*/
#define HOIID_ParameterPost      15   /*[MAX_OUTP_CTRL_PAR]*/
#define HOIID_aopCost            16
#define HOIID_numCost            17
#define HOIID_parallelMinCosts   18
#define HOIID_parallelRegionsplit 19
#define HOIID_HelpIndex          20
#define HOIID_InfoLength         21
#define HOIID_Class              22   /*[MAX_CHAPTER]*/
#define HOIID_ClassName          23   /*[MAX_CHAPTER]*/
#define HOIID_package_id         24

/* --- compute devices: */
#define HOIID_compute_device     25
#define HOIID_cd_supported_image_kinds 26
#define HOIID_cd_supported_values 27
#define HOIID_cd_supported_values_num 28

#define HOIID_procedure          50
#define HOIID_module             51


/*---------------------------------------------------------------------------
 * HXPkgOpenId initializes extension package structures and checks 
 * compatibility.
 *---------------------------------------------------------------------------*/
extern HLibExport Herror HXPkgOpenId( INT4 xpkg_id, UINT4 halcon_version, 
                                      UINT4 opinfo_version,
                                      HINT op_num, HINT *osid);

/*---------------------------------------------------------------------------
 * HXPkgSetOpInfo sets operator information of a specific extension package 
 * operator.
 *---------------------------------------------------------------------------*/
extern HLibExport Herror HXPkgSetOpInfo( INT4 xpkg_id, INT4 op_id, 
                                         INT4 oi_id, ...);


/*---------------------------------------------------------------------------*/
/* H_OPERATOR_PARAMETERS - data structure that contains the operator
 * parameters passed to the language interface. This information is only valid
 * for the processing time of the associated instance/HALCON thread.
 * All read/write accesses to the information are done exclusively
 * (thus different HALCON threads of the same instance differ in the
 * content of this structure).
 *---------------------------------------------------------------------------*/
typedef struct 
{
  /*-------------------------------- operator parameters --------------------*/
  /*______________________________________________input object parameters:___*/
  Hkey    *InpObjList[MAX_INP_OBJ_PAR+1]; /* for every input object par      *
                                           * an array of object keys         */
  Hkey    InpObjSingle[MAX_INP_OBJ_PAR+1]; /* used, when the array of obj 
                                            * keys has size 1                */
  INT4_8  InpObjNum[MAX_INP_OBJ_PAR+1];  /* number of objects per input obj. *
                                          * parameter; index: 1..inp_obj     */
  INT1    freeIOP[MAX_INP_OBJ_PAR+1];
  
  /*_____________________________________________input control parameters:___*/
  Hctuple **InpCtrlList;  /* used to access inp. ctrl handles */
  Hctuple *InpCtrlStack[MAX_INP_CTRL_PAR];/* stores interf./Single references*/
  Hctuple InpCtrlNested[MAX_INP_CTRL_PAR]; /* holds tuple trunks, eg for pure
                                            * type input ctrls(single values)*/
  HBOOL   ctrl_inherited;   /* true, if all ctrl. values are inherited from 
                             * a father instance (only important for 
                             * correctly freeing the InpCtrlList).           */
  
#if 0
  Hctuple *InpCtrlList;     /* for handling inp. ctrl. values;               */
  Hctuple *InpCtrlNested;   /* for storing inp. ctrl. values; 
                             * one Hctuple element per parameter             */
  INT1    *freeICP;         /* inp ctrl values were copied or passed 
                             * by reference                                  */
  HBOOL   ctrl_inherited;   /* true, if all ctrl. values are inherited from 
                             * a father instance (only important for 
                             * correctly freeing the InpCtrlList).
                             *                                               */
#endif
  /*_____________________________________________output object parameters:___*/
  Hkey    *OutpObjList[MAX_OUTP_OBJ_PAR+1];/* for every output object par.   *
                                            * an array of objects keys       */
  INT4_8  OutpObjNum[MAX_OUTP_OBJ_PAR+1];  /* number of objects per output   *
                                            * object par.; index: 1..        */
  INT4_8  OutpObjLen[MAX_OUTP_OBJ_PAR+1];  /* length of OutpObjList per      *
                                            * output object par.; index: 1.. */
  /*____________________________________________output control parameters:___*/
  Hctuple **OutpCtrlList;      /* used to access outp. ctrl parameters   */
  Hctuple *OutpCtrlStack[MAX_OUTP_CTRL_PAR]; /* stores interface/Nested ref. */
  Hctuple OutpCtrlNested[MAX_OUTP_CTRL_PAR]; /* holds tuple trunks for output
                                              * ctrl values (eg, pure type 
                                              * operators)   */
  UINT4    freeOCP; /* bitcoded free flag: 8*sizof(freeOCP)>=MAX_OUTP_CTRL_PAR*/

} H_OPERATOR_PARAMETERS;


/*---------------------------------------------------------------------------*/
/* H_OPERATOR_SHARED - data structure that is shared among internal threads.
 *---------------------------------------------------------------------------*/
typedef struct
{
  INT4 run_state;
} H_OPERATOR_SHARED;

typedef enum
{
  ph_ready        = 0,
  ph_running      = H_MSG_OK,
  ph_break        = H_ERR_BREAK,
  ph_hen_canceled = H_ERR_HEN_CANCEL,
  ph_canceled     = H_ERR_CANCEL
} HRunState;

typedef struct HLISTEL
{ /* placeholder for internal double linked list element type */
  struct HLISTEL* prev;
  struct HLISTEL* next;
} H_LIST_EL;


typedef struct HALCON_OPERATOR_HANDLE
{
  H_LIST_EL list_el; /*list_el must be defined in the first place*/
  void*     generator;
  INT4      proc_index;         /* Index of HALCON operator        */
  H_OPERATOR_PARAMETERS* param; /* operator parameters (thread-specific) */
  H_OPERATOR_SHARED*     shared_data; /*shared operator data*/
} H_OPHANDLE;
typedef H_OPHANDLE* Hophandle_;

#ifndef HC_NO_STRUCT_MEMBER_ALIGNMENT 
#pragma pack(pop)
#endif

#if defined(__cplusplus)
}
#endif

#endif
