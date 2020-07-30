/**
* This file contains wrappers for creating a DLL around the REDCHILLIS3 core functions.
* This is example code. The keys should be obfuscated or stored otherwise securely
* in these wrapper functions. Though this is more secure than storing it in a 
* managed executable, it is still vulnerable. Future versions of REDCHILLIS3
* will show examples of secure storage of keys.
* This DLL can be imported into other runtimes like .NET. Please see 
* redchillis3_test_dotnet for an example of how this DLL can be used in 
* a .NET application.
* For description of the core functions, please see redchillis3_interface_funcs.h
* Other usage scenarios of the core DLL like using in a c++ application is covered in 
* the redchillis3_test project.
*/

#include "redchillis3_interface_funcs.h" //REDCHILLIS3 API
#include "redchillis3mm_dll_funcs.h" //DLL helper file

#define REDCHILLIS3MM_API __declspec(dllexport)

//Example keys - Sign into amazon S3 account to get these keys. You need a credit card.
#define REDCHILLIS3_ACCESS_KEY ""
#define REDCHILLIS3_SECRET_KEY ""

extern "C" {

UINT32 REDCHILLIS3MM_API REDCHILLIS3_init(
									__int64* pContext
									)
{
	UINT32 err;
	HMODULE hDll;	
	hDll = LoadLibrary(L"redchillis3_dll.dll");
	if(!hDll)
		return 1;
	FN_REDCHILLIS3_USER_INIT FN_redchillis3_user_init;
	FN_redchillis3_user_init = 
		(FN_REDCHILLIS3_USER_INIT)GetProcAddress(hDll,(LPCSTR)"redchillis3_user_init");
	if(!FN_redchillis3_user_init)
		return 1;

	//maintain these keys in the DLL without passing to the managed framework
	char* accessKey = REDCHILLIS3_ACCESS_KEY;
	char* secretKey = REDCHILLIS3_SECRET_KEY;
	err = FN_redchillis3_user_init((void**)pContext, accessKey, secretKey);
	
	FreeLibrary(hDll);
	
	return err;
}

UINT32 REDCHILLIS3MM_API REDCHILLIS3_set_proxy(
									__int64 pContext,
									char val1,
									char val2,
									char val3,
									char val4
									)
{
	UINT32 err;
	HMODULE hDll;
	hDll = LoadLibrary(L"redchillis3_dll.dll");
	if(!hDll)
		return 1;

	FN_REDCHILLIS3_USER_SET_PROXY FN_redchillis3_set_proxy;
	FN_redchillis3_set_proxy = 
		(FN_REDCHILLIS3_USER_SET_PROXY)GetProcAddress(hDll,"redchillis3_user_set_proxy");
	if(!FN_redchillis3_set_proxy)
		return 1;

	err = FN_redchillis3_set_proxy(
						(void*)pContext, 
						val1, val2, val3, val4
						);

	FreeLibrary(hDll);

	return err;
}



UINT32 REDCHILLIS3MM_API REDCHILLIS3_get_object(
					  __int64 pContext,
					  WCHAR* getObjectName,
					  WCHAR* bucketName,
					  OUT char* responseTuple,//should be of sizeof(HEADER_TUPLE)
					  IN void* pDataBuff, //pass null to get size
					  IN UINT32 dataBuffLen, //pass 0 to get size
					  OUT UINT32* pContentLen
					)
{
	UINT32 err;

	HMODULE hDll;
	hDll = LoadLibrary(L"redchillis3_dll.dll");
	if(!hDll)
		return 1;
	FN_REDCHILLIS3_GET_OBJECT FN_redchillis3_get_object;
	FN_redchillis3_get_object = 
		(FN_REDCHILLIS3_GET_OBJECT)GetProcAddress(hDll,"redchillis3_get_object");
	if(!FN_redchillis3_get_object)
		return 1;

	err = FN_redchillis3_get_object(
					(void*)pContext,
					getObjectName,
					bucketName,
					(HEADER_TUPLE*)responseTuple,
					(char*)pDataBuff,
					dataBuffLen,
					pContentLen
					);

	FreeLibrary(hDll);

	return err;
}

UINT32 REDCHILLIS3MM_API REDCHILLIS3_put_object
					(
					__int64 pContext,
					WCHAR* putObjectName,
					WCHAR* bucketName,
					UINT32 contentLen,
					char* contentBuff,
					WCHAR* contentType,
					IN HEADER_TUPLE* pHeaderTuple, //pass optional headers through this
					OUT char* responseBuff,
					int responseBufLen
					)
{
	UINT32 err;
	HMODULE hDll;
	hDll = LoadLibrary(L"redchillis3_dll.dll");
	if(!hDll)
		return 1;
	FN_REDCHILLIS3_PUT_OBJECT FN_redchillis3_put_object;
	FN_redchillis3_put_object = 
		(FN_REDCHILLIS3_PUT_OBJECT)GetProcAddress(hDll,"redchillis3_put_object");
	if(!FN_redchillis3_put_object)
		return 1;


	err = FN_redchillis3_put_object(
						(void*)pContext,
						putObjectName,
						bucketName,
						contentLen, 
						contentBuff,
						contentType,
						pHeaderTuple,
						responseBuff,
						responseBufLen
						);
	
	FreeLibrary(hDll);

	return err;
}

UINT32 REDCHILLIS3MM_API REDCHILLIS3_list_bucket_contents(
					                __int64 pContext,
					                WCHAR* prefix,
					                WCHAR* marker,
					                WCHAR* bucketName,
					                char* responseBuff,
					                UINT32 responseBufLen,
					                UINT32* pResponseLen
					                )
{
	UINT32 err;
	HMODULE hDll;
	hDll = LoadLibrary(L"redchillis3_dll.dll");
	if(!hDll)
		return 1;

	FN_REDCHILLIS3_LIST_BUCKET_CONTENTS FN_redchillis3_list_bucket_contents;
	FN_redchillis3_list_bucket_contents = 
		(FN_REDCHILLIS3_LIST_BUCKET_CONTENTS)GetProcAddress(hDll,"redchillis3_list_bucket_contents");
	if(!FN_redchillis3_list_bucket_contents)
		return 1;


	err = FN_redchillis3_list_bucket_contents(
					(void*)pContext,
					prefix,
					marker,
					bucketName,
					responseBuff,
					responseBufLen,
					pResponseLen
					);
	FreeLibrary(hDll);

	return err;
}

UINT32 REDCHILLIS3MM_API REDCHILLIS3_uninit(
									__int64 pContext
									)
{
	HMODULE hDll;
	hDll = LoadLibrary(L"redchillis3_dll.dll");
	if(!hDll)
		return 1;
	FN_REDCHILLIS3_UNINIT FN_redchillis3_user_uninit;
	FN_redchillis3_user_uninit = 
		(FN_REDCHILLIS3_UNINIT)GetProcAddress(hDll,"redchillis3_user_uninit");
	if(!FN_redchillis3_user_uninit)
		return 1;

	FN_redchillis3_user_uninit((void*)pContext);

	FreeLibrary(hDll);

	return 0;
}

/*
Placeholder for other future functionality
*/

} //extern C
