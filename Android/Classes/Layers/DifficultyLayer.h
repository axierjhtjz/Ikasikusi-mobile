//
//  PlayLayer.h
//  Ikasitz
//
//  Created by Asier Fernandez on 26/09/13.
//
//

#ifndef __DIFFICULTY_LAYER__
#define __DIFFICULTY_LAYER__

#include "cocos2d.h"
#include "../Scenes/DifficultyScene.h"

USING_NS_CC;
using namespace cocos2d;

class DifficultyLayer : public CCLayer
{
public:
    
    virtual bool init();
    
    ~DifficultyLayer();
    
    static DifficultyLayer* create(DifficultyScene *pScene)
    {
        DifficultyLayer *pRet = new DifficultyLayer();
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
    int m_columns;
    int m_rows;
    int m_time;
    int m_responseNumber;
    
private:
    DifficultyScene *m_pScene;
    void finishLoading();
    void difficultySelected(CCObject* pSender);
};


#endif // __DIFFICULTY_LAYER_H__
