//
//  WinScene.h
//  ikasikusi
//
//  Created by Asier Fernandez on 16/10/13.
//
//

#ifndef __ikasikusi__WinScene__
#define __ikasikusi__WinScene__

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;

class WinScene : public cocos2d::CCScene
{
public:
    WinScene();
	~WinScene();
    
	virtual bool init();
	CREATE_FUNC(WinScene);
private:
    void finishLoading();
    void menuClicked(CCObject* pSender);
    void nextClicked(CCObject* pSender);
};

#endif  /* defined(__ikasikusi__WinScene__) */
