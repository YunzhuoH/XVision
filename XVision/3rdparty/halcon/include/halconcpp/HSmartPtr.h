/*****************************************************************************
 * HSmartPtr.h
 *****************************************************************************
 *
 * Project:     HALCON/C++
 * Description: Template class for smart pointers used by tools and tuples
 *
 * (c) 2010-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 *****************************************************************************/


#ifndef HCPP_SMART_PTR_H
#define HCPP_SMART_PTR_H



class LIntExport HSmartPtrRef
{
public:
  HSmartPtrRef();
  unsigned int  GetCount() const {return mCount;}
  void          addref()   const;
  bool          deref()    const;

protected:
  mutable unsigned int mCount;
};



namespace HalconCpp
{


template <class T> class HSmartPtr
{
 public:

  HSmartPtr();
  HSmartPtr(T* ptr);
  HSmartPtr(HSmartPtr const & ptr);

  virtual ~HSmartPtr();

  virtual HSmartPtr& operator=(HSmartPtr const & ptr);
  virtual HSmartPtr& operator=(T* ptr);

  T* operator->() const;
  T& operator*() const;
  T* Ref() const;
  operator T&() const;

  bool operator!() const;
  operator bool() const;

  bool operator==(const HSmartPtr& ptr) const;
  bool operator==(const T* ptr) const;
  bool operator!=(const HSmartPtr& ptr) const;
  bool operator!=(const T* ptr) const;

  void Reset();

protected:

  void deref();
  void addref();
  void reset(T* ptr=0);

  T* mPtr;
};



template <class T> HSmartPtr<T>::HSmartPtr() : mPtr(NULL) {}

template <class T> HSmartPtr<T>::HSmartPtr(T* ptr) : mPtr(ptr)
{
  addref();
}

template <class T> HSmartPtr<T>::HSmartPtr(HSmartPtr<T> const & ptr) : mPtr(ptr.mPtr)
{
  addref();
}

template <class T> HSmartPtr<T>::~HSmartPtr()
{
  deref();
}

template <class T> HSmartPtr<T>& HSmartPtr<T>::operator=(HSmartPtr<T> const & ptr)
{
  if (mPtr != ptr.mPtr)
    reset(ptr.mPtr);
  return *this;
}

template <class T> HSmartPtr<T>& HSmartPtr<T>::operator=(T* ptr)
{
  if (mPtr != ptr)
    reset(ptr);
  return *this;
}

template <class T> T* HSmartPtr<T>::operator->() const
{
  return mPtr;
}

template <class T> T& HSmartPtr<T>::operator*() const
{
  return *mPtr;
}

template <class T> T* HSmartPtr<T>::Ref() const
{
  return mPtr;
}

template <class T> HSmartPtr<T>::operator T&() const
{
  return *mPtr;
}

template <class T> bool HSmartPtr<T>::operator!() const
{
  return mPtr == NULL;
}

template <class T> HSmartPtr<T>::operator bool() const
{
  return mPtr != NULL;
}

template <class T> bool HSmartPtr<T>::operator==(const HSmartPtr<T>& ptr) const
{
  return mPtr == ptr.mPtr;
}

template <class T> bool HSmartPtr<T>::operator==(const T* ptr) const
{
  return mPtr == ptr;
}

template <class T> bool HSmartPtr<T>::operator!=(const HSmartPtr<T>& ptr) const
{
  return !operator==(ptr);
}

template <class T> bool HSmartPtr<T>::operator!=(const T* ptr) const
{
  return !operator==(ptr);
}

template <class T> void HSmartPtr<T>::Reset()
{
  deref();
}

template <class T> void HSmartPtr<T>::deref()
{
  if (mPtr)
  {
    /* It is neccessary to invalidate the smart pointer before releasing the
     * refered object for avoiding that within the update handlers of the
     * deleted object the smart pointer is used again.
     * This can happen, e.g., if this smart pointer is member of an array.
     * ------------------------------------------------------------------- */
    T* ptr = mPtr;
    mPtr = 0;
    if (ptr->deref())
      delete ptr;
  }
}

template <class T> void HSmartPtr<T>::addref()
{
  if (mPtr)
    mPtr->addref();
}

template <class T> void HSmartPtr<T>::reset(T* ptr/*=0*/)
{
  deref();
  mPtr = ptr;
  addref();
}

}


#endif
