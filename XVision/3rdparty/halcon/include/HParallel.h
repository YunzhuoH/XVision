/*****************************************************************************
 * HParallel.h
 *****************************************************************************
 *
 * Project:      HALCON/HLib
 * Description:  Basic constants for controlling the automatic 
 *               parallelization of HALCON operators and 
 *               programs (operator sequences)
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************/

#ifndef HCPAR_H
#define HCPAR_H

#if defined(__cplusplus)
extern "C" {
#endif

/* --- Defines -------------------------------------------------- */
# if defined(_POSIX_THREADS)
#  define H_POSIX_THREADS
# elif defined(_WIN32)
#  define H_WIN32_THREADS
# endif
/* else: no synchronization and threads used */


# if !defined (H_PARALLEL) || \
     !(defined(H_WIN32_THREADS)||defined(H_POSIX_THREADS)) 
  /* Sequential HALCON or no synchronization specified */
#  define H_NO_SPIN_LOCK
#  if defined H_TSD
#    undef H_TSD  /* no thread specific data */
#  endif
# else
#  define H_TSD /* use thread specific data */
# endif



/*===========================================================================*/
/*                                Constants                                  */
/*===========================================================================*/
/* -------- (knowledge default values and control weights) ----------------- */

/* constants for describing how to process an operator:                      */
#define HAG_PAR_INDEPENDENT   0            /* completely independent of other
                                            * operators, i.e., can run with
                                            * exclusive operators in parallel*/
#define HAG_PAR_NO_RESTRICT   1<<0         /* no restriction                 */
#define HAG_PAR_LOCAL         1<<1         /* force local processing         */
                                           /* by main thread/process         */
#define HAG_PAR_MUTUAL        1<<2         /* force processing under mutual  */
                                           /* exclusion, i.e. the same       */
                                           /* operator may only run once at  */
                                           /* a time                         */
#define HAG_PAR_EXCLUSIVE     1<<3         /* force exclusive processing,    */
                                           /* i.e. no other operator may run */
                                           /* while this operator works      */


/* default control values:                                                   */
#define HAG_KW_CHORD_NUM      1            /* minimal num. of chords for par.*/
#define HAG_KW_MIN_COSTS      16300        /* minimal costs for which to par.*/
#define HAG_KW_PAR_COSTS      308          /* weight of ctrl. par. costs     */
#define HAG_KW_CPU_RATING     10           /* threshold for assigning a cpu  */


/* -------- (postprocessing of control parameters) ------------------------- */
#define HAG_PAR_NOCT          1            /* no need of ctrl. par. postproc.*/
                                           /* =>adopt par. of 1. H. thread   */
#define HAG_PAR_TUCT_ADD      2            /* add ctrl. par.s ;       tuple  */
#define HAG_PAR_CHCT_ADD      4            /* add ctrl. par.s ;       channel*/
                                           /* (must be 2*HAG_PAR_TUCT_ADD)   */
#define HAG_PAR_RECT_ADD      8            /* add ctrl. par.s ;       res.de.*/
                                           /* (must be 4*HAG_PAR_TUCT_ADD)   */
#define HAG_PAR_TUCT_MIN      16           /* minimum of ctrl. par.s; tuple  */
#define HAG_PAR_CHCT_MIN      32           /* minimum of ctrl. par.s; channel*/
#define HAG_PAR_RECT_MIN      64           /* minimum of ctrl. par.s; res.de.*/
#define HAG_PAR_TUCT_MAX      128          /* maximum of ctrl. par.s; tuple  */
#define HAG_PAR_CHCT_MAX      256          /* maximum of ctrl. par.s; channel*/
#define HAG_PAR_RECT_MAX      512          /* maximum of ctrl. par.s; res.de.*/
#define HAG_PAR_TUCT_CON      1024         /* concatenate ctrl. par.s;tuple  */
#define HAG_PAR_CHCT_CON      2048         /* concatenate ctrl. par.s;channel*/
#define HAG_PAR_RECT_CON      4096         /* concatenate ctrl. par.s;res.de.*/
                                           /* ATTENTION: the difference in   */
                                           /* the codes for tuples/channels/ */
                                           /* resources must always show the */
                                           /* above scheme of *2 and *4!     */
                                           /* Because this is used in the    */
                                           /* HAgent-source code; e.g.:      */
                                           /* HAG_PAR_CHCT_MIN is assumed to */
                                           /* be HAG_PAR_TUCT_MIN*2          */
#define HAG_PAR_TUCT          1170         /* postprocess ctrl. par.; tuple  */
/* remark: this is a shortcut for: HAG_PAR_TUCT_ADD | HAG_PAR_TUCT_MIN |     */
/*                                 HAG_PAR_TUCT_MAX | HAG_PAR_TUCT_CON       */
#define HAG_PAR_CHCT          2340         /* postprocess ctrl. par.; channel*/
                                           /* (must be 2*HAG_PAR_TUCT)       */
#define HAG_PAR_RECT          4680         /* postprocess ctrl. par.; res.de.*/
                                           /* (must be 4*HAG_PAR_TUCT)       */

/* -------- (postprocessing of domains/region components of output objects)  */
#define HAG_PAR_REG_NONE      0            /* no post processing             */
#define HAG_PAR_REG_CONSI     (1<<0)       /* concatenation of (disjuntive)  */
                                           /* result regions for single      */
                                           /* input iconic parameter         */
#define HAG_PAR_REG_CONMU     (1<<1)       /* concatenation of (disjuntive)  */
                                           /* result regions for multiple    */
                                           /* input iconic parameters        */
#define HAG_PAR_REG_CONMAN    (1<<2)       /* manual concatenation of        */
                                           /* result regions for multiple    */
                                           /* input iconic parameters        */
                                           /* Use HAG_PAR_REG_CONMAN if your */
                                           /* the output region is variable, */
                                           /* and not dependent on the input */
                                           /* iconic parameters              */

/* -------- (task-/operator-/thread-parallelization; chances and states) --- */
/* -------- (and postprocessing of control parameters) --------------------- */
/* The following constants symbolize different methods of parallelization.   */
/* Their values are built up according to the following rules:               */
/*     Bit  0   signals multithreading ability (see HAG_PAR_MT)              */
/*     Bits 1-6 signal which method of parallelization can be used:          */
#define HAG_PAR_SEQ           0            /* all operators are called       */
                                           /* sequentially => no need of     */
                                           /* synchronization; no automatic  */
                                           /* parallelization                */
#define HAG_PAR_MT            (1<<0)       /* "multithreading" context;      */
                                           /* operators may called in        */
                                           /* parallel use synchronization   */
                                           /* mechanisms for reentrancy,     */
                                           /* but don't use automatic par.   */
#define HAG_PAR_FORCE         (1<<1)       /* force parallelization if 
                                            * supported */
#define HAG_PAR_NONE          (1<<2)       /* no parallelization 'lucrative' */
                                           /* is set explicitely, if the 
                                            * hardware/operator training 
                                            * showed that the processing does 
                                            * not speed up by parallelization*/
#define HAG_PAR_TUPL          (1<<5)       /* tuple parallelization possible */
#define HAG_PAR_CHNL          (1<<6)       /* channel paralleli. is possible */
#define HAG_PAR_RESC          (1<<7)       /* resource decomposition possible*/
#define HAG_PAR_REIF          (1<<8)       /* res. dec. at image filtering   */
#define HAG_PAR_PART          (1<<9)    /* partial automatic parallelization: 
                                         * an operator is parallelized 
                                         * manually within the hlib */
#define HAG_PAR_PAIF          (1<<10)   /* internal domain parallelization */


/* constants for describing the overall processing context:                  */
#define HAG_PAR_SPLIT_NONE    0
#define HAG_PAR_SPLIT_DOMAIN  (HAG_PAR_RESC|HAG_PAR_REIF)
  /* ^domain parallelization */
#define HAG_PAR_INTERFACE     (HAG_PAR_TUPL|HAG_PAR_CHNL|HAG_PAR_REIF)
  /* ^parallelization by interface */
#define HAG_PAR_INTERNAL      (HAG_PAR_PART|HAG_PAR_PAIF)
  /* ^manual, internal parallelization */
#define HAG_PAR_ALL       (HAG_PAR_TUPL|HAG_PAR_CHNL|HAG_PAR_RESC|HAG_PAR_REIF|HAG_PAR_PART|HAG_PAR_PAIF)

/* remark: all following "TRUE" values (!=0) mean in any case that HALCON    */
/* works in a parallel manner and needs synchronization mechanisms           */
#define HAG_PAR_TUPL_MT      ( HAG_PAR_TUPL | HAG_PAR_MT)
#define HAG_PAR_CHNL_MT      ( HAG_PAR_CHNL | HAG_PAR_MT)
#define HAG_PAR_RESC_MT      ( HAG_PAR_RESC | HAG_PAR_MT)
#define HAG_PAR_REIF_MT      ( HAG_PAR_REIF | HAG_PAR_MT)
#define HAG_PAR_DOM_MT       ( HAG_PAR_REIF_MT | HAG_PAR_RESC_MT)
#define HAG_PAR_PART_MT      ( HAG_PAR_PART | HAG_PAR_MT)
#define HAG_PAR_PAIF_MT      ( HAG_PAR_PAIF | HAG_PAR_MT)

#define HAG_PAR_DPAR_MT      ( HAG_PAR_TUPL_MT|HAG_PAR_CHNL_MT|\
                               HAG_PAR_RESC_MT|HAG_PAR_REIF_MT|\
                               HAG_PAR_PART_MT|HAG_PAR_PAIF_MT)
                                           /* "multithreading" context (see  */
                                           /* above) AND use automatic       */
                                           /* data parallelization for       */
                                           /* processing operators (default) */

                                          /* tuple & channel p. & res. dec. */
/*     Bits 8-23 currently not used                                          */
/* #define                    128           *                                */
/* #define                    256           *                                */
/* #define                    512           *                                */
/* #define                    1024          *                                */
/* #define                    2048          *                                */
/* #define                    4096          *                                */
/* #define                    8192          *                                */
/* #define                    16384         *                                */
/* #define                    32768         *                                */
/* #define                    65536         *                                */
/* #define                    131072        *                                */
/* #define                    262144        *                                */
/* #define                    524288        *                                */
/* #define                    1048576       *                                */
/* #define                    2097152       *                                */
/* #define                    4194304       *                                */
/*     Bits 24-31 signal which parallelization steps have already been       */
/*     done for the actual task/operator/thread:                             */
#define HAG_PAR_TUPLED        (1<<24)      /* tuple parallelized             */
#define HAG_PAR_CHNLED        (1<<25)      /* channel parallelized           */
#define HAG_PAR_RESCED        (1<<26)      /* resources already decomposed   */
#define HAG_PAR_REIFED        (1<<27)      /* res. decom. at image filtering */

/*--------------------    Compute Device constants      ---------------------*/
#define  COMPUTE_DEVICE_NONE    0
#define  COMPUTE_DEVICE_OpenCL  1

/* H_OPERATOR_INFO.compute_device bit field defines */
#define  COMPUTE_DEVICE_BIT_NONE     0
#define  COMPUTE_DEVICE_BIT_OpenCL   (1<<(COMPUTE_DEVICE_OpenCL))

#if defined(__cplusplus)
}
#endif

#endif
