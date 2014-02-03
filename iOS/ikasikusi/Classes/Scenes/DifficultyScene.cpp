#include "../Scenes/DifficultyScene.h"
#include "../Layers/DifficultyLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

DifficultyScene::~DifficultyScene()
{
    //CC_SAFE_DELETE(m_pAPI);
}

DifficultyScene::DifficultyScene()
{

}

bool DifficultyScene::init()
{
    
    if ( !CCScene::init() )
    {
        return false;
    }
    
    DifficultyLayer *layer = DifficultyLayer::create(this);
    addChild(layer);
    
    return true;
}
