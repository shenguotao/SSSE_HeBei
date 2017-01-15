/*****************************************************************************************************
 *                           CopyRight(C), 1992-2014,M&W CARD TECH.Co,Ltd.
 * FileName:    CriticalSectionLock.cpp
 * Author:      申国涛       Version:   V0.0.0.1     Date:    2014年9月9日
 * Description:  
 * Others:      
 * Function List:   
 *   1. ....
 *
 * History:
 *  <author> <time> <version > <description  > 
 *  申国涛	2014年9月9日	V0.0.1.0	创建
 *
 *****************************************************************************************************/
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#include <pthread.h>
#else
#include <Windows.h>
#endif
#else
#include <pthread.h>
#endif


#include "CriticalSectionLock.h"

namespace mw
{
    namespace reader
    {
        namespace utility
        {
            class CriticalSectionLockImpl
            {
            public:
                CriticalSectionLockImpl()
                {
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
                    pthread_mutex_init(&m_cs, NULL);
#else
                    InitializeCriticalSection(&m_cs);
#endif
#else
                    pthread_mutex_init(&m_cs, NULL);
#endif
                }
                ~CriticalSectionLockImpl()
                {
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
                    pthread_mutex_destroy(&m_cs);
#else
                    DeleteCriticalSection(&m_cs);
#endif
#else
                    pthread_mutex_destroy(&m_cs);
#endif
                }
                void enter(void)
                {
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
                    pthread_mutex_lock(&m_cs);
#else
                    EnterCriticalSection(&m_cs);
#endif
#else
                    pthread_mutex_lock(&m_cs);
#endif
                }
                void quit(void)
                {
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
                    pthread_mutex_unlock(&m_cs);
#else
                    LeaveCriticalSection(&m_cs);
#endif
#else
                    pthread_mutex_unlock(&m_cs);
#endif
                }
            private:

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
                pthread_mutex_t m_cs;
#else
                CRITICAL_SECTION m_cs;
#endif
#else
                pthread_mutex_t m_cs;
#endif
            };
            CriticalSectionLock::CriticalSectionLock()
            {
                // TODO Auto-generated constructor stub
                m_impl = new CriticalSectionLockImpl();
            }

            CriticalSectionLock::~CriticalSectionLock()
            {
                // TODO Auto-generated destructor stub
                delete m_impl;
            }

            void CriticalSectionLock::enter(void)
            {
                m_impl->enter();
            }

            void CriticalSectionLock::quit(void)
            {
                m_impl->quit();
            }

        } /* namespace utility */
    } /* namespace reader */
} /* namespace mw */
