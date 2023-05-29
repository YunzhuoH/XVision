/*****************************************************************************
 * HDevEngineCpp.h
 *****************************************************************************
 *
 * Description: Interface for executing HDevelop programs and procedures
 *              within a C++ application using the HALCON/C++ interface.
 * Attention:   This engine uses the new HALCON/C++ interface that was
 *              introduced in HALCON 11.
 *              If your HDevEngine application was developed with a prior
 *              version of HALCON and uses the old HALCON/C++ interface
 *              We recommend to migrate it to the new HALCON/C++ interface.
 *              However, if this is not possible, you can use the legacy
 *              HDevEngine from the path
 *                %HALCONROOT%/include/hdevengine10
 *              In addition, your application must be linked against the
 *              libraries halconcpp10 and hdevenginecpp10 (instead of
 *              halconcpp and hdevenginecpp).
 *              Changes within the source files are not needed.
 *
 * (c) 1996-2018 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************/

#ifndef H_DEV_ENGINE_CPP_H
#define H_DEV_ENGINE_CPP_H

// include the HALCON 11 C++ interface
#include "halconcpp/HalconCpp.h"


#ifndef HDEV_PD
#define HDEV_PD private: class Data; Data* mData
#endif

namespace HDevEngineCpp
{
// Forward declarations
class HDevEngine;
class HDevProgram;
class HDevProgramCall;
class HDevProcedure;
class HDevProcedureCall;
class HDevEngineException;
class HDevOperatorImplCpp;


/*****************************************************************************
 *****************************************************************************
 ** class HDevEngine
 **===========================================================================
 ** Class for managing global engine settings:
 **  + external procedure path
 **  + implementation of dev_ operators (HDevOperatorImpl)
 **  + Attention: all changes made to one HDevEngine instance all global
 **    for all .dev programs or .dvp procedure that are executed in one
 **    application
 *****************************************************************************
 *****************************************************************************/
class LIntExport HDevEngine
{
public:

  HDevEngine();

  // Via engine attributes the behavior of the engine can be configured
  // currently the following flags are supported:
  //  "ignore_unresolved_lines"  [default: false, 0]
  //     - if set to true (or "true"), program lines that refer to an
  //       unresolved procedure are ignored, i.e., the program or procedure is
  //       executed without the corrupted program line;
  //       this may lead to an unexpected behavior or an error during the
  //       program execution
  //     - as the default an exception is thrown while creating the program or
  //       procedure instance
  //  "ignore_invalid_lines"  [default: false, 0]
  //     - if set to true (or "true"), invalid program lines  are ignored,
  //       i.e., the program or procedure is executed without the corrupted
  //       program line;
  //       this may lead to an unexpected behavior or an error during the
  //       program execution
  //     - as the default an exception is thrown while creating the program or
  //       procedure instance
  //  "ignore_invalid_results"  [default: true, 1]
  //     - if set to false (or "false") throw an exception if the accessed
  //       procedure output parameter or program variable is invalid
  //     - the following methods are concerned:
  //         HenProgramCall::GetIconicVarObject()
  //         HenProgramCall::GetCtrlVarTuple()
  //         HenProcedureCall::GetOutputIconicParamObject()
  //         HenProcedureCall::GetOutputCtrlParamTuple()
  //     - as the default an empty region object or an empty tuple is returned
  //       if the object was not set within the program or procedure
  //  "docu_language"  [default: "" -> en_US]
  //     - could be set to "en_US","de_DE",  other languages
  //  "docu_encoding"  [default: "" -> "utf8"]
  //     - if set to "native" all natural language strings are converted
  //       to native encoding
  //  "execute_procedures_jit_compiled"  [default: false, 0]
  //     - if set to true (or "true"), procedures are tried to being compiled
  //       with a just-in-time compiler for faster execution
  //  "debug_port"  [default: 57786]
  //     - specifies the port number of the socket where the debug server
  //       waits for incoming connections
  //  "debug_password"  [default: ""]
  //     - specifying a password provides a basic layer of protection
  //       against misuse. For security reasons, it is highly recommended
  //       to always supply a password. If a password is set, it must be
  //       entered in HDevelop to allow the connection
  //  "debug_wait_for_connection"  [default: false]
  //     - if set to true, the engine switches into "stopped state"
  //       after starting the debug server (see below). This has the effect
  //       that any application thread that enters procedure execution
  //       via HDevEngine will stop on the first line of script code.
  //       This way, you can start debugging from the beginning of your code
  //       upon connecting from HDevelop
  void SetEngineAttribute(const char* name, const HalconCpp::HTuple& value);
  HalconCpp::HTuple GetEngineAttribute(const char* name);

  // Set path(s) for external procedures
  //  - several paths can be passed together separating them by ';' or ':'
  //    on Windows or UNIX-like systems resp.
  //  - NULL removes all procedure paths and unloads all external procedures
  //    (Attention: procedures that are used by programs (HDevProgram) or
  //    procedures (HDevProcedures) remain unchanged until the program or
  //    procedure is reloaded explicitly.  The appropriate calls must be
  //    recreated or reassigned by the reloaded program or procedure.)
  //  - additional calls of SetProcedurePath will remove paths set before
  //    and unload all external procedures
  void SetProcedurePath(const char* path);
  void AddProcedurePath(const char* path);
#ifdef _WIN32
  void SetProcedurePath(const wchar_t* path);
  void AddProcedurePath(const wchar_t* path);
#endif
  // Get names of all available external procedures
  HalconCpp::HTuple GetProcedureNames() const;
  // Get names of all loaded external procedures
  HalconCpp::HTuple GetLoadedProcedureNames() const;
  // Unload a specific procedure <proc_name>
  void UnloadProcedure(const char* proc_name);
  // Unload all external procedures
  void UnloadAllProcedures();

  // Starts the debug server that allows to attach HDevelop as
  // as debugger to step through engine code. With default settings
  // server waits on port 57786 and engine runs normally until HDevelop
  // is connected and F9 is pressed to stop execution.
  void StartDebugServer();

  // Stops the debug server (resuming execution if stopped)
  void StopDebugServer();

  // global variable access
  HalconCpp::HTuple  GetGlobalIconicVarNames() const;
  HalconCpp::HTuple  GetGlobalCtrlVarNames()   const;
  // get dimension of a global variable
  int  GetGlobalIconicVarDimension(const char* var_name) const;
  int  GetGlobalCtrlVarDimension(const char* var_name)   const;
  // get value of a global variable
  HalconCpp::HObject GetGlobalIconicVarObject(const char* var_name);
  HalconCpp::HTuple  GetGlobalCtrlVarTuple(const char* var_name);
  HalconCpp::HObjectVector GetGlobalIconicVarVector(const char* var_name);
  HalconCpp::HTupleVector  GetGlobalCtrlVarVector(const char* var_name);
  // these method is provided for efficiency:
  // the results are copied directly into the tuple variable provided by
  // the user without additional copying
  void GetGlobalCtrlVarTuple(const char* var_name, HalconCpp::HTuple* tuple);
  // set global variable
  void SetGlobalIconicVarObject(const char* var_name,
                                const HalconCpp::HObject& obj);
  void SetGlobalCtrlVarTuple(const char* var_name,
                             const HalconCpp::HTuple& tuple);
  void SetGlobalIconicVarVector(const char* var_name,
                                const HalconCpp::HObjectVector& vector);
  void SetGlobalCtrlVarVector(const char* var_name,
                              const HalconCpp::HTupleVector& vector);


  // Set implementation for HDevelop internal operators
  void SetHDevOperatorImpl(HDevOperatorImplCpp* hdev_op_impl);
};




/*****************************************************************************
 *****************************************************************************
 ** class HDevProgram
 **===========================================================================
 ** Class for managing HDevelop programs
 *****************************************************************************
 *****************************************************************************/
class LIntExport HDevProgram
{
  HDEV_PD;

public:

  // Create a program from a .dev program file
  HDevProgram(const char* file_name=NULL);

#ifdef _WIN32
  HDevProgram(const wchar_t* file_name);
#endif

  // Copy constructor
  HDevProgram(const HDevProgram& hdev_prog);
  HDevProgram(const Data& data);

  // Assignment operation
  HDevProgram& operator=(const HDevProgram& hdev_prog);

  // Destructor
  virtual ~HDevProgram();

  // Load a program if not yet done during construction
  void            LoadProgram(const char* file_name);

#ifdef _WIN32
  void            LoadProgram(const wchar_t* file_name);
#endif

  // check whether the program was successfully loaded
  bool            IsLoaded() const;

  // Get the program name
  const char*     GetName() const;

  // Get the names of all local and the used external procedures
  HalconCpp::HTuple  GetUsedProcedureNames()   const;
  HalconCpp::HTuple  GetLocalProcedureNames()   const;

  // Compile all procedures that are used by the program and that can be
  // compiled with a just-in-time compiler.
  // The method returns true when all used procedures could be compiled by the
  // just-in-time compiler.
  // Procedures that could not be compiled are called normally by the
  // HDevEngine interpreter.
  // To check which procedure could not be compiled and what the reason is for
  // that start HDevelop and check there the compilation states.
  bool         CompileUsedProcedures();

  // create a program call for execution
  HDevProgramCall CreateCall() const;

  // This is a method provided for convenience:
  // execute the program and return the program call for
  // accessing the variables of the program's main procedure
  HDevProgramCall Execute() const;

  // get some information about the variables of the program's main procedure:
  //  - get the variable names as a tuple
  HalconCpp::HTuple  GetIconicVarNames() const;
  HalconCpp::HTuple  GetCtrlVarNames()   const;

  //  - get the number of iconic and control variables
  size_t          GetIconicVarCount() const;
  size_t          GetCtrlVarCount()   const;

  //  - get the names of the variables
  //   (indices of the variables run from 1 to count)
  const char*     GetIconicVarName(size_t var_idx) const;
  const char*     GetCtrlVarName(size_t var_idx)   const;

  //  - get the dimensions of the variables
  //   (indices of the variables run from 1 to count)
  int GetIconicVarDimension(size_t var_idx) const;
  int GetCtrlVarDimension(size_t var_idx) const;
};




/*****************************************************************************
 *****************************************************************************
 ** class HDevProgramCall
 **===========================================================================
 ** Class for managing the execution of an HDevelop program
 *****************************************************************************
 *****************************************************************************/
class LIntExport HDevProgramCall
{
  HDEV_PD;

public:

  // Create an empty HDevelop program call instance
  HDevProgramCall();
  // Create an HDevelop program call from a program
  HDevProgramCall(const HDevProgram& prog);
  // Copy constructor
  HDevProgramCall(const HDevProgramCall& hdev_prog_call);
  HDevProgramCall(const Data& data);
  // Assignment operation
  HDevProgramCall& operator=(const HDevProgramCall& hdev_prog_call);
  // Destructor
  virtual ~HDevProgramCall();

  // Get the program
  HDevProgram GetProgram() const;

  // Execute program
  void Execute();

  // Stop execution on first line of program. This is intended for debugging
  // purposes when you wish to step through a specific program call. It only
  // has an effect when a debug server is running and it will only stop once.
  void SetWaitForDebugConnection(bool wait_once);

  // Clear program and reset callstack
  //  - this method stops the execution of the program after the current
  //    program line
  void Reset();

  // Get the objects / values of the variables by name or by index
  //   (indices of the variables run from 1 to count)
  HalconCpp::HObject GetIconicVarObject(size_t var_idx);
  HalconCpp::HObject GetIconicVarObject(const char* var_name);

  HalconCpp::HObjectVector GetIconicVarVector(size_t var_idx);
  HalconCpp::HObjectVector GetIconicVarVector(const char* var_name);

  HalconCpp::HTuple  GetCtrlVarTuple(size_t var_idx);
  HalconCpp::HTuple  GetCtrlVarTuple(const char* var_name);

  HalconCpp::HTupleVector  GetCtrlVarVector(size_t var_idx);
  HalconCpp::HTupleVector  GetCtrlVarVector(const char* var_name);

  // these methods are provided for efficiency:
  // the results are copied directly into the tuple variable provided by
  // the user without additional copying
  void GetCtrlVarTuple(size_t var_idx, HalconCpp::HTuple* tuple);
  void GetCtrlVarTuple(const char* var_name, HalconCpp::HTuple* tuple);
};




/*****************************************************************************
 *****************************************************************************
 ** class HDevProcedure
 **===========================================================================
 ** Class for managing HDevelop procedures
 *****************************************************************************
 *****************************************************************************/
class  LIntExport HDevProcedure
{
  HDEV_PD;

public:

  // Create HDevelop procedure from external or local procedure
  HDevProcedure(const char* proc_name=NULL);
  HDevProcedure(const char* prog_name, const char* proc_name);
  HDevProcedure(const HDevProgram& prog, const char* proc_name);

#ifdef _WIN32
  HDevProcedure(const wchar_t* prog_name, const char* proc_name);
#endif

  // Copy constructor
  HDevProcedure(const HDevProcedure& hdev_proc);
  HDevProcedure(const Data& data);
  // Assignment operation
  HDevProcedure& operator=(const HDevProcedure& proc);
  // Destructor
  ~HDevProcedure();

  // Load a procedure if not yet done during construction
  void         LoadProcedure(const char* proc_name);
  void         LoadProcedure(const char* prog_name, const char* proc_name);
  void         LoadProcedure(const HDevProgram& prog, const char* proc_name);

#ifdef _WIN32
  void         LoadProcedure(const wchar_t* prog_name, const char* proc_name);
#endif

  // Check whether the procedure was successfully loaded
  bool         IsLoaded() const;

  // Get the name of the procedure
  const char*  GetName() const;

  // Get the short description of the procedure. The encoding of the
  // description will be in local 8 bit or utf-8, depending on the
  // HALCON/C++ interface encoding. Note there is no wchar_t overload for
  // Windows applications compiled with UNICODE support; however, you can
  // access the description using GetInfo("short").S().TextW() instead.
  const char*  GetShortDescription() const;

  // Get all refered procedures
  HalconCpp::HTuple  GetUsedProcedureNames() const;

  // Compile all procedures that are used by the procedure and that can be
  // compiled with a just-in-time compiler.
  // The method returns true when all used procedures could be compiled by the
  // just-in-time compiler.
  // Procedures that could not be compiled are called normally by the
  // HDevEngine interpreter.
  // To check which procedure could not be compiled and what the reason is for
  // that start HDevelop and check there the compilation states.
  bool         CompileUsedProcedures();

  // Create a program call for execution
  HDevProcedureCall CreateCall() const;

  // Get name of input/output object/control parameters
  HalconCpp::HTuple GetInputIconicParamNames()  const;
  HalconCpp::HTuple GetOutputIconicParamNames() const;
  HalconCpp::HTuple GetInputCtrlParamNames()    const;
  HalconCpp::HTuple GetOutputCtrlParamNames()   const;

  // Get number of input/output object/control parameters
  int            GetInputIconicParamCount()  const;
  int            GetOutputIconicParamCount() const;
  int            GetInputCtrlParamCount()    const;
  int            GetOutputCtrlParamCount()   const;

  // Get name of input/output object/control parameters
  //   (indices of the parameters run from 1 to count)
  const char*    GetInputIconicParamName(int par_idx)  const;
  const char*    GetOutputIconicParamName(int par_idx) const;
  const char*    GetInputCtrlParamName(int par_idx)    const;
  const char*    GetOutputCtrlParamName(int par_idx)   const;

  // Get dimension of input/output object/control parameters
  //   (indices of the parameters run from 1 to count)
  int GetInputIconicParamDimension(int par_idx)  const;
  int GetOutputIconicParamDimension(int par_idx) const;
  int GetInputCtrlParamDimension(int par_idx)    const;
  int GetOutputCtrlParamDimension(int par_idx)   const;

  // Get info of procedure documentation
  HalconCpp::HTuple GetInfo(const char* slot)  const;
  // Get info of parameter documentation by name
  HalconCpp::HTuple GetParamInfo(const char* par_name,
                                 const char* slot) const;
  // Get info of parameter documentation by index
  //   (indices of the parameters run from 1 to count)
  HalconCpp::HTuple GetInputIconicParamInfo(int par_idx,
                                            const char* slot)  const;
  HalconCpp::HTuple GetOutputIconicParamInfo(int par_idx,
                                             const char* slot) const;
  HalconCpp::HTuple GetInputCtrlParamInfo(int par_idx,
                                          const char* slot)    const;
  HalconCpp::HTuple GetOutputCtrlParamInfo(int par_idx,
                                           const char* slot)   const;

  // Query possible slots for procedure/parameter info
  HalconCpp::HTuple QueryInfo()       const;
  HalconCpp::HTuple QueryParamInfo()  const;
};




/*****************************************************************************
 *****************************************************************************
 ** class HDevProcedureCall
 **===========================================================================
 ** Class for executing an HDevelop procedure and managing the parameter
 ** values
 *****************************************************************************
 *****************************************************************************/
class  LIntExport HDevProcedureCall
{
  HDEV_PD;

public:

  // Create an empty HDevelop procedure call instance
  HDevProcedureCall();
  // Create HDevelop procedure call instance
  HDevProcedureCall(const HDevProcedure& hdev_proc);
  // Copy constructor
  HDevProcedureCall(const HDevProcedureCall& hdev_proc_call);
  HDevProcedureCall(const Data& data);
  // Assignment operation
  HDevProcedureCall& operator=(const HDevProcedureCall& hdev_proc_call);
  // Destructor
  ~HDevProcedureCall();

  // Get the procedure
  HDevProcedure GetProcedure() const;

  // Execute program
  void Execute();

  // Stop execution on first line of procedure. This is intended for debugging
  // purposes when you wish to step through a specific procedure call. It only
  // has an effect when a debug server is running and it will only stop once.
  void SetWaitForDebugConnection(bool wait_once);

  // Clear procedure and reset callstack
  //  - this method stops the execution of the procedure after the current
  //    program line
  void Reset();

  // Set input object/control parameter
  void SetInputIconicParamObject(int par_idx, const HalconCpp::HObject& obj);
  void SetInputIconicParamObject(const char* par_name,
                                 const HalconCpp::HObject& obj);
  void SetInputIconicParamVector(int par_idx,
                                 const HalconCpp::HObjectVector& vector);
  void SetInputIconicParamVector(const char* par_name,
                                 const HalconCpp::HObjectVector& vector);

  void SetInputCtrlParamTuple(int par_idx, const HalconCpp::HTuple& tuple);
  void SetInputCtrlParamTuple(const char* par_name,
                              const HalconCpp::HTuple& tuple);
  void SetInputCtrlParamVector(int par_idx,
                               const HalconCpp::HTupleVector& vector);
  void SetInputCtrlParamVector(const char* par_name,
                               const HalconCpp::HTupleVector& vector);

  // Get the objects / values of the parameters by name or by index
  //   (indices of the variables run from 1 to count)
  HalconCpp::HObject GetOutputIconicParamObject(int par_idx)          const;
  HalconCpp::HObject GetOutputIconicParamObject(const char* par_name) const;
  HalconCpp::HObjectVector
    GetOutputIconicParamVector(int par_idx)                           const;
  HalconCpp::HObjectVector
    GetOutputIconicParamVector(const char* par_name)                  const;
  HalconCpp::HTuple  GetOutputCtrlParamTuple(int par_idx)             const;
  HalconCpp::HTuple  GetOutputCtrlParamTuple(const char* par_name)    const;
  HalconCpp::HTupleVector
    GetOutputCtrlParamVector(int par_idx)                             const;
  HalconCpp::HTupleVector
    GetOutputCtrlParamVector(const char* par_name)                    const;

  // These methods are provided for efficiency:
  // the results are copied directly into the tuple variable provided by
  // the user without additional copying
  void GetOutputCtrlParamTuple(int par_idx, HalconCpp::HTuple* tuple) const;
  void GetOutputCtrlParamTuple(const char* par_name,
                               HalconCpp::HTuple* tuple)              const;
};




/*****************************************************************************
 *****************************************************************************
 ** class HDevEngineException
 **===========================================================================
 ** Class for HDevelop engine exceptions
 *****************************************************************************
 *****************************************************************************/
class LIntExport HDevEngineException
{
  HDEV_PD;

public:

  // Exception categories
  enum  ExceptionCategory
  {
    Exception,            // Generic
    ExceptionInpNotInit,  // Error input parameters not initialized
    ExceptionCall,        // Error HALCON or HDevelop operator call
    ExceptionFile         // Error opening or reading HDevelop file
  };

  // Create HDevelop engine exception
  HDevEngineException(const char* message,
                      ExceptionCategory category=Exception,
                      const char* exec_proc_name="",
                      int prog_line_num=-1,
                      const char* prog_line_name="",
                      Herror h_err_nr=H_MSG_VOID,
                      const HalconCpp::HTuple& user_data=HalconCpp::HTuple());
  HDevEngineException(const HDevEngineException& exc);
  HDevEngineException(const Data& data);
  HDevEngineException& operator = (const HDevEngineException& exc);
  virtual ~HDevEngineException();

  // Error text
  const char*            Message()           const;
  // Category of exception
  ExceptionCategory      Category()          const;
  const char*            CategoryText()      const;
  // Name of executed procedure
  const char*            ExecProcedureName() const;
  // Number of executed procedure or operator program line
  int                    ProgLineNum()       const;
  // Name of executed procedure or operator program line
  const char*            ProgLineName()      const;
  // HALCON error code
  Herror                 HalconErrorCode()   const;
  HDEPRECATED(Herror     HalconErrNum()      const,
              "deprecated, please use HalconErrorCode instead.");

  HalconCpp::HTuple      UserData()          const;
  void                   UserData(HalconCpp::HTuple& user_Data) const;
};



/*****************************************************************************
 *****************************************************************************
 ** class HDevOperatorImplCpp
 **===========================================================================
 ** Class for the implemention of HDevelop internal operators
 *****************************************************************************
 *****************************************************************************/
class LIntExport HDevOperatorImplCpp
{
  HDEV_PD;

public:

  HDevOperatorImplCpp();
  // Copy constructor
  HDevOperatorImplCpp(const HDevOperatorImplCpp& hdev_op_impl);
  HDevOperatorImplCpp(const Data& data);
  // Assignment operation
  HDevOperatorImplCpp& operator=(const HDevOperatorImplCpp& hdev_op_impl);
  // Destructor
  virtual ~HDevOperatorImplCpp();

  virtual int DevClearWindow();
  virtual int DevCloseWindow();
  virtual int DevSetWindow(const HalconCpp::HTuple& win_id);
  virtual int DevGetWindow(HalconCpp::HTuple* win_id);
  virtual int DevDisplay(const HalconCpp::HObject& obj);
  virtual int DevDispText(const HalconCpp::HTuple& string,
                          const HalconCpp::HTuple& coordSystem,
                          const HalconCpp::HTuple& row,
                          const HalconCpp::HTuple& column,
                          const HalconCpp::HTuple& color,
                          const HalconCpp::HTuple& genParamName,
                          const HalconCpp::HTuple& genParamValue);
  virtual int DevSetWindowExtents(const HalconCpp::HTuple& row,
                                  const HalconCpp::HTuple& col,
                                  const HalconCpp::HTuple& width,
                                  const HalconCpp::HTuple& height);
  virtual int DevSetDraw(const HalconCpp::HTuple& draw);
  virtual int DevSetContourStyle(const HalconCpp::HTuple& style);
  virtual int DevSetShape(const HalconCpp::HTuple& shape);
  virtual int DevSetColored(const HalconCpp::HTuple& colored);
  virtual int DevSetColor(const HalconCpp::HTuple& color);
  virtual int DevSetLut(const HalconCpp::HTuple& lut);
  virtual int DevSetPaint(const HalconCpp::HTuple& paint);
  virtual int DevSetPart(const HalconCpp::HTuple& row1,
                         const HalconCpp::HTuple& col1,
                         const HalconCpp::HTuple& row2,
                         const HalconCpp::HTuple& col2);
  virtual int DevSetLineWidth(const HalconCpp::HTuple& width);
  virtual int DevOpenWindow(const HalconCpp::HTuple& row,
                            const HalconCpp::HTuple& col,
                            const HalconCpp::HTuple& width,
                            const HalconCpp::HTuple& height,
                            const HalconCpp::HTuple& background,
                            HalconCpp::HTuple* win_id);
};
} // namespace HDevEngineCpp


#endif // #ifndef H_DEV_ENGINE_CPP_H
