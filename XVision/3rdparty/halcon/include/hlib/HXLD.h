/*****************************************************************************
 * HXLD.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Extended Line Description
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 */


#ifndef HXLD_H
#define HXLD_H


#if defined(__cplusplus)
extern "C" {
#endif

extern HLibExport Herror HAllocXLDContSecure(Hproc_handle proc_handle,
                                             Hcont**      cont,
                                             HITEMCNT     num_points);

extern HLibExport Herror HAllocXLDCont(Hproc_handle proc_id, Hcont** cont,
                                       HITEMCNT num_points);

extern HLibExport Herror HAllocXLDContRC(Hproc_handle proc_id, Hcont* cont,
                                         HITEMCNT num_points);

extern HLibExport Herror HReallocXLDContRC(Hproc_handle proc_handle,
                                           HITEMCNT     num_points_new,
                                           Hcont*       cont);

extern HLibExport Herror HCopyXLDCont(Hproc_handle proc_id,
                                      const Hcont* H_RESTRICT cont_in,
                                      HBOOL                   preserve_attribs,
                                      HBOOL   preserve_global_attribs,
                                      Hcont** H_RESTRICT cont_out);

extern HLibExport Herror HCopyXLDContPart(Hproc_handle proc_id,
                                          const Hcont* H_RESTRICT cont_in,
                                          INT4_8 min_index, INT4_8 max_index,
                                          HBOOL   preserve_attribs,
                                          HBOOL   preserve_global_attribs,
                                          Hcont** H_RESTRICT cont_out);

extern HLibExport Herror HFreeXLDCont(Hproc_handle proc_id, Hcont* cont);
extern HLibExport Herror HLookupXLDContAttrib(const Hcont* H_RESTRICT cont,
                                              const char* H_RESTRICT name,
                                              INT4*                  indx);
extern HLibExport Herror HAddXLDContAttrib(Hproc_handle proc_id, Hcont* cont,
                                           const char* name, INT4* indx);

extern HLibExport Herror HLookupXLDContGlobalAttrib(
    const Hcont* H_RESTRICT cont, const char* H_RESTRICT name, INT4* indx);
extern HLibExport Herror HAddXLDContGlobalAttrib(Hproc_handle proc_id,
                                                 Hcont* cont, const char* name,
                                                 INT4* indx);

extern HLibExport Herror HXLDFreeContour(Hproc_handle proc_id, Hcont* cont);

extern HLibExport Herror HXLDFreePolygon(Hproc_handle proc_id, Hpoly* poly);

extern HLibExport Herror HXLDFreeParallel(Hproc_handle proc_id,
                                          Hpara_poly*  para);
extern HLibExport Herror HXLDFreeModParallel(Hproc_handle proc_id,
                                             Hmod_para*   mod_para);
extern HLibExport Herror HXLDFreeExtParallel(Hproc_handle proc_id,
                                             Hext_para*   ext_para);

extern HLibExport Herror HXLDCopyGlobalAttribsUntil(Hproc_handle proc_handle,
                                                    const Hcont* cont_from,
                                                    const char*  until_name,
                                                    Hcont*       cont_to);

#if defined(__cplusplus)
}
#endif


#endif
