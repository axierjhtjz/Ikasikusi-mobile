//
//  SettingScene.h
//  Ikasitz
//
//  Created by Iker Mendilibar Fernandez on 23/01/13.
//
//

#ifndef __Ikasitz__SettingScene__
#define __Ikasitz__SettingScene__

#include "cocos2d.h"

USING_NS_CC;

typedef enum
{
    kPopScene,
    kReplaScene
} ReturnType;

class PreferenceScene : public CCScene
{
public:
	PreferenceScene();
	~PreferenceScene();
    
	virtual bool init();
	CREATE_FUNC(PreferenceScene);
    
    CC_SYNTHESIZE(ReturnType, m_ReturnType, SceneReturnType);
    
private:
    bool sound;
    float volume;
    
    void backClicked(CCObject *sender);
    void sliderCallback(CCObject *sender);
    void soundCallback(CCObject *sender);
    void infoClicked(CCObject* pSender);
};

#endif /* defined(__Ikasitz__SettingScene__) */
