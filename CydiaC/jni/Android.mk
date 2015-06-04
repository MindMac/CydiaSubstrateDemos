LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)
LOCAL_MODULE:= substrate
LOCAL_SRC_FILES := libsubstrate.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := dvm.cy
LOCAL_SRC_FILES := dvm.cpp
LOCAL_LDLIBS:= -L$(LOCAL_PATH) -lsubstrate -L$(SYSROOT)/usr/lib -llog
include $(BUILD_SHARED_LIBRARY)



