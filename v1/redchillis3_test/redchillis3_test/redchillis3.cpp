
#include "windows.h"
#include "redchillis3_interface_funcs.h"
#include "redchillis3mm_dll_funcs.h"

#define REDCHILLIS3_BUCKET_NAME L"" //place bucketname
#define REDCHILLIS3_ACCESS_KEY "" //place access key
#define REDCHILLIS3_SECRET_KEY "" //place secret key

#define REDCHILLIS3_SAMPLE_KEY L"/somekey" //keys and objects start with /
#define REDCHILLIS3_SAMPLE_OBJECT1 L"/someobject"
#define REDCHILLIS3_SAMPLE_OBJECT2 L"/someobject1"
#define REDCHILLIS3_SAMPLE_MARKER L""


extern "C" {

void main()
{
	void* pChillis3;
	UINT32 err = 0;
	char responseBuff[1000];
	char* pDataBuff = 0; 
	UINT32 contentLen = 0;
	int headerLen = 0;
	char contentBuff[1000];
	HEADER_TUPLE headerTuple; 

	HMODULE hDll = NULL;
	hDll = LoadLibrary(L"redchillis3_dll.dll");
	if(!hDll)
		return;

	FN_REDCHILLIS3_USER_INIT FN_redchillis3_user_init;
	FN_redchillis3_user_init = 
		(FN_REDCHILLIS3_USER_INIT)GetProcAddress(hDll,"redchillis3_user_init");
	if(!FN_redchillis3_user_init)
		return;
	memset(&headerTuple,0,sizeof(HEADER_TUPLE)); 
	err = FN_redchillis3_user_init(
			&pChillis3,
			REDCHILLIS3_ACCESS_KEY,
			REDCHILLIS3_SECRET_KEY
			);
	if(err)
		goto UNINIT;

	FN_REDCHILLIS3_USER_SET_PROXY FN_redchillis3_set_proxy;
	FN_redchillis3_set_proxy = 
		(FN_REDCHILLIS3_USER_SET_PROXY)GetProcAddress(hDll,"redchillis3_user_set_proxy");
	if(!FN_redchillis3_set_proxy)
		return;

	err = FN_redchillis3_set_proxy(
					pChillis3,
					199,
					33,
					184,
					231
					);
	if(err)
		goto UNINIT;
#if 1
	FN_REDCHILLIS3_LIST_BUCKET_CONTENTS FN_redchillis3_list_bucket_contents;
	FN_redchillis3_list_bucket_contents = 
		(FN_REDCHILLIS3_LIST_BUCKET_CONTENTS)GetProcAddress(hDll,"redchillis3_list_bucket_contents");
	if(!FN_redchillis3_list_bucket_contents)
		return;

	//listbucket test case
	err = FN_redchillis3_list_bucket_contents(
					pChillis3,
					REDCHILLIS3_SAMPLE_KEY,
					REDCHILLIS3_SAMPLE_MARKER,
					REDCHILLIS3_BUCKET_NAME,
					NULL,
					0,
					&contentLen
					);
	//with 0 size, we will get contentLen and return 2
	if(err != 2)
		goto UNINIT;
	if(contentLen > 0) //no point reading
	{
		pDataBuff = (char*)malloc(contentLen);
		if(pDataBuff == NULL)
			goto UNINIT;
		err = FN_redchillis3_list_bucket_contents(
						pChillis3,
						REDCHILLIS3_SAMPLE_KEY,
						REDCHILLIS3_SAMPLE_MARKER,
						REDCHILLIS3_BUCKET_NAME,
						pDataBuff,
						contentLen,
						&contentLen
						);
		if(err)
			goto UNINIT;
	}
#elif 0
	FN_REDCHILLIS3_GET_OBJECT FN_redchillis3_get_object;
	FN_redchillis3_get_object = 
		(FN_REDCHILLIS3_GET_OBJECT)GetProcAddress(hDll,"redchillis3_get_object");
	if(!FN_redchillis3_get_object)
		return;

	//get object test case
	err = FN_redchillis3_get_object(
					pChillis3,
					REDCHILLIS3_SAMPLE_OBJECT1,
					REDCHILLIS3_BUCKET_NAME,
					&headerTuple,
					NULL,
					0,
					&contentLen
					);
	//with 0 size, we will get contentLen and return 2
	if(err != 2)
		goto UNINIT;
	if(contentLen > 0) //no point reading
	{
		pDataBuff = (char*)malloc(contentLen);
		if(pDataBuff == NULL)
			goto UNINIT;
		err = FN_redchillis3_get_object(
						pChillis3,
						REDCHILLIS3_SAMPLE_OBJECT1,
						REDCHILLIS3_BUCKET_NAME,
						&headerTuple,
						pDataBuff,
						contentLen,
						&contentLen
						);
		if(err)
			goto UNINIT;
	}
#elif 0
	FN_REDCHILLIS3_PUT_OBJECT FN_redchillis3_put_object;
	FN_redchillis3_put_object = 
		(FN_REDCHILLIS3_PUT_OBJECT)GetProcAddress(hDll,"redchillis3_put_object");
	if(!FN_redchillis3_put_object)
		return;

	//put object test case
	strcpy(contentBuff,"0123456789"); 
	contentLen = strlen(contentBuff);
	memset(&headerTuple,0,sizeof(HEADER_TUPLE));
	err = FN_redchillis3_put_object(
						pChillis3,
						REDCHILLIS3_SAMPLE_OBJECT2,
						REDCHILLIS3_BUCKET_NAME,
						contentLen, 
						contentBuff,
						L"text/plain",
						&headerTuple,
						responseBuff,
						sizeof(responseBuff)
   						);
	if(err)
		goto UNINIT;
#endif

UNINIT:
	FN_REDCHILLIS3_UNINIT FN_redchillis3_user_uninit;
	FN_redchillis3_user_uninit = 
		(FN_REDCHILLIS3_UNINIT)GetProcAddress(hDll,"redchillis3_user_uninit");
	if(!FN_redchillis3_user_uninit)
		return;
	FN_redchillis3_user_uninit(pChillis3);

	if(pDataBuff)
		free(pDataBuff);
	if(hDll)
		FreeLibrary(hDll);

}

}//extern C