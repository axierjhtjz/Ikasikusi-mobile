#include "../Scenes/LoadingScene.h"
#include "../Scenes/ThemeSelectionScene.h"
#include "SimpleAudioEngine.h"
#include "../Models/Category.h"
#include "../Models/Response.h"
#include "../Helpers/VisibleRect.h"

using namespace cocos2d;
using namespace CocosDenshion;

LoadingScene::~LoadingScene()
{
    //CC_SAFE_DELETE(m_pAPI);
}

LoadingScene::LoadingScene()
{

}

bool LoadingScene::init()
{

    if ( !CCScene::init() )
    {
        return false;
    }
    
    DataFileHelper *helper = DataFileHelper::SharedInstance();
    
    CCSprite *pBackground = CCSprite::create("fondo_azul.jpg");
    pBackground->setPosition(VisibleRect::center());
    addChild(pBackground, 0);
    
    CCSprite *pSpinner = CCSprite::create("loading.png");
    pSpinner->setPosition(VisibleRect::center());
    addChild(pSpinner);

    if (helper != NULL) {
        this->schedule(schedule_selector(LoadingScene::finishLoading), 2);
    }
    return true;
}

void LoadingScene::finishLoading(){
    CCScene *scene = ThemeSelectionScene::create();
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCTransitionFade *tscene = CCTransitionFade::create(0.5, scene);
    pDirector->replaceScene(tscene);
}

//void LoadingScene::menuCloseCallback(CCObject* pSender)
//{
//  CCDirector::sharedDirector()->end();
    

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//}
