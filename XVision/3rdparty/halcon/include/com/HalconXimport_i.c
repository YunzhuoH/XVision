/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Feb 26 17:53:32 2000
 */
/* Compiler settings for C:\Halcon\source\packages\grayfeat\source\com\HalconXimport.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

#pragma pack(push,8) /* sets the struct member alignment to 8 bytes (default)*/

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#pragma pack(pop)

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IHObjectX = {0x6ebd90c3,0xd219,0x11d2,{0xad,0xe5,0x00,0x00,0xc0,0x0f,0x4e,0xf9}};


const IID IID_IHUntypedObjectX = {0x6ebd90c4,0xd219,0x11d2,{0xad,0xe5,0x00,0x00,0xc0,0x0f,0x4e,0xf9}};


const IID IID_IHandleAccess = {0x6ebd90d2,0xd219,0x11d2,{0xad,0xe5,0x00,0x00,0xc0,0x0f,0x4e,0xf9}};


#ifdef __cplusplus
}
#endif

