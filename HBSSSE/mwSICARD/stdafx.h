// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>



// TODO: 在此处引用程序需要的其他头文件
//2. ====================包含头文件=============================
//包含头文件
#if defined _WIN32 || defined __CYGWIN__    //1. windows 平台或者windows/cygwin平台
#ifdef __GNUC__     //1.1 CYGWIN平台
#ifdef __x86_64__
#define  HANDLE int64_t
#elif __i386__
#define  HANDLE int32_t
#endif
#define INVALID_HANDLE_VALUE (HANDLE)(-1)
#define STDCALL
#else           //1.2 windows 平台
#include <Windows.h>
#define STDCALL __stdcall
#if (_MSC_VER<=1200)    //1.2.1 MSVC 6.0编译器
typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;    
#else                   //1.2.2 MSVC 6.0以上编译器
#include <memory>
#include <cstdint>
#include <regex>
using std::shared_ptr;
#endif                  //END 1.2.1 

#endif          //END 1.1

#else       //2. LINUX/UNIX平台
#include "dlfcn.h" /* 包含动态链接功能接口文件 */
#ifdef __x86_64__
#define  HANDLE int64_t
#else
#define  HANDLE int
#endif
#define INVALID_HANDLE_VALUE (HANDLE)(-1)
#define STDCALL


#endif  //END 1


#include <list>
#include <vector>
#include <string>
#include <functional>
#include <utility>
using std::list;
using std::string;
using std::basic_string;
//using std::u16string;
using std::wstring;
using std::vector;
using std::copy;

#include <iostream>
#include <iterator>
#include <sstream>
using std::stringstream;