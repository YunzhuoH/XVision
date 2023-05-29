/*****************************************************************************
 * HTuple.h
 *****************************************************************************
 *
 * Project:     HALCON/C++
 * Description: Tuple data used for control parameters of HALCON operators
 *              Generated via HTuple1.hop and HTuple2.hop
 *
 * (c) 2010-2018 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************/


#ifndef HCPP_TUPLE_H
#define HCPP_TUPLE_H


#include <new>



namespace HalconCpp
{


enum HTupleType
{
  // The empty tuple does not yet have a defined data type
  eTupleTypeEmpty = UNDEF_PAR,

  // The tuple is a pure array of integers
  eTupleTypeLong = LONG_PAR,

  // The tuple is a pure array of floating point values
  eTupleTypeDouble = DOUBLE_PAR,

  // The tuple is a pure array of strings
  eTupleTypeString = STRING_PAR,

  // The tuple is a pure array of handles
  eTupleTypeHandle = HANDLE_PAR,

  // The tuple is an array of Hcpar. Each element can have a different type
  eTupleTypeMixed = MIXED_PAR
};

}


#include "halconcpp/HTupleElement.h"


namespace HalconCpp
{

// Smart pointer to internal data representation

template<class T> class HSmartPtr;

typedef HSmartPtr<HTupleData> HTupleDataPtr;



// Tuple data used for control parameters of HALCON operators
class LIntExport HTuple
{
  friend class HalconAPI;
  friend class HTupleElement;

public:


  /***************************************************************************/
  /* Constructors / Destructor                                               */
  /***************************************************************************/

  // Empty tuple
  HTuple();

  // Integer (machine pointer size)
  HTuple(Hlong l);

  // Integer array (machine pointer size)
  HTuple(Hlong* l, Hlong num);

#  if defined(HCPP_INT_OVERLOADS)
  // Integer (possibly smaller size than pointer)
  HTuple(HINT i);

  // Integer array (possibly smaller size than pointer)
  HTuple(HINT* i, Hlong num);
#  endif

  // Single precision floating point value
  HTuple(float f);

  // Single precision floating point array
  HTuple(float* f, Hlong num);

  // Double precision floating point value
  HTuple(double d);

  // Double precision floating point array
  HTuple(double* d, Hlong num);

  // String (C style)
  HTuple(const char* s);

#  ifdef _WIN32
  // String (C style wide character string)
  HTuple(const wchar_t* s);
#  endif

  // String (object)
  HTuple(const HString& s);

  // Handle

#if defined(HCPP_LEGACY_HANDLE_API)
  // Implicit conversion from new handle type may cause ambiguities or
  // incompatibilies with legacy code (especially HMatrix to HTuple). Instead
  // conversion is handled by cast from HHandle to HTuple
  explicit HTuple(const HHandle& h);
#else
  HTuple(const HHandle& h);
#endif

  // Mixed
  HTuple(Hcpar* p, Hlong num);

  // Constant tuple
  HTuple(const HTuple& length, const HTuple& value);

  // Element of another tuple
  HTuple(const HTupleElement& element);

  // HTuple copy constructor
  HTuple(const HTuple& tuple);

  // Destructor
  virtual ~HTuple();


  /***************************************************************************/
  /* General members                                                         */
  /***************************************************************************/

  // Clear all data inside this tuple
  void  Clear();

  // The number of elements of this tuple
  Hlong Length() const;

  // The data type of this tuple (pure data types or mixed tuple)
  HTupleType Type() const;

  // Create a detached copy duplicating the underlying tuple data
  HTuple Clone() const;

  // Append data to existing tuple
  HTuple &Append(const HTuple& tuple);

  // Returns a simple string representation of the tuple contents,
  // mainly intended for debugging purposes
  HString ToString() const;



  /***************************************************************************/
  /* Data access                                                             */
  /***************************************************************************/

  // Direct array access will raise an exception if tuple type does not match!
  // Modifications to array will affect data in tuples as well.

  Hlong*    LArr();
  double*   DArr();
  char**    SArr();
  Hcpar*    PArr();

  // Safer but less efficient access is provided by copying the data.
  // Mismatched elements will be initialized with default values. Caller
  // is responsible for using HTuple::DeleteArr() to free the array (do
  // not use "delete []" directly as transferring memory ownership
  // across DLL boundaries may cause problems with the C++ runtime)

  // Returns the tuple data as an array of Hlong. Release using DeleteArr()!
  Hlong* ToLArr() const;

  // Returns the tuple data as an array of double. Release using DeleteArr()!
  double* ToDArr() const;

  // Returns the tuple data as an array of HString. Release using DeleteArr()!
  HString* ToSArr() const;

  static void DeleteArr(Hlong* arr);
  static void DeleteArr(double* arr);
  static void DeleteArr(HString* arr);

  // Intentionally no ToPArr() as correctly releasing memory
  // for a Hcpar* array is problematic for the library user.


  // Assignment operator
  HTuple& operator = (const HTuple& obj);

  // Element access
  HTupleElement       operator [] (Hlong index);
  const HTupleElement operator [] (Hlong index) const;
  HTupleElement       operator [] (const HTuple& index);
  const HTupleElement operator [] (const HTuple& index) const;

  // Convenience access for first element

#if defined(HCPP_INT_OVERLOADS)
  // Access integer value in first tuple element
  int I() const         { return (*this)[0].I(); }
#endif

  // Access integer value in first tuple element
  Hlong L() const       { return (*this)[0].L(); }

  // Access floating-point value in first tuple element
  double D() const      { return (*this)[0].D(); }

  // Access string value in first tuple element
  HString S() const     { return (*this)[0].S(); }

  // Access handle value in first tuple element
  HHandle H() const    { return (*this)[0].H(); }


  /***************************************************************************
   * Operators                                                               *
   ***************************************************************************/

  // Compute the union set of two input tuples.
  HTuple TupleUnion(const HTuple& Set2) const;

  // Compute the intersection set of two input tuples.
  HTuple TupleIntersection(const HTuple& Set2) const;

  // Compute the difference set of two input tuples.
  HTuple TupleDifference(const HTuple& Set2) const;

  // Compute the symmetric difference set of two input tuples.
  HTuple TupleSymmdiff(const HTuple& Set2) const;

  // Test whether the types of the elements of a tuple are of type string.
  HTuple TupleIsStringElem() const;

  // Test whether the types of the elements of a tuple are of type real.
  HTuple TupleIsRealElem() const;

  // Test whether the types of the elements of a tuple are of type integer.
  HTuple TupleIsIntElem() const;

  // Return the types of the elements of a tuple.
  HTuple TupleTypeElem() const;

  // Test whether a tuple is of type mixed.
  HTuple TupleIsMixed() const;

  // Test if the internal representation of a tuple is of type string.
  HTuple TupleIsString() const;

  // Test if the internal representation of a tuple is of type real.
  HTuple TupleIsReal() const;

  // Test if the internal representation of a tuple is of type integer.
  HTuple TupleIsInt() const;

  // Return the type of a tuple.
  HTuple TupleType() const;

  // Calculate the value distribution of a tuple within a certain value range.
  HTuple TupleHistoRange(const HTuple& Min, const HTuple& Max, const HTuple& NumBins, HTuple* BinSize) const;

  // Select tuple elements matching a regular expression.
  HTuple TupleRegexpSelect(const HTuple& Expression) const;

  // Test if a string matches a regular expression.
  HTuple TupleRegexpTest(const HTuple& Expression) const;

  // Replace a substring using regular expressions.
  HTuple TupleRegexpReplace(const HTuple& Expression, const HTuple& Replace) const;

  // Extract substrings using regular expressions.
  HTuple TupleRegexpMatch(const HTuple& Expression) const;

  // Return a tuple of random numbers between 0 and 1.
  static HTuple TupleRand(const HTuple& Length);

  // Return the number of elements of a tuple.
  HTuple TupleLength() const;

  // Calculate the sign of a tuple.
  HTuple TupleSgn() const;

  // Calculate the elementwise maximum of two tuples.
  HTuple TupleMax2(const HTuple& T2) const;

  // Calculate the elementwise minimum of two tuples.
  HTuple TupleMin2(const HTuple& T2) const;

  // Return the maximal element of a tuple.
  HTuple TupleMax() const;

  // Return the minimal element of a tuple.
  HTuple TupleMin() const;

  // Calculate the cumulative sums of a tuple.
  HTuple TupleCumul() const;

  // Select the element of rank n of a tuple.
  HTuple TupleSelectRank(const HTuple& RankIndex) const;

  // Return the median of the elements of a tuple.
  HTuple TupleMedian() const;

  // Return the sum of all elements of a tuple.
  HTuple TupleSum() const;

  // Return the mean value of a tuple of numbers.
  HTuple TupleMean() const;

  // Return the standard deviation of the elements of a tuple.
  HTuple TupleDeviation() const;

  // Discard all but one of successive identical elements of a tuple.
  HTuple TupleUniq() const;

  // Return the index of the last occurrence of a tuple within another tuple.
  HTuple TupleFindLast(const HTuple& ToFind) const;

  // Return the index of the first occurrence of a tuple within another tuple.
  HTuple TupleFindFirst(const HTuple& ToFind) const;

  // Return the indices of all occurrences of a tuple within another tuple.
  HTuple TupleFind(const HTuple& ToFind) const;

  // Sort the elements of a tuple and return the indices of the sorted tuple.
  HTuple TupleSortIndex() const;

  // Sort the elements of a tuple in ascending order.
  HTuple TupleSort() const;

  // Invert a tuple.
  HTuple TupleInverse() const;

  // Concatenate two tuples to a new one.
  HTuple TupleConcat(const HTuple& T2) const;

  // Select several elements of a tuple.
  HTuple TupleSelectRange(const HTuple& Leftindex, const HTuple& Rightindex) const;

  // Select all elements from index "n" to the end of a tuple.
  HTuple TupleLastN(const HTuple& Index) const;

  // Select the first elements of a tuple up to the index "n".
  HTuple TupleFirstN(const HTuple& Index) const;

  // Inserts one or more elements into a tuple at index.
  HTuple TupleInsert(const HTuple& Index, const HTuple& InsertTuple) const;

  // Replaces one or more elements of a tuple.
  HTuple TupleReplace(const HTuple& Index, const HTuple& ReplaceTuple) const;

  // Remove elements from a tuple.
  HTuple TupleRemove(const HTuple& Index) const;

  // Select in mask specified elements of a tuple.
  HTuple TupleSelectMask(const HTuple& Mask) const;

  // Select single elements of a tuple.
  HTuple TupleSelect(const HTuple& Index) const;

  // Select single character or bit from a tuple.
  HTuple TupleStrBitSelect(const HTuple& Index) const;

  // Generate a tuple with a sequence of equidistant values.
  static HTuple TupleGenSequence(const HTuple& Start, const HTuple& End, const HTuple& Step);

  // Generate a tuple of a specific length and initialize its elements.
  static HTuple TupleGenConst(const HTuple& Length, const HTuple& Const);

  // Read one or more environment variables.
  HTuple TupleEnvironment() const;

  // Split strings into substrings using predefined separator symbol(s).
  HTuple TupleSplit(const HTuple& Separator) const;

  // Cut characters from position "n1" through "n2" out of a string tuple.
  HTuple TupleSubstr(const HTuple& Position1, const HTuple& Position2) const;

  // Cut all characters starting at position "n" out of a string tuple.
  HTuple TupleStrLastN(const HTuple& Position) const;

  // Cut the first characters up to position "n" out of a string tuple.
  HTuple TupleStrFirstN(const HTuple& Position) const;

  // Backward search for characters within a string tuple.
  HTuple TupleStrrchr(const HTuple& ToFind) const;

  // Forward search for characters within a string tuple.
  HTuple TupleStrchr(const HTuple& ToFind) const;

  // Backward search for strings within a string tuple.
  HTuple TupleStrrstr(const HTuple& ToFind) const;

  // Forward search for strings within a string tuple.
  HTuple TupleStrstr(const HTuple& ToFind) const;

  // Determine the length of every string within a tuple of strings.
  HTuple TupleStrlen() const;

  // Test, whether a tuple is elementwise less or equal to another tuple.
  HTuple TupleLessEqualElem(const HTuple& T2) const;

  // Test, whether a tuple is elementwise less than another tuple.
  HTuple TupleLessElem(const HTuple& T2) const;

  // Test, whether a tuple is elementwise greater or equal to another tuple.
  HTuple TupleGreaterEqualElem(const HTuple& T2) const;

  // Test, whether a tuple is elementwise greater than another tuple.
  HTuple TupleGreaterElem(const HTuple& T2) const;

  // Test, whether two tuples are elementwise not equal.
  HTuple TupleNotEqualElem(const HTuple& T2) const;

  // Test, whether two tuples are elementwise equal.
  HTuple TupleEqualElem(const HTuple& T2) const;

  // Test whether a tuple is less or equal to another tuple.
  HTuple TupleLessEqual(const HTuple& T2) const;

  // Test whether a tuple is less than another tuple.
  HTuple TupleLess(const HTuple& T2) const;

  // Test whether a tuple is greater or equal to another tuple.
  HTuple TupleGreaterEqual(const HTuple& T2) const;

  // Test whether a tuple is greater than another tuple.
  HTuple TupleGreater(const HTuple& T2) const;

  // Test whether two tuples are not equal.
  HTuple TupleNotEqual(const HTuple& T2) const;

  // Test whether two tuples are equal.
  HTuple TupleEqual(const HTuple& T2) const;

  // Compute the logical not of a tuple.
  HTuple TupleNot() const;

  // Compute the logical exclusive or of two tuples.
  HTuple TupleXor(const HTuple& T2) const;

  // Compute the logical or of two tuples.
  HTuple TupleOr(const HTuple& T2) const;

  // Compute the logical and of two tuples.
  HTuple TupleAnd(const HTuple& T2) const;

  // Compute the bitwise not of a tuple.
  HTuple TupleBnot() const;

  // Compute the bitwise exclusive or of two tuples.
  HTuple TupleBxor(const HTuple& T2) const;

  // Compute the bitwise or of two tuples.
  HTuple TupleBor(const HTuple& T2) const;

  // Compute the bitwise and of two tuples.
  HTuple TupleBand(const HTuple& T2) const;

  // Shift a tuple bitwise to the right.
  HTuple TupleRsh(const HTuple& Shift) const;

  // Shift a tuple bitwise to the left.
  HTuple TupleLsh(const HTuple& Shift) const;

  // Convert a tuple of integer numbers into strings.
  HTuple TupleChrt() const;

  // Convert a tuple of strings into a tuple of integer numbers.
  HTuple TupleOrds() const;

  // Convert a tuple of integer numbers into strings.
  HTuple TupleChr() const;

  // Convert a tuple of strings of length 1 into a tuple of integer numbers.
  HTuple TupleOrd() const;

  // Convert a tuple into a tuple of strings.
  HTuple TupleString(const HTuple& Format) const;

  // Check a tuple (of strings) whether it represents numbers.
  HTuple TupleIsNumber() const;

  // Convert a tuple (of strings) into a tuple of numbers.
  HTuple TupleNumber() const;

  // Convert a tuple into a tuple of integer numbers.
  HTuple TupleRound() const;

  // Convert a tuple into a tuple of integer numbers.
  HTuple TupleInt() const;

  // Convert a tuple into a tuple of floating point numbers.
  HTuple TupleReal() const;

  // Calculate the ldexp function of two tuples.
  HTuple TupleLdexp(const HTuple& T2) const;

  // Calculate the remainder of the floating point division of two tuples.
  HTuple TupleFmod(const HTuple& T2) const;

  // Calculate the remainder of the integer division of two tuples.
  HTuple TupleMod(const HTuple& T2) const;

  // Compute the ceiling function of a tuple.
  HTuple TupleCeil() const;

  // Compute the floor function of a tuple.
  HTuple TupleFloor() const;

  // Calculate the power function of two tuples.
  HTuple TuplePow(const HTuple& T2) const;

  // Compute the base 10 logarithm of a tuple.
  HTuple TupleLog10() const;

  // Compute the natural logarithm of a tuple.
  HTuple TupleLog() const;

  // Compute the exponential of a tuple.
  HTuple TupleExp() const;

  // Compute the hyperbolic tangent of a tuple.
  HTuple TupleTanh() const;

  // Compute the hyperbolic cosine of a tuple.
  HTuple TupleCosh() const;

  // Compute the hyperbolic sine of a tuple.
  HTuple TupleSinh() const;

  // Convert a tuple from degrees to radians.
  HTuple TupleRad() const;

  // Convert a tuple from radians to degrees.
  HTuple TupleDeg() const;

  // Compute the arctangent of a tuple for all four quadrants.
  HTuple TupleAtan2(const HTuple& X) const;

  // Compute the arctangent of a tuple.
  HTuple TupleAtan() const;

  // Compute the arccosine of a tuple.
  HTuple TupleAcos() const;

  // Compute the arcsine of a tuple.
  HTuple TupleAsin() const;

  // Compute the tangent of a tuple.
  HTuple TupleTan() const;

  // Compute the cosine of a tuple.
  HTuple TupleCos() const;

  // Compute the sine of a tuple.
  HTuple TupleSin() const;

  // Compute the absolute value of a tuple (as floating point numbers).
  HTuple TupleFabs() const;

  // Compute the square root of a tuple.
  HTuple TupleSqrt() const;

  // Compute the absolute value of a tuple.
  HTuple TupleAbs() const;

  // Negate a tuple.
  HTuple TupleNeg() const;

  // Divide two tuples.
  HTuple TupleDiv(const HTuple& Q2) const;

  // Multiply two tuples.
  HTuple TupleMult(const HTuple& P2) const;

  // Subtract two tuples.
  HTuple TupleSub(const HTuple& D2) const;

  // Add two tuples.
  HTuple TupleAdd(const HTuple& S2) const;

  // Deserialize a serialized tuple.
  static HTuple DeserializeTuple(const HSerializedItem& SerializedItemHandle);

  // Serialize a tuple.
  HSerializedItem SerializeTuple() const;

  // Write a tuple to a file.
  void WriteTuple(const HTuple& FileName) const;

  // Read a tuple from a file.
  static HTuple ReadTuple(const HTuple& FileName);

  // Clear the content of a handle. 
  void ClearHandle() const;

  // Test if the internal representation of a tuple is of type handle.
  HTuple TupleIsHandle() const;

  // Test whether the elements of a tuple are of type handle.
  HTuple TupleIsHandleElem() const;

  // Test if a tuple is serializable.
  HTuple TupleIsSerializable() const;

  // Test if the elements of a tuple are serializable.
  HTuple TupleIsSerializableElem() const;

  // Check if a handle is valid. 
  HTuple TupleIsValidHandle() const;

  // Return the semantic type of a tuple.
  HTuple TupleSemType() const;

  // Return the semantic type of the elements of a tuple.
  HTuple TupleSemTypeElem() const;

  /***************************************************************************/
  /* Compatibility Layer                                                     */
  /***************************************************************************/

#if defined(HCPP_LEGACY_API)

  #include "halconcpp/HTupleLegacy.h"

#endif

#if (!defined(HCPP_LEGACY_API) || defined(_LIntDLL))

  // Casts from a HTuple to element data types are disabled in legacy mode,
  // as they may lead to ambiguous operator calls in existing user code

#if defined(HCPP_INT_OVERLOADS)
  // Access integer value in first tuple element
  operator int() const         { return I(); }
#endif

  // Access integer value in first tuple element
  operator Hlong() const       { return L(); }

  // Access floating-point value in first tuple element
  operator float() const       { return (float) D(); }

  // Access floating-point value in first tuple element
  operator double() const      { return D(); }

  // Access string value in first tuple element
  operator HString() const     { return S(); }

#if (!defined(HCPP_LEGACY_HANDLE_API) || defined(_LIntDLL))
  // Access handle value in first tuple element
  operator HHandle() const     { return H(); }
#endif

#endif


  /***************************************************************************/
  /* Operator overloads                                                      */
  /***************************************************************************/

  /* Unary operators */

  bool         operator !  (void) const;
  HTuple       operator ~  (void) const;
  HTuple       operator -  (void) const;
  HTuple      &operator ++ (void);

  /* Binary operators are declared below outside class HTuple */

  /* Selected compound operators */
  HTuple& operator += (const HTuple &val);
  H_COMPOUND_OP_OVERLOAD_DECLARATION(HTuple,+=);
  HTuple& operator -= (const HTuple &val);
  H_COMPOUND_OP_OVERLOAD_DECLARATION(HTuple,-=);
  HTuple& operator *= (const HTuple &val);
  H_COMPOUND_OP_OVERLOAD_DECLARATION(HTuple,*=);


  /***************************************************************************/
  /* Helpers for code export or extension packages, do not call in used code */
  /***************************************************************************/

  bool Continue(const HTuple &final_value, const HTuple &increment);

  // Internal use, exposed for extension packages and hdevengine only

  HTuple(const Hctuple& tuple, bool copy=true);
  Hctuple GetHctuple(bool copy) const;
  const Hctuple &GetHctupleRef() const;
  void TranscodeFromUtf8ToInterfaceEncoding();

protected:

  // Create tuple wrapping internal representation
  HTuple(HTupleData* data);

  // Initialize during construction or from cleared tuple state
  void InitFromTupleData(HTupleData* data);
  void InitFromTuple(const HTuple& tuple);

  // Internal use, exposed for C++ language interface only
  void MoveFromHctuple(Hctuple& tuple);

  // Internal use, exposed for extension packages and hdevengine only
  void SetFromHctuple(const Hctuple& tuple, bool copy/*=true*/);

  // Revert internal representation to mixed tuple
  void ConvertToMixed();

  // Resolve lazy copying on write access
  bool AssertOwnership();

protected:

  // Smart pointer to typed data container
  HTupleDataPtr* mData;

  // Direct pointer for small tuple optimizations
  HTupleData* mDataPtr;
};

/***************************************************************************/
/* Operator overloads                                                      */
/***************************************************************************/

#if defined(HCPP_OVERLOAD_TUPLE_OPERATORS)

#  ifdef _WIN32
#    define H_BIN_OP_WCHAR_OVERLOAD_DECLARATION(RET, OP)                      \
      LIntExport RET operator OP(const wchar_t* op1, const HTuple& op2);      \
      LIntExport RET operator OP(const HTuple& op1, const wchar_t* op2);      \
      LIntExport RET operator OP(const wchar_t*       op1,                    \
                                 const HTupleElement& op2);                   \
      LIntExport RET operator OP(const HTupleElement& op1, const wchar_t* op2);
#  else
#    define H_BIN_OP_WCHAR_OVERLOAD_DECLARATION(RET, OP)
#  endif

#  define H_BIN_OP_OVERLOAD_DECLARATION(RET, OP)                              \
    H_BIN_OP_WCHAR_OVERLOAD_DECLARATION(RET, OP)                              \
    LIntExport RET operator OP(const HTuple& op1, int op2);                   \
    LIntExport RET operator OP(const HTuple& op1, Hlong op2);                 \
    LIntExport RET operator OP(const HTuple& op1, float op2);                 \
    LIntExport RET operator OP(const HTuple& op1, double op2);                \
    LIntExport RET operator OP(const HTuple& op1, const HString& op2);        \
    LIntExport RET operator OP(const HTuple& op1, const char* op2);           \
    LIntExport RET operator OP(const HTuple& op1, const HHandle& op2);        \
    LIntExport RET operator OP(const HTuple& op1, const HTupleElement& op2);  \
                                                                              \
    LIntExport RET operator OP(const HTupleElement& op1, int op2);            \
    LIntExport RET operator OP(const HTupleElement& op1, Hlong op2);          \
    LIntExport RET operator OP(const HTupleElement& op1, float op2);          \
    LIntExport RET operator OP(const HTupleElement& op1, double op2);         \
    LIntExport RET operator OP(const HTupleElement& op1, const HString& op2); \
    LIntExport RET operator OP(const HTupleElement& op1, const char* op2);    \
    LIntExport RET operator OP(const HTupleElement& op1, const HHandle& op2); \
    LIntExport RET operator OP(const HTupleElement& op1,                      \
                               const HTupleElement& op2);                     \
    LIntExport RET operator OP(const HTupleElement& op1, const HTuple& op2);  \
                                                                              \
    LIntExport RET operator OP(int op1, const HTuple& op2);                   \
    LIntExport RET operator OP(Hlong op1, const HTuple& op2);                 \
    LIntExport RET operator OP(float op1, const HTuple& op2);                 \
    LIntExport RET operator OP(double op1, const HTuple& op2);                \
    LIntExport RET operator OP(const HString& op1, const HTuple& op2);        \
    LIntExport RET operator OP(const HHandle& op1, const HTuple& op2);        \
    LIntExport RET operator OP(const char* op1, const HTuple& op2);           \
                                                                              \
    LIntExport RET operator OP(int op1, const HTupleElement& op2);            \
    LIntExport RET operator OP(Hlong op1, const HTupleElement& op2);          \
    LIntExport RET operator OP(float op1, const HTupleElement& op2);          \
    LIntExport RET operator OP(double op1, const HTupleElement& op2);         \
    LIntExport RET operator OP(const HString& op1, const HTupleElement& op2); \
    LIntExport RET operator OP(const char* op1, const HTupleElement& op2);    \
    LIntExport RET operator OP(const HHandle& op1, const HTupleElement& op2);
#else
  #define H_BIN_OP_OVERLOAD_DECLARATION(RET,OP)
#endif

/* Arithmetic operators */
LIntExport HTuple operator +(const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(HTuple,+)
LIntExport HTuple operator - (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(HTuple,-)
LIntExport HTuple operator * (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(HTuple,*)
LIntExport HTuple operator / (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(HTuple,/)
LIntExport HTuple operator % (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(HTuple,%)


/* Boolean operators */

LIntExport bool operator ==   (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(bool,==)
LIntExport bool operator !=   (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(bool,!=)
LIntExport bool operator >=   (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(bool,>=)
LIntExport bool operator <=   (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(bool,<=)
LIntExport bool operator >    (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(bool,>)
LIntExport bool operator <    (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(bool,<)
LIntExport bool operator &&   (const HTuple& val1, const HTuple &val2);
// it is regarded as bad practice to overload logical operators as this leeds
// to the unexpected behaviour that both operands must be evaluated
// H_BIN_OP_OVERLOAD_DECLARATION(bool,&&)
LIntExport bool operator ||   (const HTuple& val1, const HTuple &val2);
// H_BIN_OP_OVERLOAD_DECLARATION(bool,||)


/* Bitwise operators */

LIntExport HTuple operator |  (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(HTuple,|)
LIntExport HTuple operator &  (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(HTuple,&)
LIntExport HTuple operator ^  (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(HTuple,^)
LIntExport HTuple operator << (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(HTuple,<<)
LIntExport HTuple operator >> (const HTuple& val1, const HTuple &val2);
H_BIN_OP_OVERLOAD_DECLARATION(HTuple,>>)

}

#endif
