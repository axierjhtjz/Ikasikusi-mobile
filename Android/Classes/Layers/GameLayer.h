//
//  PlayLayer.h
//  Ikasitz
//
//  Created by Asier Fernandez on 26/09/13.
//
//

#ifndef __Ikasitz__PlayLayer__
#define __Ikasitz__PlayLayer__

#include "cocos2d.h"
#include "../Scenes/GameScene.h"

USING_NS_CC;
using namespace cocos2d;

class GameLayer : public CCLayer
{
public:
    
    virtual bool init();
    
    ~GameLayer();
    
    static GameLayer* create(GameScene *pScene)
    {
        GameLayer *pRet = new GameLayer();
        pRet->m_pScene = pScene;
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
    
    static GameLayer* create(GameScene *pScene, int columns, int rows, int time, int responseNumber)
    {
        GameLayer *pRet = new GameLayer();
        pRet->m_pScene = pScene;
        pRet->m_time = time;
        pRet->m_rows = rows;
        pRet->m_columns = columns;
        pRet->m_layers = CCArray::create();
        pRet->m_responseBoxes = CCArray::create();
        pRet->m_responseNumber = responseNumber;
        CC_SAFE_RETAIN(pRet->m_layers);
        CC_SAFE_RETAIN(pRet->m_responseBoxes);
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
    int m_columns;
    int m_rows;
    int m_time;
    int m_responseNumber;
    
private:
    GameScene *m_pScene;
    void showWord();
    CCProgressTimer *m_progressTimer;
    CCArray *m_layers;
    void finishLoading();
    void startDiscovering();
    void onProgressBarUpdate();
    void removeLayer(CCNode* sender, void* i);
    void responseClicked(CCObject* pSender);
    int m_CorrectAnswer;
    int m_timer;
    float m_penalty;
    void menuClicked(CCObject* pSender);
    CCArray *m_responseBoxes;
};



#endif // __GAME_LAYER_H__
