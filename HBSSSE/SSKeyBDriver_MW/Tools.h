/*****************************************************************************************************
 *                           CopyRight(C), 1992-2014,M&W CARD TECH.Co,Ltd.
 * FileName:    Tools.h
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

#ifndef TOOLS_H_
#define TOOLS_H_

namespace mw
{
    namespace reader
    {
        namespace utility
        {

            /**
             * ClassName:        mw::reader::utility::Tools
             * Description:      
             * Others:           
             * Function List:    
             *	1. 
             *	
             * History:
             *  <author>        <time>        <version>        <desc> 
             *  申国涛        2014年9月10日        V0.0.1.0         创建
             *
             */
            class Tools
            {
            public:
                static int sleep(int millisecond);  //休眠指定毫秒数
                static bool isHexString(string data);
                static bool isAnString(string data);
                
                /**
                 *   将字符串格式的带小数点的金额转化为以分为单位的无小数点的金额
                 *   例："100.02" 转化为"10002"分
                 *   如果返回为空则表示数据不合法
                 */
                static string formatMoney(string money);

                static unsigned int getMoney(string money);
                /**
                 *   将以分为单位的整数金额转化为带小数点的以元为单位的金额
                 *   例："10002"分 转化为"100.02"元
                 */
                static string getMoney(unsigned int money);

                /************************************************************************/
                /* 分隔字符串                                                           */
                /************************************************************************/
                static vector<string> tokenizer(string str, string pattern);

                /**
                * trimSpace(string data)  去除所有的空白字符 
                */
                static string trimSpace(string data);

                /**
                * 去除空白字符      
                */
                static string trimSpace(int direction, string data);


                /**
                * 将16进制字符串转化为大写
                */
                static string getUpper(const string &strData);

                /**
                 * 将byte数组中从指定位置开始的4个字节转化为uint64_t类型
                 *
                 * @param b
                 *            要转化的数组
                 * @param offset
                 *            要转化的数据在b中的其实位置，第一个字节下标为0.
                 * @return byte
                 */
                static uint64_t byteArrayToInt(vector<uint8_t> data);

                static string num2str(uint64_t data);
                static int64_t hexString2Int(string strHex);
                static vector<uint8_t> shortToByteArray(unsigned short data);

                static vector<uint8_t> intToByteArray(uint32_t data);

                /**
                 * Function:     bytes2HexString
                 * Description:  将byte数组转化为2个16进制数字:0123456789abcdefABCDEF。
                 * 例如：输入数据为0X3a，则转化后的数据为0x33,0x41,即字符串"3A"
                 * Input:    src: 要被转换的数据
                 * Output:   dst: 保存转换后的16进制ASCII字符串
                 * Return:   转换后的字符串长度，为0表示转化失败
                 * Others:
                 */
                static uint32_t bytes2HexString(const vector<uint8_t>&src, string &dst);

                /**
                 * Function:     hexString2bytes
                 * Description:  将16进制字符串转化为byte数组。
                 * 例如：输入数据为"32"，则转化后的数据为0x32
                 * Input:    src: 要被转换的16进制ASCII字符串
                 * Output:   dst: 保存转换后的byte数组。
                 * Return:   转换后的字节长度，为0表示转化失败
                 * Others:   函数具有较强的容错性，它将忽略16进制字符串中的所有非法字符
                 */
                static uint32_t hexString2bytes(const string& src, vector<uint8_t>& dst);

                static uint8_t bcc(const vector<uint8_t> &data);

				static uint8_t crc(const vector<uint8_t> &data);

                static string s2gbk(const string& s);

                //string 转化为 wstring
                static wstring s2ws(const string& s);

                //wstring 转化为string
                static string ws2s(const wstring& inputws);

                static basic_string<uint16_t> UTF82UTF16LE(const string& s);

                static string  UTF16LE2UTF8(basic_string<uint16_t> &inputws);

            };

        } /* namespace utility */
    } /* namespace reader */
} /* namespace mw */

#endif /* TOOLS_H_ */
