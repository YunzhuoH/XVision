/*****************************************************************************
 * Hvector.h
 *****************************************************************************
 *
 * Project:     HALCON/C
 * Description: HALCON/C implementation of HDevelop vectors
 *
 * (c) 2014-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 ****************************************************************************/

#ifndef HVECTOR_H
#define HVECTOR_H

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * The data structure Hvector is used to the vector functionality of the
 * hdevelop language. Creating, access and deletion must only be done with the
 * supplied procedures.
 */
typedef Hlong Hvector; /* Handle implementation of vector */
typedef enum {
  eVector=0x05EC0000,eTupleVector,eTupleLeaf,eObjectVector,eObjectLeaf
} Hvectype;

#define HVECTOR_UNDEF 0

/**************************************************************************
 * Hvector functionality
 *************************************************************************/

/* create_obj_vector creates an empty vector of dimension dim. The vector is
 * returned in vec and can contain objects only.*/
LIntExport Herror V_create_obj_vector(Hlong dim, Hvector *H_RESTRICT vec);

/* create_tuple_vector creates an empty vector of dimension dim. The vector is
 * returned in vec and can contain tuples only.*/
LIntExport Herror V_create_tuple_vector(Hlong dim, Hvector *H_RESTRICT vec);

/* destroy_vector frees the vector, its subvectors and leafs of any type and
 * dimension. */
LIntExport Herror V_destroy_vector(Hvector vec);

/* copy_vector returns a copy of src in dest. Deep copy is performed. */
LIntExport Herror V_copy_vector(Hvector const src, Hvector *H_RESTRICT dest);

/* set_vector_elem sets a sub vector subvec in vector vec. Therefore,
 * index addresses a sub vector that gets replaced by subvec. The old sub
 * vector is freed if existing. Otherwise, vec is extended accordingly (and
 * initialized with empty elements) to fulfill index.(self modifying)
 * Precondition: type(subvec) == type(vec) && dim(vec) == dim(subvec)+|index|
 */
LIntExport Herror V_set_vector_elem(Hvector vec, Htuple const vec_idx,
                                    Hvector const subvec);

/* set_vector_obj sets a iconic object obj in vector vec. Therefore,
 * vec_idx addresses an object in vec that gets replaced by obj. The old
 * iconic object in vec is freed if existing. Otherwise, vec is extended
 * accordingly (and initialized with empty elements) to fulfill vec_idx.(self
 * modifying)
 * Precondition: type(vec) == eObjectVector && dim(vec) == dim(subvec)+|index|
 */
LIntExport Herror V_set_vector_obj(Hobject const obj, Hvector vec,
                                   Htuple const vec_idx);

/* set_vector_tuple sets a tuple tpl in vector vec. Therefore,
 * vec_idx addresses a tuple in vec that gets replaced by obj. The old tuple
 * in vec is freed if existing. Otherwise, vec is extended accordingly (and
 * initialized with empty elements) to fulfill vec_idx.(self modifying)
 * Precondition: type(vec) == eTupleVector && dim(vec) == |index|
 */
LIntExport Herror V_set_vector_tuple(Hvector vec, Htuple const vec_idx,
                                     Htuple const tpl);

/* set_vector_tuple_elem executes a self modifying tuple_replace in the indexed
 * tuple in vec. vec_idx is a tuple of n=dim elements and indexes the tuple
 * in vec. tpl_idx contains the tuple indices to be replaced. val contains
 * the values to set.
 * If the length of any sub vector indexed by vec_idx is not sufficient,
 * set_vector_tuple_elem extends it automatically (initialized with empty
 * elements).
 * Precondition: type(vec) == eTupleVector && dim(vec) == |vec_idx|. */
LIntExport Herror V_set_vector_tuple_elem(Hvector vec, Htuple const vec_idx,
                                          Htuple const tpl_idx, 
                                          Htuple const val);


/* get_vector_elem returns a copy of the sub vector of vec at index. The
 * error H_ERR_WIPV2 is returned if any value of index addresses an element
 * of a sub vector of vec beyond its length.
 * Remark: dim(subvec) = dim(vec)-|index|
 *         type(subvec) = type(vec) */
LIntExport Herror V_get_vector_elem(Hvector const vec, Htuple const index,
                                    Hvector *H_RESTRICT subvec);

/* get_vector_obj returns a copy of an iconic object of vec at index. The
 * error H_ERR_WIPV2 is returned if any value of index addresses an element of a
 * sub vector of vec beyond its length.
 * Precondition: dim(vec) == |index| && type(vec) == eObjectVector */
LIntExport Herror V_get_vector_obj(Hobject *H_RESTRICT obj, Hvector const vec,
                                   Htuple const index);

/* get_vector_tuple returns a copy of a tuple of vector vec at index. The
 * error H_ERR_WIPV2 is returned if any value of index addresses an element of
 * a sub vector of vec beyond its length.
 * Precondition: dim(vec) == |index| && type(vec) == eTupleVector */
LIntExport Herror V_get_vector_tuple( Hvector const vec, Htuple const index,
                                      Htuple *H_RESTRICT tpl);


/* concat_vector appends vec2 at vec1 and returns the concatenated vector in
 * concat. vec1 and vec2 have to be of same dimension and type. */
LIntExport Herror V_concat_vector(Hvector const vec1, Hvector const vec2,
                                  Hvector *H_RESTRICT vec_concat);

/* insert_vector_elem inserts a vector ins at position ins_idx into a
 * sub vector of vec, indexed by vec_idx.
 * Different to set_vector_elem, the length of the sub vector indexed by
 * vec_idx gets increased by one. (self modifying)
 * Precondition: dim(vec) == dim(ins)+|vec_ins|
 *               type(ins) == type(vec)
 *               |ins_idx| == 1 */
LIntExport Herror V_insert_vector_elem(Hvector vec, Htuple const vec_idx,
                                       Htuple const ins_idx,
                                       Hvector const ins);

/* remove_vector_elem is the counterpart of insert_vector_elem. It frees all
 * contents at position rmv_idx of a sub vector indexed by vec_idx.
 * If the sub vector indexed by vec_idx does not exist, it gets created.
 * The length of the sub vector indexed by vec_idx gets decreased by one,
 * when rmv_idx is smaller than the length of the sub vector. (self modifying)
 * Precondition: dim(vec)>=|vec_idx| */
LIntExport Herror V_remove_vector_elem(Hvector vec, Htuple const vec_idx,
                                       Htuple const rmv_idx);

/* clear_vector frees all contents of a sub vector of vec and makes it empty.
 * The sub vector is indexed by 'index'. Type and dimension of the sub
 * vector remain. (self modifying)
 * Precondition: dim(vec)>=|index| */
LIntExport Herror V_clear_vector(Hvector vec, Htuple const index);

/* insert_vector_obj inserts an iconic object obj at position ins_idx into a
 * sub vector of vec, indexed by vec_idx.
 * Different to set_vector_obj, the length of the sub vector indexed by
 * vec_idx gets increased by one. (self modifying)
 * Precondition: dim(vec) == |vec_ins|
 *               type(vec) == eObjectVector
 *               |ins_idx| == 1 */
LIntExport Herror V_insert_vector_obj(Hobject const obj, Hvector vec,
                                      Htuple const vec_idx,Htuple const ins_idx);

/* insert_vector_tupel inserts a tuple tpl at position ins_idx into a
 * sub vector of vec, indexed by vec_idx.
 * Different to set_vector_tuple, the length of the sub vector indexed by
 * vec_idx gets increased by one. (self modifying)
 * Precondition: dim(vec) == |vec_ins|
 *               type(vec) == eTupleVector
 *               |ins_idx| == 1 */
LIntExport Herror V_insert_vector_tuple(Hvector vec, Htuple const vec_idx,
                                        Htuple const ins_idx, Htuple const tpl);

/* convert_vector_to_tuple concatenates the tuple leafs of a tuple vector
 * vec  into one tuple tpl.
 * Precondition: type(vec) == eTupleVector */
LIntExport Herror V_convert_vector_to_tuple( Hvector const vec, 
                                             Htuple *H_RESTRICT tpl);

/* convert_tuple_to_vector_1d separates the tuple elements of tpl according
 * to the length values in lengths into new sub tuples and generates a new
 * tuple vector vec with all these tuples as leafs. If lengths contains only
 * one value, tpl is separated into tuples of the same length (with the last
 * tuple containing the residuum).
 * Precondition: |lengths|==1 || sum(lengths)==|tpl|
 *   dim(vec)=1, type(vec)=eTupleVector */
LIntExport Herror V_convert_tuple_to_vector_1d( Htuple const tpl,
                                                Htuple const lengths,
                                                Hvector *H_RESTRICT vec);

/* vector_equal returns TRUE if both vectors are identic. I.e.
 * both vectors have the same 'tree', the same type, and test_equal_obj
 * (tuple_equal, respectively) is true for all leafs. Else, equal is set
 * to FALSE.*/
LIntExport Herror V_vector_equal(Hvector const vec1, Hvector const vec2,
                                 HBOOL *H_RESTRICT equal);

/* vector_dim returns the dimensionality of the vector vec */
LIntExport Herror V_vector_dim(Hvector const vec, Hlong *H_RESTRICT dim);

/* vector type returns the type of the vector. eTupleVector, eObjectVector
 * are possible values */
LIntExport Herror V_vector_type(Hvector const vec, Hvectype *H_RESTRICT type);

/* vector_length returns the number of elements in vec */
LIntExport Herror V_vector_length(Hvector const vec,
                                  Hlong *H_RESTRICT length);

/* V_sub_vector_length returns the number of elements of a sub vector of vec,
 * indexed by vec_idx. Passing an empty tuple for vec_idx receives the same 
 * result as V_vector_length. */
LIntExport Herror V_sub_vector_length(Hvector const vec, Htuple const vec_idx,
                                      Hlong *H_RESTRICT length);

/* Some printf auxiliary functions for debug support. They allow to transform
 * the basic HALCON/C data types into readable strings.
 * str points to a pre-allocated buffer of size bytes.
 * Upon successful completion, the Hsnprintf_* functions shall return the
 * number of bytes that would be written to str had size been sufficiently
 * large excluding the terminating null byte. If an output error was
 * encountered, these functions shall return a negative value.*/
LIntExport int Hsnprintf_Hvector( char *H_RESTRICT str, Hlong size,
                                  Hvector const vec);
LIntExport int Hsnprintf_Htuple( char *H_RESTRICT str, Hlong size,
                                  Htuple const tpl);
LIntExport int Hsnprintf_Hobject( char *H_RESTRICT str, Hlong size,
                                  Hobject const obj);

#if defined(__cplusplus)
}
#endif

#endif
