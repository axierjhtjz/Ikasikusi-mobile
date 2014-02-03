//
//  LogoScene.h
//  ikasikusi
//
//  Created by Asier Fernandez on 24/09/13.
//
//

#ifndef __LOGO_SCENE_H__
#define __LOGO_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class LogoScene : public CCScene
{
public:
    LogoScene();
    ~LogoScene();
    
    virtual bool init();
    void finishLoading();
	CREATE_FUNC(LogoScene);
private:

};

#endif // __LOGO_SCENE_H__

