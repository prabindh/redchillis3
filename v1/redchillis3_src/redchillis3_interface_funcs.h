
#ifndef _REDCHILLIS3_INTERFACE_FUNCS_H
#define _REDCHILLIS3_INTERFACE_FUNCS_H

#ifdef _WIN32
#include "windows.h"
#endif

#ifndef _USRDLL
#define REDCHILLIS3_API
#else
#ifdef REDCHILLIS3_DLL_EXPORTS 
#define REDCHILLIS3_API __declspec(dllexport)
#else
#define REDCHILLIS3_API __declspec(dllimport)
#endif
#endif //_LIB

#define OUT
#define IN

#define HEADER_TUPLES_NUM 20
#define HEADER_TUPLE_KEY_LEN 50
#define HEADER_TUPLE_VALUE_LEN 500
typedef struct _HEADER_TUPLE
{
	char* contentStart;
	char key[HEADER_TUPLES_NUM][HEADER_TUPLE_KEY_LEN]; /*!< Key name, ex "Content-Type" */
	char value[HEADER_TUPLES_NUM][HEADER_TUPLE_VALUE_LEN]; /*!< Value, ex "text/plain" */ 
}HEADER_TUPLE;

extern "C" {

/**
This function initialises the REDCHILLIS3 module. Returns a token that needs to be
be passed to later REDCHILLIS3 calls. This function does NOT use the network.
\param pContent - Pointer, that will be returned.
\param accessKey - String containing the access key provided by Amazon
\param secretKey - String containing teh secret key provided by Amazon
\return 0 on success, non-zero on failure
*/
UINT32 REDCHILLIS3_API redchillis3_user_init(
						IN void **pContext,
						IN char* accessKey, 
						IN char* secretKey 
					   )
;

/**
This function sets the proxy in the aaa.bbb.ccc.ddd format. If REDCHILLIS3 is unable
to find a route to s3.amazonaws.com, it will try with the provided proxy. This function
needs to be called before calling other REDCHILLIS3 functions that use the network.
\param pContent - Pointer, that was returned by redchillis3_user_init
\param val1 - aaa
\param val2 - bbb
\param val3 - ccc
\param val4 - ddd
\return 0
*/
UINT32 REDCHILLIS3_API redchillis3_user_set_proxy(
								void* pContext,
								  char val1, char val2, char val3, char val4
								  )
;
/**
This function uninitialises the REDCHILLIS3 module.  This function does NOT use the network.
\param pContent - Pointer, that was returned by redchillis3_user_init
\return 0 on success, non-zero on failure
\see redchillis3_user_init
*/
UINT32 REDCHILLIS3_API redchillis3_user_uninit(
							IN void* pContext
							)
;
/**
This function retrieves an object stored previously in S3.  This function uses the network.
\param pContext - Token received earlier from init
\param getObjectName - Name of object to be retrieved. Needs to start with \. Null terminated.
 Cannot be NULL or empty.
\param bucketName - Name of bucket in which the object resides.  Null terminated.
Cannot be NULL or empty.
\param pUnUsed - Key-value tuple structure, which will be filled. NULL can be passed. Currently unused.
\param dataBuff - Pointer to buffer in which data of the object is to be stored. Pass NULL to get 
actual size of data.
\param dataBuffLen - Length of dataBuff in bytes.
\param pContentLen - Pointer to a 32bit variable which will receive actual size of data in bytes.
\return 0 - on success, 2 when successful but NULL dataBuff was passed, other values on failure.
*/
UINT32 REDCHILLIS3_API redchillis3_get_object(
					  IN void* pContext,
					  IN WCHAR* getObjectName,
					  IN WCHAR* bucketName,
					  OUT HEADER_TUPLE* pUnused, //returns additional headers through this
					  IN char* dataBuff,
					  IN UINT32 dataBuffLen, //pass 0 size buf to get data size, then pass full size
					  OUT UINT32* pContentLen
					  )
;
/**
This function puts an object into S3.  This function uses the network.
\param pContext - Token received earlier from init
\param putObjectName - Name of object to be stored. Needs to start with \. Null terminated.
Cannot be NULL or empty.
\param bucketName - Name of bucket in which the object is to reside.  Null terminated.
Cannot be NULL or empty.
\param contentLen - Length of data of object in bytes
\param pContentBuff - Pointer to buffer in which data of the object is stored.
\param pContentType - Null terminated string having content type ex "text/plain"
Cannot be NULL or empty.
\param pUnUsed - Key-value tuple having additional user defined headers. NULL can be passed. Currently unused.
\param pResponseBuff - Pointer to buffer in which the response will be stored.
\param responseBufLen - Length of returned response in bytes.
\return 0 - on success, other values on failure
*/
UINT32 REDCHILLIS3_API redchillis3_put_object(
					IN void* pContext,
					IN WCHAR* putObjectName,
					IN WCHAR* bucketName,
					IN UINT32 contentLen,
					IN OUT char* pContentBuff,
					IN WCHAR* pContentType,
					IN HEADER_TUPLE* pUnused, //pass optional headers through this
					OUT char* pResponseBuff,
					IN int responseBufLen
					)
;
/**
This function creates a bucket in S3.  This function uses the network.
\param pContext - Token received earlier from init
\param bucketName - Name of bucket to be created. Null terminated.
Cannot be NULL or empty.
\param pResponseBuff - Pointer to buffer in which the response will be stored.
\param responseBufLen - Length of returned response in bytes.
\return 0 - on success, other values on failure
*/
UINT32 REDCHILLIS3_API redchillis3_create_bucket(
					void* pContext,
					WCHAR* bucketName,
					OUT char* responseBuff,
					int responseBufLen
					)
;

/**
This function lists contents of a bucket, with specified keys, in S3.  This function uses the network.
\param pContext - Token received earlier from init
\param prefix - Null terminated string containing prefix of objects to be retrieved
Cannot be NULL or empty.
\param marker - Null terminated string containing marker. See AWS S3 documentation for usage.
Cannot be NULL or empty.
\param bucketName - Null terminated string containing naem of bucket to be created.
Cannot be NULL or empty.
\param responseBuff - Pointer to buffer to hold the response.
\param responseBufLen - Length of response buffer in bytes.
\param pResponseLen - Pointer to variable to hold length of actually returned response. NOTE that
this length may be slightly more than the actual length.
The application needs to check for and strip the trailing zeros to get actual data.
\return 0 - on success, other values on failure
*/
UINT32 REDCHILLIS3_API redchillis3_list_bucket_contents(
					void* pContext,
					WCHAR* prefix,
					WCHAR* marker,
					WCHAR* bucketName,
					OUT char* responseBuff,
					UINT32 responseBufLen,
					OUT UINT32* pResponseLen
					)
;
} //extern C
#endif //_REDCHILLIS3_INTERFACE_FUNCS_H

