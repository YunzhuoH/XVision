/*****************************************************************************
 * HDataBase.h
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


#ifndef HCPP_DATA_BASE_H
#define HCPP_DATA_BASE_H


namespace HalconCpp
{

class LIntExport HDataBase
{

public:

  // Create an uninitialized data object
  HDataBase();

  // Create data object from tuple data
  HDataBase(const HTuple& data);

  // Copy constructor
  HDataBase(const HDataBase& data);

  // Assignment
  HDataBase& operator = (const HDataBase& data);
  HDataBase& operator = (const HTuple& data);

  // Cast
  operator HTuple() const;

  // Set data from tuple
  void SetFromTuple(const HTuple& data);

  // Get data as tuple
  HTuple ConvertToTuple() const;

  void Clear();

protected:

  HTuple mData;
};



class LIntExport HDataArray
{

public:

  // Create empty tool array for use as output parameter
  HDataArray();

  virtual ~HDataArray();

  // Assignment
  HDataArray& operator = (const HDataArray& data_array);

  HDataBase* Data();
  const HDataBase* Data() const;

  Hlong Length() const;

  void Clear();

  // Create data class array from splittable tuple
  void SetFromTuple(const HTuple& concatenated);

  // Get concatenated data tuple for data array
  HTuple ConvertToTuple() const;

protected:

  void InitFromArray(HDataBase* data, Hlong length);

  virtual void CreateArray(Hlong length) = 0;

  virtual int GetFixedSize() const = 0;

  HDataBase* mArray;
  Hlong      mLength;
};



}

#endif
