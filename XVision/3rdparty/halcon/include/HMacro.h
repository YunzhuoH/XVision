/*****************************************************************************
 * HMacro.h
 *****************************************************************************
 *
 * Project:      HALCON/libhalcon
 * Description:  Definition of macros
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *               www.mvtec.com
 *
 *****************************************************************************/

#ifndef HMACRO_H
#define HMACRO_H

/*
 * HALCON traditionally used 'FAST' instead of 'HC_FAST', but that clashes
 * with VxWorks.
 */
#if !defined(__vxworks) && defined(FAST) && !defined(HC_FAST)
#  define HC_FAST
#endif

/*
 * If SMALL is defined, file names and line number information should not be
 * included in the binary.
 */
#ifndef SMALL
#  define H__FILE__ __FILE__
#  define H__LINE__ __LINE__
#else
#  define H__FILE__ ""
#  define H__LINE__ -1
#endif


#define HDFImage(VAR,IMAGE_IN,KOOR) { VAR = 0.0; \
  switch ((IMAGE_IN)->kind) {\
    case BYTE_IMAGE: VAR = (double)(IMAGE_IN)->pixel.b[KOOR]; break;\
    case INT1_IMAGE: VAR = (double)(IMAGE_IN)->pixel.i[KOOR]; break;\
    case INT2_IMAGE: VAR = (double)(IMAGE_IN)->pixel.s.p[KOOR]; break;\
    case UINT2_IMAGE: VAR = (double)(IMAGE_IN)->pixel.u.p[KOOR]; break;\
    case DIR_IMAGE: VAR = (double)(IMAGE_IN)->pixel.d[KOOR]; break;\
    case CYCLIC_IMAGE: VAR = (double)(IMAGE_IN)->pixel.z[KOOR]; break;\
    case INT4_IMAGE: VAR = (double)(IMAGE_IN)->pixel.l[KOOR]; break;\
    case INT8_IMAGE: VAR = (double)(IMAGE_IN)->pixel.i8[KOOR]; break;\
    case FLOAT_IMAGE: VAR = (double)(IMAGE_IN)->pixel.f[KOOR]; break;\
    case COMPLEX_IMAGE: return(H_ERR_WITFO); /* wrong image type */ \
    case VF_IMAGE: return(H_ERR_WITFO);      /* wrong image type */ \
    default: return(H_ERR_NIIT);             /* not implemented image type */\
  }}


#define HAbsImage(VAR,IMAGE_IN,KOOR)                                    \
  switch ((IMAGE_IN)->kind) {                                           \
    case BYTE_IMAGE: VAR = ABS((double)(IMAGE_IN)->pixel.b[KOOR]); break; \
    default: ;                                                          \
  }


#define HImageFD(IMAGE_OUT,VAR,KOOR)                                    \
  switch ((IMAGE_OUT)->kind) {                                          \
    case BYTE_IMAGE: {                                                  \
      HINT HHH;                                                          \
      HHH = HIRound(VAR);                                               \
      if (HHH > 255) HHH = 255; else if (HHH < 0) HHH = 0;              \
      (IMAGE_OUT)->pixel.b[KOOR] = (HBYTE)HHH;                          \
      break; }                                                          \
    case CYCLIC_IMAGE:                                                  \
      (IMAGE_OUT)->pixel.z[KOOR] = HMOD(HLRound(VAR),(HINT)(UCHAR_MAX+1)); \
      break;                                                            \
    case INT1_IMAGE: {                                                  \
      HINT HHH;                                                          \
      HHH = HIRound(VAR);                                               \
      if (HHH > INT1_MAX) HHH = INT1_MAX;                               \
      else if (HHH < INT1_MIN) HHH = INT1_MIN;                          \
      (IMAGE_OUT)->pixel.i[KOOR] = (INT1)HHH;                           \
      break; }                                                          \
    case INT2_IMAGE: {                                                  \
      double DDD = (VAR);                                               \
      if (DDD > (double)INT2_MAX) DDD = INT2_MAX;                       \
      else if (DDD < INT2_MIN) DDD = INT2_MIN;                          \
     (IMAGE_OUT)->pixel.s.p[KOOR] = (INT2)HLRound(DDD);                 \
      break; }                                                          \
    case UINT2_IMAGE: {                                                 \
      double DDD = (VAR);                                               \
      if (DDD > (double)UINT2_MAX) DDD = UINT2_MAX;                     \
      else if (DDD < 0) DDD = 0;                                        \
     (IMAGE_OUT)->pixel.s.p[KOOR] = (UINT2)HLRound(DDD);                \
      break; }                                                          \
    case LONG_IMAGE: {                                                  \
      double DDD = (VAR);                                               \
      if (DDD > (double)INT4_MAX) DDD = INT4_MAX;                       \
      else if (DDD < INT4_MIN) DDD = INT4_MIN;                          \
     (IMAGE_OUT)->pixel.l[KOOR] = (INT4)HLRound(DDD);                   \
      break; }                                                          \
    case INT8_IMAGE: {                                                  \
      double DDD = (VAR);                                               \
      if (DDD > (double)HINT8_MAX) DDD = HINT8_MAX;                     \
      else if (DDD < HINT8_MIN) DDD = HINT8_MIN;                        \
     (IMAGE_OUT)->pixel.i8[KOOR] = (HINT8)HI8Round(DDD);                \
      break; }                                                          \
    case FLOAT_IMAGE: {                                                 \
      double DDD = (VAR);                                               \
      if (DDD > (double)FLT_MAX) DDD = FLT_MAX;                         \
      else if (DDD < -(double)FLT_MAX) DDD = -(double)FLT_MAX;          \
      (IMAGE_OUT)->pixel.f[KOOR] = (float)DDD;                          \
      break; }                                                          \
    case COMPLEX_IMAGE: {                                               \
      double DDD = (VAR);                                               \
      if (DDD > (double)FLT_MAX) DDD = FLT_MAX;                         \
      else if (DDD < -(double)FLT_MAX) DDD = -(double)FLT_MAX;          \
      (IMAGE_OUT)->pixel.c[KOOR].re = (float)DDD;                       \
      (IMAGE_OUT)->pixel.c[KOOR].im = (float)0.0;                       \
      break; }                                                          \
    case DIR_IMAGE: return(H_ERR_WITFO);                                \
    case VF_IMAGE: return(H_ERR_WITFO); /* wrong image type */          \
    default: return(H_ERR_NIIT); /* not implemented image type */       \
  }


#define HCkFilterSize(IMAGE_WIDTH,IMAGE_HEIGHT,FILTER_WIDTH,FILTER_HEIGHT) \
  if(((IMAGE_WIDTH) < ((FILTER_WIDTH)>>1)+1) ||                         \
     ((IMAGE_HEIGHT) < ((FILTER_HEIGHT)>>1)+1))                         \
     return(H_ERR_FSEIS);

#define HCkFilterSize_2(IMAGE_WIDTH,IMAGE_HEIGHT,                       \
                        FILTER_WIDTH_2, FILTER_HEIGHT_2)                \
  if(((IMAGE_WIDTH) < (FILTER_WIDTH_2)+1) ||                            \
     ((IMAGE_HEIGHT) < (FILTER_HEIGHT_2)+1))                            \
     return(H_ERR_FSEIS);


#define DIST(PIX,PIX2,ABSDIF,IMAGE_IN_KIND)                           \
  switch (IMAGE_IN_KIND) {                                            \
    case BYTE_IMAGE:                                                  \
    case LONG_IMAGE:                                                  \
    case INT8_IMAGE:                                                  \
    case INT1_IMAGE:                                                  \
    case INT2_IMAGE:                                                  \
    case UINT2_IMAGE:                                                 \
    case FLOAT_IMAGE:                                                 \
      ABSDIF = ABS((PIX)-(PIX2));                                     \
      break;                                                          \
    case CYCLIC_IMAGE:                                                \
      { double dmax,dmaxh;                                            \
        dmax = (double)UCHAR_MAX + 1.;                                      \
        dmaxh = (double)(int)(dmax/2.);                                     \
        ABSDIF = ABS((PIX)-(PIX2));                                         \
        if ((ABSDIF) > dmaxh) ABSDIF = dmax - (ABSDIF);                     \
      }                                                               \
      break;                                                          \
    case DIR_IMAGE:                                                   \
      if ((PIX) > 200. || (PIX2) > 200.) ABSDIF = (double)UCHAR_MAX;  \
      else                                                            \
      { ABSDIF = ABS((PIX)-(PIX2));                                   \
        if ((ABSDIF) > 90.) ABSDIF = 181. - (ABSDIF);                       \
      }                                                               \
      break;                                                          \
    default: return(H_ERR_NIIT);                                      \
  }

#define HiType2iIDX(iTYPE,iIDX)                 \
  switch (iTYPE)                                \
  {                                             \
  case UNDEF_IMAGE:                             \
    iIDX  = iUNDEF;                             \
    break;                                      \
  case BYTE_IMAGE:                              \
    iIDX  = iBYTE;                              \
    break;                                      \
  case INT4_IMAGE:                              \
    iIDX  = iINT4;                              \
    break;                                      \
  case FLOAT_IMAGE:                             \
    iIDX  = iFLOAT;                             \
    break;                                      \
  case DIR_IMAGE:                               \
    iIDX  = iDIR;                               \
    break;                                      \
  case CYCLIC_IMAGE:                            \
    iIDX  = iCYCLIC;                            \
    break;                                      \
  case INT1_IMAGE:                              \
    iIDX  = iINT1;                              \
    break;                                      \
  case COMPLEX_IMAGE:                           \
    iIDX  = iCOMPLEX;                           \
    break;                                      \
  case INT2_IMAGE:                              \
    iIDX  = iINT2;                              \
    break;                                      \
  case UINT2_IMAGE:                             \
    iIDX  = iUINT2;                             \
    break;                                      \
  case VF_IMAGE:                                \
    iIDX  = iVF;                                \
    break;                                      \
  default:                                      \
    iIDX  = UNDEF_IMAGE;                        \
    break;                                      \
  }



#define HMOD(VAL,VALMAX) (((VAL) < 0) ? \
  ((unsigned char)(((VALMAX) - (-(VAL) % (VALMAX))) % (VALMAX))) :\
  ((unsigned char)((VAL) % (VALMAX))))




/* Grauwertkomponente eines Graubildes */
#define IMAGE_INDEX  1

#define HBitImageSize(WIDTH,HEIGHT) (size_t)((HIMGCNT)WIDTH*HEIGHT/8+1)

#define WarningCompl(Proc) \
    (void)printf("warning: is_compl not yet full implemented (%s)\n",Proc)


/*****************************************************************************
 * Routines for freeing and reallocating "permanent","local", or "temporary"
 * memory.
 *****************************************************************************/
#ifndef _LIntStatic
#  define HFreeGeneral(PROC_HANDLE,VOID_PTR)                            \
  (HTraceMemory ?                                                       \
   HXFreeGeneralMemCheck(PROC_HANDLE, (void*)VOID_PTR,                  \
                         H__FILE__,(INT4_8)H__LINE__):                  \
   HXFreeGeneral(PROC_HANDLE,(void*)VOID_PTR) )
#else
/* in case of static language interfaces, do not use HTraceMemory to allow
 * delayed loading */
#  define HFreeGeneral(PROC_HANDLE,VOID_PTR)    \
   HXFreeGeneral(PROC_HANDLE,(void*)VOID_PTR)
#endif

#define HReallocGeneral(PROC_HANDLE,VOID_PTR,SIZE,NEW_PTR)              \
  HXReallocGeneral(PROC_HANDLE,(void*)(VOID_PTR),SIZE,(void*)(NEW_PTR), \
                   H__FILE__, (INT4_8)H__LINE__)

#define HFreeRLGeneral(PROC_HANDLE,REGION)                              \
  HXFreeRLGeneral(PROC_HANDLE,REGION,H__FILE__,(INT4_8)H__LINE__)

#define HReallocRLNumGeneral(PROC_HANDLE,REGION,SIZE,NEW_REGION)        \
  HXReallocRLNumGeneral(PROC_HANDLE,REGION,SIZE,NEW_REGION,             \
                        H__FILE__,(INT4_8)H__LINE__)


/*****************************************************************************
 * Routines for allocating "permanent" memory from the heap.  This memory is
 * _not_ freed automatically after each call to a HALCON operator.
 *****************************************************************************/
#ifndef _LIntStatic
#  define HAlloc(PROC_HANDLE,SIZE,VOID_PTR)                             \
  (HTraceMemory ?                                                       \
   HXAllocMemCheck(PROC_HANDLE,SIZE,H__FILE__,(INT4_8)H__LINE__,        \
                   H_GLOBAL_ALLOC,(void*)(VOID_PTR)):                   \
   HXAlloc(PROC_HANDLE,SIZE,(void*)(VOID_PTR)))
#else
/* in case of static language interfaces, do not use HTraceMemory to allow
 * delayed loading */
#  define HAlloc(PROC_HANDLE,SIZE,VOID_PTR)                             \
   HXAlloc(PROC_HANDLE,SIZE,(void*)(VOID_PTR))
#endif

#define HIsAligned(VOID_PTR,ALIGNMENT) (((UINT4_8)ptr & (ALIGNMENT-1)) == 0)

#ifndef _LIntStatic
#  define HAllocAlign(PROC_HANDLE,SIZE,ALIGNMENT,VOID_PTR)              \
  (HTraceMemory ?                                                       \
   HXAllocAlignMemCheck(PROC_HANDLE,SIZE,ALIGNMENT,H__FILE__,           \
                        (INT4_8)H__LINE__,H_GLOBAL_ALLOC,               \
                        (void*)(VOID_PTR)):                             \
   HXAllocAlign(PROC_HANDLE,SIZE,ALIGNMENT,(void*)(VOID_PTR)))
#else
/* in case of static language interfaces, do not use HTraceMemory to allow
 * delayed loading */
#  define HAllocAlign(PROC_HANDLE,SIZE,ALIGNMENT,VOID_PTR)              \
  HXAllocAlign(PROC_HANDLE,SIZE,ALIGNMENT,(void*)(VOID_PTR))
#endif

#define HRealloc(PROC_HANDLE,VOID_PTR,SIZE,NEW_PTR)                     \
  HXRealloc(PROC_HANDLE,(void*)(VOID_PTR),SIZE,(void*)(NEW_PTR),        \
            H__FILE__,(INT4_8)H__LINE__)

#define HReallocToGlobal(PROC_HANDLE,VOID_PTR,SIZE,NEW_PTR)             \
  HXReallocToGlobal(PROC_HANDLE,(void*)(VOID_PTR),SIZE,(void*)(NEW_PTR),\
                    H__FILE__, (INT4_8)H__LINE__)


#ifndef _LIntStatic
#  define HFree(PROC_HANDLE,VOID_PTR)                                   \
  (HTraceMemory ?                                                       \
   HXFreeMemCheck(PROC_HANDLE,(void*)(VOID_PTR),                        \
                  H__FILE__,(INT4_8)H__LINE__):                         \
   HXFree(PROC_HANDLE,(void*)(VOID_PTR)))
#else
/* in case of static language interfaces, do not use HTraceMemory to allow
 * delayed loading */
#  define HFree(PROC_HANDLE,VOID_PTR)                                   \
   HXFree(PROC_HANDLE,(void*)(VOID_PTR))
#endif

#define HAllocRLNum(PROC_HANDLE,REGION,SIZE)                            \
  HXAllocRLNum(PROC_HANDLE,REGION,SIZE,H__FILE__,(INT4_8)H__LINE__)

#define HReallocRLNum(PROC_HANDLE,REGION,SIZE,NEW_REGION)               \
  HXReallocRLNum(PROC_HANDLE,REGION,SIZE,NEW_REGION,H__FILE__,          \
                 (INT4_8)H__LINE__)

#define HReallocRLNumToGlobal(PROC_HANDLE,REGION,SIZE,NEW_REGION)     \
  HXReallocRLNumToGlobal(PROC_HANDLE,REGION,SIZE,NEW_REGION,          \
                         H__FILE__,(INT4_8)H__LINE__)

#define HAllocRL(PROC_HANDLE,REGION)                            \
  HXAllocRL(PROC_HANDLE,REGION,H__FILE__,(INT4_8)H__LINE__)

#define HFreeRL(PROC_HANDLE,REGION)                             \
  HXFreeRL(PROC_HANDLE,REGION,H__FILE__,(INT4_8)H__LINE__)


/*****************************************************************************
 * Routines for allocating temporary memory from a "stack" of memory.  This
 * memory is freed automatically after each call to a HALCON operator.
 *****************************************************************************/

#define HAllocTmp(PROC_HANDLE,PTR,SIZE)                                 \
  HXAllocTmp(PROC_HANDLE,(void*)(PTR),SIZE,H__FILE__,(INT4_8)H__LINE__)

#define HAllocTmpAlign(PROC_HANDLE,PTR,SIZE,ALIGNMENT)          \
  HXAllocTmpAlign(PROC_HANDLE,(void*)(PTR),SIZE,ALIGNMENT,      \
                  H__FILE__,(INT4_8)H__LINE__)

#define HAllocDomainImageTmp(PROC_HANDLE,MEM_PTR,IMAGE_PTR,REGION,      \
                             WIDTH,HEIGHT,BYTE_PER_PIXEL,               \
                             BORDER_ROWS,BORDER_BYTES)                  \
  HXAllocDomainImageTmp(PROC_HANDLE,(void*)(MEM_PTR),(void*)(IMAGE_PTR),\
                        REGION,                                         \
                        WIDTH,HEIGHT,BYTE_PER_PIXEL,                    \
                        BORDER_ROWS,BORDER_BYTES,                       \
                        H__FILE__,(INT4_8)H__LINE__)

#define HFreeTmp(PROC_HANDLE,VOID_PTR)                                  \
  HXFreeTmp(PROC_HANDLE,(void*)(VOID_PTR),H__FILE__,(INT4_8)H__LINE__)

#define HFreeNTmp(PROC_HANDLE,NUM)                              \
  HXFreeNTmp(PROC_HANDLE,NUM,H__FILE__,(INT4_8)H__LINE__)

#define HFreeAllTmp(PROC_HANDLE)                        \
  HXFreeAllTmp(PROC_HANDLE,H__FILE__,(INT4_8)H__LINE__)

#define HFreeUpToTmp(PROC_HANDLE,VOID_PTR)                              \
  HXFreeUpToTmp(PROC_HANDLE,(void*)(VOID_PTR),H__FILE__,(INT4_8)H__LINE__)

#define HFreeUpToTmpExcl(PROC_HANDLE,VOID_PTR)                          \
  HXFreeUpToTmpExcl(PROC_HANDLE,(void*)(VOID_PTR),H__FILE__,(INT4_8)H__LINE__)

#define HAllocRLNumTmp(PROC_HANDLE,REGION,SIZE)                         \
  HXAllocRLNumTmp(PROC_HANDLE,REGION,SIZE,H__FILE__,(INT4_8)H__LINE__)

#define HAllocRLTmp(PROC_HANDLE,REGION)                         \
  HXAllocRLTmp(PROC_HANDLE,REGION,H__FILE__,(INT4_8)H__LINE__)

#define HFreeRLTmp(PROC_HANDLE,REGION)                          \
  HXFreeRLTmp(PROC_HANDLE,REGION,H__FILE__,(INT4_8)H__LINE__)

#define HTestTmp(PROC_HANDLE,VOID_PTR)                                  \
  HXTestTmp(PROC_HANDLE,VOID_PTR,H__FILE__,(INT4_8)H__LINE__,TRUE)

#define HTestPtr(VOID_PTR)                              \
  HXTestPtr(VOID_PTR,H__FILE__,(INT4_8)H__LINE__)

#define HTestAllTmp(VOID_PTR)                           \
  HXTestAllTmp(VOID_PTR,H__FILE__,(INT4_8)H__LINE__)


/*****************************************************************************
 * Routines for allocating temporary memory from the heap.  This memory is
 * freed automatically after each call to a HALCON operator.
 *****************************************************************************/

#define HAllocLocal(PROC_HANDLE,SIZE,VOID_PTR) \
  HXAllocLocal(PROC_HANDLE,SIZE,H__FILE__,(INT4_8)H__LINE__,(void*)(VOID_PTR))

/*
 * HAllocLocalGC: Operator local, garbage collecting mermory allocation. In
 * comparison to HAllocLocal, HAllocLocalGC does not prompt low error messages
 * when freeing memory if HDoLowErrors and HTraceMemory are turned on.
 */
#define HAllocLocalGC(PROC_HANDLE, SIZE, VOID_PTR)                            \
  HXAllocLocalGC(PROC_HANDLE,SIZE,H__FILE__,(INT4_8)H__LINE__,(void*)(VOID_PTR))

#define HAllocLocalAlign(PROC_HANDLE,SIZE,ALIGNMENT,VOID_PTR)           \
  HXAllocLocalAlign(PROC_HANDLE,SIZE,ALIGNMENT,H__FILE__,(INT4_8)H__LINE__, \
                    (void*)(VOID_PTR))

#define HReallocLocal(PROC_HANDLE,VOID_PTR,SIZE,NEW_PTR)              \
  HXReallocLocal(PROC_HANDLE,(void*)(VOID_PTR),SIZE,(void*)(NEW_PTR), \
                 H__FILE__,(INT4_8)H__LINE__)

#define HFreeLocal(PROC_HANDLE,VOID_PTR)                                \
  HXFreeLocal(PROC_HANDLE,(void*)(VOID_PTR),H__FILE__,(INT4_8)H__LINE__)

#define HAllocRLNumLocal(PROC_HANDLE,REGION,SIZE)                       \
  HXAllocRLNumLocal(PROC_HANDLE,REGION,SIZE,H__FILE__,(INT4_8)H__LINE__)

#define HReallocRLNumLocal(PROC_HANDLE,REGION,SIZE,NEW_REGION)          \
  HXReallocRLNumLocal(PROC_HANDLE,REGION,SIZE,NEW_REGION,               \
                      H__FILE__,(INT4_8)H__LINE__)

#define HAllocRLLocal(PROC_HANDLE,REGION)                       \
  HXAllocRLLocal(PROC_HANDLE,REGION,H__FILE__,(INT4_8)H__LINE__)

#define HFreeRLLocal(PROC_HANDLE,REGION)                        \
  HXFreeRLLocal(PROC_HANDLE,REGION,H__FILE__,(INT4_8)H__LINE__)

#ifndef ABS
#  define ABS(A)  (((A) >= 0) ? (A) : (-(A)))
#endif

/* Umwandlung Bogenmass in Grad und zurueck */
#define RadToDeg(x) (double)(x) * 57.295779513082
#define DegToRad(x) (double)(x) / 57.295779513082

#define HIRound(Val) (((Val) < 0.0) ? ((HINT)((Val)-0.5)):((HINT)((Val)+0.5)))
#define HI4Round(Val) (((Val) < 0.0) ? ((INT4)((Val)-0.5)):((INT4)((Val)+0.5)))
#define HLRound(Val) (((Val) < 0.0) ? ((INT4_8)((Val)-0.5)):  \
                      ((INT4_8)((Val)+0.5)))
#define HI8Round(Val) (((Val) < 0.0) ? ((HINT8)((Val)-0.5)):  \
                       ((HINT8)((Val)+0.5)))
#define HIMGCOORRound(Val) (((Val) < 0.0) ? ((HIMGCOOR)((Val)-0.5)):  \
                            ((HIMGCOOR)((Val)+0.5)))
#define HFIRound(Val) (((Val)<0.0f)?((HINT)((Val)-0.5f)):((HINT)((Val)+0.5f)))


/*
 * Edge handling for images by mirroring.
 *
 * IMPORTANT: 'width' and 'height' are assumed to be defined for any code
 * using these macros
 */
#define BR(ROW)   (((ROW) < 0) ? (-(ROW)) :      \
  (((ROW) >= height) ? (height-(ROW)+height-2) : \
    (ROW)))
#define BC(COL)   (((COL) < 0) ? (-(COL)) :         \
  (((COL) >= width) ? (width - (COL) + width - 2) : \
    (COL)))

/*
 * Optimized variants of the BR and BC macros above when the bound to check
 * against (upper or lower) is known by the caller.
 */
#define BRL(ROW) (((ROW) < 0) ? -(ROW) : (ROW))
#define BRU(ROW) (((ROW) >= height) ? (height-(ROW)+height-2) : (ROW))
#define BCL(COL) (((COL) < 0) ? -(COL) : (COL))
#define BCU(COL) (((COL) >= width) ? (width-(COL)+width-2) : (COL))

/* Hrlregion */
#define HRLReset(RL)                                                  \
  {                                                                   \
    (RL)->feature.def.all = 0;                                        \
    (RL)->feature.shape = 0;                                          \
    (RL)->is_compl = FALSE;                                           \
    (RL)->num = 0;                                                    \
    (RL)->rl = (Hrun*)(((HBYTE*)(void*)&(RL)->rl)+sizeof((RL)->rl));  \
  }

#define HRLSize(NumRuns) ((size_t)((NumRuns) * sizeof(Hrun) + \
                                   (sizeof(Hrlregion))))

/* Binaerbild */
#define HTestBit(D,P) ((D)[(P)>>3] & (1<<(7-((P)&7))))

#define HDelBit(D,P) (D)[(P)>>3] &= (UINT1)(~(1<<(7-((P)&7))))

#define HSetBit(D,P) (D)[(P)>>3] |= (UINT1)(1<<(7-((P)&7)))

/* Koordinaten */
#define HLinCoor(L,C,W) (((INT4_8)(L)*(INT4_8)(W))+(INT4_8)(C))

#define HXLinCoor(L,C,W) HLinCoor(L,C,W)

#define HCol(K,W) (HIMGCOOR)(((K) % (W)))

#define HRow(K,W) (HIMGCOOR)(((K) / (W)))

#define CB(RL,I,W) HLinCoor((RL)[I].l,(RL)[I].cb,W)

#define CE(RL,I,W) HLinCoor((RL)[I].l,(RL)[I].ce,W)


#define FLinCoor(R,C,H) ((C)*(H)+(R))


/* misc */
#ifndef SGN
#define SGN(X) (((X)==0)?0:(((X)>0)?1:(-1)))
#endif

#ifndef ODD
#define ODD(X) ((X) % 2)
#endif

#ifndef EVEN
#define EVEN(X) (!((X)%2))
#endif

#ifndef MIN
#define MIN(X,Y) (((X)>(Y))?(Y):(X))
#endif

#ifndef MAX
#define MAX(X,Y) (((X)>(Y))?(X):(Y))
#endif

#define DToINT4_8(Val) ((Val)<(double)INT4_8_MIN?INT4_8_MIN: \
                        ((Val)<INT_4_8_MAXDOUBLE?(INT4_8)(Val): \
                        (((INT4_8_MIN==(INT4_8)(Val))&&((Val)>0))?INT4_8_MAX: \
                        ((INT4_8)(Val)))))
#define DToINT4(Val) ((INT4)MIN((double)INT4_MAX,MAX((double)INT4_MIN,(Val))))
#define DToINT2(Val) ((INT2)MIN((double)INT2_MAX,MAX((double)INT2_MIN,(Val))))
#define DToINT(Val) ((HINT)MIN((double)INT_MAX,MAX((double)INT_MIN,(Val))))

#define HInsideImage(R,C,WIDTH,HEIGHT)                                  \
  ((((R)>=0) && ((C)>=0) && ((R)<(HEIGHT)) && ((C)<(WIDTH)))?TRUE:FALSE)


#if !defined HCkP
# if !defined(NO_SPY) && !defined(HC_FAST)
#  define HCkP(Proc)                                                    \
   XHCkP(Proc)
#  define XHCkP(Proc)                                                   \
do{                                                                     \
  Herror _H_ERR;                                                        \
  Herror _H_ERR_P;                                                      \
  if (IOGetSpyProcCallSwitch())                                         \
    IOSpyProcCall(#Proc,__LINE__,__FILE__);                             \
  if ( HIsError(_H_ERR = (Proc)))                                       \
  {                                                                     \
    if( HIsError(_H_ERR_P = HProcessErr(#Proc,_H_ERR,__LINE__,__FILE__))) \
      return(_H_ERR_P);                                                 \
    return(_H_ERR);                                                     \
  }                                                                     \
} while(0)
# else
#  define HCkP(Proc)                            \
   XHCkP(Proc)
#  define XHCkP(Proc)                           \
do {                                            \
  Herror _H_ERR;                                \
  if (HIsError(_H_ERR = (Proc)))                \
  {                                             \
    return(_H_ERR);                             \
  }                                             \
} while(0)
# endif
#endif /* if not defined HCkP */

#if !defined(NO_SPY) && !defined(HC_FAST)
# define HCkPCloseFile(Proc,File)                                       \
  XHCkPCloseFile(Proc,File)
# define XHCkPCloseFile(Proc,File)                                      \
do {                                                                    \
    Herror ERR;                                                         \
    Herror H_ERR_P;                                                     \
    if (IOGetSpyProcCallSwitch())                                       \
      IOSpyProcCall(#Proc,__LINE__,__FILE__);                           \
    if ((ERR = (Proc)) != H_MSG_OK)                                     \
    {                                                                   \
      fclose(File);                                                     \
      if( (H_ERR_P = HProcessErr(#Proc,ERR,__LINE__,__FILE__)) != H_MSG_OK) \
        return(H_ERR_P);                                                \
      return(ERR);                                                      \
    }                                                                   \
} while(0)
#else
# define HCkPCloseFile(Proc,File)                \
  XHCkPCloseFile(Proc,File)
# define XHCkPCloseFile(Proc,File)               \
do {                                              \
    Herror ERR;                                  \
    if ((ERR = (Proc)) != H_MSG_OK)              \
    {                                            \
      fclose(File);                              \
      return(ERR);                               \
    }                                            \
} while(0)
#endif

#if !defined(NO_SPY) && !defined(HC_FAST)
#define HCkPasync(Proc,GapingFlag,ComplFlag,ErrFlag)                    \
do {                                                                    \
  Herror ERR,H_ERR_P;                                                   \
  if(IOGetSpyProcCallSwitch())                                           \
    IOSpyProcCall(#Proc,__LINE__,__FILE__);                             \
  if( (ERR = Proc) != H_MSG_OK)                                         \
  {                                                                     \
    if( (H_ERR_P = HProcessErr(#Proc,ERR,__LINE__,__FILE__)) != H_MSG_OK) \
    {                                                                   \
      if(GapingFlag == FALSE)                                           \
      {                                                                 \
        *ErrFlag = H_ERR_P;                                             \
        *ComplFlag = TRUE;                                              \
      }                                                                 \
      return(H_ERR_P);                                                  \
    }                                                                   \
    if(GapingFlag == FALSE)                                             \
    {                                                                   \
      *ErrFlag = ERR;                                                   \
      *ComplFlag = TRUE;                                                \
    }                                                                   \
    return(ERR);                                                        \
  }                                                                     \
} while(0)
#else
#define HCkPasync(Proc,GapingFlag,ComplFlag,ErrFlag)                    \
do {                                                                    \
  Herror ERR;                                                           \
  if( (ERR = Proc) != H_MSG_OK)                                         \
  {                                                                     \
    if(GapingFlag == FALSE)                                             \
    {                                                                   \
      *ErrFlag = ERR;                                                   \
      *ComplFlag = TRUE;                                                \
    }                                                                   \
    return(ERR);                                                        \
  }                                                                     \
} while(0)
#endif

#define HCkE(ERR) XHCkE(ERR)
#if defined(HC_FAST) || defined (NO_SPY)
#define XHCkE(ERR) {if (ERR != H_MSG_OK) return(ERR);}
#else
#define XHCkE(ERR)                                    \
do {                                                  \
    if (ERR != H_MSG_OK)                              \
    {                                                 \
      if (IOGetSpyProcCallSwitch())                    \
        (void)HProcessErr("-",ERR,__LINE__,__FILE__); \
      return(ERR);                                    \
    }                                                 \
} while(0)
#endif

#define HCkPME(ERR,PROC) XHCkPME(ERR,PROC)
#if defined(HC_FAST) || defined (NO_SPY)
#define XHCkPME(ERR,PROC)                       \
do {                                            \
  Herror _terr;                                 \
  if (H_MSG_OK!=(_terr=(PROC))) (ERR)=_terr;    \
} while(0)
#else
#define XHCkPME(ERR,PROC)                             \
  { Herror _terr;                                     \
    if (H_MSG_OK!=(_terr=(PROC)))                     \
    {                                                 \
      if (IOGetSpyProcCallSwitch())                    \
        (void)HProcessErr("-",ERR,__LINE__,__FILE__); \
      (ERR)=_terr;                                    \
    }                                                 \
  }
#endif

#define HCkNoObj(PROC_HANDLE)                            \
do {                                                     \
  HBOOL BOOL_PTR;                                        \
  if ((HNoInpObj(PROC_HANDLE, &BOOL_PTR) != H_MSG_OK) || \
      (BOOL_PTR == TRUE))                                \
  {                                                      \
    Herror N_OBJ_RESULT;                                 \
    HReadGV(PROC_HANDLE,HGNoObjResult,&N_OBJ_RESULT);    \
    return(N_OBJ_RESULT);                                \
  }                                                      \
} while(0)

#define HCkSingleInputObj(PROC_HANDLE, OBJ_NUM)                               \
  HCkP(HPCheckSingleInputObject(PROC_HANDLE, OBJ_NUM)) 

#define HCkOnlySqr(width,height) \
  if (!HIs2Pot(width) || (!HIs2Pot(height))) return(H_ERR_NPOT)

#define HIsError(ERR) ((ERR) != H_MSG_OK)
#define HIsMessage(ERR) ((ERR) == H_MSG_OK)

#ifdef HC_FAST
#define HCkRL(PROC_HANDLE,RL,PROC,IN_OUT)
#else
#define HCkRL(PROC_HANDLE,RL,PROC,IN_OUT)                               \
do {                                                                    \
  Herror H_ERR_RL;                                                      \
  INT4 CHECK_F;                                                         \
  HReadGV(PROC_HANDLE,HGcheck,&CHECK_F);                                \
  if (CHECK_F & CHECK_CHORD)                                            \
  {                                                                     \
    H_ERR_RL = HRLTest(PROC_HANDLE,RL,FALSE);                           \
    if (H_ERR_RL != H_MSG_OK)                                           \
    {                                                                   \
      (void)fprintf(stderr,"runlength error (%s) %s: #%u\n",            \
                    IN_OUT,PROC,H_ERR_RL);                              \
      (void)fprintf(stderr,"runlength data dump in file: <<%s>>\n",RL_DUMP); \
      HCkP(HRLDump(PROC_HANDLE,RL,RL_DUMP));                            \
      return(H_ERR_RL);                                                 \
    }                                                                   \
  }                                                                     \
} while(0)
#endif


#define LongToNet(L,N)                            \
{                                                 \
  unsigned char  *HH; HH = (unsigned char*)&(N);  \
  HH[0] = ((L) >> 24) & 255;                      \
  HH[1] = ((L) >> 16) & 255;                      \
  HH[2] = ((L) >> 8) & 255;                       \
  HH[3] = (L) & 255;                              \
}

#define NetToLong(N,L)                          \
{                                               \
  unsigned char *HH;                            \
  HH = (unsigned char*)&(N);                    \
  L = ((INT4)(HH[0]) << 24) |                   \
    ((INT4)(HH[1]) << 16) |                     \
    ((INT4)(HH[2]) << 8) |                      \
    ((INT4)(HH[3]));                            \
}

#define ShortToNet(S,N)                           \
{                                                 \
  unsigned char  *HH; HH = (unsigned char*)&(N);  \
  HH[0] = ((S) >> 8) & 255;                       \
  HH[1] = (S) & 255;                              \
}

#define NetToShort(N,S)                         \
{                                               \
  unsigned char *HH; HH = (unsigned char*)&(N); \
  S = ((short)(HH[0]) << 8) |                   \
    ((short)(HH[1]));                           \
}

#define HAllocStringMem(PROC_HANDLE,SIZE)              \
  HCkP(HPAllocStringMem(PROC_HANDLE,(size_t)SIZE))

/* macros for accessing input ctrl parameters
 *  - without copying
 *  - with type and/or number check
 *===========================================================================*/
#define HGetCParNum(PROC_HANDLE,Par,Num) {Herror ERR; \
    ERR = HPGetCParNum(PROC_HANDLE,Par,Num);          \
    if (ERR != H_MSG_OK) return(ERR); }

#if !defined(NO_SPY) && !defined(SMALL)
# define HGetPElemL(PROC_HANDLE,PAR,CONVERT,ELEM,N)                     \
  do{                                                                   \
    Herror _ERR;                                                        \
    _ERR = HPGetPElemL(PROC_HANDLE,PAR,CONVERT,ELEM,N);                 \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
    _ERR = IOSpyElem(PROC_HANDLE,PAR,*(INT4_8**)(ELEM),*(INT4_8*)(N),   \
                     LONG_PAR,TRUE);                                    \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
  }while(0)
#else
# define HGetPElemL(PROC_HANDLE,PAR,CONVERT,ELEM,N)                     \
  HCkP( HPGetPElemL(PROC_HANDLE,PAR,CONVERT,ELEM,N) )
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HGetPElemD(PROC_HANDLE,PAR,CONVERT,ELEM,N)                     \
  do{                                                                   \
    Herror _ERR;                                                        \
    _ERR = HPGetPElemD(PROC_HANDLE,PAR,CONVERT,ELEM,N);                 \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
    _ERR = IOSpyElem(PROC_HANDLE,PAR,*(double**)(ELEM),*(INT4_8*)(N),   \
                     DOUBLE_PAR,TRUE);                                  \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
  }while(0)
#else
# define HGetPElemD(PROC_HANDLE,PAR,CONVERT,ELEM,N)                     \
  HCkP( HPGetPElemD(PROC_HANDLE,PAR,CONVERT,ELEM,N) )
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HGetPElemS(PROC_HANDLE,PAR,CONVERT,ELEM,N)                     \
  do{                                                                   \
    Herror _ERR;                                                        \
    _ERR = HPGetPElemS(PROC_HANDLE,PAR,CONVERT,ELEM,N);                 \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
    _ERR = IOSpyElem(PROC_HANDLE,PAR,*(char***)(ELEM),*(INT4_8*)(N),    \
                     STRING_PAR,TRUE);                                  \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
  }while(0)
#else
# define HGetPElemS(PROC_HANDLE,PAR,CONVERT,ELEM,N)                     \
  HCkP( HPGetPElemS(PROC_HANDLE,PAR,CONVERT,ELEM,N) )
#endif

/* Retrives a single handle from an input parameter */
#define HGetCElemH1(PROC_HANDLE, PAR, HTYPE, ELEM)                            \
  HCkP(HPGetPElemH(PROC_HANDLE, PAR, HTYPE, 1, (void **)ELEM, NULL, FALSE))

/* Retrives all handles from an input parameter. The returned array contains
 * pointers to the data stored in the handles. It is freed automatically
 * when the operator finishes. */
#define HGetCElemH(PROC_HANDLE, PAR, HTYPE, ELEM, N)                          \
  HCkP(HPGetPElemH(PROC_HANDLE, PAR, HTYPE, -1, (void **)ELEM, N, TRUE))

/* Retrives given number of handles from an input parameter. The returned array
 * contains pointers to the data stored in the handles. It is freed
 * automatically when the operator finishes. */
#define HGetCElemHN(PROC_HANDLE, PAR, HTYPE, N, ELEM)                         \
  HCkP(HPGetPElemH(PROC_HANDLE, PAR, HTYPE, N, ELEM, TRUE))

#if !defined(NO_SPY) && !defined(SMALL)
# define HGetPElem(PROC_HANDLE,PAR,ELEM,N,TYPE)                         \
  do{                                                                   \
    Herror _ERR;                                                        \
    HPGetPElem(PROC_HANDLE,PAR,ELEM,N,TYPE);                            \
    _ERR = IOSpyElem(PROC_HANDLE,PAR,*(void**)(ELEM),*(INT4_8*)(N),     \
                     *(HINT*)(TYPE),TRUE);                              \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
  }while(0)
#else
# define HGetPElem(PROC_HANDLE,PAR,ELEM,N,TYPE)                         \
  HPGetPElem(PROC_HANDLE,PAR,ELEM,N,TYPE)
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HGetElemL(PROC_HANDLE,PAR,CONVERT,MEM_TYPE,ELEM,N)             \
  do{                                                                   \
    Herror _ERR;                                                        \
    _ERR = HPGetElemL(PROC_HANDLE,PAR,CONVERT,MEM_TYPE,ELEM,N);         \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
    _ERR = IOSpyElem(PROC_HANDLE,PAR,*(INT4_8**)(ELEM),*(INT4_8*)(N),   \
                     LONG_PAR,TRUE);                                    \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
  }while(0)
#else
# define HGetElemL(PROC_HANDLE,PAR,CONVERT,MEM_TYPE,ELEM,N)             \
  HCkP( HPGetElemL(PROC_HANDLE,PAR,CONVERT,MEM_TYPE,ELEM,N) )
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HGetElemD(PROC_HANDLE,PAR,CONVERT,MEM_TYPE,ELEM,N)             \
  do{                                                                   \
    Herror _ERR;                                                        \
    _ERR = HPGetElemD(PROC_HANDLE,PAR,CONVERT,MEM_TYPE,ELEM,N);         \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
    _ERR = IOSpyElem(PROC_HANDLE,PAR,*(double**)(ELEM),*(INT4_8*)(N),   \
                     DOUBLE_PAR,TRUE);                                  \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
  }while(0)
#else
# define HGetElemD(PROC_HANDLE,PAR,CONVERT,MEM_TYPE,ELEM,N)             \
  HCkP( HPGetElemD(PROC_HANDLE,PAR,CONVERT,MEM_TYPE,ELEM,N) )
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HGetElemS(PROC_HANDLE,PAR,CONVERT,MEM_TYPE,ELEM,N)             \
  do{                                                                   \
    Herror _ERR;                                                        \
    _ERR = HPGetElemS(PROC_HANDLE,PAR,CONVERT,MEM_TYPE,ELEM,N);         \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
    _ERR = IOSpyElem(PROC_HANDLE,PAR,*(char***)(ELEM),*(INT4_8*)(N),    \
                     STRING_PAR,TRUE);                                  \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
  }while(0)
#else
# define HGetElemS(PROC_HANDLE,PAR,CONVERT,MEM_TYPE,ELEM,N)             \
  HCkP( HPGetElemS(PROC_HANDLE,PAR,CONVERT,MEM_TYPE,ELEM,N) )
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HCopyElemL(PROC_HANDLE,PAR,CONVERT,ELEM,N)                     \
  do{                                                                   \
    Herror _ERR;                                                        \
    _ERR = HPCopyElemL(PROC_HANDLE,PAR,CONVERT,ELEM,N);                 \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
    _ERR = IOSpyElem(PROC_HANDLE,PAR,ELEM,*(INT4_8*)(N),LONG_PAR,TRUE); \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
  }while(0)
#else
# define HCopyElemL(PROC_HANDLE,PAR,CONVERT,ELEM,N)                     \
  HCkP( HPCopyElemL(PROC_HANDLE,PAR,CONVERT,ELEM,N) )
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HCopyElemD(PROC_HANDLE,PAR,CONVERT,ELEM,N)                     \
  do{                                                                   \
    Herror _ERR;                                                        \
    _ERR = HPCopyElemD(PROC_HANDLE,PAR,CONVERT,ELEM,N);                 \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
    _ERR = IOSpyElem(PROC_HANDLE,PAR,ELEM,*(INT4_8*)(N),DOUBLE_PAR,     \
                     TRUE);                                             \
    if (_ERR != H_MSG_OK) return(_ERR);                                 \
  }while(0)
#else
# define HCopyElemD(PROC_HANDLE,PAR,CONVERT,ELEM,N)                     \
  HCkP( HPCopyElemD(PROC_HANDLE,PAR,CONVERT,ELEM,N) )
#endif

/*
 * Note: since there is no easy way to implement the SPY functionality
 * for HCopyElemF, we don't bother.
 */
# define HCopyElemF(PROC_HANDLE,PAR,CONVERT,ELEM,N)     \
  HCkP( HPCopyElemF(PROC_HANDLE,PAR,CONVERT,ELEM,N) )


/* HGetPParN:
 *   specify the exact number of the read parameter (any type)
 *---------------------------------------------------------------------------*/
#if !defined(NO_SPY) && !defined(SMALL)
# define HGetPParN(PROC_HANDLE,PAR,NUM,VAL) {                   \
  INT4_8 _NUM;                                                  \
  Herror ERR = HPGetPPar(PROC_HANDLE,PAR,VAL,&_NUM);            \
  if (ERR != H_MSG_OK)            return ERR;                   \
  if (NUM != _NUM)                return (H_ERR_WIPN1-1)+(PAR); \
  ERR = IOSpyCPar(PROC_HANDLE,PAR,*VAL,_NUM,TRUE);              \
  if (ERR != H_MSG_OK) return ERR;                        }
#else
# define HGetPParN(PROC_HANDLE,PAR,NUM,VAL) {                   \
  INT4_8 _NUM;                                                  \
  Herror ERR = HPGetPPar(PROC_HANDLE,PAR,VAL,&_NUM);            \
  if (ERR != H_MSG_OK)            return ERR;                   \
  if (NUM != _NUM)                return (H_ERR_WIPN1-1)+(PAR); }
#endif


/* HGetPParMM:
 *    the value number of the read parameter is expected to be within a
 *    certain range
 *---------------------------------------------------------------------------*/
#if !defined(NO_SPY) && !defined(SMALL)
# define HGetPParMM(PROC_HANDLE,PAR,MIN,MAX,VAL,NUM) {          \
  Herror ERR = HPGetPPar(PROC_HANDLE,PAR,VAL,NUM);              \
  if (ERR != H_MSG_OK)            return ERR;                   \
  if (*NUM < MIN || *NUM > MAX)   return (H_ERR_WIPN1-1)+(PAR); \
  ERR = IOSpyCPar(PROC_HANDLE,PAR,*VAL,*(NUM),TRUE);            \
  if (ERR != H_MSG_OK) return ERR;                          }
#else
# define HGetPParMM(PROC_HANDLE,PAR,MIN,MAX,VAL,NUM) {          \
  Herror ERR = HPGetPPar(PROC_HANDLE,PAR,VAL,NUM);              \
  if (ERR != H_MSG_OK)            return ERR;                   \
  if (*NUM < MIN || *NUM > MAX)   return (H_ERR_WIPN1-1)+(PAR); }
#endif


/* HGetPParT:
 *   specify the expected type(s) of the read parameter
 *---------------------------------------------------------------------------*/
#if !defined(NO_SPY) && !defined(SMALL)
# define HGetPParT(PROC_HANDLE,PAR,TYPE,VAL,NUM) {                     \
  INT4_8 _IDX;                                                         \
  Herror ERR = HPGetPPar(PROC_HANDLE,PAR,VAL,NUM);                     \
  if (ERR != H_MSG_OK)                       return ERR;               \
  for (_IDX=0; _IDX<*(NUM); _IDX++)                                    \
    if (((TYPE) & (*(VAL))[_IDX].type) == 0) return (H_ERR_WIPT1-1)+(PAR); \
  ERR = IOSpyCPar(PROC_HANDLE,PAR,*(VAL),*(NUM),TRUE);                 \
  if (ERR != H_MSG_OK) return ERR;                                     }
#else
# define HGetPParT(PROC_HANDLE,PAR,TYPE,VAL,NUM) {                     \
  INT4_8 _IDX;                                                         \
  Herror ERR = HPGetPPar(PROC_HANDLE,PAR,VAL,NUM);                     \
  if (ERR != H_MSG_OK)                       return ERR;               \
  for (_IDX=0; _IDX<*(NUM); _IDX++)                                    \
    if (((TYPE) & (*(VAL))[_IDX].type) == 0) return (H_ERR_WIPT1-1)+(PAR); }
#endif


/* HGetPParTN:
 *   specify the exact number and the expected type(s) of the read parameter
 *---------------------------------------------------------------------------*/
#if !defined(NO_SPY) && !defined(SMALL)
# define HGetPParTN(PROC_HANDLE,PAR,TYPE,NUM,VAL) {                        \
  INT4_8 _IDX, _NUM;                                                       \
  Herror ERR = HPGetPPar(PROC_HANDLE,PAR,VAL,&_NUM);                       \
  if (ERR != H_MSG_OK)                    return ERR;                      \
  if ((NUM) != _NUM)                       return (H_ERR_WIPN1-1)+(PAR);   \
  for (_IDX=0; _IDX<_NUM; _IDX++)                                          \
    if (((TYPE) & (*(VAL))[_IDX].type) == 0) return (H_ERR_WIPT1-1)+(PAR); \
  ERR = IOSpyCPar(PROC_HANDLE,PAR,*(VAL),_NUM,TRUE);                       \
  if (ERR != H_MSG_OK) return ERR;                                     }
#else
# define HGetPParTN(PROC_HANDLE,PAR,TYPE,NUM,VAL) {                        \
  INT4_8 _IDX, _NUM;                                                       \
  Herror ERR = HPGetPPar(PROC_HANDLE,PAR,VAL,&_NUM);                       \
  if (ERR != H_MSG_OK)                     return ERR;                     \
  if ((NUM) != _NUM)                       return (H_ERR_WIPN1-1)+(PAR);   \
  for (_IDX=0; _IDX<_NUM; _IDX++)                                          \
    if (((TYPE) & (*(VAL))[_IDX].type) == 0) return (H_ERR_WIPT1-1)+(PAR); }
#endif


/* HGetPParTMM:
 *   specify a range for the number of the read parameters as well as
 *   the expected type(s)
 *---------------------------------------------------------------------------*/
#if !defined(NO_SPY) && !defined(SMALL)
# define HGetPParTMM(PROC_HANDLE,PAR,TYPE,MIN,MAX,VAL,NUM) {               \
  INT4_8 _IDX;                                                             \
  Herror ERR = HPGetPPar(PROC_HANDLE,PAR,VAL,NUM);                         \
  if (ERR != H_MSG_OK)                    return ERR;                      \
  if (*(NUM) < MIN || *(NUM) > MAX)       return (H_ERR_WIPN1-1)+(PAR);    \
  for (_IDX=0; _IDX<*(NUM); _IDX++)                                        \
    if (((TYPE) & (*(VAL))[_IDX].type) == 0) return (H_ERR_WIPT1-1)+(PAR); \
  ERR = IOSpyCPar(PROC_HANDLE,PAR,*(VAL),*(NUM),TRUE);                     \
  if (ERR != H_MSG_OK) return ERR;                                     }
#else
# define HGetPParTMM(PROC_HANDLE,PAR,TYPE,MIN,MAX,VAL,NUM) {               \
  INT4_8 _IDX;                                                             \
  Herror ERR = HPGetPPar(PROC_HANDLE,PAR,VAL,NUM);                         \
  if (ERR != H_MSG_OK)                    return ERR;                      \
  if (*(NUM) < MIN || *(NUM) > MAX)       return (H_ERR_WIPN1-1)+(PAR);    \
  for (_IDX=0; _IDX<*(NUM); _IDX++)                                        \
    if (((TYPE) & (*(VAL))[_IDX].type) == 0) return (H_ERR_WIPT1-1)+(PAR); }
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HGetPPar(PROC_HANDLE,P,V,N) {Herror ERR;       \
    ERR = HPGetPPar(PROC_HANDLE,P,V,N);                 \
    if (ERR != H_MSG_OK) return(ERR);                   \
    ERR = IOSpyCPar(PROC_HANDLE,P,*V,*N,TRUE);          \
    if (ERR != H_MSG_OK) return(ERR); }
#else
# define HGetPPar(PROC_HANDLE,P,V,N) {Herror ERR;       \
    ERR = HPGetPPar(PROC_HANDLE,P,V,N);                 \
    if (ERR != H_MSG_OK) return(ERR); }
#endif


#if !defined(NO_SPY) && !defined(SMALL)
# define HGetPar(PROC_HANDLE,Par,Kind,Val,Num) {Herror ERR;     \
    ERR = HPGetPar(PROC_HANDLE,Par,ANY_ELEM,Kind,Val,(INT4_8)0, \
                   (INT4_8)10000000,Num);                       \
    if (ERR != H_MSG_OK) return(ERR);                           \
    ERR = IOSpyCPar(PROC_HANDLE,Index,Val,*(Num),TRUE);         \
    if (ERR != H_MSG_OK) return(ERR); }
#else
# define HGetPar(Par,Kind,Val,Num) {Herror ERR;     \
    ERR = HPGetPar(Par,ANY_ELEM,Kind,Val,(INT4_8)0, \
                   (INT4_8)10000000,Num);           \
    if (ERR != H_MSG_OK) return(ERR); }
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HGetSPar(PROC_HANDLE,Index,Type,Val,N) {INT4_8 _HN; Herror ERR;      \
    ERR = HPGetCPar(PROC_HANDLE,Index,Type,Val,(INT4_8)(N),(INT4_8)(N),&_HN); \
    if (ERR != H_MSG_OK) return(ERR);                                         \
    ERR = IOSpyCPar(PROC_HANDLE,Index,Val,_HN,TRUE);                          \
    if (ERR != H_MSG_OK) return(ERR); }
#else
# define HGetSPar(PROC_HANDLE,Index,Type,Val,N) {INT4_8 _HN; Herror ERR;      \
    ERR = HPGetCPar(PROC_HANDLE,Index,Type,Val,(INT4_8)(N),(INT4_8)(N),&_HN); \
    if (ERR != H_MSG_OK) return(ERR); }
#endif


#if !defined(NO_SPY) && !defined(SMALL)
# define HGetCPar(PROC_HANDLE,Index,InpType,Val,Min,Max,ResNum) {Herror ERR;  \
    ERR = HPGetCPar(PROC_HANDLE,Index,InpType,Val,(INT4_8)(Min),              \
                    (INT4_8)(Max),ResNum);                                    \
    if (ERR != H_MSG_OK) return(ERR);                                         \
    ERR = IOSpyCPar(PROC_HANDLE,Index,Val,(INT4_8)*ResNum,TRUE);              \
    if (ERR != H_MSG_OK) return(ERR); }
#else
# define HGetCPar(PROC_HANDLE,Index,InpType,Val,Min,Max,ResNum) {Herror ERR;  \
    ERR = HPGetCPar(PROC_HANDLE,Index,InpType,Val,(INT4_8)(Min),              \
                    (INT4_8)(Max),ResNum);                                    \
    if (ERR != H_MSG_OK) return(ERR); }
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HGetFPar(PROC_HANDLE,Index,Type,Val,Num)               \
{                                                               \
  int _HT; INT4_8 _HN; Herror ERR;                              \
  ERR = HPGetPar(PROC_HANDLE,Index,Type,&_HT,Val,(INT4_8)(Num), \
                 (INT4_8)(Num),&_HN);                           \
  if (ERR != H_MSG_OK) return(ERR);                             \
  ERR = IOSpyPar(PROC_HANDLE,Index,_HT,Val,_HN,TRUE);           \
  if (ERR != H_MSG_OK) return(ERR);                             \
}
#else
# define HGetFPar(PROC_HANDLE,Index,Type,Val,Num)               \
{                                                               \
  int _HT; INT4_8 _HN; Herror ERR;                              \
  ERR = HPGetPar(PROC_HANDLE,Index,Type,&_HT,Val,(INT4_8)(Num), \
                 (INT4_8)(Num),&_HN);                           \
  if (ERR != H_MSG_OK) return(ERR);                             \
}
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HGetEPar(PROC_HANDLE,Index,InpType,ResType,Val,Min,Max,Num)  \
{                                                                     \
  Herror ERR;                                                         \
  ERR = HPGetPar(PROC_HANDLE,Index,InpType,ResType,Val,(INT4_8)(Min), \
                 (INT4_8)(Max),Num);                                  \
  if (ERR != H_MSG_OK) return(ERR);                                   \
  ERR = IOSpyPar(PROC_HANDLE,Index,*ResType,Val,(INT4_8)*Num,TRUE);   \
  if (ERR != H_MSG_OK) return(ERR);                                   \
}
#else
# define HGetEPar(PROC_HANDLE,Index,InpType,ResType,Val,Min,Max,Num)  \
{                                                                     \
  Herror ERR;                                                         \
  ERR = HPGetPar(PROC_HANDLE,Index,InpType,ResType,Val,(INT4_8)(Min), \
                 (INT4_8)(Max),Num);                                  \
  if (ERR != H_MSG_OK) return(ERR);                                   \
}
#endif

/* macros for accessing ctrl output parameters
 *===========================================================================*/

#define HPutPElem(PROC_HANDLE,PAR,ELEM,NUM,TYPE)       \
do{                                                    \
  HCkP( HPPutPElem(PROC_HANDLE,PAR,ELEM,NUM,TYPE));    \
} while(0)

#define HPutElem(PROC_HANDLE,PAR,ELEM,NUM,TYPE)        \
do{                                                    \
  HCkP( HPPutElem(PROC_HANDLE,PAR,ELEM,NUM,TYPE));     \
} while(0)

#if !defined(NO_SPY) && !defined(SMALL)
# define HPutPar(PROC_HANDLE,P,K,V,N) {Herror ERR;        \
    ERR = IOSpyPar(PROC_HANDLE,P,K,V,(INT4_8)(N),FALSE);  \
    if (ERR != H_MSG_OK) return(ERR);                     \
    ERR = HPPutPar(PROC_HANDLE,P,K,V,(INT4_8)(N));        \
    if (ERR != H_MSG_OK) return(ERR); }
#else
# define HPutPar(PROC_HANDLE,P,K,V,N) {Herror ERR;  \
    ERR = HPPutPar(PROC_HANDLE,P,K,V,(INT4_8)(N));  \
    if (ERR != H_MSG_OK) return(ERR); }
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HPutCPar(PROC_HANDLE,P,V,N) {Herror ERR;       \
    ERR = IOSpyCPar(PROC_HANDLE,P,V,(INT4_8)N,FALSE);   \
    if (ERR != H_MSG_OK) return(ERR);                   \
    ERR = HPPutCPar(PROC_HANDLE,P,V,(INT4_8)(N));       \
    if (ERR != H_MSG_OK) return(ERR); }
#else
# define HPutCPar(PROC_HANDLE,P,V,N) {Herror ERR;       \
    ERR = HPPutCPar(PROC_HANDLE,P,V,(INT4_8)(N));       \
  if (ERR != H_MSG_OK) return(ERR); }
#endif

#if !defined(NO_SPY) && !defined(SMALL)
# define HPutPPar(PROC_HANDLE,P,V,N) {Herror ERR;       \
    ERR = IOSpyCPar(PROC_HANDLE,P,V,(INT4_8)N,FALSE);   \
    if (ERR != H_MSG_OK) return(ERR);                   \
    ERR = HPPutPPar(PROC_HANDLE,P,V,N);                 \
    if (ERR != H_MSG_OK) return(ERR); }
#else
# define HPutPPar(PROC_HANDLE,P,V,N) {Herror ERR; \
    ERR = HPPutPPar(PROC_HANDLE,P,V,N);           \
    if (ERR != H_MSG_OK) return(ERR); }
#endif

/* Write NUM handle references in the output control PAR.
 * HANDLETYPE is the type of the corresponding handles (const HhandleInfo*).
 * ELEM points to an array that holds NUM elements.
 *
 * IMPORTANT: The output control variable gains ownership of all pointers that
 *            are in ELEM.  When aborting an operator with an error,
 *            those values MUST NOT be cleared inside the operator's code,
 *            but will be cleared automatically when cleaning the output
 *            control variable.
 */
#define HPutElemH(PROC_HANDLE, PAR, ELEM, NUM, HANDLETYPE)                    \
  do                                                                          \
  {                                                                           \
    HCkP(HPPutElemH(PROC_HANDLE, PAR, ELEM, NUM, HANDLETYPE));                \
  } while (0)

/* Allocates one handle in the output control parameter PAR.
 * HANDLETYPE is the type of the corresponding handles (const HhandleInfo*).
 * ELEM is modified to point to where the new tool can be allocated.
 *
 * IMPORTANT: The output control variable gains ownership of the pointer in
 *            ELEM.  When aborting an operator with an error,
 *            the value MUST NOT be cleared inside the operator's code,
 *            but will be cleared automatically when cleaning the output
 *            control variable.
 */
#define HAllocOutputHandle(PROC_HANDLE, PAR, ELEM, HANDLETYPE)                    \
  HXAllocOutputHandle(PROC_HANDLE, PAR, (void ***)ELEM, HANDLETYPE)

/* macros for accessing iconic object parameters
 *===========================================================================*/

#define HNumOfChannels(PROC_HANDLE,OBJ,NUM)                     \
  HCkP(HPNumOfChannels(PROC_HANDLE,(HINT)1,                      \
                       (INT4_8)OBJ,NUM))

#define HAllObj(PROC_HANDLE,VAR,Hkey,I)                                \
  I=0;                                                                 \
  while ((HCheckInpObjNum(PROC_HANDLE,VAR,I+1) == TRUE) &&             \
         (HPGetObj(PROC_HANDLE,VAR,(INT4_8)++I, &Hkey) == H_MSG_OK) && \
         (Hkey != H_UNDEFINED))

#define HAllOutpObj(PROC_HANDLE,VAR,Hkey,I)                                \
  I=0;                                                                 \
  while ((HCheckOutpObjNum(PROC_HANDLE,VAR,I+1) == TRUE) &&             \
         (HPGetOutpObj(PROC_HANDLE,VAR,(INT4_8)++I, &Hkey) == H_MSG_OK) && \
         (Hkey != H_UNDEFINED))

#define HAllSegm(PROC_HANDLE,RL,IMAGES,MAX_CHANNELS,I)                  \
  I=0;                                                                  \
  while ((HCheckInpObjNum(PROC_HANDLE,1,I+1) == TRUE) &&                \
         (HPAllSegm(PROC_HANDLE,(INT4_8)++I,RL,IMAGES,MAX_CHANNELS) == H_MSG_OK))

#define HAllReg(PROC_HANDLE,RL,I)                             \
  I=0;                                                        \
  while ((HCheckInpObjNum(PROC_HANDLE,1,I+1) == TRUE) &&      \
         (HPAllReg(PROC_HANDLE,(INT4_8)++I,RL) == H_MSG_OK))

#define HAllFilter(PROC_HANDLE,RL,IMA_IN,IMA_OUT,MAX_CHANNELS,I)        \
  I=0;                                                                  \
  while ((HCheckInpObjNum(PROC_HANDLE,1,I+1) == TRUE) &&                \
         (HPAllFilter(PROC_HANDLE,(INT4_8)++I,RL,IMA_IN,IMA_OUT,MAX_CHANNELS) == H_MSG_OK))

#define HAllComp(PROC_HANDLE,OBJ_IN,IM_IN_KEY,IM_IN,INDEX)            \
  HPGetComp(PROC_HANDLE,OBJ_IN,IMAGE_INDEX,&IM_IN_KEY);               \
  if (IM_IN_KEY == H_UNDEFINED) return(H_ERR_AUDI);                   \
  for(INDEX = IMAGE_INDEX;                                            \
      (HPGetComp(PROC_HANDLE,OBJ_IN,INDEX,&IM_IN_KEY) == H_MSG_OK) && \
        (IM_IN_KEY != H_UNDEFINED) &&                                 \
        HPGetImage(PROC_HANDLE,IM_IN_KEY,&IM_IN) == H_MSG_OK;         \
      INDEX++)

#define HIfFirstComp(INDEX)  if(INDEX == IMAGE_INDEX)

#define HAllFilter2(PROC_HANDLE,RL,IMA_IN1,IMA_IN2,IMA_OUT,MAX_CHANNELS,I) \
  I=0;                                                                  \
  while ((HCheckInpObjNum(PROC_HANDLE,1,I+1) == TRUE) &&                \
         (HPAllFilter2(PROC_HANDLE,(INT4_8)++I,RL,IMA_IN1,IMA_IN2,IMA_OUT,MAX_CHANNELS) == H_MSG_OK))

#define HGetFRL(PROC_HANDLE,Key,region)         \
  HCkP(HPGetFRL(PROC_HANDLE,Key,region))

#define HGetRL(PROC_HANDLE,Key,region)          \
  HCkP(HPGetRL(PROC_HANDLE,Key,region))

#define HGetFDRL(PROC_HANDLE,Key,region)        \
  HCkP(HPGetFDRL(PROC_HANDLE,Key,region))

#define HGetDRL(PROC_HANDLE,Key,region)         \
  HCkP(HPGetDRL(PROC_HANDLE,Key,region))

#define HGetURL(PROC_HANDLE,Par,region)         \
  HCkP(HPGetURL(PROC_HANDLE,Par,region))

#define HGetImage(PROC_HANDLE,Key,Image)        \
  HCkP(HPGetImage(PROC_HANDLE,Key,Image))

#define HGetImageInfo(PROC_HANDLE,Key,Image)     \
  HCkP(HP0GetCDImage(PROC_HANDLE,Key,Image))

#define HGetDImage(PROC_HANDLE,Key,Comp,Image)  \
  HCkP(HPGetDImage(PROC_HANDLE,Key,Comp,Image))

#define HDelObj(PROC_HANDLE,Key) HCkP(HPDelObj(PROC_HANDLE,Key))

#define HNewRegion(PROC_HANDLE,RL) HCkP(HPNewRegion(PROC_HANDLE,RL))

#define HPushRegion(PROC_HANDLE,RL)  HCkP(HPPushRegion(PROC_HANDLE,RL))

#define HPushGlobalRegion(PROC_HANDLE,RL)  \
  HCkP(HPPushGlobalRegion(PROC_HANDLE,RL))

#define HDupObj(PROC_HANDLE,INDEX) HCkP(HPDupObj(PROC_HANDLE,INDEX))

#define HPutDRL(PROC_HANDLE,Key,RL,KEY_PTR)     \
  HCkP(HPPutDRL(PROC_HANDLE,Key,RL,KEY_PTR));

#define HPutPRLComp(PROC_HANDLE,ObjKey,RL,KEY_PTR)    \
  HCkP(HPPutPRLComp(PROC_HANDLE,ObjKey,RL,KEY_PTR));

#define HPutRect(PROC_HANDLE,Key,W,H) HCkP(HPPutRect(PROC_HANDLE,Key,W,H));

#define HPutImage(PROC_HANDLE,Image,Copy,KEY_PTR)   \
  HCkP(HPPutImage(PROC_HANDLE,Image,Copy,KEY_PTR));

#define HPutDImage(PROC_HANDLE,Key,Comp,Image,Copy,KEY_PTR)   \
  HCkP(HPPutDImage(PROC_HANDLE,Key,Comp,Image,Copy,KEY_PTR));

#define HDefObj(PROC_HANDLE,Obj,Key,Comp)       \
  HCkP(HPDefObj(PROC_HANDLE,Obj,Key,Comp));

#define HCrObj(PROC_HANDLE,Par,KEY_PTR) HCkP(HPCrObj(PROC_HANDLE,Par,KEY_PTR));

#define HCopyObj(PROC_HANDLE,Key,Par,KEY_PTR)   \
  HCkP(HPCopyObj(PROC_HANDLE,Key,Par,KEY_PTR));

#define HGetObj(PROC_HANDLE,Par,Num,KEY_PTR)            \
  HCkP(HPGetObj(PROC_HANDLE,Par,(INT4_8)Num,KEY_PTR));

#define HGetObjNum(PROC_HANDLE,Par,Num)         \
  HCkP(HPGetObjNum(PROC_HANDLE,Par,Num));

#define HGetComp(PROC_HANDLE,Obj,CompId,Id)     \
  HCkP(HPGetComp(PROC_HANDLE,Obj,CompId,Id));

#define HGetXLD(PROC_HANDLE,DBKEY,TYPE,XLD)                        \
{                                                                  \
  HINT TMP_TYPE; HINT NUM_USES; Hkey *USES;                          \
  HCkP(HPGetXLD(PROC_HANDLE,DBKEY,&TMP_TYPE,XLD,&USES,&NUM_USES)); \
  if (TYPE != TMP_TYPE) return(H_ERR_XLDWT);                       \
}

#define HGetSXLD(PROC_HANDLE,DBKEY,TYPE,XLD)                    \
{                                                               \
  HINT NUM_USES; Hkey *USES;                                     \
  HCkP(HPGetXLD(PROC_HANDLE,DBKEY,TYPE,XLD,&USES,&NUM_USES));   \
}

#define HCrXLD(PROC_HANDLE,PAR,XLD,TYPE,USES,NUM_USES,FREE,KEY_PTR)   \
  HCkP(HPCrXLD(PROC_HANDLE,PAR,XLD,TYPE,USES,NUM_USES,FREE,KEY_PTR));


/* -------- Makros for accessing HALCON operator context information ------- */
/* write a global context Variable ('normal' variable)                       */
#define HWriteGV(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0))
/* write a global context Variable ('normal' variable) with index            */
#define HWriteGVI(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,Index))
/* write a global context Variable (String)                                  */
#define HWriteGVS(ProcHandle,Element,String) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,String,(Hkey)NULL,0))
/* write a global context variable (String in element of Array)              */
#define HWriteGVSA(ProcHandle,Element,String,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,String,(Hkey)NULL,Index))
/* write a global context variable (HALCON object Key in element of Array)   */
#define HWriteGVKA(ProcHandle,Element,Key,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,(char *)NULL,Key,Index))
/* write a global context variable (Pointer in element of Array)             */
#define HWriteGVPA(ProcHandle,Element,Pointer,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,Pointer,(double)0,(char *)NULL,NULL,Index))
/* write a global context variable (element of Array)                        */
#define HWriteGVA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,Index))
/* write a global context Variable ('normal' variable); force changement of  */
/* the corresponding reference version                                       */
#define HWriteGVR(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_REF,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0))
/* write a global context Variable ('normal' variable) with index;           */
/* force changement of the corresponding reference version                   */
#define HWriteGVRI(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_REF,NULL,(double)Value,(char *)NULL,(Hkey)NULL,Index))
/* read a global context Variable ('normal' variable)                        */
#define HReadGV(ProcHandle,Element,Buffer) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Buffer,(double)0,(char *)NULL,(Hkey)NULL,0))
/* read a global context Variable (element of Array)                         */
#define HReadGVA(ProcHandle,Element,Buffer,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Buffer,(double)0,(char *)NULL,(Hkey)NULL,Index))
/* read a global context Variable from reference                             */
#define HReadGVR(ProcHandle,Element,Buffer) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_REF,Buffer,(double)0,(char *)NULL,(Hkey)NULL,0))
/* read a global context Variable from reference with index                  */
#define HReadGVRI(ProcHandle,Element,Buffer,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_REF,Buffer,(double)0,(char *)NULL,(Hkey)NULL,Index))
/* initialize a global context Variable (Array)                              */
#define HInitGVA(ProcHandle,Element,Address) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_INIT_INFO,Address,(double)0,(char *)NULL,(Hkey)NULL,0))
/* get the address of a global context Variable (Array)                      */
#define HGetAddrGVA(ProcHandle,Element,Buffer) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_GET_ADRESS,Buffer,(double)0,(char *)NULL,(Hkey)NULL,0))
/* realloc the memory of a global context Variable (Array)                   */
#define HReallocGVA(ProcHandle,Element,NewSize) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_REALLOC_A,NULL,(double)0,(char *)NULL,(Hkey)NULL,NewSize))


/* lock a global context mutex variable                                      */
#if defined H_PARALLEL
# define HLockGVM(ProcHandle,Element)                                   \
  HCkP(HAccessGlVar(ProcHandle,Element,GV_LOCK,NULL,(double)0,(char *)NULL, \
                    (Hkey)NULL,0))
/* lock a global context mutex variable and directly return Herror result    */
# define HLockGVMdirect(ProcHandle,Element)                             \
  HAccessGlVar(ProcHandle,Element,GV_LOCK,NULL,(double)0,(char *)NULL,  \
               (Hkey)NULL,0)
/* unlock a global context mutex variable                                    */
# define HUnlockGVM(ProcHandle,Element)                           \
  HCkP(HAccessGlVar(ProcHandle,Element,GV_UNLOCK,NULL,(double)0,  \
                    (char *)NULL,(Hkey)NULL,0))
/* unlock a global context mutex variable and directly return Herror result  */
# define HUnlockGVMdirect(ProcHandle,Element)                           \
  HAccessGlVar(ProcHandle,Element,GV_UNLOCK,NULL,(double)0,(char *)NULL, \
               (Hkey)NULL,0)
#else
# define HLockGVM(ProcHandle,Element)
# define HLockGVMdirect(ProcHandle,Element) H_MSG_OK
# define HUnlockGVM(ProcHandle,Element)
# define HUnlockGVMdirect(ProcHandle,Element) H_MSG_OK
#endif

/* calculate 'bitwise OR' with the content of a global context variable      */
#define HBOrGV(ProcHandle,Element,Value)                                \
  HCkP(HAccessGlVar(ProcHandle,Element,GV_BOR_INFO,NULL,(double)Value,  \
                    (char *)NULL,(Hkey)NULL,0))
/* calculate 'bitwise AND' with the content of a global context variable     */
#define HBAndGV(ProcHandle,Element,Value)                               \
  HCkP(HAccessGlVar(ProcHandle,Element,GV_BAND_INFO,NULL,(double)Value, \
                    (char *)NULL,(Hkey)NULL,0))
/* - - - -  old Makros for accessing HALCON operator context information - - */
/* (all accesses using the old makros should be replaced by the new ones in  */
/* the long term                                                             */
/* write an element of the global structure HInterInfo                       */
#define HWriteInterInfo(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0))
/* write an element of the global structure HInterInfo (String)              */
#define HWriteInterInfoS(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,0))
/* write an element of the global structure HInterInfo (String into Array)   */
#define HWriteInterInfoSA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,Index))
/* write an element of the global structure HInterInfo (Array element)       */
#define HWriteInterInfoA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,Index))
/* read an element of the global structure HInterInfo                        */
#define HReadInterInfo(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,0))
/* read an element of the global structure HInterInfo (Array element)        */
#define HReadInterInfoA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,Index))
/* initialize an element of the global structure HInterInfo (Array element)  */
#define HInitInterInfoA(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_INIT_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,0))

/* write an element of the global structure HSysComInfo                      */
#define HWriteSysComInfo(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0))
/* write an element of the global structure HSysComInfo (String)             */
#define HWriteSysComInfoS(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,0))
/* write an element of the global structure HSysComInfo (String into Array)  */
#define HWriteSysComInfoSA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,Index))
/* write an element of the global structure HSysComInfo (Array element)      */
#define HWriteSysComInfoA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,Index))
/* write an element of the global structure HSysInfoShared                   */
#define HWriteSysInfoShared(ProcHandle,Element,Value) \
HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0)
/* write an element of the global structure HSysInfoShared (String)          */
#define HWriteSysInfoSharedS(ProcHandle,Element,Value) \
HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,0)
/* write an element of the global structure HSysInfoShared(String into Array)*/
#define HWriteSysInfoSharedSA(ProcHandle,Element,Value,Index)           \
HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,Index)
/* write an element of the global structure HSysComInfo (Array element)      */
#define HWriteSysInfoSharedA(ProcHandle,Element,Value,Index)            \
HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,Index)

/* read an element of the global structure HSysComInfo                       */
#define HReadSysComInfo(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,0))
/* read an element of the global structure HSysComInfo (Array element)       */
#define HReadSysComInfoA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,Index))
/* initialize an element of the global structure HSysComInfo (Array element) */
#define HInitSysComInfoA(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_INIT_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,0))
/* write an element of the global structure HProcCallInfo                    */
#define HWriteProcCallInfo(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,0))
/* write an element of the global structure HProcCallInfo (String)           */
#define HWriteProcCallInfoS(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,0))
/* write an element of the global structure HProcCallInfo (String into Array)*/
#define HWriteProcCallInfoSA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,Value,(Hkey)NULL,Index))
/* write an element of the global structure HProcCallInfo (Key into Array)   */
#define HWriteProcCallInfoKA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)0,(char *)NULL,Value,Index))
/* write an element of the global structure HProcCallInfo (Array element)    */
#define HWriteProcCallInfoA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_WRITE_INFO,NULL,(double)Value,(char *)NULL,(Hkey)NULL,Index))
/* Lesen eines Elements der globalen Struktur HProcCallInfo                  */
#define HReadProcCallInfo(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,0))
/* read an element of the global structure HProcCallInfo                     */
#define HReadProcCallInfoA(ProcHandle,Element,Value,Index) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_READ_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,Index))
/* initialize an element of the global structure HProcCallInfo (Array)       */
#define HInitProcCallInfoA(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_INIT_INFO,Value,(double)0,(char *)NULL,(Hkey)NULL,0))
/* get the address of an array element of the global structure HProcCallInfo */
#define HGetAdrProcCallInfoA(ProcHandle,Element,Value) \
HCkP(HAccessGlVar(ProcHandle,Element,GV_GET_ADRESS,Value,(double)0,(char *)NULL,(Hkey)NULL,0))

#endif /* HMACRO_H */

