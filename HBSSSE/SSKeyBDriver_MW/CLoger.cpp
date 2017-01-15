/*****************************************************************************************************
 *                           CopyRight(C), 1992-2014,M&W CARD TECH.Co,Ltd.
 * FileName:    CLoger.cpp
 * Author:      申国涛       Version:   V0.0.0.1     Date:    2014年9月12日
 * Description:  
 * Others:      
 * Function List:   
 *   1. ....
 *
 * History:
 *  <author> <time> <version > <description  > 
 *  申国涛	2014年9月12日	V0.0.1.0	创建
 *
 *****************************************************************************************************/
//1. STD标准头文件
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <ios>
#include <iomanip>
#include <string>
using std::string;

#include <sstream>
using std::stringstream;

//0. 系统兼容头文件
#if defined _WIN32 || defined __CYGWIN__
    #ifdef __GNUC__

    #else
            #include <Windows.h>
            #include <sys/stat.h>
            #include <direct.h> 
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
    #endif
#else
    #include <stdint.h>
    #include <unistd.h>
    #include <sys/time.h>
    #include <sys/stat.h>
    #include <sys/types.h>

#endif



//2. 自定义头文件
#include "CriticalSectionLock.h"
#include "CLoger.h"
using namespace mw::reader::utility;

static string g_strFileName = "mwcard";
static string g_strDirName = "log";
static string g_strFileExt = ".txt";

//==========VC6 定义日志函数====================
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#else
    #if (_MSC_VER<=1200)
        void MWLog(const char *pData, ...)
        {
            #ifdef _DEBUG
            CLoger::m_cs->enter();
            //1. 创建文件夹
            string strDir;
            if(!CLoger::creatLogDir("log", strDir))
            {
                CLoger::m_cs->quit();
                return ;
            }
            //2. 获取日志文件名称(用时间来创建，每半个小时一个文件)
            uint32_t year = 0;
            uint32_t month = 0;
            uint32_t day = 0;
            uint32_t hour = 0;
            uint32_t minute = 0;
            uint32_t second = 0;
            uint32_t milliseconds = 0;
            int st = CLoger::getSystemTime(year, month, day, hour, minute, second, milliseconds);
            if (st != 0)
            {
                CLoger::m_cs->quit();
                return ;/* code */
            }
            int iMinutes = 0;
            if (minute >= 30)
            {
                iMinutes = 30;
            }

            stringstream ssFormat;
            ssFormat << std::setfill('0') 
                <<std::setw(4)  << year << "-"
                <<std::setw(2) << month << "-"
                <<std::setw(2) << day << "-"
                <<std::setw(2) << hour << "-"
                <<std::setw(2) << iMinutes;
            string strFileName = strDir + g_strFileName + ssFormat.str() + g_strFileExt;    
            FILE *pFlog = fopen(strFileName.c_str(), "ab+");
            if (NULL == pFlog)
            {
                CLoger::m_cs->quit();
                return;
            }
            //3. 获取当前记录所在的时间写日志
            string strDate;
            stringstream ssFormatData;
            ssFormatData << std::setfill('0') << "["
                <<std::setw(4) << year << "-"
                <<std::setw(2) << month << "-"
                <<std::setw(2) << day << "-"
                <<std::setw(2) << hour << ":"
                <<std::setw(2) << minute << ":"
                <<std::setw(2) << second << "."
                <<std::setw(2) << milliseconds
                << "]";
            strDate = ssFormatData.str();
            //4. 写日志
            strDate += string(pData) + string("\r\n");
            va_list ap;
            va_start(ap, pData);
            vfprintf(pFlog, strDate.c_str(), ap);
            va_end(ap);


            //5. 关闭设备
            fclose(pFlog);
            CLoger::m_cs->quit();
            #else
            #endif
        }
    #else
    #endif

#endif
#else

#endif



namespace mw
{
    namespace reader
    {
        namespace utility
        {
            CLoger::CGarbo CLoger::Garbo;
            CLoger::CGarbo::~CGarbo()
            {

                if (CLoger::m_instance)
                {
                    delete CLoger::m_instance;
                }
            }
            /* 饿汉模式：即无论是否调用该类的实例，在程序开始时就会产生一个该类的实例


             * ，并在以后仅返回此实例。由静态初始化实例保证其线程安全性，WHY？因为静态实例


             * 初始化在程序开始时进入主函数之前就由主线程以单线程方式完成了初始化，不必担心


             * 多线程问题。故在性能需求较高时，应使用这种模式，避免频繁的锁争夺。 */
            CLoger* CLoger::m_instance = new CLoger();
            CLoger::CLoger()
            {
                // TODO Auto-generated constructor stub
                m_cs = new CriticalSectionLock();
            }
			CLoger::~CLoger()
            {
                // TODO Auto-generated destructor stub
                if (m_cs)
                {
                    delete m_cs;
                }
                
            }
            CLoger* CLoger::getInstance()
            {
                //饿汉模式
                return m_instance;
            }
            bool CLoger::creatLogDir(string dirName, string &realDirName)   //创建日志目录，返回tre表示成功，false表示失败
            {
                bool isExist = false;
                int st = 0;
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
    //TODO 1
#else
                struct _stat fileStat;
                if ((_stat(dirName.c_str(), &fileStat) == 0) && (fileStat.st_mode & _S_IFDIR))
                {
                    isExist = true;
                    realDirName = dirName + "\\";
                }
                else
                {
                    st = _mkdir(dirName.c_str());
                    if (st == 0)
                    {
                        isExist = true;
                        realDirName = dirName + "\\";
                    }
                }
#endif
#else
                struct stat fileStat;
                if ((stat(dirName.c_str(), &fileStat) == 0) && S_ISDIR(fileStat.st_mode))
                {
                    isExist = true;
                    realDirName = dirName + "/";
                }
                else
                {
                    st = mkdir(dirName.c_str(), 0755);
                    if (st == 0)
                    {
                        isExist = true;
                        realDirName = dirName + "/";
                    }
                }
#endif
                return isExist;
            }
            int CLoger::getSystemTime(uint32_t&year , uint32_t&month , uint32_t&day
                , uint32_t&hour, uint32_t&minute, uint32_t&second, uint32_t&milliseconds)
            {
                int st = 0;
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
                //TODO 1
#else
                SYSTEMTIME sys;
                GetLocalTime( &sys );
                year = sys.wYear;
                month = sys.wMonth;
                day = sys.wDay;
                hour = sys.wHour;
                minute = sys.wMinute;
                second = sys.wSecond;
                milliseconds = sys.wMilliseconds;
#endif
#else
                struct timeval tv;
                struct timezone tz;
                gettimeofday(&tv, &tz); //获取毫秒值
                time_t timep;
                struct tm *p;
                time(&timep);
                p = localtime(&timep); /*取得当地时间*/
                year = p->tm_year + 1900;
                month = p->tm_mon + 1;
                day = p->tm_mday;
                hour = p->tm_hour;
                minute = p->tm_min;
                second = p->tm_sec;
                milliseconds = tv.tv_usec/1000;
#endif
                return st;
            }


            void CLoger::Log(const char* pData, ...)
            {
                int st  = 0;
                m_cs->enter();
                //1. 创建文件夹
                string strDir;
                //if(!creatLogDir("log", strDir))
                //{
                //    m_cs->quit();
                //    return ;
                //}
                while (true)
                {
                    st = creatLogDir("log", strDir);
                    if (st != 0)
                    {
                        break;
                    }
                }
                //2. 获取日志文件名称(用时间来创建，每半个小时一个文件)
                uint32_t year = 0;
                uint32_t month = 0;
                uint32_t day = 0;
                uint32_t hour = 0;
                uint32_t minute = 0;
                uint32_t second = 0;
                uint32_t milliseconds = 0;
                

                while (true)
                {
                    st = getSystemTime(year, month, day, hour, minute, second, milliseconds);
                    if (st == 0)
                    {
                        break;
                    }
                }


                int iMinutes = 0;
                if (minute >= 30)
                {
                    iMinutes = 30;
                }

                stringstream ssFormat;
                ssFormat << std::setfill('0')
                    <<std::setw(4)  << year << "-"
                    <<std::setw(2) << month << "-"
                    <<std::setw(2) << day << "-"
                    <<std::setw(2) << hour << "-"
                    <<std::setw(2) << iMinutes;
                string strFileName = strDir + g_strFileName + ssFormat.str() + g_strFileExt;    
                FILE *pFlog = NULL;
                while (true)
                {
                    pFlog = fopen(strFileName.c_str(), "ab+");
                    if (NULL != pFlog)
                    {
                        break;
                    }
                }
                /*FILE *pFlog = fopen(strFileName.c_str(), "ab+");
                if (NULL == pFlog)
                {
                    m_cs->quit();
                    return;
                }*/
                //3. 获取当前记录所在的时间写日志
                string strDate;
                stringstream ssFormatData;
                ssFormatData << std::setfill('0') << "["
                    <<std::setw(4) << year << "-"
                    <<std::setw(2) << month << "-"
                    <<std::setw(2) << day << "-"
                    <<std::setw(2) << hour << ":"
                    <<std::setw(2) << minute << ":"
                    <<std::setw(2) << second << "."
                    <<std::setw(2) << milliseconds
                    << "]";
                strDate = ssFormatData.str();
                //4. 写日志
                strDate += string(pData) + string("\r\n");
                va_list ap;
                va_start(ap, pData);
                vfprintf(pFlog, strDate.c_str(), ap);
                va_end(ap);

                st = fflush(pFlog);
                while (true)
                {
                    if (0 == st)
                    {
                        break;
                    }
                }
                //5. 关闭设备
                fclose(pFlog);
                m_cs->quit();
            }
            /*
            void CLoger::Log(const char* fun, int line, const char* pData, ...)
            {
                m_cs->enter();
                //1. 创建文件夹
                string strDir;
                if(!creatLogDir("log", strDir))
                {
                    m_cs->quit();
                    return ;
                }
                //2. 获取日志文件名称(用时间来创建，每半个小时一个文件)
                uint32_t year = 0;
                uint32_t month = 0;
                uint32_t day = 0;
                uint32_t hour = 0;
                uint32_t minute = 0;
                uint32_t second = 0;
                uint32_t milliseconds = 0;
                int st = getSystemTime(year, month, day, hour, minute, second, milliseconds);
                if (st != 0)
                {
                    m_cs->quit();
                    return ;
                }
                int iMinutes = 0;
                if (minute >= 30)
                {
                    iMinutes = 30;
                }

                stringstream ssFormat;
                ssFormat << std::setfill('0')
                    <<std::setw(4)  << year << "-"
                    <<std::setw(2) << month << "-"
                    <<std::setw(2) << day << "-"
                    <<std::setw(2) << hour << "-"
                    <<std::setw(2) << iMinutes;
                string strFileName = strDir + g_strFileName + ssFormat.str() + g_strFileExt;    
                FILE *pFlog = fopen(strFileName.c_str(), "ab+");
                if (NULL == pFlog)
                {
                    m_cs->quit();
                    return;
                }
                //3. 获取当前记录所在的时间写日志
                string strDate;
                stringstream ssFormatData;
                ssFormatData << std::setfill('0') << "["
                    <<std::setw(4) << year << "-"
                    <<std::setw(2) << month << "-"
                    <<std::setw(2) << day << "-"
                    <<std::setw(2) << hour << ":"
                    <<std::setw(2) << minute << ":"
                    <<std::setw(2) << second << "."
                    <<std::setw(2) << milliseconds
                    << "]";
                strDate = ssFormatData.str();
                //4. 写日志
                strDate += string(pData) + string("\r\n");
                va_list ap;
                va_start(ap, pData);
                vfprintf(pFlog, strDate.c_str(), ap);
                va_end(ap);


                //5. 关闭设备
                fclose(pFlog);
                m_cs->quit();
            }
            */

            

            void CLoger::Log(int flag, const char *pData, ...)
            {
                if (flag )
                {
                    m_cs->enter();
                    //1. 创建文件夹
                    string strDir;
                    if(!creatLogDir("log", strDir))
                    {
                        m_cs->quit();
                        return ;
                    }
                    //2. 获取日志文件名称(用时间来创建，每半个小时一个文件)
                    uint32_t year = 0;
                    uint32_t month = 0;
                    uint32_t day = 0;
                    uint32_t hour = 0;
                    uint32_t minute = 0;
                    uint32_t second = 0;
                    uint32_t milliseconds = 0;
                    int st = getSystemTime(year, month, day, hour, minute, second, milliseconds);
                    if (st != 0)
                    {
                        m_cs->quit();
                        return ;/* code */
                    }
                    int iMinutes = 0;
                    if (minute >= 30)
                    {
                        iMinutes = 30;
                    }

                    stringstream ssFormat;
                    ssFormat << std::setfill('0')
                        <<std::setw(4)  << year << "-"
                        <<std::setw(2) << month << "-"
                        <<std::setw(2) << day << "-"
                        <<std::setw(2) << hour << "-"
                        <<std::setw(2) << iMinutes;
                    string strFileName = strDir + g_strFileName + ssFormat.str() + g_strFileExt;    
                    FILE *pFlog = fopen(strFileName.c_str(), "ab+");
                    if (NULL == pFlog)
                    {
                        m_cs->quit();
                        return;
                    }
                    //3. 获取当前记录所在的时间写日志
                    string strDate;
                    stringstream ssFormatData;
                    ssFormatData << std::setfill('0') << "["
                        <<std::setw(4) << year << "-"
                        <<std::setw(2) << month << "-"
                        <<std::setw(2) << day << "-"
                        <<std::setw(2) << hour << ":"
                        <<std::setw(2) << minute << ":"
                        <<std::setw(2) << second << "."
                        <<std::setw(2) << milliseconds
                        << "]";
                    strDate = ssFormatData.str();
                    //4. 写日志
                    strDate += string(pData) + string("\r\n");
                    va_list ap;
                    va_start(ap, pData);
                    vfprintf(pFlog, strDate.c_str(), ap);
                    va_end(ap);


                    //5. 关闭设备
                    fclose(pFlog);
                    m_cs->quit();
                }
                else
                {
#ifdef _DEBUG
                    m_cs->enter();
                    //1. 创建文件夹
                    string strDir;
                    if(!creatLogDir("log", strDir))
                    {
                        m_cs->quit();
                        return ;
                    }
                    //2. 获取日志文件名称(用时间来创建，每半个小时一个文件)
                    uint32_t year = 0;
                    uint32_t month = 0;
                    uint32_t day = 0;
                    uint32_t hour = 0;
                    uint32_t minute = 0;
                    uint32_t second = 0;
                    uint32_t milliseconds = 0;
                    int st = getSystemTime(year, month, day, hour, minute, second, milliseconds);
                    if (st != 0)
                    {
                        m_cs->quit();
                        return ;/* code */
                    }
                    int iMinutes = 0;
                    if (minute >= 30)
                    {
                        iMinutes = 30;
                    }

                    stringstream ssFormat;
                    ssFormat << std::setfill('0')
                        <<std::setw(4)  << year << "-"
                        <<std::setw(2) << month << "-"
                        <<std::setw(2) << day << "-"
                        <<std::setw(2) << hour << "-"
                        <<std::setw(2) << iMinutes;
                    string strFileName = strDir + g_strFileName + ssFormat.str() + g_strFileExt;    
                    FILE *pFlog = fopen(strFileName.c_str(), "ab+");
                    if (NULL == pFlog)
                    {
                        m_cs->quit();
                        return;
                    }
                    //3. 获取当前记录所在的时间写日志
                    string strDate;
                    stringstream ssFormatData;
                    ssFormatData << std::setfill('0') << "["
                        <<std::setw(4) << year << "-"
                        <<std::setw(2) << month << "-"
                        <<std::setw(2) << day << "-"
                        <<std::setw(2) << hour << ":"
                        <<std::setw(2) << minute << ":"
                        <<std::setw(2) << second << "."
                        <<std::setw(2) << milliseconds
                        << "]";
                    strDate = ssFormatData.str();
                    //4. 写日志
                    strDate += string(pData) + string("\r\n");
                    va_list ap;
                    va_start(ap, pData);
                    vfprintf(pFlog, strDate.c_str(), ap);
                    va_end(ap);


                    //5. 关闭设备
                    fclose(pFlog);
                    m_cs->quit();
#endif // _DEBUG
                }

            }

        } /* namespace utility */
    } /* namespace reader */
} /* namespace mw */
