/*****************************************************************************
 * HVector.h
 ***************************************************************************** 
 *
 * Project:     HALCON/C++
 * Description: Vector class for engine and HDevelop export
 *
 * (c) 2014-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 *
 *****************************************************************************/


#ifndef HCPP_VECTOR_H
#define HCPP_VECTOR_H


#include "halconcpp/HTuple.h"
#include "halconcpp/HObjectBase.h"
#include "halconcpp/HObject.h"


namespace HalconCpp
{

class Hvector;


class LIntExport HVector
{

protected:

  // No public constructors, create HTupleVector or HObjectVector instead

  // Create an empty vector
  HVector(Hlong dimension);
  
  // Copy constructor
  HVector(const HVector& vector);


public:

  // Destroy vector
  virtual ~HVector();


  /* Operator overloads */

  // Assignment operator
  HVector& operator=(const HVector& vector);

  // Comparison operators
  bool operator==(const HVector& vector) const;
  bool operator!=(const HVector& vector) const;


  // Non-const indexing operator. If necessary, the vector 
  // will be enlarged to accomodate the index 
  HVector& operator[](Hlong index);

  // Const indexing operator. An exception will be raised if the
  // index is out of range.
  const HVector& operator[](Hlong index) const;


  /* Methods */
    
  // Dimension of vector;
  Hlong Dimension() const
  {
    return mDimension;
  }

  // Length of vector
  Hlong Length() const;
  
  // Clear contents of vector
  HVector& Clear();

  // Remove element from vector
  HVector& Remove(Hlong index);

  // Insert element into vector
  HVector& Insert(Hlong index, const HVector& vector);

  // Return a simple string representation of the vector contents,
  // mainly for logging and debugging purposes. The result should not
  // be parsed and text format may change in the future.
  virtual HString ToString() const;


  // Assistive functionality for engine and code export
  
  // Raise exception on dimension mismatch
  void AssertDimension(Hlong dimension) const;


  // Assistive functionality for internal vector use

protected:

  // FOR INTERNAL IMPLEMENTATION ONLY. NOT INTENDED
  // TO BE USED IN USER-DERIVED CLASSES

  // Increase length of vector (with dimension > 0) to ensure index is valid
  void AssertSize(Hlong index);

  // Test for equality
  virtual bool EqualImpl(const HVector& vector) const;

  // Create empty element to initialize gaps in vector
  virtual void ClearImpl();

  // Create concatenation of two vectors on the heap.
  HVector* ConcatImpl(const HVector& vector) const;

  // Create deep copy of all subvectors and elements
  virtual HVector* CloneImpl() const = 0;

  // Create empty element to initialize gaps in vector
  virtual HVector* GetDefaultElement() const = 0;

  // Returns new copy of this instance on the heap
  HVector* Clone() const;


  // Member variables

protected:
  
  Hlong mDimension;

  // Data container
  Hvector* mVector;
};



class LIntExport HTupleVector : public HVector
{

public:

  //   Create empty vector of specified dimension. In case of dimension
  //   0 a leaf vector for an empty tuple is created
  explicit HTupleVector(Hlong dimension) 
    : HVector(dimension)
  {
  }

  // Create leaf vector of dimension 0 for the specified tuple
  explicit HTupleVector(const HTuple& tuple) 
    : HVector(0),
      mTuple(tuple)
  {
  }

  // Create 1-dimensional vector by splitting input tuple into
  // blocks of fixed size (except possibly for the last block)
  // This corresponds to convert_tuple_to_vector_1d in HDevelop.
  explicit HTupleVector(const HTuple& tuple, Hlong block_size);

  // Copy constructor
  HTupleVector(const HTupleVector& vector);


  /* Operator overloads */

  // Assignment operator
  HTupleVector& operator=(const HTupleVector& vector);

  // Comparison operator
  bool operator==(const HTupleVector& vector) const;
  bool operator!=(const HTupleVector& vector) const;

  // Non-const indexing operator. If necessary, the vector 
  // will be enlarged to accomodate the index 
  HTupleVector& operator[](Hlong index);

  // Const indexing operator. An exception will be raised if the
  // index is out of range.
  const HTupleVector& operator[](Hlong index) const;


  /* Methods */

  // Clear contents of vector
  HTupleVector& Clear();

  // Remove element from vector
  HTupleVector& Remove(Hlong index);

  // Insert element into vector
  HTupleVector& Insert(Hlong index, const HTupleVector& vector);

  // Concatenate two vectors (creating new vector)
  HTupleVector Concat(const HTupleVector& vector);


  /* Value access (for leaf vectors of dimension 0) */

  const HTuple& T() const;

  HTuple& T();

  // Concatenates all tuples stored in the vector
  HTuple ConvertVectorToTuple() const;

  // Return a simple string representation of the vector contents,
  // mainly for logging and debugging purposes. The result should not
  // be parsed and text format may change in the future.
  virtual HString ToString() const;


  // Assistive functionality for internal vector use

protected:

  // Test for equality
  virtual bool EqualImpl(const HVector& vector) const;

  // Create deep copy of all subvectors and elements
  virtual HVector* CloneImpl() const;

  // Create empty element to initialize gaps in vector
  virtual HVector* GetDefaultElement() const;


protected:

  HTuple mTuple;
};



class LIntExport HObjectVector : public HVector
{

public:

  //   Create empty vector of specified dimension. In case of dimension
  //   0 a leaf vector for an empty object is created
  explicit HObjectVector(Hlong dimension);

  // Create leaf vector of dimension 0 for the specified object
  explicit HObjectVector(const HObject& obj)
    : HVector(0),
      mObject(obj)
  {
  }

  // Copy constructor
  HObjectVector(const HObjectVector& vector);


  /* Operator overloads */

  // Assignment operator
  HObjectVector& operator=(const HObjectVector& vector);

  // Comparison operator
  bool operator==(const HObjectVector& vector) const;
  bool operator!=(const HObjectVector& vector) const;

  // Non-const indexing operator. If necessary, the vector 
  // will be enlarged to accomodate the index 
  HObjectVector& operator[](Hlong index);

  // Const indexing operator. An exception will be raised if the
  // index is out of range.
  const HObjectVector& operator[](Hlong index) const;


  /* Methods */

  // Clear contents of vector
  HObjectVector& Clear();

  // Remove element from vector
  HObjectVector& Remove(Hlong index);

  // Insert element into vector
  HObjectVector& Insert(Hlong index, const HObjectVector& vector);

  // Concatenate two vectors (creating new vector)
  HObjectVector Concat(const HObjectVector& vector);


  /* Value access (for leaf vectors of dimension 0) */

  const HObject& O() const;

  HObject& O();


  // Return a simple string representation of the vector contents,
  // mainly for logging and debugging purposes. The result should not
  // be parsed and text format may change in the future.
  virtual HString ToString() const;


  // Assistive functionality for internal vector use

protected:

  // Test for equality
  virtual bool EqualImpl(const HVector& vector) const;

  // Create deep copy of all subvectors and elements
  virtual HVector* CloneImpl() const;

  // Create empty element to initialize gaps in vector
  virtual HVector* GetDefaultElement() const;


protected:

  HObject mObject;
};




}

#endif
