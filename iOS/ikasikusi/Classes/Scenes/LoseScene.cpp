//
//  LoseScene.cpp
//  ikasikusi
//
//  Created by Asier Fernandez on 16/10/13.
//
//

#include "LoseScene.h"
#include "../Scenes/ThemeSelectionScene.h"
#include "../Helpers/VisibleRect.h"
#include "SimpleAudioEngine.h"
#include "../Helpers/SpriteButton.h"
#include "../Scenes/PreferenceScene.h"
#include "../Helpers/StatsHelper.h"
#include "../Models/Category.h"
#include "../Models/Response.h"
#include "../Helpers/DataFileHelper.h"
#include "../Scenes/GameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

LoseScene::~LoseScene()
{
    
}

LoseScene::LoseScene()
{
    
}

bool LoseScene::init()
{
    
    if ( !CCScene::init() )
    {
        return false;
    }
    
    CCLayer *layer = CCLayer::create();
    layer->setContentSize(ccp(VisibleRect::right().x, VisibleRect::top().y));
    layer->setPosition( VisibleRect::center() );
    layer->setAnchorPoint(ccp(0.5f, 0.5f));
    layer->ignoreAnchorPointForPosition(false);
    
    CCSprite *pBackground = CCSprite::create("fondo_azul.jpg");
    pBackground->setPosition(VisibleRect::center());
    layer->addChild(pBackground);
    
    CCSprite *lContainer = CCSprite::create("forma_base_big.png");
    lContainer->setPosition(ccp(VisibleRect::right().x /2, VisibleRect::top().y / 2));
    
    CCTexture2D *pTexture1 = CCTextureCache::sharedTextureCache()->addImage("restart.png");
    SpriteButton *pWinBox = SpriteButton::create(pTexture1, this, callfuncO_selector(LoseScene::restartClicked));
    pWinBox->setPosition(ccp(lContainer->getContentSize().width / 2 , lContainer->getContentSize().height / 2));
    lContainer->addChild(pWinBox);
    
    std::string points = " puntu";
    std::ostringstream text;
    text << StatsHelper::SharedInstance()->getPoints() << points;
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCLabelTTF *pLabel1 = CCLabelTTF::create("Denbora amaitu egin da!!", "IndieFlower", 70.0);
        CCLabelTTF *pLabel2 = CCLabelTTF::create(text.str().c_str(), "IndieFlower", 50.0);
        CCLabelTTF *pLabel3 = CCLabelTTF::create("lortu dituzu", "IndieFlower", 30.0);
    #else
        CCLabelTTF *pLabel1 = CCLabelTTF::create("Denbora amaitu egin da!!", "fonts/IndieFlower.ttf", 70.0);
        CCLabelTTF *pLabel2 = CCLabelTTF::create(text.str().c_str(), "fonts/IndieFlower.ttf", 50.0);
        CCLabelTTF *pLabel3 = CCLabelTTF::create("lortu dituzu", "fonts/IndieFlower.ttf", 30.0);
    #endif
    
    pLabel1->setPosition(ccp(VisibleRect::right().x / 2, VisibleRect::center().y + pWinBox->getContentSize().height * 1.5f));
    pLabel2->setPosition(ccp(VisibleRect::right().x / 2, VisibleRect::center().y + pWinBox->getContentSize().height * 1.1f));
    pLabel3->setPosition(ccp(VisibleRect::right().x / 2 + pLabel3->getContentSize().width, VisibleRect::center().y + pWinBox->getContentSize().height * 0.75f));
    pLabel1->setColor(ccc3(255, 255, 255));
    pLabel2->setColor(ccc3(255, 255, 255));
    pLabel3->setColor(ccc3(255, 255, 255));
    
    layer->addChild(lContainer);
    
    addChild(layer);
    addChild(pLabel1);
    addChild(pLabel2);
    addChild(pLabel3);
    
    CCTexture2D *pTexture2 = CCTextureCache::sharedTextureCache()->addImage("menu.png");
    SpriteButton *pBackButton = SpriteButton::create(pTexture2, this, callfuncO_selector(LoseScene::menuClicked));
    CCPoint bottomLeft = VisibleRect::leftBottom();
    pBackButton->setPosition(ccp(bottomLeft.x + 70, bottomLeft.y + 60));
    addChild(pBackButton);
    
    finishLoading();
    return true;
}

void LoseScene::restartClicked(CCObject* pSender)
{
    StatsHelper::SharedInstance()->resetStats();
    CCArray *categories = DataFileHelper::SharedInstance()->getCategories();
    Category *cat;
    Response *res;
    
    for (int i = 0; i < categories->count(); i++) {
        cat = (Category*)categories->objectAtIndex(i);
        if (cat->getID() == StatsHelper::SharedInstance()->getCurrentLevel()) {
            int numResponses = cat->getResponses()->count();
            srand ( time(NULL) );
            int index = rand() % numResponses;
            res = (Response*)cat->getResponses()->objectAtIndex(index);
        }
    }
    CCTransitionFade *tscene = CCTransitionFade::create(0.5, GameScene::create());
    CCDirector::sharedDirector()->replaceScene(tscene);
}

void LoseScene::menuClicked(CCObject* pSender)
{
    CCScene *scene = ThemeSelectionScene::create();
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCTransitionFade *tscene = CCTransitionFade::create(0.5, scene);
    pDirector->replaceScene(tscene);
}


void LoseScene::finishLoading(){
    
}
