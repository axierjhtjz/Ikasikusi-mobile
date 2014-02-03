#ifndef __DIFFICULTY_SCENE_H__
#define __DIFFICULTY_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class DifficultyScene : public cocos2d::CCScene
{
public:
    DifficultyScene();
	~DifficultyScene();
    
	virtual bool init();
	CREATE_FUNC(DifficultyScene);
private:

};

#endif // __DIFFICULTY_SCENE_H__