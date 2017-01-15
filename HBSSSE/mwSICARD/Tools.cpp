/*****************************************************************************************************
 *                           CopyRight(C), 1992-2014,M&W CARD TECH.Co,Ltd.
 * FileName:    Tools.cpp
 * Author:      申国涛       Version:   V0.0.0.1     Date:    2014年9月10日
 * Description:  
 * Others:      
 * Function List:   
 *   1. ....
 *
 * History:
 *  <author> <time> <version > <description  > 
 *  申国涛	2014年9月10日	V0.0.1.0	创建
 *
 *****************************************************************************************************/
#include <ios>
#include <iomanip>
#include <cctype>
#include <string>
using std::string;
using std::wstring;
using std::basic_string;

#include <vector>
using std::vector;

#include <sstream>
using std::stringstream;



#if defined _WIN32 || defined __CYGWIN__    //1. windows 平台或者windows/cygwin平台

#ifdef __GNUC__     //1.1 CYGWIN平台
    #include <unistd.h>
    #include "iconv.h"
    #include <stdint.h>
#else           //1.2 windows 平台
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
        #include <cstdint>

    #endif                  //END 1.2.1 
#endif                  //END 1.2.1

#else       //2. LINUX/UNIX平台
    #include <unistd.h>
    #include "iconv.h"
    #include <stdint.h>
#endif  //END 1



#include "Tools.h"
namespace mw
{
    namespace reader
    {
        namespace utility
        {

            int Tools::sleep( int millisecond )
            {
#if defined _WIN32 || defined __CYGWIN__    //1. windows 平台或者windows/cygwin平台
#ifdef __GNUC__     //1.1 CYGWIN平台
                usleep(millisecond * 1000);
#else           //1.2 windows 平台
                Sleep(millisecond);
#endif                  //END 1.2.1

#else       //2. LINUX/UNIX平台
                usleep(millisecond * 1000);
               
#endif  //END 1
                return 0;
            }
            
            bool Tools::isHexString(string data)
            {
                uint32_t length = data.size();
                for ( unsigned int j = 0; j < length; j++)
                {
                    if (!isxdigit(data[j]) )
                    {
                        return false;
                    }
                }
                return true;
            }

            bool Tools::isAnString(string data)
            {
                uint32_t length = data.size();
                for ( unsigned int j = 0; j < length; j++)
                {
                    if (!isdigit(data[j]) )
                    {
                        return false;
                    }
                }
                return true;
            }

            string Tools::formatMoney(string money)
            {
                string strResult;
                string data;
                string strFen;
                string cFlagMoney = ".";
                unsigned int i = 0;
                unsigned int j = 0;
                //1.先分隔成2部分,如果没有.则只有一部分
                vector<string> vecMoney = tokenizer(money, cFlagMoney);
                

                //2.检查合法性
                for ( i = 0; i < vecMoney.size(); i++)
                {
                    for (j = 0; j < vecMoney[i].size(); j++)
                    {
                        if (!isdigit(vecMoney[i][j]) )
                        {
                            return strResult;
                        }
                    }
                }
                //3. 获得'.'之前的数据
                string::size_type pos = vecMoney[0].find_first_not_of('0');
                if (pos != string::npos)
                {
                    data.assign(vecMoney[0].begin() + pos, vecMoney[0].end());
                }

                if (2 == vecMoney.size())
                {
                    //判断小数点后面有几位
                    strFen = vecMoney[1];
                    if (strFen.length() >= 2)
                    {
                        data += strFen.substr(0, 2);
                    }
                    else if (strFen.length() == 1)
                    {
                        data += strFen + "0";
                    }
                    else
                    {
                        data += "00";
                    }
                    
                }
                if (data.length() > 10)
                {
                    return strResult;
                }
                uint64_t uiMoney= 0;
                stringstream ssMoney(data);
                ssMoney >>uiMoney;
                if (uiMoney > 0xffffffff)
                {
                    return strResult;
                }
                //3.拼装到一起
                
                

                
                

                strResult = data;
                return strResult;
            }

            unsigned int Tools::getMoney(string money)
            {
                unsigned int iFen = 0;
                stringstream fen(money);
                fen >> iFen;
                return iFen;
            }

            string Tools::getMoney(unsigned int money)
            {
                unsigned int iYuan = money / 100;
                unsigned int iFen = money % 100;
                stringstream yuan;
                yuan << iYuan;
                stringstream fen;
                fen.fill('0');
                fen << std::setw(2) << std::setiosflags(std::ios::right) << iFen;
                string result = yuan.str() + "." + fen.str();
                return result;
            }

            vector<string> Tools::tokenizer(string str, string pattern)
            {
                std::string::size_type pos;
                std::vector<std::string> result;
                //str += pattern; //扩展字符串以方便操作
                uint32_t size = str.size();

                for (uint32_t i = 0; i < size; i++)
                {
                    pos = str.find(pattern, i);
                    if (pos < size)
                    {
                        std::string s = str.substr(i, pos - i);
                        result.push_back(s );
                        i = pos + pattern.size() - 1;
                    }
                    else
                    {   
                        //如果字符串最后没有分隔符则一直取到尾部作为最后一个字段
                        string s = string(str.begin() +i, str.end());
                        result.push_back(s );
                        break;
                    }
                }
                return result;
            }

            string Tools::trimSpace(string data)
            {
                vector<char> tmp;
                for (unsigned int i = 0; i < data.length(); i++)
                {
                    if (0 == isspace((unsigned char) (data[i]))) //不是空白字符
                    {
                        tmp.push_back(data[i]);
                    }
                }
                return string(tmp.begin(), tmp.end());
            }

            string Tools::trimSpace(int direction, string data)
            {
                string::size_type pos = 0;
                string strResult;
                if (direction)
                {
                    //反方向
                    pos = data.find_last_not_of(' ');
                    if (pos != string::npos)
                    {
                        strResult.assign(data.begin(), data.begin() + (pos + 1));
                    }
                    else
                    {
                        strResult = data;
                    }

                }
                else
                {
                    pos = data.find_first_not_of(' ');
                    if (pos != string::npos)
                    {
                        strResult.assign(data.begin() + pos, data.end());
                    }
                    else
                    {
                        strResult = data;
                    }
                }
                return strResult;
            }

            string Tools::getUpper(const string &strData)
            {
                string strSourceData;
                string::const_iterator it = strData.begin();
                for (; it != strData.end(); it++)
                {
                    strSourceData += (char) std::toupper(*it);
                }
                return strSourceData;
            }

            uint64_t Tools::byteArrayToInt(vector<unsigned char> data)
            {
                uint64_t value = 0;
                int length = data.size();
                for (int i = 0; i < length; i++)
                {
                    int shift = (length - 1 - i) * 8;
                    value += (data[i] & 0x000000FF) << shift; // 往高位游
                }
                return value;
            }

            string Tools::num2str(uint64_t data)
            {
                stringstream ss;
                ss << data;
                return ss.str();
            }

            int64_t Tools::hexString2Int( string strHex )
            {
                string hex;
                if (0 == strncmp("0x", strHex.c_str(),2) && 0 == strncmp("0X", strHex.c_str(),2))
                {

                    hex.assign(strHex.begin() + 2, strHex.end());
                }
                else
                {
                    hex = strHex;
                }
                if (hex.size()%2)
                {
                    hex = "0" + hex;
                }
                vector<uint8_t> vecHex;
                hexString2bytes(hex, vecHex);
                return byteArrayToInt(vecHex);
            }

            vector<unsigned char> Tools::shortToByteArray(unsigned short data)
            {
                vector<unsigned char> result(2, 0);

                result[0] = (unsigned char) ((data >> 8) & 0xFF);
                result[1] = (unsigned char) (data & 0xFF);
                return result;
            }

            vector<unsigned char> Tools::intToByteArray(unsigned int data)
            {
                vector<unsigned char> result(4, 0);
                result[0] = (unsigned char) ((data >> 24) & 0xFF);
                // 必须把我们要的值弄到最低位去，有人说不移位这样做也可以， result[0] = (byte)(i & 0xFF000000);
                // ，这样虽然把第一个字节取出来了，但是若直接转换为byte类型，会超出byte的界限，出现error。再提下数//之间转换的原则（不管两种类型的字节大小是否一样，原则是不改变值，内存内容可能会变，比如int转为//float肯定会变）所以此时的int转为byte会越界，只有int的前三个字节都为0的时候转byte才不会越界。虽//然
                // result[0] = (byte)(i & 0xFF000000); 这样不行，但是我们可以这样 result[0] =
                // (byte)((i & //0xFF000000) >>24);
                result[1] = (unsigned char) ((data >> 16) & 0xFF);
                result[2] = (unsigned char) ((data >> 8) & 0xFF);
                result[3] = (unsigned char) (data & 0xFF);
                return result;
            }

            uint32_t Tools::bytes2HexString(const vector<uint8_t>&src, string &dst)
            {
                uint32_t srcLen = src.size();
                if (srcLen == 0)
                {
                    return 0;
                }
                vector<int8_t> dstAsc(srcLen *2, 0x00);
                unsigned int index = 0;
                unsigned char hLowbit, hHighbit;
                for (index = 0; index < srcLen * 2; index += 2)
                {
                    hLowbit = src[index / 2] & 0x0f;
                    hHighbit = src[index / 2] / 16;
                    dstAsc[index] = hHighbit >= 10 ? (hHighbit + '7') : (hHighbit + '0');
                    dstAsc[index + 1] = hLowbit >= 10 ? (hLowbit + '7') : (hLowbit + '0');

                }
                dst.assign(dstAsc.begin(), dstAsc.end());
                return srcLen * 2;

            }

            uint32_t Tools::hexString2bytes(const string& src, vector<uint8_t>& dst)
            {
                vector<uint8_t> tmp;
                uint32_t srcLen = src.size();
                //计算总长度
                int totalLen = srcLen;
                //遍历字符串，遇到第一个合法字符则转化，遇到第二个合法字符则合并，并记录2进制数据长度
                int flag = 0; //位置标记，如果遇到了第二个合法字符则数据长度+1

                char aLowbit = '0', aHighbit = '0';
                char hconval = '0', lconval = '0';
                for (int i = 0; i < totalLen; i++)
                {
                    if (isxdigit((unsigned char)src[i])) //是合法字符
                    {
                        flag += 1;
                        if (flag % 2)
                        {
                            aHighbit = tolower(src[i]);
                        }
                        else
                        {
                            aLowbit = tolower(src[i]);
                            //转化数据
                            hconval = ((aHighbit >= 'a') && (aHighbit <= 'f')) ? 'W' : '0';
                            lconval = ((aLowbit >= 'a') && (aLowbit <= 'f')) ? 'W' : '0';
                            tmp.push_back((aHighbit - hconval) * 16 + (aLowbit - lconval));
                        }
                    }
                }
                dst = tmp;
                return dst.size();

            }

            unsigned char Tools::bcc(const vector<unsigned char> &data)
            {
                unsigned char temp = 0;
                unsigned int i = 0;
                for (i = 0; i < data.size(); ++i)
                {
                    temp = temp ^ data[i];
                }

                return (temp);
            }

			unsigned char Tools::crc(const vector<unsigned char> &data)
			{
				unsigned char CrcTable[16] = {0x1a, 0x2f, 0x45, 0x64, 
											  0x8e, 0x9a, 0xa1, 0xb5,
											  0xf6, 0x7e, 0xf9, 0xbf, 
											  0x91, 0x34, 0x67, 0x80};
				unsigned char bccval;
				unsigned char temp=0;
				
				int bcc1,bcc2;

				bccval=bcc(data);

				bcc1=0x0f & bccval;
				bcc2=0x0f & (bccval>>4);

				temp=CrcTable[bcc1]+ CrcTable[bcc2];

				return temp;
			}

            string Tools::s2gbk(const string& s)
            {
                string strGBK;
                //TODO 如果是windows平台则参数为GBK编码，不用转换，如果是其他系统，则参数规定是UTF-8格式，要转化为GBK编码，
#if defined _WIN32 || defined __CYGWIN__    //1. windows 平台或者windows/cygwin平台
#ifdef __GNUC__     //1.1 CYGWIN平台

#else           //1.2 windows 平台
                strGBK = s;
#endif                  //END 1.2.1

#else       //2. LINUX/UNIX平台

                //2.1 多字节数据
                const char *psrc = s.c_str();
                size_t srcLen = s.size(); //源字符串占用的字节数

                //2.2 分配宽字符缓冲区
                vector<char> vecDst(s.size() * 2+ 1, 0x00);  //GBK 一个字最多占2个字节
                const char *pDst = &vecDst[0];
                size_t dstLen = s.size();

                //2.3 打开iconv
                iconv_t env;
                env = iconv_open("GBK", "UTF-8");
                if (env != (iconv_t)(-1))
                {
                    size_t result = iconv(env, (char**) &psrc, (size_t*) &srcLen, (char**) &pDst,
                            (size_t*) &dstLen);
                    if (result != (size_t)(-1))
                    {
                        strGBK = string( &vecDst[0]);
                    }
                    iconv_close(env);
                }
#endif  //END 1

                return strGBK;
            }
            
            //string 转化为 wstring
            wstring Tools::s2ws(const string& s)
            {
#if defined _WIN32 || defined __CYGWIN__    //1. windows 平台或者windows/cygwin平台
#ifdef __GNUC__     //1.1 CYGWIN平台

#else           //1.2 windows 平台
                const char* _Source = s.c_str();
                size_t _Dsize = MultiByteToWideChar(CP_ACP, 0, _Source, -1, NULL, 0);
                wchar_t *_Dest = new wchar_t[_Dsize];
                MultiByteToWideChar(CP_ACP, 0, _Source, -1, _Dest, _Dsize);
                wstring result = _Dest;
                delete []_Dest;
                return result;

#endif                  //END 1.2.1

#else       //2. LINUX/UNIX平台
                std::wstring val = L"";

                //2.1 多字节数据
                const char *psrc = s.c_str();
                size_t srcLen = s.size(); //源字符串占用的字节数

                //2.2 分配宽字符缓冲区
                vector<wchar_t> vecDst((s.size() + 1) * sizeof(wchar_t), 0x00);
                char *pDst = (char *)&vecDst[0];
                size_t dstLen = s.size() * sizeof(wchar_t);

                //2.3 打开iconv
                iconv_t env;
                env = iconv_open("UTF-32LE", "UTF-8");
                if (env != (iconv_t)(-1))
                {
                    size_t result = iconv(env, (char**) &psrc, (size_t*) &srcLen, (char**) &pDst,
                            (size_t*) &dstLen);
                    if (result != (size_t)(-1))
                    {
                        val = wstring((wchar_t *) &vecDst[0]);
                    }
                    iconv_close(env);
                }

                return val;
#endif  //END 1

            }

            //wstring 转化为string
            string Tools::ws2s(const wstring& inputws)
            {
#if defined _WIN32 || defined __CYGWIN__    //1. windows 平台或者windows/cygwin平台
#ifdef __GNUC__     //1.1 CYGWIN平台

#else           //1.2 windows 平台
                const wchar_t* _Source = inputws.c_str();
                size_t _Dsize = WideCharToMultiByte(CP_ACP, 0, _Source, -1, NULL, 0, NULL, NULL);
                char *_Dest = new char[_Dsize];
                WideCharToMultiByte(CP_ACP, 0, _Source, -1, _Dest, _Dsize, NULL, NULL);
                string result = _Dest;
                delete[] _Dest;
                return result;
#endif                  //END 1.2.1

#else       //2. LINUX/UNIX平台

                string val;

                //2.1 宽字节数据
                const wchar_t *psrc = inputws.c_str();
                size_t srcLen = inputws.size() * sizeof(wchar_t); //源字符串占用的字节数

                //2.2 分配多字节缓冲区
                vector<char> vecDst(inputws.size() * 6 + 1, 0x00); //UTF-8 一个字最多占6个字节
                char *pDst = &vecDst[0];
                size_t dstLen = inputws.size() * 6;

                //2.3 打开iconv
                iconv_t env;
                env = iconv_open("UTF-8", "UTF-32LE");
                //
                if (env != (iconv_t)(-1))
                {
                    size_t result = iconv(env, (char**) &psrc, (size_t*) &srcLen, (char**) &pDst,
                            (size_t*) &dstLen);
                    if (result != (size_t)(-1))
                    {
                        val = string((char *) &vecDst[0]);
                    }
                    iconv_close(env);
                }

                return val;
#endif  //END 1

            }

            //string 转化为 wstring
            basic_string<uint16_t> Tools::UTF82UTF16LE(const string& s)
            {
#if defined _WIN32 || defined __CYGWIN__    //1. windows 平台或者windows/cygwin平台
#ifdef __GNUC__     //1.1 CYGWIN平台

#else           //1.2 windows 平台
                const char* _Source = s.c_str();
                size_t _Dsize = MultiByteToWideChar(CP_ACP, 0, _Source, -1, NULL, 0);
                wchar_t *_Dest = new wchar_t[_Dsize];
                MultiByteToWideChar(CP_ACP, 0, _Source, -1, _Dest, _Dsize);
                basic_string<uint16_t> result = (basic_string<uint16_t>::value_type *)_Dest;
                delete []_Dest;
                return result;

#endif                  //END 1.2.1

#else       //2. LINUX/UNIX平台
                basic_string<uint16_t> val ;

                //2.1 多字节数据
                const char *psrc = s.c_str();
                size_t srcLen = s.size(); //源字符串占用的字节数

                //2.2 分配宽字符缓冲区
                vector<wchar_t> vecDst((s.size() + 1) * sizeof(wchar_t), 0x00);
                char *pDst = (char *)&vecDst[0];
                size_t dstLen = s.size() * sizeof(wchar_t);

                //2.3 打开iconv
                iconv_t env;
                env = iconv_open("UTF-16LE", "UTF-8");
                if (env != (iconv_t)(-1))
                {
                    size_t result = iconv(env, (char**) &psrc, (size_t*) &srcLen, (char**) &pDst,
                        (size_t*) &dstLen);
                    if (result != (size_t)(-1))
                    {
                        val = basic_string<uint16_t>((uint16_t *) &vecDst[0]);
                    }
                    iconv_close(env);
                }

                return val;
#endif  //END 1

            }

            //wstring 转化为string
            string Tools::UTF16LE2UTF8(basic_string<uint16_t> &inputws)
            {
#if defined _WIN32 || defined __CYGWIN__    //1. windows 平台或者windows/cygwin平台
#ifdef __GNUC__     //1.1 CYGWIN平台

#else           //1.2 windows 平台
                const wchar_t* _Source = (const wchar_t*)inputws.c_str();
                size_t _Dsize = WideCharToMultiByte(CP_ACP, 0, _Source, -1, NULL, 0, NULL, NULL);
                char *_Dest = new char[_Dsize];
                WideCharToMultiByte(CP_ACP, 0, _Source, -1, _Dest, _Dsize, NULL, NULL);
                string result = _Dest;
                delete[] _Dest;
                return result;
#endif                  //END 1.2.1

#else       //2. LINUX/UNIX平台

                string val;

                //2.1 宽字节数据
               const uint16_t *psrc = inputws.c_str();
                size_t srcLen = inputws.size() * sizeof(basic_string<uint16_t>::value_type); //源字符串占用的字节数

                //2.2 分配多字节缓冲区
                vector<char> vecDst(inputws.size() * 6 + 1, 0x00); //UTF-8 一个字最多占6个字节
                char *pDst = &vecDst[0];
                size_t dstLen = inputws.size() * 6;

                //2.3 打开iconv
                iconv_t env;
                env = iconv_open("UTF-8", "UTF-16LE");
                //
                if (env != (iconv_t)(-1))
                {
                    size_t result = iconv(env, (char**) &psrc, (size_t*) &srcLen, (char**) &pDst,
                        (size_t*) &dstLen);
                    if (result != (size_t)(-1))
                    {
                        val = string((char *) &vecDst[0]);
                    }
                    iconv_close(env);
                }

                return val;
#endif  //END 1

            }

        } /* namespace utility */
    } /* namespace reader */
} /* namespace mw */
