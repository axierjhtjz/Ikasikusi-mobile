#include "../Scenes/LogoScene.h"
#include "../Scenes/LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "../Helpers/VisibleRect.h"
#include "../MobHawk/MobHawkAPI.h"

using namespace cocos2d;
using namespace CocosDenshion;

LogoScene::~LogoScene()
{
    //CC_SAFE_DELETE(m_pAPI);
}

LogoScene::LogoScene()
{
    
}

bool LogoScene::init()
{
    if ( !CCScene::init() )
    {
        return false;
    }
    
    
    
    CCSize iSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLayerColor *layer = CCLayerColor::create();
    layer->initWithColor(ccc4(255, 255, 255, 255), iSize.width , iSize.height);
    layer->setPosition(VisibleRect::center());
    layer->setAnchorPoint(ccp(0.5f, 0.5f));
    layer->ignoreAnchorPointForPosition(false);
    this->addChild(layer, 0);
    
    CCSprite *sprite = CCSprite::create("logo.png");
    sprite->setPosition(VisibleRect::center());
    this->addChild(sprite);
    
    MobHawkAPI *mobHawk = MobHawkAPI::SharedInstance();
    mobHawk->setScene(this);
    mobHawk->call();
    
    return true;
}

void LogoScene::finishLoading()
{    
    CCScene *scene = LoadingScene::create();
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCTransitionFade *tscene = CCTransitionFade::create(0.5, scene);
    pDirector->replaceScene(tscene);
}
