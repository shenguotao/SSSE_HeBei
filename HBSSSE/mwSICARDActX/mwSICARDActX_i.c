

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jan 19 17:31:08 2017
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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_mwSICARDActXLib,0x9A2AAE9B,0x4EBA,0x4725,0xB6,0xF6,0x84,0xCF,0xF3,0x15,0xDB,0x47);


MIDL_DEFINE_GUID(IID, DIID__DmwSICARDActX,0x3FFE3C52,0xF20E,0x4E61,0x90,0x25,0x2E,0x3C,0x7B,0x5D,0x89,0xBA);


MIDL_DEFINE_GUID(IID, DIID__DmwSICARDActXEvents,0x192ECAEA,0xD223,0x465E,0xB3,0x79,0x39,0xC0,0x8A,0x90,0xFA,0xD3);


MIDL_DEFINE_GUID(CLSID, CLSID_mwSICARDActX,0xE2BACA2A,0x6ABC,0x4751,0x81,0xA3,0xDA,0x19,0xED,0xF1,0x81,0x05);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



