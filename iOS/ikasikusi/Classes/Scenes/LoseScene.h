//
//  LoseScene.h
//  ikasikusi
//
//  Created by Asier Fernandez on 16/10/13.
//
//

#ifndef __ikasikusi__LoseScene__
#define __ikasikusi__LoseScene__

#include "cocos2d.h"

using namespace cocos2d;

class LoseScene : public cocos2d::CCScene
{
public:
    LoseScene();
	~LoseScene();
    
	virtual bool init();
	CREATE_FUNC(LoseScene);
private:
    void finishLoading();
    void restartClicked(CCObject* pSender);
    void facebookClicked(CCObject* pSender);
    void twitterClicked(CCObject* pSender);
    void menuClicked(CCObject* pSender);
};

#endif /* defined(__ikasikusi__LoseScene__) */
