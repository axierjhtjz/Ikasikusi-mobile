#include "../Scenes/GameScene.h"
#include "../Layers/GameLayer.h"
#include "SimpleAudioEngine.h"
#include "../Helpers/StatsHelper.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameScene::~GameScene()
{
    //CC_SAFE_DELETE(m_pAPI);
}

GameScene::GameScene()
{
    m_columns = 10;
    m_rows = 4;
    m_time = 50;
    m_responseNumber = 4;
}

bool GameScene::init()
{
    
    if ( !CCScene::init() )
    {
        return false;
    }
    
    int difficulty = StatsHelper::SharedInstance()->getDifficulty();
    switch (difficulty) {
        case 1:
            m_columns = 10;
            m_rows = 4;
            m_time = 50;
            m_responseNumber = 4;
            break;
        case 2:
            m_columns = 13;
            m_rows = 5;
            m_time = 70;
            m_responseNumber = 4;
            break;
        case 3:
            m_columns = 16;
            m_rows = 6;
            m_time = 90;
            m_responseNumber = 4;
            break;
        default:
            break;
    }
    
    GameLayer *layer = GameLayer::create(this, m_columns, m_rows, m_time, m_responseNumber);
    addChild(layer);
    
    return true;
}
