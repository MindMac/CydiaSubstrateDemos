#include <android/log.h>
#include "substrate.h"

#define LOG_TAG "CydiaSubstrate-JNI"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

MSConfig(MSFilterExecutable, "/system/bin/app_process")

static jstring (*_getDeviceId)(JNIEnv *jni, jobject _this, ...);

static jstring getDeviceId(JNIEnv *jni, jobject _this){
	//jstring deviceId = _getDeviceId(jni, _this);
	return jni->NewStringUTF("fake-device-id");
}

static void OnGetDeviceId(JNIEnv *jni, jclass wifiinfo, void *data){
	jmethodID method = jni->GetMethodID(wifiinfo, "getDeviceId", "()Ljava/lang/String;");
	LOGI("OnGetDeviceId");
	if(method != NULL){
		LOGI("GetDeviceId");
		MSJavaHookMethod(jni, wifiinfo, method, &getDeviceId, &_getDeviceId);
	}
}

MSInitialize {
    MSJavaHookClassLoad(NULL, "android/telephony/TelephonyManager", &OnGetDeviceId);
}


