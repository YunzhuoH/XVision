/*****************************************************************************
 * HDevThread.h
 *****************************************************************************
 *
 * Project:     Halcon/C++
 * Description: Helper class for export of HDevelop's parallel 
 *              language extensions.
 *
 * (c) 2014-2019 by MVTec Software GmbH
 *               www.mvtec.com
 *
 *****************************************************************************
 *
 *
 *****************************************************************************/


#ifndef HCPP_DEV_THREAD_H
#define HCPP_DEV_THREAD_H


namespace HalconCpp
{

class LIntExport HDevThreadContext
{

public:

  HDevThreadContext();
  ~HDevThreadContext();

  void* GetHandle() const 
  {
    return mContextHandle;
  }

private:

  void* mContextHandle;
};


class HDevInputParam;
class HDevOutputParam;


class LIntExport HDevThread
{

public:

  // Manage threads and procedure calls

  explicit HDevThread(const HDevThreadContext& context, 
                      const void* proc, Hlong num_in, Hlong num_out);
  ~HDevThread();


  void Start();

  void ParStart(HTuple *par_handle);

  static void ParJoin(const HTuple& par_handles);

  void Exit(void);

  void CallProc();

  bool IsDirectCall() const {return mDirectCall;}



  // Store copy of input parameter value in thread-specific context

  void SetInputIconicParamObject(Hlong par_index, const HObject& obj);
  void SetInputIconicParamVector(Hlong par_index,
                                 const HObjectVector& vector);
  void SetInputCtrlParamTuple(Hlong par_index, const HTuple& tuple);
  void SetInputCtrlParamVector(Hlong par_index,
                               const HTupleVector& vector);


  // Access thread-specific copy of input value

  const HObject& GetInputIconicParamObject(Hlong par_index) const;
  const HObjectVector& GetInputIconicParamVector(Hlong par_index) const;
  const HTuple& GetInputCtrlParamTuple(Hlong par_index) const;
  const HTupleVector& GetInputCtrlParamVector(Hlong par_index) const;


  // Bind variable reference to output parameter

  void BindOutputIconicParamObject(Hlong par_index, bool global,
                                   HObject* obj);
  void BindOutputIconicParamVector(Hlong par_index, bool global,
                                   HObjectVector* vector,
                                   HTuple index = HTuple());
  void BindOutputCtrlParamTuple(Hlong par_index, bool global, HTuple* obj);
  void BindOutputCtrlParamVector(Hlong par_index, bool global,
                                 HTupleVector* vector,
                                 HTuple index = HTuple());


  // Store result of procedure call into bound output variables

  void StoreOutputIconicParamObject(Hlong par_index, const HObject& obj);
  void StoreOutputIconicParamVector(Hlong par_index,
                                    const HObjectVector& vector);
  void StoreOutputCtrlParamTuple(Hlong par_index, const HTuple& tuple);
  void StoreOutputCtrlParamVector(Hlong par_index,
                                  const HTupleVector& vector);



protected:

  void* mThreadHandle;

  const void* mProc;

  bool mDirectCall;

  Hlong mNumParamsInput;
  Hlong mNumParamsOutput;

  HDevInputParam**  mParamsInput;
  HDevOutputParam** mParamsOutput;

};

} // namespace HalconCpp

#endif
