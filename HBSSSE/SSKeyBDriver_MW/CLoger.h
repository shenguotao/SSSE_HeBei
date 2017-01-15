/*****************************************************************************************************
 *                           CopyRight(C), 1992-2014,M&W CARD TECH.Co,Ltd.
 * FileName:    CLoger.h
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

#ifndef CLOGER_H_
#define CLOGER_H_
//前置声明
namespace mw
{
    namespace reader
    {
        namespace utility
        {
            class CriticalSectionLock;
        } /* namespace utility */
    } /* namespace reader */
} /* namespace mw */


#define  MWWriteLog(flag, format, ...) CLoger::getInstance()->Log(flag, format, ##__VA_ARGS__)
#if defined _WIN32 || defined __CYGWIN__    //1判断在WINDOWS平台上
#if defined __GNUC__ //1.1 判断是CYGWIN
        //TODO 1.1.1
#ifdef _DEBUG
#define  MWLog(format, ...)  CLoger::getInstance()->Log(format, ##__VA_ARGS__)
#else
#define  MWLog(format, ...)
#endif

#else   //1.2 WINDOWS系统
#if _MSC_VER <= 1200 //1.2.1 VC6.0
        void MWLog(const char *pData, ...);

#else //1.2.2 高版本VS
#ifdef _DEBUG
#define  MWLog(format, ...)  CLoger::getInstance()->Log(format, ##__VA_ARGS__)
#else
#define  MWLog(format, ...)
#endif

#endif  //end 1.2 结束VS版本判断
#endif  //end 1
#else
    #ifdef _DEBUG
        #ifdef __ANDROID__
            #include <android/log.h>  
            #ifndef  LOG_TAG  
                #define  LOG_TAG    "mwcard"  
                #define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)  
                #define  MWLog(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)  
            #endif  
        #else
            #define  MWLog(format, ...)  CLoger::getInstance()->Log(format, ##__VA_ARGS__)
        #endif
        
    #else
    #define  MWLog(format, ...)
    #endif
#endif

namespace mw
{
    namespace reader
    {

        namespace utility
        {
            /**
             * ClassName: mw::reader::utility::CLoger
             * Description:
             * Others:
             * Function List:
             * 1.
             *
             * History:
             * <author> <time> <version> <desc>
             * 申国涛 2014年9月12日 V0.0.1.0 创建
             *
             */
            class CLoger
            {
            public:
                static CLoger* getInstance(); //单例模式
				static CLoger* m_instance; //该变量保存了当前的通信端口管理实例
				CriticalSectionLock *m_cs;
                static bool creatLogDir(string dirName, string &realDirName);   //创建日志目录，返回tre表示成功，false表示失败,返回指定特定系统下目录表示方式
                static int getSystemTime(unsigned int&year, unsigned int&month, unsigned int&day
					, unsigned int&hour, unsigned int&minute, unsigned int&second, unsigned int&milliseconds);
                void Log(const char *pData, ...); // 写日志的方法
                //void Log(const char *fun, int line, const char *pData, ...); // 写日志的方法
                void Log(int flag, const char *pData, ...);
                ~CLoger();
            private:
                CLoger();
                class CGarbo // 它的唯一工作就是在析构函数中删除CSingleton的实例
                {
                public:
                    ~CGarbo();
                };
                static CGarbo Garbo; // 定义一个静态成员，在程序结束时，系统会调用它的析构函数
            };


    }
/* namespace utility */
} /* namespace reader */
} /* namespace mw */

#endif /* CLOGER_H_ */
