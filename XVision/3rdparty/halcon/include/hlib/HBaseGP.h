/*****************************************************************************
 * HBaseGP.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Basic tools
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 */


#ifndef HBASEGP_H
#define HBASEGP_H


#if defined(__cplusplus)
extern "C" {
#endif


extern HLibExport Herror HSetImageTime(Hproc_handle proc_handle,
                                       Himage*      image);

extern HLibExport Herror HImageName2Type(const char* str, HINT* kind);

extern HLibExport Herror HPrepNewImage(Hproc_handle proc_handle, HIMGDIM width,
                                       HIMGDIM height);

extern HLibExport double Hatan2(double x, double y);

extern HLibExport Herror HStripQuotes(Hproc_handle proc_handle, char* in,
                                      char** out);


/* for some functions we have an old version without the Hproc_handle parameter
 * -> keep them for binary compatibility (The progress versions before
 *    HALCON 18.12 must be binary compatible with all current
 *    image acquisition interfaces released with HALCON 13)
 * and a new version with Hproc_handle for optimizing the memory allocation */
extern HLibExport char* HGetHalconRoot();
extern HLibExport char* HGetHalconRootPh(Hproc_handle ph);

#if defined(__APPLE__)
extern HLibExport char* HGetHalconFrameworkRootPh(Hproc_handle ph);
#endif

extern HLibExport char* HGetHalconLibraryPath();
extern HLibExport char* HGetHalconLibraryPathPh(Hproc_handle ph);

extern HLibExport HBOOL HSetEnv(const char* name, const char* value);
extern HLibExport HBOOL HSetEnvPh(Hproc_handle ph, const char* name,
                                  const char* value);

extern HLibExport char* HGetEnv(const char* name);
extern HLibExport char* HGetEnvPh(Hproc_handle ph, const char* name);

extern HLibExport void HGetEnvFree(char* mem);
extern HLibExport Herror HGetEnvFreePh(Hproc_handle ph, char* mem);

extern HLibExport char* HGetEnvRaw(Hproc_handle ph, const char* name);

extern HLibExport Herror HIncrRL(Hproc_handle proc_handle);

extern HLibExport Herror HIncrRLNum(Hproc_handle proc_handle, size_t num);

extern HLibExport Herror HCopyData(const void* source, void* destination,
                                   size_t size);

extern HLibExport Herror HSetData(void* c, HINT val, size_t size);

#define HBackupDataLocal(PROC_HANDLE, SRC_PTR, NUM, DEST_PTR)                 \
  HXBackupDataLocal(PROC_HANDLE, (const void*)SRC_PTR,                        \
                    sizeof(*SRC_PTR) * NUM, (void*)(DEST_PTR))

extern HLibExport Herror HXBackupDataLocal(Hproc_handle proc_id,
                                           const void* source, size_t size,
                                           void* destination);
#define HRestoreData(SRC_PTR, NUM, DEST_PTR)                                  \
  HCopyData((const void*)SRC_PTR, (void*)(DEST_PTR), sizeof(*SRC_PTR) * NUM)

extern HLibExport Herror HClearData(void* c, size_t size);

extern HLibExport Herror HCopyImage(const Himage* in, Himage* out);

extern HLibExport Herror HClearImage(Himage* image);

extern HLibExport Herror HSetImage(Himage* image, double grayval);

extern HLibExport Herror HAdaptImsize(Hproc_handle proc_handle, HIMGDIM width,
                                      HIMGDIM height);

extern HLibExport Herror HFreeTmpImage(Hproc_handle proc_handle,
                                       Himage*      image);

extern HLibExport Herror HTmpImage(Hproc_handle proc_handle, Himage* image,
                                   HINT kind, HIMGDIM width, HIMGDIM height,
                                   HBOOL clear);

extern HLibExport Herror HFreeLocalImage(Hproc_handle proc_handle,
                                         Himage*      image);

extern HLibExport Herror HLocalImageToGlobal(Hproc_handle proc_handle,
                                             Himage*      image);

extern HLibExport Herror HLocalImage(Hproc_handle proc_handle, Himage* image,
                                     HINT kind, HIMGDIM width, HIMGDIM height,
                                     HBOOL clear);

extern HLibExport Herror HCrImage(Hproc_handle proc_handle, Hkey key_in,
                                  HINT num, HINT type, HIMGDIM width,
                                  HIMGDIM height, Hkey* key_out,
                                  Himage* image);

extern HLibExport Herror HCrImageMatrix(Hproc_handle proc_id, Himage* image,
                                        Hkey key);

extern HLibExport Herror HCrImageMKeyCkD(Hproc_handle proc_handle,
                                         Hrlregion* domain[], Hkey key_in[],
                                         HINT num_keys, HINT num, HINT type,
                                         HIMGDIM width, HIMGDIM height,
                                         Hkey* key_out, Himage* image);

extern HLibExport Herror HCrImageMKey(Hproc_handle proc_handle, Hkey key_in[],
                                      HINT num_keys, HINT num, HINT type,
                                      HIMGDIM width, HIMGDIM height,
                                      Hkey* key_out, Himage* image);

extern HLibExport Herror HFreeImage(Hproc_handle proc_handle, Himage* image);

extern HLibExport Herror HNewImage(Hproc_handle proc_handle, Himage* image,
                                   HINT kind, HIMGDIM width, HIMGDIM height);

extern HLibExport Herror HAllocImageMatrix(Hproc_handle proc_handle,
                                           Himage* image, HINT kind,
                                           HIMGDIM width, HIMGDIM height,
                                           HBOOL clear);

extern HLibExport Herror HNewImagePtr(Hproc_handle proc_handle, Himage* image,
                                      HINT kind, HIMGDIM width, HIMGDIM height,
                                      void* data, HBOOL initImg);

Herror HSortDouble(Hproc_handle proc_handle, double* array, INT4_8 num,
                   HBOOL ascending);

Herror HSortINT4_8(Hproc_handle proc_handle, INT4_8* array, INT4_8 num,
                   HBOOL ascending);

Herror HSortString(Hproc_handle proc_handle, char** array, INT4_8 num,
                   HBOOL ascending);

Herror HSortHcpar(Hproc_handle proc_handle, Hcpar* array, INT4_8 num,
                  HBOOL ascending);

#if defined(__cplusplus)
}
#endif


#endif
