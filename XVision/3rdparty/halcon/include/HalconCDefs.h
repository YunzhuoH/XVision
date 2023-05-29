/*****************************************************************************
 * HalconCDefs.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Defines, types, and declarations for HALCON/C
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 ****************************************************************************/

#ifndef HALCON_C_DEFS_H
#define HALCON_C_DEFS_H

#include "HParallel.h"
#include "HIntDef.h"
#include "HDeclSpec.h"
#include "HErrorDef.h"
#include "HConst.h"
#include "HBase.h"
#include "IPType.h"
#include "HMacro.h"
#include "HExtern.h"

#include <string.h>

#define     UNDEF_TYPE  (-1)  /* Type after deleting a tuple               */
                              /* instead of STRING_PAR, INT_PAR, etc       */

/*
 * Data of type Hobject is a pointer into the HALCON object data base.
 * Thus it has to be treated as a magic number and must not be changed
 * by the user.
 */
typedef Hkey     Hobject;      /* Pointer to HALCON iconic data            */


/*
 * The data structure Htuple is used to pass control data to the
 * HALCON operators and get various kinds to non iconic data back
 * the the application.
 * Creating, access and deletion must only be done with the
 * supplied procedures. For global, static initialization, the
 * HTUPLE_INITIALIZER  macro is provided.
 */
typedef Hctuple Htuple;
#define HTUPLE_INITIALIZER HCTUPLE_INITIALIZER


/*
 * Constants
 */
#ifdef HC_LEGACY_PAR
#define _                 (Hlong*)0      /* anonyme Variable               */
#define _i                (Hlong*)0      /* anonyme Variable (long)        */
#define _d                (double*)0     /* anonyme Variable (double)      */
#define _s                (char*)0       /* anonyme Variable (string)      */
#define _t                (Htuple*)0     /* anonyme Variable (Tupel)       */
#endif

#define HALCONC_HNULL     ((Hphandle)0)  /* undefined handle               */

#define NO_OBJECTS        (Hobject)(1)   /* leere Objektliste          */
#define EMPTY_REGION      (Hobject)(2)   /* Objekt mit leerer Region   */
#if 0
#define FULL_REGION       (Hobject)(3)   /* Objekt mit maximaler Region*/
#endif


#if defined(__cplusplus)
extern "C" {
#endif

LIntExport void SetHcInterfaceStringEncodingIsUtf8(int is_utf8);
LIntExport int  IsHcInterfaceStringEncodingUtf8();


LIntExport void* CMalloc(size_t size, const char* file, INT4_8 line);
LIntExport void  CFree(void* mem, const char* file, INT4_8 line);

/* HALCON/C interface utility functions */

LIntExport void  Mcreate_tuple(Htuple* t, Hlong l, char const* file, int line);
LIntExport void  Mcreate_tuple_type(Htuple* t, Hlong l, int type,
                                    char const* file, int line);
LIntExport void  Mcopy_tuple(Htuple const* input, Htuple* output,
                             char const* file, int line);
LIntExport void  Mattach_tuple(Htuple* H_RESTRICT src, Htuple* H_RESTRICT dest,
                               char const* file, int line);
LIntExport void  Mresize_tuple(Htuple* input, Hlong LEN, char const* file,
                               int line);
LIntExport void  Mdestroy_tuple(Htuple* t, char const* file, int line);
LIntExport Hlong Mlength_tuple(Htuple const* t, char const* file, int line);
LIntExport void  Mset_i(Htuple* t, Hlong v, Hlong i, char const* file,
                        int line);
LIntExport void  Mset_d(Htuple* t, double v, Hlong i, char const* file,
                        int line);
LIntExport void  Mset_s(Htuple* t, char const* v, Hlong i, const char* file,
                        int line);
LIntExport void  Mset_s_from_utf8(Htuple* t, char const* v, Hlong i,
                                  const char* file, int line);
LIntExport void  Mset_s_from_local8bit(Htuple* t, char const* v, Hlong i,
                                       const char* file, int line);
#ifdef _WIN32
LIntExport void  Mset_s_from_wcs(Htuple* t, wchar_t const* v, Hlong i,
                                 const char* file, int line);
#endif
LIntExport void  Mset_s_len(Htuple* t, Hlong len, Hlong i, char const* file,
                            int line);

LIntExport void  Mset_h(Htuple* t, Hphandle v, Hlong i, const char* file,
                        int line);
LIntExport Hlong  Mget_i(Htuple const* t, Hlong i, char const* file, int line);
LIntExport double Mget_d(Htuple const* t, Hlong i, char const* file, int line);
LIntExport char const* Mget_s(Htuple const* t, Hlong i, char const* file,
                              int line);

LIntExport Hlong Mget_s_to_utf8(char* dest, Hlong dest_size, Htuple const* t,
                                Hlong i, char const* file, int line);
LIntExport Hlong Mget_s_to_local8bit(char* dest, Hlong dest_size,
                                     Htuple const* t, Hlong i,
                                     char const* file, int line);
#ifdef _WIN32
LIntExport Hlong Mget_s_to_wcs(wchar_t* dest, Hlong dest_size, Htuple const* t,
                               Hlong i, char const* file, int line);
#endif

LIntExport Hphandle Mget_h(Htuple const* t, Hlong i, char const* file,
                           int line);
LIntExport int Mget_type(Htuple const* t, Hlong i, char const* file, int line);

/* functions combining (re)creation and one value setting */
LIntExport void Mcreate_tuple_i(Htuple* t, Hlong value, char const* file,
                                int line);
LIntExport void Mcreate_tuple_d(Htuple* t, double value, char const* file,
                                int line);
LIntExport void Mcreate_tuple_s(Htuple* t, char const* value, char const* file,
                                int line);
LIntExport void Mcreate_tuple_s_from_utf8(Htuple* t, char const* value,
                                          char const* file, int line);
LIntExport void Mcreate_tuple_s_from_local8bit(Htuple* t, char const* value,
                                               char const* file, int line);
#ifdef _WIN32
LIntExport void Mcreate_tuple_s_from_wcs(Htuple* t, wchar_t const* value,
                                         char const* file, int line);
#endif
LIntExport void Mcreate_tuple_h(Htuple* t, Hphandle value, char const* file,
                                int line);
LIntExport void Mreuse_tuple_i(Htuple* t, Hlong value, char const* file,
                               int line);
LIntExport void Mreuse_tuple_d(Htuple* t, double value, char const* file,
                               int line);
LIntExport void Mreuse_tuple_s(Htuple* t, char const* value, char const* file,
                               int line);
LIntExport void Mreuse_tuple_s_from_utf8(Htuple* t, char const* value,
                                         char const* file, int line);
LIntExport void Mreuse_tuple_s_from_local8bit(Htuple* t, char const* value,
                                              char const* file, int line);
#ifdef _WIN32
LIntExport void Mreuse_tuple_s_from_wcs(Htuple* t, wchar_t const* value,
                                        char const* file, int line);
#endif
LIntExport void Mreuse_tuple_h(Htuple* t, Hphandle value, char const* file,
                               int line);


LIntExport void F_create_tuple_type(Htuple* H_RESTRICT htuple, Hlong len,
                                    HINT type);
LIntExport void F_create_tuple(Htuple* H_RESTRICT htuple, Hlong l);
LIntExport void F_copy_tuple(Htuple const* H_RESTRICT in,
                             Htuple* H_RESTRICT out);
LIntExport void F_attach_tuple(Htuple* H_RESTRICT src,
                               Htuple* H_RESTRICT dest);
LIntExport void F_resize_tuple(Htuple* H_RESTRICT htuple, Hlong LEN);
LIntExport void F_destroy_tuple(Htuple* H_RESTRICT htuple);
LIntExport void F_set_i(Htuple* H_RESTRICT t, Hlong value, Hlong idx);
LIntExport void F_set_d(Htuple* H_RESTRICT t, double value, Hlong idx);
LIntExport void F_set_s(Htuple* H_RESTRICT t, char const* H_RESTRICT val,
                        Hlong idx);
LIntExport void F_set_s_from_utf8(Htuple* H_RESTRICT t,
                                  char const* H_RESTRICT val, Hlong idx);
LIntExport void F_set_s_from_local8bit(Htuple* H_RESTRICT t,
                                       char const* H_RESTRICT val, Hlong idx);
#ifdef _WIN32
LIntExport void F_set_s_from_wcs(Htuple* H_RESTRICT t,
                                 wchar_t const* H_RESTRICT val, Hlong idx);
#endif
LIntExport void F_set_h(Htuple* H_RESTRICT t, Hphandle val, Hlong idx);

LIntExport void F_init_i(Htuple* H_RESTRICT t, Hlong value, Hlong idx);
LIntExport void F_init_d(Htuple* H_RESTRICT t, double value, Hlong idx);
LIntExport void F_init_s(Htuple* H_RESTRICT t, char const* H_RESTRICT value,
                         Hlong idx);
LIntExport void F_init_s_from_utf8(Htuple* H_RESTRICT t,
                                   char const* H_RESTRICT value, Hlong idx);
LIntExport void F_init_s_from_local8bit(Htuple* H_RESTRICT t,
                                        char const* H_RESTRICT value,
                                        Hlong                  idx);
#ifdef _WIN32
LIntExport void F_init_s_from_wcs(Htuple* H_RESTRICT t,
                                  wchar_t const* H_RESTRICT value, Hlong idx);
#endif
LIntExport void F_init_s_len(Htuple* H_RESTRICT t, Hlong len, Hlong idx);
LIntExport void F_init_h(Htuple* H_RESTRICT t, Hphandle value, Hlong idx);

LIntExport Hlong       F_get_i(Htuple const* H_RESTRICT t, Hlong idx);
LIntExport double      F_get_d(Htuple const* H_RESTRICT t, Hlong idx);
LIntExport char const* F_get_s(Htuple const* H_RESTRICT t, Hlong idx);
LIntExport Hlong F_get_s_to_utf8(char* dest, Hlong dest_size,
                                 Htuple const* H_RESTRICT t, Hlong i);
LIntExport Hlong F_get_s_to_local8bit(char* dest, Hlong dest_size,
                                      Htuple const* H_RESTRICT t, Hlong i);
#ifdef _WIN32
LIntExport Hlong F_get_s_to_wcs(wchar_t* dest, Hlong dest_size,
                                Htuple const* H_RESTRICT t, Hlong i);
#endif
LIntExport Hphandle F_get_h(Htuple const* H_RESTRICT t, Hlong idx);


/* functions combining (re)creation and one value setting */
LIntExport void F_create_tuple_i(Htuple* H_RESTRICT t, Hlong val);
LIntExport void F_create_tuple_d(Htuple* H_RESTRICT t, double val);
LIntExport void F_create_tuple_s(Htuple* H_RESTRICT t, char const* val);
LIntExport void F_create_tuple_s_from_utf8(Htuple* H_RESTRICT t,
                                           char const*        val);
LIntExport void F_create_tuple_s_from_local8bit(Htuple* H_RESTRICT t,
                                                char const*        val);
#ifdef _WIN32
LIntExport void F_create_tuple_s_from_wcs(Htuple* H_RESTRICT t,
                                          wchar_t const*     val);
#endif
LIntExport void F_create_tuple_h(Htuple* H_RESTRICT t, Hphandle val);

LIntExport void F_reuse_tuple_i(Htuple* H_RESTRICT t, Hlong val);
LIntExport void F_reuse_tuple_d(Htuple* H_RESTRICT t, double val);
LIntExport void F_reuse_tuple_s(Htuple* H_RESTRICT t,
                                char const* H_RESTRICT val);
LIntExport void F_reuse_tuple_s_from_utf8(Htuple* H_RESTRICT t,
                                          char const* H_RESTRICT val);
LIntExport void F_reuse_tuple_s_from_local8bit(Htuple* H_RESTRICT t,
                                               char const* H_RESTRICT val);
#ifdef _WIN32
LIntExport void F_reuse_tuple_s_from_wcs(Htuple* H_RESTRICT t,
                                         wchar_t const* H_RESTRICT val);
#endif
LIntExport void F_reuse_tuple_h(Htuple* H_RESTRICT t, Hphandle val);


/* new generic HALCON operator call style:
 * - the operator is called by an id that is returned by get_operator_id;
 *    attention: this id may differ for different HALCON versions
 * - the tuple arrays are passed directly to the call -> this method is
 *   thread safe
 *---------------------------------------------------------------------------*/
LIntExport int    get_operator_id(char const* name);
LIntExport Herror T_call_halcon_by_id(int id, Hobject const in_objs[],
                                      Hobject      out_objs[],
                                      Htuple const in_ctrls[],
                                      Htuple       out_ctrls[]);

/* old generic HALCON operator call style (legacy)
 * the parameters are set befor calling T_call_halcon with set_*_[t|o]par
 * this approach is not thread safe without additional synchronisation
 *---------------------------------------------------------------------------*/
LIntExport void   set_in_tpar(Htuple* t, int i);
LIntExport void   set_out_tpar(Htuple* t, int i);
LIntExport void   set_in_opar(Hobject o, int i);
LIntExport void   set_out_opar(Hobject* o, int i);
LIntExport Herror T_call_halcon(const char* n);

/* obsolete method, kept inside for compatibility reasons, returns always 0
 *---------------------------------------------------------------------------*/
LIntExport Hlong num_tuple(void);

/*
 * The following functions can be used to emulate the behavior of
 * HDevelop graphics windows for HALCON graphics windows. They are primarily
 * intended for usage in C programs exported from HDevelop programs containing
 * HDevelop window operators (e.g. dev_set_window, dev_open_window,
 * dev_close_window...). On multithreaded systems, every thread has its own
 * graphics windows stack.
 *---------------------------------------------------------------------------*/
LIntExport void hdev_window_stack_push(const Htuple win_handle);
LIntExport void hdev_window_stack_pop(Htuple* win_handle);
LIntExport void hdev_window_stack_get_active(Htuple* win_handle);
LIntExport void hdev_window_stack_set_active(const Htuple win_handle);
LIntExport int  hdev_window_stack_is_open(void);
LIntExport void hdev_window_stack_close_all(void);

/*
 * The following functions are kept for downward compatibility only.
 * DO NOT USE !!!
 * Use the hdev_window_stack_... functions instead !
 *---------------------------------------------------------------------------*/
LIntExport void  window_stack_push(Hlong win_handle);
LIntExport Hlong window_stack_pop(void);
LIntExport Hlong window_stack_get_active(void);
LIntExport void  window_stack_set_active(Hlong win_handle);
LIntExport int   window_stack_is_open(void);
LIntExport void  window_stack_close_all(void);

/* Used in C programs exported from HDevelop */
LIntExport Herror replace_elements(Htuple* htuple, Htuple* index,
                                   Htuple const* replace_val);

#if defined(__cplusplus)
}
#endif

#if !defined(H_NO_INLINE) && !defined(H_INLINE)
#  define H_NO_INLINE
#endif


/*
 * Short versions for the tuple operators
 */
#define CT(TUP,LEN)              create_tuple(TUP,LEN)
#define CPT(TUP,Out)             copy_tuple(TUP,Out)
#define RT(TUP,LEN)              resize_tuple(TUP,LEN)
#define DT(TUP)                  destroy_tuple(TUP)
#define LT(TUP)                  length_tuple(TUP)
#define SS(TUP,VAL,IDX)          set_s(TUP,VAL,IDX)
#define SS_U8(TUP,VAL,IDX)       set_s_from_utf8(TUP,VAL,IDX)
#define SS_LOC(TUP,VAL,IDX)      set_s_from_local8bit(TUP,VAL,IDX)
#ifdef _WIN32
#define SS_W(TUP,VAL,IDX)        set_s_from_wcs(TUP,VAL,IDX)
#endif
#define SI(TUP,VAL,IDX)          set_i(TUP,VAL,IDX)
#define SD(TUP,VAL,IDX)          set_d(TUP,VAL,IDX)
#define SH(TUP,VAL,IDX)          set_h(TUP,VAL,IDX)
#define GS(TUP,IDX)              get_s(TUP,IDX)
#define GS_U8(BUF,SIZE,TUP,IDX)  get_s_to_utf8(BUF,SIZE,TUP,IDX)
#define GS_LOC(BUF,SIZE,TUP,IDX) get_s_to_local8bit(BUF,SIZE,TUP,IDX)
#ifdef _WIN32
#define GS_W(BUF,SIZE,TUP,IDX)   get_s_to_wcs(BUF,SIZE,TUP,IDX)
#endif
#define GI(TUP,IDX)              get_i(TUP,IDX)
#define GD(TUP,IDX)              get_d(TUP,IDX)
#define GH(TUP,IDX)              get_h(TUP,IDX)
#define GT(TUP,IDX)              get_type(TUP,IDX)

#define TC(PROC_NAME)            T_call_halcon(PROC_NAME)
#define IT(TUP,NUM)              set_in_tpar(&(TUP),NUM)
#define OT(TUP,NUM)              set_out_tpar(TUP,NUM)
#define IO(OBJ,NUM)              set_in_opar(OBJ,NUM)
#define OO(OBJ,NUM)              set_out_opar(OBJ,NUM)


#ifdef HC_FAST /* Compiler option for tested programs */


#  define C_TUPLE_IDX_TYPE(PCTUPLE, IDX)                                      \
    ((MIXED_PAR != (PCTUPLE)->type)                                           \
         ? (PCTUPLE)->type                                                    \
         : (IDX < (PCTUPLE)->num) ? (PCTUPLE)->elem.cpar[IDX].type            \
                                  : UNDEF_PAR)

#  define length_tuple(TUP) ((TUP).num)
#  define get_type(TUP, IDX) (C_TUPLE_IDX_TYPE(&(TUP), IDX))

#  define create_tuple(TUP, LEN) F_create_tuple(TUP, LEN)
#  define create_tuple_type(TUP, LEN, TYP) F_create_tuple_type(TUP, LEN, TYP)
#  define destroy_tuple(TUP) F_destroy_tuple(&(TUP))
#  define copy_tuple(TUP_I, TUP_O) F_copy_tuple(&(TUP_I), TUP_O)
#  define attach_tuple(TUP_S, TUP_D) F_attach_tuple(&(TUP_S), TUP_D)
#  define resize_tuple(TUP, LEN) F_resize_tuple(TUP, LEN)

#  define create_tuple_i(TUP, VAL) F_create_tuple_i(TUP, VAL)
#  define create_tuple_d(TUP, VAL) F_create_tuple_d(TUP, VAL)
#  define create_tuple_s(TUP, VAL) F_create_tuple_s(TUP, VAL)
#  define create_tuple_s_from_utf8(TUP, VAL)                                  \
    F_create_tuple_s_from_utf8(TUP, VAL)
#  define create_tuple_s_from_local8bit(TUP, VAL)                             \
    F_create_tuple_s_from_local8bit(TUP, VAL)
#  ifdef _WIN32
#    define create_tuple_s_from_wcs(TUP, VAL)                                 \
      F_create_tuple_s_from_wcs(TUP, VAL)
#  endif
#  define create_tuple_h(TUP, VAL) F_create_tuple_h(TUP, VAL)

#  define reuse_tuple_i(TUP, VAL) F_reuse_tuple_i(TUP, VAL)
#  define reuse_tuple_d(TUP, VAL) F_reuse_tuple_d(TUP, VAL)
#  define reuse_tuple_s(TUP, VAL) F_reuse_tuple_s(TUP, VAL)
#  define reuse_tuple_s_from_utf8(TUP, VAL) F_reuse_tuple_s_from_utf8(TUP, VAL)
#  define reuse_tuple_s_from_local8bit(TUP, VAL)                              \
    F_reuse_tuple_s_from_local8bit(TUP, VAL)
#  ifdef _WIN32
#    define reuse_tuple_s_from_wcs(TUP, VAL) F_reuse_tuple_s_from_wcs(TUP, VAL)
#  endif
#  define reuse_tuple_h(TUP, VAL) F_reuse_tuple_h(TUP, VAL)

#  define init_i(TUP, VAL, IDX) F_init_i(&(TUP), VAL, IDX)
#  define init_d(TUP, VAL, IDX) F_init_d(&(TUP), VAL, IDX)
#  define init_s(TUP, VAL, IDX) F_init_s(&(TUP), VAL, IDX)
#  define init_s_len(TUP, LEN, IDX) F_init_s_len(&(TUP), LEN, IDX)
#  define init_s_from_utf8(TUP, VAL, IDX) F_init_s_from_utf8(&(TUP), VAL, IDX)
#  define init_s_from_local8bit(TUP, VAL, IDX)                                \
    F_init_s_from_local8bit(&(TUP), VAL, IDX)
#  ifdef _WIN32
#    define init_s_from_wcs(TUP, VAL, IDX) F_init_s_from_wcs(&(TUP), VAL, IDX)
#  endif
#  define init_h(TUP, VAL, IDX) F_init_h(&(TUP), VAL, IDX)

#  define at_i(TUP, IDX)                                                      \
    ((LONG_PAR == (TUP).type) ? (TUP).elem.l[IDX]                             \
                              : (TUP).elem.cpar[IDX].par.l /*MIXED_PAR*/)
#  define at_d(TUP, IDX)                                                      \
    ((DOUBLE_PAR == (TUP).type) ? (TUP).elem.f[IDX]                           \
                                : (TUP).elem.cpar[IDX].par.f /*MIXED_PAR*/)
#  define at_s(TUP, IDX)                                                      \
    ((char const*const)((STRING_PAR == (TUP).type)                            \
                                ? (TUP).elem.s[IDX]                           \
                                : (TUP).elem.cpar[IDX].par.s /*MIXED_PAR*/)
#  define at_h(TUP, IDX)                                                      \
    ((char const*const)((HANDLE_PAR == (TUP).type)                            \
                                ? (TUP).elem.h[IDX]                           \
                                : (TUP).elem.cpar[IDX].par.h /*MIXED_PAR*/)


#  define set_i(TUP, VAL, IDX) F_set_i(&(TUP), VAL, IDX)
#  define set_d(TUP, VAL, IDX) F_set_d(&(TUP), VAL, IDX)
#  define set_s(TUP, VAL, IDX) F_set_s(&(TUP), VAL, IDX)
#  define set_s_from_utf8(TUP, VAL, IDX) F_set_s_from_utf8(&(TUP), VAL, IDX)
#  define set_s_from_local8bit(TUP, VAL, IDX)                                 \
    F_set_s_from_local8bit(&(TUP), VAL, IDX)
#  ifdef _WIN32
#    define set_s_from_wcs(TUP, VAL, IDX) F_set_s_from_wcs(&(TUP), VAL, IDX)
#  endif
#  define set_h(TUP, VAL, IDX) F_set_h(&(TUP), VAL, IDX)

#  define get_i(TUP, IDX) F_get_i(&(TUP), IDX)
#  define get_d(TUP, IDX) F_get_d(&(TUP), IDX)
#  define get_s(TUP, IDX) F_get_s(&(TUP), IDX)
#  define get_s_to_utf8(BUF, SIZE, TUP, IDX)                                  \
    F_get_s_to_utf8(BUF, SIZE, &(TUP), IDX)
#  define get_s_to_local8bit(BUF, SIZE, TUP, IDX)                             \
    F_get_s_to_local8bit(BUF, SIZE, &(TUP), IDX)
#  ifdef _WIN32
#    define get_s_to_wcs(BUF, SIZE, TUP, IDX)                                 \
      F_get_to_wcs(BUF, SIZE, &(TUP), IDX)
#  endif
#  define get_h(TUP, IDX) F_get_h(&(TUP), IDX)


#else /* := #ifndef HC_FAST -> paranoiac version */


#  define create_tuple(TUP, LEN) Mcreate_tuple(TUP, LEN, __FILE__, __LINE__)
#  define create_tuple_type(TUP, LEN, TYP)                                    \
    Mcreate_tuple_type(TUP, LEN, TYP, __FILE__, __LINE__)
#  define destroy_tuple(TUP) Mdestroy_tuple(&(TUP), __FILE__, __LINE__)
#  define copy_tuple(TUP_I, TUP_O)                                            \
    Mcopy_tuple(&(TUP_I), TUP_O, __FILE__, __LINE__)
#  define attach_tuple(TUP_S, TUP_D)                                          \
    Mattach_tuple(&(TUP_S), TUP_D, __FILE__, __LINE__)
#  define resize_tuple(TUP, LEN) Mresize_tuple(TUP, LEN, __FILE__, __LINE__)

#  define length_tuple(TUP) Mlength_tuple(&(TUP), __FILE__, __LINE__)
#  define get_type(TUP, IDX) Mget_type(&(TUP), IDX, __FILE__, __LINE__)

#  define init_i(TUP, VAL, IDX) Mset_i(&(TUP), VAL, IDX, __FILE__, __LINE__)
#  define init_d(TUP, VAL, IDX) Mset_d(&(TUP), VAL, IDX, __FILE__, __LINE__)
#  define init_s(TUP, VAL, IDX) Mset_s(&(TUP), VAL, IDX, __FILE__, __LINE__)
#  define init_s_len(TUP, LEN, IDX)                                           \
    Mset_s_len(&(TUP), LEN, IDX, __FILE__, __LINE__)
#  define init_s_from_utf8(TUP, VAL, IDX)                                     \
    Minit_s_from_utf8(&(TUP), VAL, IDX, __FILE__, __LINE__)
#  define init_s_from_local8bit(TUP, VAL, IDX)                                \
    Minit_s_from_local8bit(&(TUP), VAL, IDX, __FILE__, __LINE__)
#  ifdef _WIN32
#    define init_s_from_wcs(TUP, VAL, IDX)                                    \
      Minit_s_from_wcs(&(TUP), VAL, IDX, __FILE__, __LINE__)
#  endif
#  define init_h(TUP, VAL, IDX) Mset_h(&(TUP), VAL, IDX, __FILE__, __LINE__)

#  define set_i(TUP, VAL, IDX) Mset_i(&(TUP), VAL, IDX, __FILE__, __LINE__)
#  define set_d(TUP, VAL, IDX) Mset_d(&(TUP), VAL, IDX, __FILE__, __LINE__)
#  define set_s(TUP, VAL, IDX) Mset_s(&(TUP), VAL, IDX, __FILE__, __LINE__)
#  define set_s_from_utf8(TUP, VAL, IDX)                                      \
    Mset_s_from_utf8(&(TUP), VAL, IDX, __FILE__, __LINE__)
#  define set_s_from_local8bit(TUP, VAL, IDX)                                 \
    Mset_s_from_local8bit(&(TUP), VAL, IDX, __FILE__, __LINE__)
#  ifdef _WIN32
#    define set_s_from_wcs(TUP, VAL, IDX)                                     \
      Mset_s_from_wcs(&(TUP), VAL, IDX, __FILE__, __LINE__)
#  endif
#  define set_h(TUP, VAL, IDX) Mset_h(&(TUP), VAL, IDX, __FILE__, __LINE__)

#  define get_i(TUP, IDX) Mget_i(&(TUP), IDX, __FILE__, __LINE__)
#  define get_d(TUP, IDX) Mget_d(&(TUP), IDX, __FILE__, __LINE__)
#  define get_s(TUP, IDX) Mget_s(&(TUP), IDX, __FILE__, __LINE__)
#  define get_h(TUP, IDX) Mget_h(&(TUP), IDX, __FILE__, __LINE__)
#  define get_s_to_utf8(BUF, SIZE, TUP, IDX)                                  \
    Mget_s_to_utf8(BUF, SIZE, &(TUP), IDX, __FILE__, __LINE__)
#  define get_s_to_local8bit(BUF, SIZE, TUP, IDX)                             \
    Mget_s_to_local8bit(BUF, SIZE, &(TUP), IDX, __FILE__, __LINE__)
#  ifdef _WIN32
#    define get_s_to_wcs(BUF, SIZE, TUP, IDX)                                 \
      Mget_s_to_wcs(BUF, SIZE, &(TUP), IDX, __FILE__, __LINE__)
#  endif

#  define at_i(TUP, IDX) Mget_i(&(TUP), IDX, __FILE__, __LINE__)
#  define at_d(TUP, IDX) Mget_d(&(TUP), IDX, __FILE__, __LINE__)
#  define at_s(TUP, IDX) Mget_s(&(TUP), IDX, __FILE__, __LINE__)
#  define at_h(TUP, IDX) Mget_h(&(TUP), IDX, __FILE__, __LINE__)

#  define create_tuple_i(TUP, VAL)                                            \
    Mcreate_tuple_i(TUP, VAL, __FILE__, __LINE__)
#  define create_tuple_d(TUP, VAL)                                            \
    Mcreate_tuple_d(TUP, VAL, __FILE__, __LINE__)
#  define create_tuple_s(TUP, VAL)                                            \
    Mcreate_tuple_s(TUP, VAL, __FILE__, __LINE__)
#  define create_tuple_h(TUP, VAL)                                            \
    Mcreate_tuple_h(TUP, VAL, __FILE__, __LINE__)
#  define create_tuple_s_from_utf8(TUP, VAL)                                  \
    Mcreate_tuple_s_from_utf8(TUP, VAL, __FILE__, __LINE__)
#  define create_tuple_s_from_local8bit(TUP, VAL)                             \
    Mcreate_tuple_s_from_local8bit(TUP, VAL, __FILE__, __LINE__)
#  ifdef _WIN32
#    define create_tuple_s_from_wcs(TUP, VAL)                                 \
      Mcreate_tuple_s_from_wcs(TUP, VAL, __FILE__, __LINE__)
#  endif

#  define reuse_tuple_i(TUP, VAL) Mreuse_tuple_i(TUP, VAL, __FILE__, __LINE__)
#  define reuse_tuple_d(TUP, VAL) Mreuse_tuple_d(TUP, VAL, __FILE__, __LINE__)
#  define reuse_tuple_s(TUP, VAL) Mreuse_tuple_s(TUP, VAL, __FILE__, __LINE__)
#  define reuse_tuple_h(TUP, VAL) Mreuse_tuple_h(TUP, VAL, __FILE__, __LINE__)
#  define reuse_tuple_s_from_utf8(TUP, VAL)                                   \
    Mreuse_tuple_s_from_utf8(TUP, VAL, __FILE__, __LINE__)
#  define reuse_tuple_s_from_local8bit(TUP, VAL)                              \
    Mreuse_tuple_s_from_local8bit(TUP, VAL, __FILE__, __LINE__)
#  ifdef _WIN32
#    define reuse_tuple_s_from_wcs(TUP, VAL)                                  \
      Mreuse_tuple_s_from_wcs(TUP, VAL, __FILE__, __LINE__)
#  endif


#endif  /* ifdef HC_FAST .. else */


#endif
