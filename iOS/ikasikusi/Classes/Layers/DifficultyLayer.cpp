//
//  GameLayer.cpp
//  ikasikusi
//
//  Created by Asier Fernandez on 26/09/13.
//
//

#include "DifficultyLayer.h"
#include "../Helpers/VisibleRect.h"
#include "../Helpers/SpriteButton.h"
#include "../Scenes/GameScene.h"
#include "../Helpers/StatsHelper.h"

DifficultyLayer::~DifficultyLayer()
{
    
}


bool DifficultyLayer::init()
{
    CCLayer *lBackground= CCLayer::create();
    lBackground->setContentSize(ccp(VisibleRect::right().x, VisibleRect::top().y));
    lBackground->setPosition(VisibleRect::center());
    lBackground->setAnchorPoint(ccp(0.5f, 0.5f));
    lBackground->ignoreAnchorPointForPosition(false);
    
    CCSprite *pBackground = CCSprite::create("fondo_azul.jpg");
    pBackground->setPosition(VisibleRect::center());
    lBackground->addChild(pBackground);
    addChild(lBackground);
    
    CCSprite *lContainer = CCSprite::create("forma_base_big.png");
    lContainer->setPosition(VisibleRect::center());
    addChild(lContainer);
    
    int dificultyCount = 3;
    
    for (int i = 1; i <= dificultyCount; i++) {
        CCLayer *lDifficulty = CCLayer::create();
        lDifficulty->setContentSize(lContainer->getContentSize());
        lDifficulty->setAnchorPoint(ccp(0.5f, 0.5f));
        lDifficulty->ignoreAnchorPointForPosition(false);
        
        CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("difficulty_box.png");
        SpriteButton *pBox = SpriteButton::create(pTexture ,this, callfuncO_selector(DifficultyLayer::difficultySelected), 1.0f);
        pBox->setPosition(ccp(lDifficulty->getContentSize().width / 2, lDifficulty->getContentSize().height / 2));
        pBox->setTag(i);
        lDifficulty->addChild(pBox);
        
        std::string text = "";
        switch (i) {
            case 1:
                text = "Erraza";
                lDifficulty->setPosition(ccp(VisibleRect::right().x/2, VisibleRect::center().y + (pBox->getContentSize().height + 10)));
                break;
            case 2:
                text = "Tarteko zailtasuna";
                lDifficulty->setPosition(ccp(VisibleRect::right().x/2, VisibleRect::center().y));
                break;
            case 3:
                text = "Zaila";
                lDifficulty->setPosition(ccp(VisibleRect::right().x/2, VisibleRect::center().y - (pBox->getContentSize().height + 10)));
                break;
            default:
                break;
        }
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            CCLabelTTF *pLabel = CCLabelTTF::create(text.c_str(), "IndieFlower", 35.0);
        #else
            CCLabelTTF *pLabel = CCLabelTTF::create(text.c_str(), "fonts/IndieFlower.ttf", 35.0);
        #endif
        CCSize parentSize = lDifficulty->getContentSize();
        pLabel->setPosition(ccp(parentSize.width/2, parentSize.height/2));
        pLabel->setColor(ccc3(3, 72, 140));
        pLabel->setAnchorPoint(ccp(0.5f, 0.5f));
        lDifficulty->addChild(pLabel);
        
        addChild(lDifficulty);

    }
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCLabelTTF *pEzarpenak = CCLabelTTF::create("Zailtasuna aukeratu", "IndieFlower", 50.0);
    #else
        CCLabelTTF *pEzarpenak = CCLabelTTF::create("Zailtasuna aukeratu", "fonts/IndieFlower.ttf", 50.0);
    #endif
    pEzarpenak->setPosition(ccp(VisibleRect::center().x - pEzarpenak->getContentSize().width / 2, 480));
    pEzarpenak->setColor(ccc3(255, 255, 255));
    lContainer->addChild(pEzarpenak);
    
    CCSprite *pLinea = CCSprite::create("linea.png");
    pLinea->setPosition(ccp(VisibleRect::center().x + 20, 450));
    lContainer->addChild(pLinea);
    
    finishLoading();
    
    return true;
}

void DifficultyLayer::difficultySelected(CCObject* pSender)
{
    SpriteButton *selectedDifficulty = (SpriteButton*) pSender;
    CCTransitionFade *tscene;
    switch (selectedDifficulty->getTag()) {
        case 1:
            StatsHelper::SharedInstance()->setDifficulty(1);
            tscene = CCTransitionFade::create(0.5, GameScene::create());
            break;
        case 2:
            StatsHelper::SharedInstance()->setDifficulty(2);
            tscene = CCTransitionFade::create(0.5, GameScene::create());
            break;
        case 3:
            StatsHelper::SharedInstance()->setDifficulty(3);
            tscene = CCTransitionFade::create(0.5, GameScene::create());
            break;
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(tscene);
}

void DifficultyLayer::finishLoading()
{
    
}
