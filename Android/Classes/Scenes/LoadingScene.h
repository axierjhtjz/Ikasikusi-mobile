#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cJSON.h"
#include "../Helpers/DataFileHelper.h"

class LoadingScene : public cocos2d::CCScene
{
public:
    LoadingScene();
	~LoadingScene();
    
	virtual bool init();
	CREATE_FUNC(LoadingScene);
private:
    void finishLoading();
};

#endif // __LOADING_SCENE_H__
