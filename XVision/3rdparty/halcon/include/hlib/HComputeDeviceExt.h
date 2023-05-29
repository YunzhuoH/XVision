/*****************************************************************************
 * HComputeDeviceExt.h
 *****************************************************************************
 *
 * Project:      Halcon/libhalcon
 * Description:  External Compute Device Interface
 *
 * (c) 2011-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************/

#ifndef HCOMPUTEDEVICEEXT_H
#define HCOMPUTEDEVICEEXT_H

#include "hlib/DBNew.h"

#ifndef HC_NO_COMPUTE_DEVICES
#  ifdef __APPLE__
#    include "OpenCL/opencl.h"
#  else
#    include "CL/opencl.h"
#  endif

#  if defined(__cplusplus)
extern "C" {
#  endif

/*****************************************************************************/
/** HXPkgCDInitDevice: initiales a compute device
 *****************************************************************************
 * Effectively does nothing if the device had been activated before
 *
 * \pi   proc_id      HALCON procedure handle
 * \pi   device_kind  currently only COMPUTE_DEVICE_OpenCL is supported
 *****************************************************************************/
extern HLibExport Herror HXPkgCDInitDevice(Hproc_handle proc_id,
                                           INT4         device_kind);


/*****************************************************************************/
/** HXPkgCDDeviceActive: tests if a device is active for the current thread
 *****************************************************************************
 * \pi   proc_id      HALCON procedure handle
 * \pi   device_kind  currently only COMPUTE_DEVICE_OpenCL is supported
 *
 * \ret  TRUE if a device is active for the current thread
 *****************************************************************************/
extern HLibExport HBOOL HXPkgCDDeviceActive(Hproc_handle proc_id,
                                            INT4         device_kind);


/*****************************************************************************/
/** HXPkgCDActiveDeviceKind: returns the kind of the currently active device
 *****************************************************************************
 * \pi   proc_id      HALCON procedure handle
 * \po   device_kind  COMPUTE_DEVICE_OpenCL or COMPUTE_DEVICE_NONE
 *****************************************************************************/
extern HLibExport Herror HXPkgCDActiveDeviceKind(Hproc_handle proc_id,
                                                 INT4*        device_kind);


/*****************************************************************************/
/** HXPkgCDTransferToBuffer: transfer an image object to a device buffer
 *****************************************************************************
 * Is used to transfer input image objects onto the device. May allocate
 * memory on the device. If the image object already is on the device,
 * HXPkgCDTransferToBuffer does not transfer it again.
 *
 * \pi   proc_id      HALCON procedure handle
 * \pi   image_key    key of the image object to be transferred
 * \po   device_ptr   pointer to the device memory of image_key
 *****************************************************************************/
extern HLibExport Herror HXPkgCDTransferToBuffer(Hproc_handle proc_id,
                                                 Hkey         image_key,
                                                 HCDPtr*      device_ptr);


/*****************************************************************************/
/** HXPkgCDTransferToImage: transfer an image object to a device image
 *****************************************************************************
 * Is used to transfer input image objects onto the device. May allocate
 * memory on the device. If the image object already is on the device,
 * HXPkgCDTransferToImage does not transfer it again.
 *
 * \pi   proc_id      HALCON procedure handle
 * \pi   image_key    key of the image object to be transferred
 * \po   device_ptr   pointer to the device memory of image_key
 *****************************************************************************/
extern HLibExport Herror HXPkgCDTransferToImage(Hproc_handle proc_id,
                                                Hkey         image_key,
                                                HCDPtr*      device_ptr);


/*****************************************************************************/
/** HXPkgCDAllocBuffer: allocates device memory for an output object
 *****************************************************************************
 * Is used to allocate memory for an output image object on the device.
 *
 * \pi   proc_id      HALCON procedure handle
 * \pi   image_key    key of the output image object
 * \po   device_ptr   pointer to the device memory of image_key
 *****************************************************************************/
extern HLibExport Herror HXPkgCDAllocBuffer(Hproc_handle proc_id,
                                            Hkey         image_key,
                                            HCDPtr*      device_ptr);


/*****************************************************************************/
/** HXPkgCDAttachComputeEvent: attaches an event to an output object
 *****************************************************************************
 * To allow for asynchronous execution of compute device operations
 * HXPkgCDAttachComputeEvent must be used to attach an event to an output
 * object such that a subsequent operator that depends on the results of
 * the compute device operation, can wait for this event
 *
 * \pi   proc_id      HALCON procedure handle
 * \pi   image_key    key of the output image object
 *****************************************************************************/
extern HLibExport Herror HXPkgCDAttachComputeEvent(Hproc_handle proc_id,
                                                   Hkey         image_key);


/*****************************************************************************/
/** HXPkgCDGetOpenCLContext: returns the OpenCL context
 *****************************************************************************
 * \pi   proc_id      HALCON procedure handle
 * \po   context      OpenCL context
 *****************************************************************************/
extern HLibExport Herror HXPkgCDGetOpenCLContext(Hproc_handle proc_id,
                                                 cl_context*  context);


/*****************************************************************************/
/** HXPkgCDGetOpenCLCommandQueue: returns the OpenCL command queue
 *****************************************************************************
 * \pi   proc_id      HALCON procedure handle
 * \po   queue        OpenCL command queue
 *****************************************************************************/
extern HLibExport Herror HXPkgCDGetOpenCLCommandQueue(Hproc_handle proc_id,
                                                      cl_command_queue* queue);


/*****************************************************************************/
/** HXPkgCDKernelFileOpenCL: add a new OpenCL source file
 *****************************************************************************
 * HXPkgCDKernelFileOpenCL must be called in HXPkgMain such that it is
 * executed before any HALCON operator call.
 *
 * The kernel source file must have the extension .cl. file_name must be
 * passed without extension.
 *
 * You can pass NULL for path. In this case the source file must be located
 * in the subfolder opencl_kernel within the extension package folder.
 *
 * \pi   proc_id         HALCON procedure handle
 * \pi   file_name       name of the source file
 * \pi   path            path to the source file
 * \pi   kernel_names    names of __kernel functions in the source file
 * \pi   num_kernel      number of kernels in the source file
 * \pi   operator_names  name of the operator a kernel is assigned to
 *                       (used in init_compute_device)
 * \po   kernel_ids      identifiers that can later be passed to
 *                       HXPkgCDGetKernelOpenCL
 *****************************************************************************/
extern HLibExport Herror HXPkgCDKernelFileOpenCL(
    Hproc_handle proc_id, char* file_name, char* path, char** kernel_names,
    INT4 num_kernel, char** operator_names, INT4* kernel_ids);


/*****************************************************************************/
/** HXPkgCDGetKernelOpenCL: returns a handle to an OpenCL kernel
 *****************************************************************************
 * If the kernel has not been compiled before (e.g. by init_compute_device)
 * it is done on demand.
 *
 * \pi   proc_id          HALCON procedure handle
 * \pi   kernel_id        as obtained by HXPkgCDKernelFileOpenCL
 * \po   kernel           handle to the OpenCL kernel
 *****************************************************************************/
extern HLibExport Herror HXPkgCDGetKernelOpenCL(Hproc_handle proc_id,
                                                INT4         kernel_id,
                                                cl_kernel*   kernel);


/*****************************************************************************/
/** HXPkgCDAllocDeviceBufferOpenCL: allocate a device buffer
 *****************************************************************************
 * Uses the HALCON device buffer cache
 *
 * \pi   proc_id           HALCON procedure handle
 * \po   ptr               pointer to the allocated device buffer
 * \pi   size              requested size
 *****************************************************************************/
extern HLibExport Herror HXPkgCDAllocDeviceBufferOpenCL(Hproc_handle proc_id,
                                                        HCDPtr*      ptr,
                                                        UINT4_8      size);


/*****************************************************************************/
/** HXPkgCDAllocConstantDeviceBufferOpenCL: allocate a constant device buffer
 *****************************************************************************
 * Uses the HALCON device buffer cache. The only difference to
 * HXPkgCDAllocDeviceBufferOpenCL is that the size of the returned memory block
 * is smaller than the maximum size of constant buffers.
 *
 * \pi   proc_id       HALCON procedure handle
 * \po   ptr           pointer to the allocated device buffer
 * \pi   size          requested size
 *****************************************************************************/
extern HLibExport Herror HXPkgCDAllocConstantDeviceBufferOpenCL(
    Hproc_handle proc_id, HCDPtr* ptr, UINT4_8 size);


/*****************************************************************************/
/** HXPkgCDFreeDeviceBufferOpenCL: free a device buffer
 *****************************************************************************
 * Free blocks obtained by HXPkgCDAllocDeviceBufferOpenCL or
 * HXPkgCDAllocConstantDeviceBufferOpenCL.
 *
 * \pi   proc_id       HALCON procedure handle
 * \po   ptr           pointer to the device buffer
 *****************************************************************************/
extern HLibExport Herror HXPkgCDFreeDeviceBufferOpenCL(Hproc_handle proc_id,
                                                       HCDPtr       ptr);


/*****************************************************************************/
/** HXPkgCDAllocLocalDeviceBufferOpenCL: allocate a local device buffer
 *****************************************************************************
 * A device buffer allocated by HXPkgCDAllocLocalDeviceBufferOpenCL is freed
 * automatically if the output image object assigned to the current operation
 * (via HXPkgAttachComputeEvent) is freed or transferred to the host.
 *
 * This allows for the usage of temporary buffers in asynchronously executed
 * compute device code.
 *
 * \pi   proc_id       HALCON procedure handle
 * \po   ptr           pointer to the allocated device buffer
 * \pi   size          requested size
 *****************************************************************************/
extern HLibExport Herror HXPkgCDAllocLocalDeviceBufferOpenCL(
    Hproc_handle proc_id, HCDPtr* ptr, UINT4_8 size);


/*****************************************************************************/
/** HXPkgCDAllocLocalConstantDeviceBufferOpenCL
 *****************************************************************************
 * The only difference to HXPkgCDAllocLocalDeviceBufferOpenCL is that the
 * size of the returned memory block is smaller than the maximum size of
 * constant buffers.
 *
 * \pi   proc_id       HALCON procedure handle
 * \po   ptr           pointer to the allocated device buffer
 * \pi   size          requested size
 *****************************************************************************/
extern HLibExport Herror HXPkgCDAllocLocalConstantDeviceBufferOpenCL(
    Hproc_handle proc_id, HCDPtr* ptr, UINT4_8 size);


/*****************************************************************************/
/** HXPkgCDAllocDeviceImageOpenCL: allocate a device image
 *****************************************************************************
 * Uses the HALCON device image cache
 *
 * \pi   proc_id           HALCON procedure handle
 * \po   ptr               pointer to the allocated device image
 * \pi   kind              of the image
 * \pi   width             of the image
 * \pi   height            of the image
 *****************************************************************************/
extern HLibExport Herror HXPkgCDAllocDeviceImageOpenCL(Hproc_handle proc_id,
                                                       HCDPtr* ptr, HINT kind,
                                                       HIMGDIM width,
                                                       HIMGDIM height);


/*****************************************************************************/
/** HXPkgCDFreeDeviceImageOpenCL: free a device image
 *****************************************************************************
 * Free blocks obtained by HXPkgCDAllocDeviceImageOpenCL .
 *
 * \pi   proc_id       HALCON procedure handle
 * \po   ptr           pointer to the device image
 *****************************************************************************/
extern HLibExport Herror HXPkgCDFreeDeviceImageOpenCL(Hproc_handle proc_id,
                                                      HCDPtr       ptr);


/*****************************************************************************/
/** HXPkgCDAllocPinnedOpenCL: allocate a pinned block in host memory
 *****************************************************************************
 * Uses the HALCON pinned memory cache.
 *
 * \pi   proc_id        HALCON procedure handle
 * \pi   size           required size
 * \po   ptr_p          pointer to the pinned memory block
 * \po   pinned_handle  handle to the pinned memory block
 *****************************************************************************/
extern HLibExport Herror HXPkgCDAllocPinnedOpenCL(Hproc_handle proc_id,
                                                  size_t size, void* ptr_p,
                                                  HCDPinnedPtr* pinned_handle);


/*****************************************************************************/
/** HXPkgCDFreePinnedOpenCL: free a pinned memory block
 *****************************************************************************
 * \pi   proc_id        HALCON procedure handle
 * \po   ptr            pointer to the pinned memory block
 * \po   pinned_handle  handle to the pinned memory block
 *****************************************************************************/
extern HLibExport Herror HXPkgCDFreePinnedOpenCL(Hproc_handle proc_id,
                                                 void*        ptr,
                                                 HCDPinnedPtr pinned_handle);


/*****************************************************************************/
/** HXPkgCDAllocLocalPinnedOpenCL: allocate a local pinned block in host memory
 *****************************************************************************
 * A pinned memory lblock allocated by HXPkgCDAllocLocalPinnedOpenCL is freed
 * automatically if the output image object assigned to the current operation
 * (via HXPkgAttachComputeEvent) is freed or transferred to the host.
 *
 * \pi   proc_id        HALCON procedure handle
 * \pi   size           required size
 * \po   ptr_p          pointer to the pinned memory block
 * \po   pinned_handle  handle to the pinned memory block
 *****************************************************************************/
extern HLibExport Herror
                  HXPkgCDAllocLocalPinnedOpenCL(Hproc_handle proc_id, size_t size, void* ptr_p,
                                                HCDPinnedPtr* pinned_handle);


/*****************************************************************************/
/** HXPkgCDGetDevicePtr: obtain the device pointer of an image object
 *****************************************************************************
 * ptr is removed from the HALCON device buffer/image cache and must be
 * retained before the image object refrenced by image_key is freed.
 *
 * \pi   proc_id        HALCON procedure handle
 * \pi   image_key      image object
 * \po   ptr            device pointer of the image object
 *****************************************************************************/
extern HLibExport Herror HXPkgCDGetDevicePtr(Hproc_handle proc_id,
                                             Hkey image_key, HCDPtr* ptr);


/*****************************************************************************/
/** HXPkgCDSetDevicePtr: set the device pointer of an image object
 *****************************************************************************
 * ptr is retained by HXPkgCDSetDevicePtr.
 *
 * \pi   proc_id         HALCON procedure handle
 * \pi   image_key       image object
 * \pi   mem_handle      OpenCL memory object
 * \pi   mem_kind        HCD_BUFFER or HCD_IMAGE
 *****************************************************************************/
extern HLibExport Herror HXPkgCDSetDevicePtr(Hproc_handle proc_id,
                                             Hkey image_key, cl_mem mem_handle,
                                             INT4 mem_kind);


#  if defined(__cplusplus)
}
#  endif

#endif
#endif
