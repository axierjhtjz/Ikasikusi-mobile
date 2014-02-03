//
//  ikasikusiAppDelegate.cpp
//  ikasikusi
//
//  Created by Asier Fernandez on 23/09/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Scenes/LogoScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/ThemeSelectionScene.h"
#include "Scenes/PreferenceScene.h"
#include "Scenes/DifficultyScene.h"
#include "Scenes/LoadingScene.h"
#include "Scenes/WinScene.h"
#include "AppMacros.h"
#include <vector>
#include <string>

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    

    
    pDirector->setOpenGLView(pEGLView);
    
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
    
	CCSize frameSize = pEGLView->getFrameSize();
    
    vector<string> searchPath;
    
	if (frameSize.height > mediumResource.size.height) {
        searchPath.push_back(largeResource.directory);
        searchPath.push_back(largeGameAnswers.directory);
        searchPath.push_back(largeGameTopics.directory);
        pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	} else {
        searchPath.push_back(mediumResource.directory);
        searchPath.push_back(mediumGameAnswers.directory);
        searchPath.push_back(mediumGameTopics.directory);
        pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
    }
    
    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(searchPath);
    
    pDirector->setDisplayStats(false);
    
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *pScene = LogoScene::create();
    //CCScene *pScene = LoadingScene::create();
    //CCScene *pScene = ThemeSelectionScene::create();
    //CCScene *pScene = DifficultyScene::create();
    //CCScene *pScene = GameScene::create();
    //CCScene *pScene = PreferenceScene::create();
    //CCScene *pScene = WinScene::create();
    
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
