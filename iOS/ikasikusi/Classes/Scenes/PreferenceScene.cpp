//
//  SettingScene.cpp
//  Ikasitz
//
//  Created by Iker Mendilibar Fernandez on 23/01/13.
//
//

#include "PreferenceScene.h"
#include "../Helpers/SpriteButton.h"
#include "../Helpers/VisibleRect.h"
#include "SimpleAudioEngine.h"
#include "CCApplication.h"

extern char* getTimeWithFormat(int seconds);

using namespace CocosDenshion;
using namespace cocos2d::extension;


PreferenceScene::~PreferenceScene()
{
    
}

PreferenceScene::PreferenceScene()
{
    sound = true;
}

bool PreferenceScene::init()
{
    CCLayer *layer = CCLayer::create();
    layer->setContentSize(ccp(VisibleRect::right().x, VisibleRect::top().y));
    layer->setPosition( VisibleRect::center() );
    layer->setAnchorPoint(ccp(0.5f, 0.5f));
    layer->ignoreAnchorPointForPosition(false);
    
    CCSprite *pBackground2 = CCSprite::create("fondo_azul.jpg");
    pBackground2->setPosition(VisibleRect::center());
    layer->addChild(pBackground2);
    addChild(layer);
    
    CCSprite *lContainer = CCSprite::create("forma_base_big.png");
    lContainer->setPosition(ccp(VisibleRect::right().x / 2, VisibleRect::top().y / 2));
    layer->addChild(lContainer);
    
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("back.png");
    SpriteButton *pBackButton = SpriteButton::create(pTexture, this, callfuncO_selector(PreferenceScene::backClicked));
    CCPoint bottomLeft = VisibleRect::leftBottom();
    pBackButton->setPosition(ccp(bottomLeft.x + 70, bottomLeft.y + 60));
    addChild(pBackButton);
    
    //Read default value
    CCUserDefault *pUserDefaults = CCUserDefault::sharedUserDefault();
    volume = pUserDefaults->getFloatForKey("volume");
    sound = pUserDefaults->getBoolForKey("sound");
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCLabelTTF *pEzarpenak = CCLabelTTF::create("Ezarpenak", "IndieFlower", 50.0);
    #else
        CCLabelTTF *pEzarpenak = CCLabelTTF::create("Ezarpenak", "fonts/IndieFlower.ttf", 50.0);
    #endif
    pEzarpenak->setPosition(ccp(150, 420));
    pEzarpenak->setColor(ccc3(255, 255, 255));
    //pEzarpenak->setDimensions(CCSizeMake(250, 40));
    pEzarpenak->setHorizontalAlignment(kCCTextAlignmentRight);
    lContainer->addChild(pEzarpenak);
    
    CCSprite *pLinea = CCSprite::create("linea.png");
    pLinea->setPosition(ccp(VisibleRect::center().x + 20, 390));
    lContainer->addChild(pLinea);
    
    //Sound
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCLabelTTF *pSoinuaLabel = CCLabelTTF::create("Soinua", "IndieFlower", 40.0);
    #else
        CCLabelTTF *pSoinuaLabel = CCLabelTTF::create("Soinua", "fonts/IndieFlower.ttf", 40.0);
    #endif
    pSoinuaLabel->setPosition(ccp(120, 320));
    pSoinuaLabel->setColor(ccc3(255, 255, 255));
    //pSoinuaLabel->setDimensions(CCSizeMake(250, 40));
    lContainer->addChild(pSoinuaLabel);
    
    CCMenu *pSoinuaMenu = CCMenu::create();
    CCMenuItemSprite* pMenuOn = CCMenuItemSprite::create(CCSprite::create("check_on.png"), NULL);
    CCMenuItemSprite* pMenuOff = CCMenuItemSprite::create(CCSprite::create("check_off.png"), NULL);
    CCMenuItemToggle* pToggle = CCMenuItemToggle::createWithTarget( this,
                                                                   menu_selector(PreferenceScene::soundCallback),
                                                                   pMenuOn,
                                                                   pMenuOff,
                                                                   NULL );
    pSoinuaMenu->addChild(pToggle);
    pSoinuaMenu->setPosition(ccp(290,320));
    lContainer->addChild(pSoinuaMenu);
    
    if (!sound) {
        pToggle->setSelectedIndex(1);
    }
    
    
    //Volume
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCLabelTTF *pVolumeLabel = CCLabelTTF::create("Bolumena", "IndieFlower", 40.0);
    #else
        CCLabelTTF *pVolumeLabel = CCLabelTTF::create("Bolumena", "fonts/IndieFlower.ttf", 40.0);
    #endif
    pVolumeLabel->setPosition(ccp(120, 250));
    pVolumeLabel->setColor(ccc3(255, 255, 255));
    pVolumeLabel->setHorizontalAlignment(kCCTextAlignmentRight);
    //pVolumeLabel->setDimensions(CCSizeMake(250, 40));
    lContainer->addChild(pVolumeLabel);
    
    CCSprite *pVolOn = CCSprite::create("volume_on.png");
    pVolOn->setPosition(ccp(710,250));
    lContainer->addChild(pVolOn);
    
    
    CCSprite *pVolOff = CCSprite::create("volume_off.png");
    pVolOff->setPosition(ccp(280,250));
    lContainer->addChild(pVolOff);
    
    CCControlSlider *slider = CCControlSlider::create("slider_track.png","slider_track.png", "slider_knob.png");
    slider->setPosition(ccp(490,250));
    //slider->setContentSize(ccp(100,20));
    slider->setMaximumValue(100.0f);
    slider->setValue(volume);
    slider->setMinimumValue(0.0f);
    slider->setEnabled(true);
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(PreferenceScene::sliderCallback), CCControlEventValueChanged);
    lContainer->addChild(slider);

    CCTexture2D *pInfoTexture = CCTextureCache::sharedTextureCache()->addImage("info_box.png");
    SpriteButton *pInfoBox = SpriteButton::create(pInfoTexture ,this, callfuncO_selector(PreferenceScene::infoClicked), 1.0f);
    pInfoBox->setPosition(ccp(120, 200));
    lContainer->addChild(pInfoBox);

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCLabelTTF *pInfoLable = CCLabelTTF::create("info", "IndieFlower", 20.0);
    #else
        CCLabelTTF *pInfoLable = CCLabelTTF::create("info", "fonts/IndieFlower.ttf", 20.0);
    #endif
    pInfoLable->setPosition(ccp(120, 200));
    pInfoLable->setColor(ccc3(3, 72, 140));
    lContainer->addChild(pInfoLable);

    return true;
}

void PreferenceScene::infoClicked(CCObject* pSender)
{
#ifdef __APPLE__
    CCApplication::sharedApplication()->openURL("http://ikastek.net/guri-buruz/");
#endif
#ifdef ANDROID
    CCApplication::sharedApplication()->openURLJNI("http://ikastek.net/guri-buruz/");
#endif
}

void PreferenceScene::soundCallback(CCObject *sender)
{
    CCMenuItemToggle *pToggle = (CCMenuItemToggle*) sender;
    int index = pToggle->getSelectedIndex();
    if (!index) {
        sound = true;
        /*if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
         SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/music.wav", true);*/
    } else {
        sound = false;
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
}

void PreferenceScene::sliderCallback(CCObject *sender)
{
    CCControlSlider *pSlider = (CCControlSlider*) sender;
    
    volume = pSlider->getValue();
    
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

void PreferenceScene::backClicked(CCObject *sender)
{
    //Save preferences
    CCUserDefault *pUserDefaults = CCUserDefault::sharedUserDefault();
    pUserDefaults->setFloatForKey("volume", volume);
    pUserDefaults->setBoolForKey("sound", sound);
    pUserDefaults->flush();
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    
    if (getSceneReturnType() == kPopScene) {
        pDirector->popScene();
    } else {

    }
    
}