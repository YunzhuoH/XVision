/*****************************************************************************
 * HException.h
 ***************************************************************************** 
 *
 * Project:     HALCON/C++
 * Description: Error handling
 *
 * (c) 2010-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 *****************************************************************************/


#ifndef HCPP_EXCEPTION_H
#define HCPP_EXCEPTION_H


#include "halconcpp/HString.h"
#include "halconcpp/HTuple.h"


namespace HalconCpp
{


// Base class for all exception that is raised for generic
// errors within the HALCON/C++ interface

class LIntExport HException 
{

public:

  // Constructors / Destructor

  HException(const char *proc_name, Herror err);

  HException(const char *proc_name, const char *msg, Herror err = H_MSG_OK);

  HException(const HException &except);

  HException(const HTuple &tuple);

  virtual ~HException();


  // Raising exceptions (synchronization-aware)

  virtual void ThrowInstance() const;

  static void Throw(const char *proc_name, const char *msg, Herror err = H_MSG_OK);

  static void Throw(const char *proc_name, Herror err);


  // Conversion and copying

  static void    GetExceptionData(const HTuple &exception,
                                  const HTuple &name, HTuple *value);

  void           ToHTuple(HTuple *exception) const;

  HException&    operator = (const HException &except);


  // Accessors

  const HString& ProcName()    const {return mProcName;}
  const HString& ErrorMessage()   const {return mErrorMessage;}
  Herror         ErrorCode() const {return mErrorCode;}
  HDEPRECATED(const HString& ErrorText() const ,
              "deprecated, please use ErrorMessage instead.")
              {return mErrorMessage;}
  HDEPRECATED(Herror ErrorNumber() const ,
             "deprecated, please use ErrorCode instead.")
             {return mErrorCode;}
  const HTuple&  UserData()    const {return mUserData;}

  // Legacy
#ifdef HCPP_LEGACY_EXCEPTION
  // Handler for user defined exception handling.
  // Used with InstallHHandler()
  typedef void (*Handler)(const HException &exception);

  void           React(Hproc_handle proc_handle) const;

  static Handler InstallHHandler(Handler proc);
  // default exception handler
  void           PrintException(void) const;
  static Handler handler;   /* handler in use */
#endif

protected:

  HString        mProcName;     // Name of procedure/operator
  HString        mErrorMessage; // Error message
  Herror         mErrorCode;    // Error code

  HTuple         mUserData;    // User defined error data

private:

  void InitException(const HString& proc_name, const HString& msg,
                     Herror err, const HTuple& user_data);

};


// Exception that is raised if operator call in HALCON library fails 

class LIntExport HOperatorException : public HException
{
public:

  // Failure during operator call
  HOperatorException(Hproc_handle proc, Herror err);

  // Precall failure before procedure handle is available
  HOperatorException(HINT proc_index, Herror err);

  // Failure during operator-like call, e.g. emulated dev_* operators
  HOperatorException(const char* name, Herror err);

  HOperatorException(const HOperatorException &except);

  static void Throw(Hproc_handle proc, Herror err);

  static void Throw(HINT proc_index, Herror err);

  static void Throw(const char* name, Herror err);

  void ThrowInstance() const;

  // Extended Error Info
  HString  ExtendedErrorMessage() const;
  INT4_8   ExtendedErrorCode() const;

};


// Exception that is raised from user code (code export)

class LIntExport HUserException : public HException
{
public:

  HUserException(Herror err, const char *msg);

  HUserException(const HUserException &except);

  HUserException(const HTuple &tuple);

};


// Exception that is raised for tuple-related errors

class LIntExport HTupleAccessException: public HException
{
public:

  HTupleAccessException(void) : HException("","Illegal operation on tuple") {}
  HTupleAccessException(const char *m) : HException("",m) {}
  HTupleAccessException(Herror err) : HException("",err) {}
  static void Throw(void);
  static void Throw(const char* m);
  static void Throw(Herror err);
  void ThrowInstance() const;
  ~HTupleAccessException();
};



// Exception that is raised for vector-related errors

class LIntExport HVectorAccessException: public HException
{
public:

  HVectorAccessException(void) : HException("",
                                   "Illegal operation on vector") {}
  HVectorAccessException(const char *m) : HException("",m) {}
  HVectorAccessException(Herror err) : HException("",err) {}
  HVectorAccessException(const char *m, Herror err) : HException("",m,err) {}
  static void Throw(void);
  static void Throw(const char* m);
  static void Throw(Herror err);
  void ThrowInstance() const;
  ~HVectorAccessException();
};


}

#endif
