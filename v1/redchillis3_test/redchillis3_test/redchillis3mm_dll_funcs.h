#ifndef _REDCHILLIS3MM_DLL_FUNCS_H
#define _REDCHILLIS3MM_DLL_FUNCS_H

typedef unsigned int UINT32;

typedef UINT32 (*FN_REDCHILLIS3_USER_INIT)(
						void **pContext,
						char* accessKey, 
						char* secretKey 
					   )
;

typedef UINT32 (*FN_REDCHILLIS3_USER_SET_PROXY)(
								void* pContext,
								  char val1, char val2, char val3, char val4
								  )
;
typedef UINT32 (*FN_REDCHILLIS3_UNINIT)(
							IN void* pContext
							)
;
typedef UINT32 (*FN_REDCHILLIS3_GET_OBJECT)(
					  IN void* pContext,
					  IN WCHAR* getObjectName,
					  IN WCHAR* bucketName,
					  OUT HEADER_TUPLE* pUnused, //returns additional headers through this
					  IN char* dataBuff,
					  IN UINT32 dataBuffLen, //pass 0 size buf to get data size, then pass full size
					  OUT UINT32* pContentLen
					  )
;
typedef UINT32 (*FN_REDCHILLIS3_PUT_OBJECT)(
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
typedef UINT32 (*FN_REDCHILLIS3_CREATE_BUCKET)(
					void* pContext,
					WCHAR* bucketName,
					OUT char* responseBuff,
					int responseBufLen
					)
;
typedef UINT32 (*FN_REDCHILLIS3_LIST_BUCKET_CONTENTS)(
					void* pContext,
					WCHAR* prefix,
					WCHAR* marker,
					WCHAR* bucketName,
					OUT char* responseBuff,
					UINT32 responseBufLen,
					OUT UINT32* pResponseLen
					)
;
#endif //_REDREDCHILLIS3MM_DLL_FUNCS_H