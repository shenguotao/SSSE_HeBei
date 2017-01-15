/*****************************************************************************************************
 *                           CopyRight(C), 1992-2014,M&W CARD TECH.Co,Ltd.
 * FileName:    CriticalSectionLock.h
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

#ifndef CRITICALSECTIONLOCK_H_
#define CRITICALSECTIONLOCK_H_

namespace mw
{
    namespace reader
    {
        namespace utility
        {
            class CriticalSectionLockImpl;
            /**
             * ClassName:        mw::reader::utility::CriticalSectionLock
             * Description:      
             * Others:           
             * Function List:    
             *	1. 
             *	
             * History:
             *  <author>        <time>        <version>        <desc> 
             *  申国涛        2014年9月9日        V0.0.1.0         创建
             *
             */
            class CriticalSectionLock
            {
            public:
                CriticalSectionLock();
                ~CriticalSectionLock();
                void enter(void);
                void quit(void);
            protected:
            private:
                CriticalSectionLockImpl * m_impl;
            };

        } /* namespace utility */
    } /* namespace reader */
} /* namespace mw */

#endif /* CRITICALSECTIONLOCK_H_ */
