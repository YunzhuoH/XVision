/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Feb 26 17:53:32 2000
 */
/* Compiler settings for C:\Halcon\source\packages\grayfeat\source\com\HalconXimport.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __HalconXimport_h__
#define __HalconXimport_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IHObjectX_FWD_DEFINED__
#define __IHObjectX_FWD_DEFINED__
typedef interface IHObjectX IHObjectX;
#endif  /* __IHObjectX_FWD_DEFINED__ */


#ifndef __IHUntypedObjectX_FWD_DEFINED__
#define __IHUntypedObjectX_FWD_DEFINED__
typedef interface IHUntypedObjectX IHUntypedObjectX;
#endif  /* __IHUntypedObjectX_FWD_DEFINED__ */


#ifndef __IHandleAccess_FWD_DEFINED__
#define __IHandleAccess_FWD_DEFINED__
typedef interface IHandleAccess IHandleAccess;
#endif  /* __IHandleAccess_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IHObjectX_INTERFACE_DEFINED__
#define __IHObjectX_INTERFACE_DEFINED__

/* interface IHObjectX */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IHObjectX;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6ebd90c3-d219-11d2-ade5-0000c00f4ef9")
    IHObjectX : public IDispatch
    {
    public:
    };
    
#else   /* C style interface */

#pragma pack(push,8) /* sets the struct member alignment to 8 (default) */

    typedef struct IHObjectXVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHObjectX __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHObjectX __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHObjectX __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IHObjectX __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IHObjectX __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IHObjectX __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IHObjectX __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IHObjectXVtbl;

#pragma pack(pop)

    interface IHObjectX
    {
        CONST_VTBL struct IHObjectXVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHObjectX_QueryInterface(This,riid,ppvObject) \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHObjectX_AddRef(This)  \
    (This)->lpVtbl -> AddRef(This)

#define IHObjectX_Release(This) \
    (This)->lpVtbl -> Release(This)


#define IHObjectX_GetTypeInfoCount(This,pctinfo)  \
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IHObjectX_GetTypeInfo(This,iTInfo,lcid,ppTInfo) \
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IHObjectX_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) \
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IHObjectX_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) \
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif  /* C style interface */




#endif  /* __IHObjectX_INTERFACE_DEFINED__ */


#ifndef __IHUntypedObjectX_INTERFACE_DEFINED__
#define __IHUntypedObjectX_INTERFACE_DEFINED__

/* interface IHUntypedObjectX */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IHUntypedObjectX;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6ebd90c4-d219-11d2-ade5-0000c00f4ef9")
    IHUntypedObjectX : public IDispatch
    {
    public:
    };
    
#else   /* C style interface */

#pragma pack(push,8) /* sets the struct member alignment to 8 (default) */

    typedef struct IHUntypedObjectXVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHUntypedObjectX __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHUntypedObjectX __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHUntypedObjectX __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IHUntypedObjectX __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IHUntypedObjectX __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IHUntypedObjectX __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IHUntypedObjectX __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IHUntypedObjectXVtbl;

#pragma pack(pop)

    interface IHUntypedObjectX
    {
        CONST_VTBL struct IHUntypedObjectXVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHUntypedObjectX_QueryInterface(This,riid,ppvObject)  \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHUntypedObjectX_AddRef(This) \
    (This)->lpVtbl -> AddRef(This)

#define IHUntypedObjectX_Release(This)  \
    (This)->lpVtbl -> Release(This)


#define IHUntypedObjectX_GetTypeInfoCount(This,pctinfo) \
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IHUntypedObjectX_GetTypeInfo(This,iTInfo,lcid,ppTInfo)  \
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IHUntypedObjectX_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)  \
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IHUntypedObjectX_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)  \
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif  /* C style interface */




#endif  /* __IHUntypedObjectX_INTERFACE_DEFINED__ */


#ifndef __IHandleAccess_INTERFACE_DEFINED__
#define __IHandleAccess_INTERFACE_DEFINED__

/* interface IHandleAccess */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IHandleAccess;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6ebd90d2-d219-11d2-ade5-0000c00f4ef9")
    IHandleAccess : public IDispatch
    {
    public:
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE HandleAccess( 
            /* [retval][out] */ long __RPC_FAR *rVal) = 0;
        
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE HandleEnterCriticalSection( void) = 0;
        
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE HandleLeaveCriticalSection( void) = 0;
        
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE HandleCleanUp( 
            /* [in] */ BOOL CallDestructor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HandleIsValid( 
            /* [retval][out] */ long __RPC_FAR *isValid) = 0;
        
    };
    
#else   /* C style interface */

#pragma pack(push,8)

    typedef struct IHandleAccessVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHandleAccess __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHandleAccess __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHandleAccess __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IHandleAccess __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IHandleAccess __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IHandleAccess __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IHandleAccess __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleAccess )( 
            IHandleAccess __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *rVal);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleEnterCriticalSection )( 
            IHandleAccess __RPC_FAR * This);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleLeaveCriticalSection )( 
            IHandleAccess __RPC_FAR * This);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleCleanUp )( 
            IHandleAccess __RPC_FAR * This,
            /* [in] */ BOOL CallDestructor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleIsValid )( 
            IHandleAccess __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *isValid);
        
        END_INTERFACE
    } IHandleAccessVtbl;

#pragma pack(pop)

    interface IHandleAccess
    {
        CONST_VTBL struct IHandleAccessVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHandleAccess_QueryInterface(This,riid,ppvObject) \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHandleAccess_AddRef(This)  \
    (This)->lpVtbl -> AddRef(This)

#define IHandleAccess_Release(This) \
    (This)->lpVtbl -> Release(This)


#define IHandleAccess_GetTypeInfoCount(This,pctinfo)  \
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IHandleAccess_GetTypeInfo(This,iTInfo,lcid,ppTInfo) \
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IHandleAccess_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) \
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IHandleAccess_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) \
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IHandleAccess_HandleAccess(This,rVal) \
    (This)->lpVtbl -> HandleAccess(This,rVal)

#define IHandleAccess_HandleEnterCriticalSection(This)  \
    (This)->lpVtbl -> HandleEnterCriticalSection(This)

#define IHandleAccess_HandleLeaveCriticalSection(This)  \
    (This)->lpVtbl -> HandleLeaveCriticalSection(This)

#define IHandleAccess_HandleCleanUp(This,CallDestructor)  \
    (This)->lpVtbl -> HandleCleanUp(This,CallDestructor)

#define IHandleAccess_HandleIsValid(This,isValid) \
    (This)->lpVtbl -> HandleIsValid(This,isValid)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE IHandleAccess_HandleAccess_Proxy( 
    IHandleAccess __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *rVal);


void __RPC_STUB IHandleAccess_HandleAccess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE IHandleAccess_HandleEnterCriticalSection_Proxy( 
    IHandleAccess __RPC_FAR * This);


void __RPC_STUB IHandleAccess_HandleEnterCriticalSection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE IHandleAccess_HandleLeaveCriticalSection_Proxy( 
    IHandleAccess __RPC_FAR * This);


void __RPC_STUB IHandleAccess_HandleLeaveCriticalSection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE IHandleAccess_HandleCleanUp_Proxy( 
    IHandleAccess __RPC_FAR * This,
    /* [in] */ BOOL CallDestructor);


void __RPC_STUB IHandleAccess_HandleCleanUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHandleAccess_HandleIsValid_Proxy( 
    IHandleAccess __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *isValid);


void __RPC_STUB IHandleAccess_HandleIsValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif  /* __IHandleAccess_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
