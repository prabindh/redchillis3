/*
* Example .NET application for testing REDCHILLIS3 library in DLL mode.
*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Xml;
using System.IO;

namespace redchillis3_test_dotnet
{
    class Program
    {
        [DllImport("redchillis3mm.dll", CharSet = CharSet.Unicode)]
        static extern unsafe UInt32 REDCHILLIS3_init(
                                    ref Int64 pContext
                                    );
        [DllImport("redchillis3mm.dll", CharSet = CharSet.Unicode)]
        static extern unsafe UInt32 REDCHILLIS3_set_proxy(
                                    Int64 pContext,
                                    byte val1, byte val2, byte val3, byte val4
                                    );

        [DllImport("redchillis3mm.dll", CharSet = CharSet.Unicode)]
        static extern unsafe UInt32 REDCHILLIS3_list_bucket_contents(
                                    Int64 pContext,
                                    String prefix,
                                    String marker,
                                    String bucketName,
                                    byte* responseBuff,
                                    UInt32 responseBufLen,
                                    ref UInt32 pResponseLen
                                    );
        [DllImport("redchillis3mm.dll", CharSet = CharSet.Unicode)]
        static extern unsafe UInt32 REDCHILLIS3_get_object(
                                          Int64 pContext,
                                          String getObjectName,
                                          String bucketName,
                                          Int32 responseTuple,//should be of sizeof(HEADER_TUPLE)
                                          byte* pDataBuff,
                                            UInt32 dataBuffLen,
                                          ref UInt32 pContentLen
                                        );
        [DllImport("redchillis3mm.dll", CharSet = CharSet.Unicode)]
        static extern unsafe UInt32 REDCHILLIS3_put_object
                                            (
                                            Int64 pContext,
                                            String putObjectName,
                                            String bucketName,
                                            UInt32 contentLen,
                                            byte* contentBuff,
                                            String contentType,
                                            Int32 pHeaderTuple, //pass optional headers through this
                                            byte* responseBuff,
                                            Int32 responseBufLen
                                            );
        [DllImport("redchillis3mm.dll", CharSet = CharSet.Unicode)]
        static extern unsafe UInt32 REDCHILLIS3_uninit(
                                    Int64 pContext
                                    );

        static unsafe int get_bytearray_len(byte* name, uint nameLen)
        {
            int len = 0;
            for(uint i = 0;i < nameLen;i ++)
            {
                if (name[i] == '\0')
                    break;
                len ++;
            }
            return len;
        }

        static unsafe void Main(string[] args)
        {
            Int64 predchillis3 = 0;
            UInt32 err = 0;
            byte[] responseBuff = new byte[1000];
            byte* pDataBuff = null;
            UInt32 contentLen = 0, headerLen = 0;
            byte[] contentBuff = new byte[11];
            char[] headerData = null;

            String bucketName = ""; //bucketname here
            String testObjectName = "/someobject"; //objectname starts with /
            String testObjectName1 = "/someobject";
            String testObjectName2 = "/someobject";

            err = REDCHILLIS3_init(
                    ref predchillis3
                    );
            if (err > 0)
                goto UNINIT;
            err = REDCHILLIS3_set_proxy(
                    predchillis3,
                    199,
                    33,
                    184,
                    231
                    );
            if (err > 0)
                goto UNINIT;
#if true

            //list objects test case
            {
                err = REDCHILLIS3_list_bucket_contents(
                                predchillis3,
                                testObjectName,
                                "",
                                bucketName,
                                pDataBuff, //get the pointer in pDataBuff
                                0, //pass 0 to get actual len
                                ref contentLen
                                );
                if (err != 2)
                    goto UNINIT;
                byte[] recvdContent = new byte[contentLen];
                fixed (byte* pContentBuff = &recvdContent[0])
                {
                    UInt32 gotContentLen = contentLen;
                    err = REDCHILLIS3_list_bucket_contents(
                                    predchillis3,
                                    testObjectName,
                                    "",
                                    bucketName,
                                    pContentBuff,
                                    gotContentLen,
                                    ref contentLen
                                    );
                    if (err > 0)
                        goto UNINIT;
                    //check out the XML response we received
                    try
                    {
                        MemoryStream responseStream =
                            new MemoryStream(recvdContent,
                                                0,
                                                get_bytearray_len(pContentBuff, contentLen)
                                                );
                        XmlDocument responseDoc = new XmlDocument();
                        responseDoc.Load(responseStream);
                        responseStream.Close();
                    }
                    catch (Exception ex) { };
                }//fixed
            }
#endif
#if false
	        //get test case
            {
                err = REDCHILLIS3_get_object(
                                predchillis3,
                                "/1::temp1::Drive_Letter_Access::webdrive_transcript.txt",
                                bucketName,
                                0,
                                pDataBuff, //get the pointer in pDataBuff
                                0, //pass 0 to get actual len
                                ref contentLen
                                );
                if (err != 2)
                    goto UNINIT;
                byte[] recvdContent = new byte[contentLen];
                fixed (byte* pContentBuff = &recvdContent[0])
                {
                    UInt32 gotContentLen = contentLen;
                    err = REDCHILLIS3_get_object(
                                predchillis3,
                                testObjectName1,
                                bucketName,
                                0,
                                pContentBuff, //get the pointer in pDataBuff
                                gotContentLen, //pass 0 to get actual len
                                ref contentLen
                                );
                    if (err > 0)
                        goto UNINIT;
                }//fixed
            }
#endif
#if false
	        //put test case
	        contentLen = (uint)contentBuff.Length;
            for (UInt32 i = 0; i < contentLen; i++)
                contentBuff[i] = (byte)i;
            fixed (byte* pContentBuff = &contentBuff[0], pResponseBuff = &responseBuff[0])
            {
                err = REDCHILLIS3_put_object(
                                    predchillis3,
                                    testObjectName2,
                                    bucketName,
                                    contentLen,
                                    pContentBuff, //send the data in this buffer
                                    "text/plain",
                                    0,
                                    pResponseBuff,
                                    responseBuff.Length
                                    );
            }
	        if(err > 0)
		        goto UNINIT;

#endif //
        UNINIT:
            REDCHILLIS3_uninit(predchillis3);
        }
    }
}
