//
//  WinScene.cpp
//  ikasikusi
//
//  Created by Asier Fernandez on 16/10/13.
//
//

#include "WinScene.h"

#include "../Scenes/ThemeSelectionScene.h"
#include "../Helpers/CCScrollLayer.h"
#include "../Helpers/VisibleRect.h"
#include "SimpleAudioEngine.h"
#include "../Helpers/SpriteButton.h"
#include "../Helpers/DataFileHelper.h"
#include "../Models/Category.h"
#include "../Models/Response.h"
#include "../Helpers/SpriteButton.h"
#include "../Scenes/DifficultyScene.h"
#include "../Scenes/PreferenceScene.h"
#include "../Helpers/StatsHelper.h"
#include "../Scenes/GameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

WinScene::~WinScene()
{

}

WinScene::WinScene()
{

}

bool WinScene::init()
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
    lContainer->setPosition(ccp(VisibleRect::right().x / 2, VisibleRect::top().y / 2));
    
    CCTexture2D *pTexture1 = CCTextureCache::sharedTextureCache()->addImage("win_box.png");
    SpriteButton *pWinBox = SpriteButton::create(pTexture1, this, callfuncO_selector(WinScene::nextClicked));
    pWinBox->setPosition(ccp(lContainer->getContentSize().width / 2 , lContainer->getContentSize().height / 2));
    lContainer->addChild(pWinBox);
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCLabelTTF *pLabel1 = CCLabelTTF::create("Hurrengo", "IndieFlower", 40.0);
        CCLabelTTF *pLabel2 = CCLabelTTF::create("pantaila", "IndieFlower", 40.0);
        CCLabelTTF *pLabel = CCLabelTTF::create("Erantzun zuzena!!!", "IndieFlower", 100.0);
    #else
        CCLabelTTF *pLabel1 = CCLabelTTF::create("Hurrengo", "fonts/IndieFlower.ttf", 40.0);
        CCLabelTTF *pLabel2 = CCLabelTTF::create("pantaila", "fonts/IndieFlower.ttf", 40.0);
        CCLabelTTF *pLabel = CCLabelTTF::create("Erantzun zuzena!!!", "fonts/IndieFlower.ttf", 100.0);
    #endif

    pLabel1->setPosition(ccp(pWinBox->getContentSize().width / 4, pWinBox->getContentSize().height / 2 + 20));
    pLabel2->setPosition(ccp(pWinBox->getContentSize().width / 4, pWinBox->getContentSize().height / 2 - 20));
    pLabel1->setColor(ccc3(3, 72, 140));
    pLabel2->setColor(ccc3(3, 72, 140));
    pWinBox->addChild(pLabel1);
    pWinBox->addChild(pLabel2);
    
    layer->addChild(lContainer);

    addChild(layer);

    pLabel->setPosition(ccp(VisibleRect::right().x / 2, VisibleRect::center().y + pWinBox->getContentSize().height));
    pLabel->setColor(ccc3(255, 255, 255));
    addChild(pLabel);
    
    CCTexture2D *pTexture2 = CCTextureCache::sharedTextureCache()->addImage("menu.png");
    SpriteButton *pBackButton = SpriteButton::create(pTexture2, this, callfuncO_selector(WinScene::menuClicked));
    CCPoint bottomLeft = VisibleRect::leftBottom();
    pBackButton->setPosition(ccp(bottomLeft.x + 70, bottomLeft.y + 60));
    addChild(pBackButton);
    
    
    
    finishLoading();
    return true;
}

void WinScene::nextClicked(CCObject* pSender)
{
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

void WinScene::menuClicked(CCObject* pSender)
{
    CCScene *scene = ThemeSelectionScene::create();
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCTransitionFade *tscene = CCTransitionFade::create(0.5, scene);
    pDirector->replaceScene(tscene);
}

void WinScene::finishLoading(){
    
}
