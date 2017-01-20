

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Jan 20 14:43:51 2017
 */
/* Compiler settings for mwSICARDActX.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __mwSICARDActXidl_h__
#define __mwSICARDActXidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DmwSICARDActX_FWD_DEFINED__
#define ___DmwSICARDActX_FWD_DEFINED__
typedef interface _DmwSICARDActX _DmwSICARDActX;
#endif 	/* ___DmwSICARDActX_FWD_DEFINED__ */


#ifndef ___DmwSICARDActXEvents_FWD_DEFINED__
#define ___DmwSICARDActXEvents_FWD_DEFINED__
typedef interface _DmwSICARDActXEvents _DmwSICARDActXEvents;
#endif 	/* ___DmwSICARDActXEvents_FWD_DEFINED__ */


#ifndef __mwSICARDActX_FWD_DEFINED__
#define __mwSICARDActX_FWD_DEFINED__

#ifdef __cplusplus
typedef class mwSICARDActX mwSICARDActX;
#else
typedef struct mwSICARDActX mwSICARDActX;
#endif /* __cplusplus */

#endif 	/* __mwSICARDActX_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __mwSICARDActXLib_LIBRARY_DEFINED__
#define __mwSICARDActXLib_LIBRARY_DEFINED__

/* library mwSICARDActXLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_mwSICARDActXLib;

#ifndef ___DmwSICARDActX_DISPINTERFACE_DEFINED__
#define ___DmwSICARDActX_DISPINTERFACE_DEFINED__

/* dispinterface _DmwSICARDActX */
/* [uuid] */ 


EXTERN_C const IID DIID__DmwSICARDActX;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("3FFE3C52-F20E-4E61-9025-2E3C7B5D89BA")
    _DmwSICARDActX : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DmwSICARDActXVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DmwSICARDActX * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DmwSICARDActX * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DmwSICARDActX * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DmwSICARDActX * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DmwSICARDActX * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DmwSICARDActX * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DmwSICARDActX * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DmwSICARDActXVtbl;

    interface _DmwSICARDActX
    {
        CONST_VTBL struct _DmwSICARDActXVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DmwSICARDActX_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DmwSICARDActX_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DmwSICARDActX_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DmwSICARDActX_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DmwSICARDActX_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DmwSICARDActX_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DmwSICARDActX_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DmwSICARDActX_DISPINTERFACE_DEFINED__ */


#ifndef ___DmwSICARDActXEvents_DISPINTERFACE_DEFINED__
#define ___DmwSICARDActXEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DmwSICARDActXEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DmwSICARDActXEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("192ECAEA-D223-465E-B379-39C08A90FAD3")
    _DmwSICARDActXEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DmwSICARDActXEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DmwSICARDActXEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DmwSICARDActXEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DmwSICARDActXEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DmwSICARDActXEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DmwSICARDActXEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DmwSICARDActXEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DmwSICARDActXEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DmwSICARDActXEventsVtbl;

    interface _DmwSICARDActXEvents
    {
        CONST_VTBL struct _DmwSICARDActXEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DmwSICARDActXEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DmwSICARDActXEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DmwSICARDActXEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DmwSICARDActXEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DmwSICARDActXEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DmwSICARDActXEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DmwSICARDActXEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DmwSICARDActXEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_mwSICARDActX;

#ifdef __cplusplus

class DECLSPEC_UUID("E2BACA2A-6ABC-4751-81A3-DA19EDF18105")
mwSICARDActX;
#endif
#endif /* __mwSICARDActXLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


