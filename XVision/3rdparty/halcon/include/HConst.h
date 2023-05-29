/*****************************************************************************
 * HConst.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Definition of constants
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************/

#ifndef HCONST_H
#define HCONST_H

/*****************************************************************************/
/*****************************************************************************/
/*             General constants for the HALCON library                      */
/*****************************************************************************/
/*****************************************************************************/


/* Data Base */
#define H_UNDEFINED  UNDEF_KEY /* Ctype.h, CORE*.c do not change */


/*****************************************************************************/
/* Max. values for the library                                               */
/*****************************************************************************/
#if !defined(HC_LARGE_IMAGES)
#define LD_MAX_FORMAT             15
#else
#define LD_MAX_FORMAT             30
#endif
#define MAX_FORMAT                (1<<LD_MAX_FORMAT)

#define RL_LENGTH                 1       /* Only for typedef                */
#define DEF_RL_LENGTH             50000   /* initial value for CurrentRL     */
#define OBJ_PER_PROC              5000    /* Typical # of objects per param. */
#define FILE_TRANS_SIZE           1024*16 /* max. # of byte per read call    */
#define MAX_FILES                 20      /* max. # of open files            */
#define MAX_EDGE_LENGTH1          101     /* max. filter size                */
#define MAX_CLUSTER               1024    /* LearnNDim,ClassNDim             */
#define MAX_CONVOL                50000   /* IPConvol.c (> 10000!)           */
#define MAX_IMAGE_DIR             (16*MAX_STRING) /* length of the image dir */
#define MAX_GRAPHIC_COLOR         64/* max. number of graphics colors in LUT */
#define MAX_COLOR_NAME_LENGTH     40 /* max. length of a color name          */


/*****************************************************************************/
/* Environment variables of HALCON                                           */
/*****************************************************************************/
#define HALCONROOT                "HALCONROOT"       /* Environment variable */
#define HALCONIMAGES              "HALCONIMAGES"     /* Environment variable */
#define HALCONHELP                "HALCONHELP"       /* Environment variable */
#define HALCONSPY                 "HALCONSPY"        /* Environment variable */
#define HALCONEXTENSIONS          "HALCONEXTENSIONS" /* Environment variable */
#define HALCONEXAMPLES            "HALCONEXAMPLES"   /* Environment variable */


/*****************************************************************************/
/* Core Interface and operator implementation                                */
/*****************************************************************************/
#define MAX_INP_OBJ_PAR           9       /* max # input object parameters   */
#define MAX_OUTP_OBJ_PAR          9       /* max # output object parameters  */
#define MAX_INP_CTRL_PAR          20      /* max # inpput control parameters */
#define MAX_OUTP_CTRL_PAR         20      /* max # output control parameters */
#define MAX_CHAPTER                2      /* max # chapters / operator       */
#define MAX_CHAPTER_PROC         300      /* max # operators / chapter       */

#define MAX_KEY_NAME              5       /* old */
#define KEY_NAME_LENGTH           20      /* old */
#define MAX_BUFFER                10      /* old */

/* Shortcut for object access */
#define REGION                    0       /* object component: region        */
#define CHORD                     0       /* object component: region (old)  */
#define IMAGE1                    1       /* object component: 1st image     */
#define IMAGE2                    2       /* object component: 2nd image     */
#define IMAGE3                    3       /* object component: 3rd image     */
#define IMAGE4                    4       /* object component: 4th image     */
#define IMAGE5                    5       /* object component: 5th image     */
#define IMAGE6                    6       /* object component: 6th image     */
#define IMAGE7                    7       /* object component: 7th image     */
#define IMAGE8                    8       /* object component: 8th image     */


#define REGION_ID                 1
#define IMAGE_ID                  2
#define OBJECT_ID                 3
#define TUPLE_ID                  4
#define XLD_CONTOUR_ID            5
#define XLD_POLYGON_ID            6
#define XLD_PARALLEL_ID           7
#define XLD_MOD_PARALLEL_ID       8
#define XLD_EXT_PARALLEL_ID       9
#define MIN_XLD_ID                XLD_CONTOUR_ID
#define MAX_XLD_ID                XLD_EXT_PARALLEL_ID
#define STD_FREE                  HFree

/*****************************************************************************/
/* File extensions                                                           */
/*****************************************************************************/

#define TRAINF_EXT                "trf"   /* OCR training file               */
#define OCR_EXT                   "fnt"   /* OCR                             */
#define OCR_BOX_EXT               "obc"   /* OCR box classifier              */
#define OCR_MLP_EXT               "omc"   /* OCR MLP classifier              */
#define OCR_SVM_EXT               "osc"   /* OCR SVM classifier              */
#define OCR_KNN_EXT               "onc"   /* OCR kNN classifier              */
#define OCR_KNN_EXT_LEGACY        "okc"   /* OCR kNN classifier (legacy)     */
#define OCR_CNN_EXT               "occ"   /* OCR CNN classifier              */
#define OCV_EXT                   "ocv"   /* OCV                             */
#define PS_EXTENSION              "ps"    /* Postscript                      */
#define TIFF_EXTENSION            "tiff"  /* TIFF                            */
#define EXP_EXTENSION             "exp"   /* Extension image description     */
#define IMAGE_EXTENSION           "ima"   /* Extension HALCON image          */
#define REGION_EXTENSION          "reg"   /* Extension region file           */
#define FILTER_EXTENSION          "fil"   /* Extension convol filters        */
#define LUT_EXTENSION             "lut"   /* Extension LUT                   */
#define GREYSE_EXT                "gse"   /* Extension gray struct element   */
#define BMP_EXTENSION             "bmp"   /* Extension Windows-BMP           */
#define DEEP_LEARNING_EXTENSION   "hdl"   /* Extension deep networks         */




/*****************************************************************************/
/* Mathematical constants                                                    */
/*****************************************************************************/

#ifndef PI
#ifdef  M_PI
#define PI               M_PI
#else
#define PI               3.14159265358979323846
#endif
#endif
#ifndef PI_2
#define PI_2             (PI / 2.0)
#endif
#ifndef PI_4
#define PI_4             (PI / 4.0)
#endif


/*****************************************************************************/
/* Thread handling                                                           */
/*****************************************************************************/

#define GLOBAL_ID             NULL         /* 'global' operator handle       */
#define DEFAULT_AGENTS_NR     4            /* default # for agents           */

/* controlling the access to global/local context variables (see HInstance.c)*/
#define GV_WRITE_INFO         0            /* Flag: write global context var.*/
#define GV_READ_INFO          1            /* Flag: read global context var. */
#define GV_INIT_INFO          2            /* Flag: init. global context var.*/
#define GV_GET_ADRESS         3            /* Flag: get address of var.      */
#define GV_REALLOC_A          4            /* Flag: realloc an array         */
#define GV_LOCK               5            /* Flag: lock a mutex variable    */
#define GV_UNLOCK             6            /* Flag: unlock a mutex variable  */
#define GV_BOR_INFO           7            /* Flag: bitwise OR with variable */
#define GV_BAND_INFO          8            /* Flag: bitwise AND with variable*/
#define GV_WRITE_REF          9            /* Flag: write in reference var.; */
                                    /* (forces changes in reference version) */
#define GV_READ_REF          10            /* Flag: read from reference var. */

/*****************************************************************************/
/* H_SYS_INFO_READ_ONLY                                                      */
/*****************************************************************************/

#define CLOCK_MODE_PROCESSOR_TIME      0  /* clock mode */
#define CLOCK_MODE_ELAPSED_TIME        1
#define CLOCK_MODE_PERFORMANCE_COUNTER 2
#define CLOCK_MODE_MULTIMEDIA_TIMER    3
#define CLOCK_MODE_PROCESS_TIME        4
#define OCR_TRAINFILE_VERSION1_0       1  /* file version when writing OCR */
#define OCR_TRAINFILE_VERSION2_0       2  /* trainf */
#define OCR_TRAINFILE_VERSION3_0       3  /* trainf + UINT2 images */
#define H_ENCODING_NATIVE              1  /* local8bit character encoding    */
#define H_ENCODING_UTF8                2  /* UTF-8 character encoding        */
#define H_ENCODING_HLIB                3  /* encoding that is used by hlib   */
#define H_ENCODING_ASCII               4  /* promise that a passed string is
                                           * pure ASCII                      */
#define H_ENCODING_SYSTEM              5  /* promise that a passed string is
                                           * in system encoding: which is the
                                           * locale under Linux, utf8 on Mac,
                                           * and for Windows not needed      */
#define H_ENCODING_AUTO                6  /* generic mode for detecting the
                                           * encoding automatically */
#define TIMER_MODE_ELAPSED_TIME        0
#define TIMER_MODE_MULTIMEDIA_TIMER    1
#define TIMER_MODE_PERFORMANCE_COUNTER 2


#endif
