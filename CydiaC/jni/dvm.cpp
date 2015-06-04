#include <android/log.h>
#include <sys/types.h>
#include <unistd.h>
#include "substrate.h"

#define LOG_TAG "CydiaSubstrate-C"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

MSConfig(MSFilterLibrary, "/system/lib/libdvm.so")

int (*oldDexOpen)(const void * addr,int len, void ** dvmdex);

int myDexOpen(const void * addr,int len,void ** dvmdex)
{
	LOGI("Call myDexOpen: %d", getpid());

    return oldDexOpen(addr, len, dvmdex);
}

MSInitialize {
	LOGI("Substrate initialized.");

	MSImageRef image = MSGetImageByName("/system/lib/libdvm.so");
	if (image != NULL){
		void * dexOpen = MSFindSymbol(image, "_Z21dvmDexFileOpenPartialPKviPP6DvmDex");
		if(dexOpen==NULL){
			LOGD("Error find _Z21dvmDexFileOpenPartialPKviPP6DvmDex");
		}else{
			MSHookFunction(dexOpen, (void*)&myDexOpen, (void **)&oldDexOpen);
		}
	}else{
		LOGD("ERROR FIND LIBDVM");
	}
}



