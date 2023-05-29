/*****************************************************************************
 * HObjectBase.h
 ***************************************************************************** 
 *
 * Project:     HALCON/C++
 * Description: Base class for all iconic objects
 *
 * (c) 2010-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 *****************************************************************************/


#ifndef HCPP_OBJECT_BASE_H
#define HCPP_OBJECT_BASE_H


namespace HalconCpp
{

class LIntExport HObjectBase
{

public:

  static const Hkey UNDEF;

  // Create an uninitialized object
  HObjectBase();

  // Create object from object id. For copy=false, takes
  // over management of input key
  HObjectBase(Hkey key, bool copy=true);

  // Copy constructor
  HObjectBase(const HObjectBase &obj);

  // Destructor
  ~HObjectBase();

  // Assignment
  HObjectBase& operator = (const HObjectBase& obj);

  // Comparison operators
  bool operator==(const HObjectBase& obj) const;
  bool operator!=(const HObjectBase& obj) const;

  // Set object from object id. For copy=false takes
  // over management of input key
  void SetKey(Hkey key, bool copy=true);

  // Return the managed key
  Hkey Key() const;

  // Return a copy of the managed key, which can
  // (and needs to) be disposed of separately
  Hkey CopyKey() const;

  // Return true if this object instance manages a valid key.
  bool IsInitialized() const;

  // Key life cycle will no longer be managed by this object
  void Detach();

  // Clear managed key and free resources if attached
  void Clear();


  /******************************************************************/
  /* Internal operations, exposed for use by extension package only */
  /******************************************************************/

  // Load output object from HALCON operator call
  void   Load(Hproc_handle proc, HINT par_index, Herror err) const;

  // Store as input object for HALCON operator call
  Herror Store(Hproc_handle proc, HINT par_index) const;


#if defined(HCPP_LEGACY_API)
  void AdaptId(Hkey key) {SetKey(key,false);}
  Hkey Id() const        {return Key();}
  void Reset()           {Clear();}
#endif


protected:

  Hkey mKey;
  bool mAttached;
};

}

#endif
