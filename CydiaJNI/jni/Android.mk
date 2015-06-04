LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)
LOCAL_MODULE:= substrate-dvm
LOCAL_SRC_FILES := libsubstrate-dvm.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := deviceid.cy
LOCAL_SRC_FILES := deviceid.cpp
LOCAL_LDLIBS:= -L$(LOCAL_PATH) -lsubstrate-dvm -L$(SYSROOT)/usr/lib -llog
include $(BUILD_SHARED_LIBRARY)

