//=============================================================================
//              |
// Headerfile   |   common.h
//              |   Header file describing data types
//              |
// Created      |   04.11.2008, by H.-Peter Classen
//              |
// Last Change  |   
//-----------------------------------------------------------------------------

#ifndef __COMMON_H__
// Protect against multiple file inclusion
#define __COMMON_H__


//  declaration of data types using by RoboPro (fischertechnik)

typedef char                CCHAR8;
typedef signed char         CHAR8;
typedef unsigned char       UCHAR8;

typedef unsigned char       BOOL8;      //  Boolean variable (should be TRUE or FALSE)
typedef unsigned short      BOOL16;     //  Boolean variable (should be TRUE or FALSE)
typedef unsigned long       BOOL32;     //  Boolean variable (should be TRUE or FALSE)

typedef signed char         INT8;
typedef signed short        INT16;
typedef signed int          INT32;

typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
#ifndef WIN32
typedef unsigned int       UINT32; //2019-12-8 was long

#define INVALID_SOCKET -1

#endif

#endif
