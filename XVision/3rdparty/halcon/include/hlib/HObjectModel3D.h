/*****************************************************************************
 * HObjectModel3D.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Creation and management of 3D object models
 *
 * (c) 2016-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 */

#ifndef HOBJECTMODEL3D_H
#define HOBJECTMODEL3D_H

#if defined(__cplusplus)
extern "C" {
#endif

/* Creates a new 3D object model with the given handle. */
extern HLibExport Herror HOM3DCreate(Hproc_handle proc_handle,
                                     INT4_8*      object_model);

/* Frees the given 3D object model handle. Note that this function should
 * usually only be called in case of errors during object model creation. Once
 * a handle has been returned to the user, it should be freed outside using the
 * operator  clear_object_model_3d */
extern HLibExport Herror HOM3DFree(Hproc_handle proc_handle,
                                   INT4_8       object_model);

/* Add points to a 3D object model. The points are NOT initialized and must be
 * filled by the caller. The point coordinates are expected in [mm]. */
extern HLibExport Herror HOM3DAddPoints(Hproc_handle proc_handle,
                                        INT4_8 object_model, HINT num_points,
                                        float** x, float** y, float** z);

/* Add points and a 2D mapping to a 3D object model. The points and the mapping
 * are NOT initialized and must be filled by the caller. The point coordinates
 * are expected in [mm]. */
extern HLibExport Herror HOM3DAddPointsAndMapping(
    Hproc_handle proc_handle, INT4_8 object_model, HINT num_points, float** x,
    float** y, float** z, HIMGDIM w, HIMGDIM h, HIMGCOOR** br, HIMGCOOR** bc);

/* Add points from non-interleaved XYZ images. The region defines which points
 * are valid. The points are copied into the 3D object model. The values are
 * interpreted as [mm]. */
extern HLibExport Herror HOM3DAddPointsFromImagesRegion(
    Hproc_handle proc_handle, INT4_8 object_model, Hrlregion* region,
    HIMGDIM w, HIMGDIM h, float* x, float* y, float* z);

/* Add points from non-interleaved XYZ images. Points where the z value is
 * identical to the given 'invalid' value are ignored and not added to the 3D
 * object model. The points are copied into the 3D object model. The values are
 * interpreted as [mm]. */
extern HLibExport Herror HOM3DAddPointsFromImagesInvalid(
    Hproc_handle proc_handle, INT4_8 object_model, float invalid, HIMGDIM w,
    HIMGDIM h, float* x, float* y, float* z);

/* Add 2D mappings to a 3D object model. The mappings are NOT initialized and
 * must be filled by the caller. The object model must already contain points,
 * and the number of points must be identical to the number of mappings. */
extern HLibExport Herror HOM3DAddMapping(Hproc_handle proc_handle,
                                         INT4_8       object_model,
                                         HINT num_mappings, HIMGDIM w,
                                         HIMGDIM h, HIMGCOOR** br,
                                         HIMGCOOR** bc);

/* Add normal vectors to a 3D object model. The normals are NOT initialized and
 * must be filled by the caller. The object model must already contain points,
 * and the number of points must be identical to the number of normals. */
extern HLibExport Herror HOM3DAddNormals(Hproc_handle proc_handle,
                                         INT4_8 object_model, HINT num_normals,
                                         float** nx, float** ny, float** nz);

/* Add triangles to a 3D object model. The triangles are NOT initialized and
 * must be filled by the caller. The 3D obejct model must already contain
 * points. The triangle array has a length of 3*num_triangles, each triangle
 * is represented by three consecutive vertex indices. */
extern HLibExport Herror HOM3DAddTriangles(Hproc_handle proc_handle,
                                           INT4_8       object_model,
                                           HINT         num_triangles,
                                           INT4**       triangles);

/* Add a user-defined attribute, which contains one double value per 3D
 * point. The length of the returned array (user_attrib) equals the number
 * of contained 3D points.
 * NOTE that the name of the attribute must start with an ampersand. For
 *      example, "&intensity", "&score", "&red" are valid names. */
extern HLibExport Herror HOM3DAddUserAttrib(Hproc_handle proc_handle,
                                            INT4_8       object_model,
                                            const char*  name,
                                            double**     user_attrib);

/* Returns the list of points contained in the given 3D object model.
 * The point coordinates are returned in [mm]. */
extern HLibExport Herror HOM3DGetPoints(INT4_8 object_model, HINT* num_points,
                                        float** x, float** y, float** z);

/* Returns the 2D mappings contained in the given 3D object model */
extern HLibExport Herror HOM3DGetMapping(INT4_8 object_model, HINT* num_points,
                                         HIMGDIM* w, HIMGDIM* h, HIMGCOOR** br,
                                         HIMGCOOR** bc);

/* Returns the point normal vectors contained in the given 3D object model */
extern HLibExport Herror HOM3DGetNormals(INT4_8 object_model, HINT* num_points,
                                         float** nx, float** ny, float** nz);

/* Returns the triangles contained in the given 3D object model */
extern HLibExport Herror HOM3DGetTriangles(INT4_8 object_model,
                                           HINT*  num_triangles,
                                           HINT** triangles);

/* Returns a user-defined attribute, which contains one double value per 3D
 * point. The length of the returned array (user_attrib) equals the number
 * of contained 3D points. */
extern HLibExport Herror HOM3DGetUserAttrib(INT4_8 object_model,
                                            HINT* num_points, const char* name,
                                            double** user_attrib);

#if defined(__cplusplus)
}
#endif

#endif /* ifndef HOBJECTMODEL3D_H */
