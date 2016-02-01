LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libmegjb

LOCAL_SRC_FILES := prebuilt/libmegjb.so

include $(PREBUILT_SHARED_LIBRARY)

LOCAL_SHARED_LIBRARIES := libmegjb


include $(CLEAR_VARS)
LOCAL_MODULE := libzimon

LOCAL_SRC_FILES := prebuilt/libzimon.so

include $(PREBUILT_SHARED_LIBRARY)

LOCAL_SHARED_LIBRARIES := libzimon





$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp





define walk
$(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef


ALLFILES = $(call walk, $(LOCAL_PATH)/../../Classes)
FILE_LIST := hellocpp/main.cpp
FILE_LIST += hellocpp/payproxy.cpp

FILE_LIST += $(filter %.cpp, $(ALLFILES))

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes 
																


LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
