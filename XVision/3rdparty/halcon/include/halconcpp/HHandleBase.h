/*****************************************************************************
 * HHandleBase.h
 *****************************************************************************
 *
 * Project:     HALCON/C++
 * Description: Base class for wrapping all handle types
 *
 * (c) 2017-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 *****************************************************************************/

#ifndef HCPP_HANDLE_BASE_H
#define HCPP_HANDLE_BASE_H

#include "Halcon.h"

#include "halconcpp/HString.h"

namespace HalconCpp
{

class LIntExport HHandleBase
{

friend class HTuple;
friend class HTupleElement;
friend class HalconAPI;
friend class HalconAPIInternal;

public:

  // Create an uninitialized handle
  HHandleBase();

  // Creation from numeric handle, for interacting with legacy code
  // or for transferring handle across language interface boundaries
  explicit HHandleBase(Hlong handle);

  // Copy constructor
  HHandleBase(const HHandleBase &handle);

  // Destructor
  virtual ~HHandleBase();

  // Set from numeric handle, for interacting with legacy code or
  // for transferring handle across language interface boundaries
  void SetHandle(Hlong handle);

  // Return the managed handle
  Hlong GetHandle() const;

  // Return true if this handle instance manages a valid handle. Returns
  // false if the managed handle has already been destroyed or when this
  // instance manages no handle (uninitialized or cleared). Equivalent to
  // new HALCON operator HandleIsValid but kept for convenience of having
  // boolean signature and backwards compatible name.
  bool IsInitialized() const;

  // Return a textual representation of the handle. This is mainly for
  // logging and debugging purposes, result should not be parsed and text
  // format may change in the future.
  HString ToString() const;

  // Release the managed handle (decreases reference count of handle)
  void Clear();


  /******************************************************************/
  /* Operator overloads                                             */
  /******************************************************************/

  // Assignment
  HHandleBase& operator = (const HHandleBase& obj);

  // Comparison
  bool operator==(const HHandleBase& obj) const;
  bool operator!=(const HHandleBase& obj) const;

#if defined(HCPP_LEGACY_HANDLE_API)

  // Extraction to long is now rare use case and should be done explicitely
  operator Hlong() const;

  // For all practical purposes now handled by HHandle constructor of HTuple
  operator HTuple() const;

#endif


  /******************************************************************/
  /* Internal operations, exposed for use by extension package only */
  /******************************************************************/

  // Load output handle from HALCON operator call
  void   Load(Hproc_handle proc, HINT par_index, Herror err) const;

  // Store as input handle for HALCON operator call
  Herror Store(Hproc_handle proc, HINT par_index) const;


  /******************************************************************/
  /* Legacy handle management                                       */
  /******************************************************************/

#if defined(HCPP_LEGACY_HANDLE_API)

  // Not useful with new reference counting mechanism
  void Detach();

  // Not useful with new reference counting mechanism
  void InvalidateHandle();

  // Deprecated, replaced by IsInitialized
  bool IsToolValid() const { return IsInitialized(); };

#endif


protected:

  // Over management of input handle
  HHandleBase(Hphandle handle, bool copy);

  // Return the managed handle
  Hphandle GetHandleInternal() const;

  // For copy=false takes over management of input handle
  void SetHandleInternal(Hphandle handle, bool copy);

  // Verify type of external handle, raise exception on mismatch
  virtual void AssertType(Hphandle handle) const;

  // Verify type of wrapped handle, raise exception on mismatch
  void AssertType() const;


protected:

  static const Hphandle HANDLE_INVALID;

  Hphandle mHandle;

};



// Base class for actual tool array classes

class LIntExport HHandleBaseArray
{

public:

  // Destructor
  virtual ~HHandleBaseArray() {};

  // Clears array and all tool instances
  virtual void Clear() = 0;

  // Get number of tools
  virtual Hlong Length() const = 0;

  // Create tool array from tuple of handles
  virtual void SetFromTuple(const HTuple& handles) = 0;

  // Get tuple of handles for tool array
  virtual HTuple ConvertToTuple() const = 0;

};

// Forward declaration
class HHandle;

// Constant for supporting export of HNULL literal from HDevelop
extern const LIntExport HHandle HNULL;

}

#endif
