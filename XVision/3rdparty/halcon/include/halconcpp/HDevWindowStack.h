/*****************************************************************************
 * HDevWindowStack.h
 ***************************************************************************** 
 *
 * Project:     HALCON/C++
 * Description: Window management for exported HDevelop code
 *
 * (c) 2010-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 *
 *****************************************************************************/


#ifndef HCPP_DEV_WINDOW_STACK_H
#define HCPP_DEV_WINDOW_STACK_H


#include "halconcpp/HTuple.h"


namespace HalconCpp
{

// The class HDevWindowStack can be used to emulate the behavior of HDevelop
// graphics windows for HALCON graphics windows. It is primarily intended for
// usage in C++ programs exported from HDevelop programs containing HDevelop
// window operators (e.g. dev_set_window, dev_open_window, dev_close_window...)
class LIntExport HDevWindowStack
{

public:  

  // Push handle for new window (dev_open_window)
  static void   Push(const HTuple &win_handle);
  
  // Pop handle for closed window (dev_close_window)
  static HTuple Pop();
  
  // Get handle for active window
  static HTuple GetActive();
  
  // Set active window (dev_set_window)
  static void   SetActive(const HTuple &win_handle);
  
  // Test if any open window is available
  static bool   IsOpen();
  
  // Close all open windows
  static void   CloseAll();
  
};

}

#endif
