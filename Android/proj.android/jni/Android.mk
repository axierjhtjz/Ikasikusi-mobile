LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_CFLAGS += -DCOCOS2D_DEBUG=1

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/Helpers/CCScrollLayer.cpp \
../../Classes/Helpers/CCSlider.cpp \
../../Classes/Helpers/DataFileHelper.cpp \
../../Classes/Helpers/ListViewLayer.cpp \
../../Classes/Helpers/SpriteButton.cpp \
../../Classes/Helpers/VisibleRect.cpp \
../../Classes/Layers/DifficultyLayer.cpp \
../../Classes/Layers/GameLayer.cpp \
../../Classes/Scenes/DifficultyScene.cpp \
../../Classes/Scenes/GameScene.cpp \
../../Classes/Scenes/LoadingScene.cpp \
../../Classes/Scenes/LogoScene.cpp \
../../Classes/Scenes/PreferenceScene.cpp \
../../Classes/Scenes/ThemeSelectionScene.cpp \
../../Classes//Helpers/StatsHelper.cpp \
../../Classes/Scenes/WinScene.cpp \
../../Classes/Scenes/LoseScene.cpp \
../../Classes/MobHawk/MobHawkAPI.cpp \
../../Classes//json/cJSON.c 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
		    $(LOCAL_PATH)/../../Classes//Helpers \
		    $(LOCAL_PATH)/../../Classes//json \
			/Applications/cocos2d-x-2.1.5/cocos2dx/cocoa \
/Applications/cocos2d-x-2.1.5/cocos2dx/touch_dispatcher \
/Applications/cocos2d-x-2.1.5/cocos2dx/support/zip_support
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static cocos_curl_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
