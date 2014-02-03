//
//  GameLayer.cpp
//  ikasikusi
//
//  Created by Asier Fernandez on 26/09/13.
//
//

#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "../Helpers/VisibleRect.h"
#include "../Helpers/SpriteButton.h"
#include "../Helpers/DataFileHelper.h"
#include "../Models/Category.h"
#include "../Models/Response.h"
#include "../Scenes/WinScene.h"
#include "../Scenes/LoseScene.h"
#include "../Helpers/StatsHelper.h"
#include "../Scenes/ThemeSelectionScene.h"

GameLayer::~GameLayer()
{
    
}


bool GameLayer::init()
{
    setTouchEnabled(true);
    
    m_penalty = 1.0;
    
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

    m_CorrectAnswer = res->getValid();
    int fileId = res->getID();
    std::string ext = ".jpeg";
    std::ostringstream filePath;
    filePath << fileId << ext;
    
    //cat->release();
    //res->release();

    CCSprite *pBackground = CCSprite::create("fondo_azul.jpg");
    pBackground->setPosition(VisibleRect::center());
    addChild(pBackground);
    
    CCSprite *photo = CCSprite::create(filePath.str().c_str());
    
    CCSize visibleSize = VisibleRect::getVisibleRect().size;
    
    float lPhotoHeight = photo->getContentSize().height;//(visibleSize.height * 2) / 3; // 2/3 del alto
    float lPhotoWidth = photo->getContentSize().width;//visibleSize.width;
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        float lDataHeight = visibleSize.height - lPhotoHeight - 100; // 1/3 del alto
    #else
        float lDataHeight = visibleSize.height - lPhotoHeight; // 1/3 del alto
    #endif
    float lDataWidth = visibleSize.width;
    
    CCLayerColor *lPhoto = CCLayerColor::create();
    lPhoto->setContentSize(CCSizeMake(lPhotoWidth, lPhotoHeight));
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        lPhoto->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y - 100));
    #else
        lPhoto->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y - 10));
    #endif
    lPhoto->setAnchorPoint(ccp(0.5f, 1));
    lPhoto->ignoreAnchorPointForPosition(false);
   
    photo->setPosition( ccp(lPhoto->getContentSize().width / 2, lPhoto->getContentSize().height / 2) );
    photo->setAnchorPoint(ccp(0.5f,0.5f));
    photo->ignoreAnchorPointForPosition(false);
    lPhoto->addChild(photo);
    
    CCLayer *lPhotoCover = CCLayer::create();
    lPhotoCover->setPosition(VisibleRect::leftTop());
    lPhotoCover->setAnchorPoint(ccp(0,1));
    
    float lTestWidth = lPhotoWidth / m_columns;
    float lTestHeight = lPhotoHeight / m_rows;
    
    int coverCount = m_columns * m_rows;
    int x = 0;
    int y = 0;
    for (int i = 1; i <= coverCount; i++) {
        CCLayerColor *lTest = CCLayerColor::create();
        lTest->initWithColor(ccc4(3, 72, 140, 255), lTestWidth, lTestHeight);
        lTest->setPosition(ccp((x * lTestWidth), y * lTestHeight));
        m_layers->addObject(lTest);
        lPhoto->addChild(lTest);
        x++;
        if (i % m_columns == 0) {
            x = 0;
            y++;
        }
    }
    lPhoto->addChild(lPhotoCover);
    
    CCLayer *lData = CCLayer::create();
    lData->setContentSize(CCSizeMake(lDataWidth, lDataHeight));
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        lData->setPosition(ccp(VisibleRect::left().x, VisibleRect::top().y - lPhotoHeight - 100));
    #else
        lData->setPosition(ccp(VisibleRect::left().x, VisibleRect::top().y - lPhotoHeight));
    #endif
    lData->setAnchorPoint(ccp(0, 1));
    lData->ignoreAnchorPointForPosition(false);
    
    CCSprite * progressBorder = CCSprite::create();
    progressBorder->initWithFile("bt_progressbarborder.png");
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        progressBorder->setPosition(ccp(VisibleRect::right().x / 2, VisibleRect::bottom().y + 10));
    #else
        progressBorder->setPosition(ccp(VisibleRect::right().x / 2, VisibleRect::bottom().y));
    #endif
    progressBorder->setAnchorPoint(ccp(0.5f, 0));
    addChild(progressBorder,1);
    
    m_progressTimer = CCProgressTimer::create( CCSprite::create("bt_progressbar.png") );
    if ( m_progressTimer != NULL )
    {
        m_progressTimer->setType(kCCProgressTimerTypeBar);
        m_progressTimer->setMidpoint(ccp(0, 0));
        m_progressTimer->setBarChangeRate(ccp(1, 0));
        m_progressTimer->setPercentage(100);
        m_progressTimer->setAnchorPoint(ccp(0.5f,0.5f));
        m_progressTimer->ignoreAnchorPointForPosition(false);
        m_progressTimer->setPosition(ccp(progressBorder->getContentSize().width / 2, progressBorder->getContentSize().height / 2));
        progressBorder->addChild(m_progressTimer,50);
    }
    
    addChild(lPhoto);
    addChild(lData);
    
    //CCLayerColor *lResponsesParent = CCLayerColor::create(ccc4(255, 255, 255, 100), lDataWidth, lDataHeight);
    CCLayer *lResponsesParent = CCLayer::create();
    lResponsesParent->setContentSize(CCSizeMake(lDataWidth, lDataHeight));
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        lResponsesParent->setPosition(ccp(VisibleRect::left().x, VisibleRect::top().y - lPhotoHeight - 100));
    #else
        lResponsesParent->setPosition(ccp(VisibleRect::left().x, lPhoto->getPosition().y - lPhotoHeight));
    #endif
    lResponsesParent->setAnchorPoint(ccp(0, 1));
    lResponsesParent->ignoreAnchorPointForPosition(false);
    lData->addChild(lResponsesParent);
    
    std::string responseLabels[4] = {res->getOption1(), res->getOption2(), res->getOption3(), res->getOption4()};
        
    for (int i = 1; i <= m_responseNumber; i++) {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            CCLabelTTF *pLabel = CCLabelTTF::create(responseLabels[i-1].c_str(), "IndieFlower", 30.0);
        #else
            CCLabelTTF *pLabel = CCLabelTTF::create(responseLabels[i-1].c_str(), "fonts/IndieFlower.ttf", 30.0);
        #endif
        pLabel->setColor(ccc3(3, 72, 140));

        CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("response_box.png");
        SpriteButton *lResponses = SpriteButton::create(pTexture ,this, callfuncO_selector(GameLayer::responseClicked), 1.0f);
        lResponses->setAnchorPoint(ccp(0.5f,0.5f));
        lResponses->ignoreAnchorPointForPosition(false);
        if (i % 2 == 0) {
            if (i > 2) {
                lResponses->setPosition(
                    ccp(( lData->getContentSize().width / 2 + (lResponses->getContentSize().width / 2)) + 10, ( lData->getContentSize().height - (lResponses->getContentSize().height * 2) - 20))); // 4
                pLabel->setPosition(
                    ccp(( lData->getContentSize().width / 2 + (lResponses->getContentSize().width / 2)) + 10, ( lData->getContentSize().height - (lResponses->getContentSize().height * 2) - 20))); // 4
            } else {
                lResponses->setPosition(
                    ccp(( lData->getContentSize().width / 2 + (lResponses->getContentSize().width / 2)) + 10, (lData->getContentSize().height - lResponses->getContentSize().height) - 10)); // 2
                pLabel->setPosition(
                   ccp(( lData->getContentSize().width / 2 + (lResponses->getContentSize().width / 2)) + 10, (lData->getContentSize().height - lResponses->getContentSize().height) - 10)); // 2
            }
        } else {
            if (i > 2) {
                lResponses->setPosition(
                    ccp(( lData->getContentSize().width / 2 ) - (lResponses->getContentSize().width / 2), ( lData->getContentSize().height - (lResponses->getContentSize().height * 2) - 20))); // 3
                pLabel->setPosition(
                    ccp(( lData->getContentSize().width / 2 ) - (lResponses->getContentSize().width / 2), ( lData->getContentSize().height - (lResponses->getContentSize().height * 2) - 20))); // 3
            } else {
                lResponses->setPosition(
                    ccp(( lData->getContentSize().width / 2 ) - (lResponses->getContentSize().width / 2), (lData->getContentSize().height - lResponses->getContentSize().height) - 10)); // 1
                pLabel->setPosition(
                    ccp(( lData->getContentSize().width / 2 ) - (lResponses->getContentSize().width / 2), (lData->getContentSize().height - lResponses->getContentSize().height) - 10)); // 1
            }
        }
        lResponses->setTag(i);
        m_responseBoxes->addObject(lResponses);
        lData->addChild(lResponses);
        lData->addChild(pLabel);
        x++;
    }
    
    std::ostringstream s;
    s << StatsHelper::SharedInstance()->getPoints();
    
    CCSprite *pPointsBox = CCSprite::create("points_box.png");
    float boxX = progressBorder->getPosition().x - progressBorder->getContentSize().width /2 - (pPointsBox->getContentSize().width/2) - 10;
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        pPointsBox->setPosition(ccp(boxX, VisibleRect::bottom().y + 10));
    #else
        pPointsBox->setPosition(ccp(boxX, VisibleRect::bottom().y));
    #endif
    pPointsBox->setAnchorPoint(ccp(0.5f,0));
    addChild(pPointsBox);
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCLabelTTF *pLabel = CCLabelTTF::create(s.str().c_str(), "IndieFlower", 25.0);
        CCLabelTTF *lPuntuazioa = CCLabelTTF::create("Puntuazioa:", "IndieFlower", 20.0);
        CCLabelTTF *lDenbora = CCLabelTTF::create("Denbora:", "IndieFlower", 20.0);
    #else
        CCLabelTTF *pLabel = CCLabelTTF::create(s.str().c_str(), "fonts/IndieFlower.ttf", 25.0);
        CCLabelTTF *lPuntuazioa = CCLabelTTF::create("Puntuazioa:", "fonts/IndieFlower.ttf", 20.0);
        CCLabelTTF *lDenbora = CCLabelTTF::create("Denbora:", "fonts/IndieFlower.ttf", 20.0);
    #endif
    pLabel->setPosition(ccp(pPointsBox->getContentSize().width /2 , pPointsBox->getContentSize().height/2));
    pLabel->setColor(ccc3(3, 72, 140));
    pLabel->setAnchorPoint(ccp(0.5f,0.5f));
    pPointsBox->addChild(pLabel);
    
    lPuntuazioa->setPosition(ccp(pPointsBox->getPosition().x - pPointsBox->getContentSize().width/2, pPointsBox->getContentSize().height + 5));
    lPuntuazioa->setAnchorPoint(ccp(0, 0));
    lPuntuazioa->setColor(ccc3(3, 72, 140));
    addChild(lPuntuazioa);
    
    lDenbora->setPosition(ccp(progressBorder->getPosition().x - progressBorder->getContentSize().width/2, pPointsBox->getContentSize().height + 5));
    lDenbora->setAnchorPoint(ccp(0, 0));
    lDenbora->setColor(ccc3(3, 72, 140));
    addChild(lDenbora);
    
    CCTexture2D *pTexture2 = CCTextureCache::sharedTextureCache()->addImage("menu.png");
    SpriteButton *pBackButton = SpriteButton::create(pTexture2, this, callfuncO_selector(GameLayer::menuClicked));
    CCPoint rightBottom = VisibleRect::rightBottom();
    pBackButton->setPosition(ccp(rightBottom.x - 60, rightBottom.y + 50));
    addChild(pBackButton);
    
    finishLoading();
    
    return true;
}

void GameLayer::menuClicked(CCObject* pSender)
{
    CCScene *scene = ThemeSelectionScene::create();
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCTransitionFade *tscene = CCTransitionFade::create(0.5, scene);
    pDirector->replaceScene(tscene);
}

void GameLayer::finishLoading()
{
    float temp = ((float)m_time / (float)(m_columns * m_rows));
    m_timer = m_time;
    schedule(schedule_selector(GameLayer::startDiscovering), temp);
    schedule(schedule_selector(GameLayer::onProgressBarUpdate), 1);
}

void GameLayer::startDiscovering()
{
    int lcount = m_layers->count();
    if (lcount == 0) {
        this->unscheduleAllSelectors();
    } else {
        int isGoingToDesapear = arc4random()%lcount;
        CCLayer *willFadeLayer = (CCLayer*)m_layers->objectAtIndex(isGoingToDesapear);
        int* value = new int(isGoingToDesapear);
        CCFadeOut *fadeAction = CCFadeOut::create(0.5f);
        fadeAction->initWithDuration(0.3f);
        CCSequence *sequence = CCSequence::createWithTwoActions(fadeAction,CCCallFuncND::create(this, callfuncND_selector(GameLayer::removeLayer),(void*) value));
        delete value;
        willFadeLayer->runAction(sequence);
        m_layers->removeObjectAtIndex(isGoingToDesapear);
    }
}

void GameLayer::onProgressBarUpdate()
{
    float percentage;
    int difficulty = StatsHelper::SharedInstance()->getDifficulty();
    int levelsDone = StatsHelper::SharedInstance()->getNumberOfLevelsDone();
    switch (difficulty) {
        case 1:
            m_timer = m_timer - 1 - (0.15 * levelsDone);
            break;
        case 2:
            m_timer = m_timer - 2 - (0.15 * levelsDone);
            break;
        case 3:
            m_timer = m_timer - 2 - (0.25 * levelsDone);
            break;
        default:
            break;
    }
    if (m_penalty != 0.0) {
        m_timer = m_timer - m_penalty;
        m_penalty = 0.0;
    }
    
    percentage = ((float)m_timer * 100.0f) / ((float)(m_time) * 1.0f);
    m_progressTimer->setPercentage(percentage);
    if (percentage <= 0.0f) {
        //CCLog("Layer count: %d", m_layers->count());
        CCTransitionFade *tscene = CCTransitionFade::create(0.5, LoseScene::create());
        CCDirector::sharedDirector()->replaceScene(tscene);
    } else {
        for (int i = 0; i < m_responseBoxes->count(); i++) {
            SpriteButton *button = (SpriteButton*) m_responseBoxes->objectAtIndex(i);
            button->setEnabled(true);
        }
    }

}

void GameLayer::responseClicked(CCObject* pSender)
{
    for (int i = 0; i < m_responseBoxes->count(); i++) {
        SpriteButton *button = (SpriteButton*) m_responseBoxes->objectAtIndex(i);
        button->setEnabled(false);
    }
    StatsHelper::SharedInstance()->setOneMoreLevelDone();
    StatsHelper::SharedInstance()->getPoints(m_progressTimer->getPercentage());
    SpriteButton *theResponse = (SpriteButton*)pSender;
    if (theResponse->getTag() == m_CorrectAnswer) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/bien.wav");
        CCTransitionFade *tscene = CCTransitionFade::create(0.5, WinScene::create());
        CCDirector::sharedDirector()->replaceScene(tscene);
    } else {
        m_penalty = m_time / 3;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/mal.wav");
    }
}

void GameLayer::removeLayer(CCNode* sender, void* i)
{
    
}

void GameLayer::showWord()
{
    
}