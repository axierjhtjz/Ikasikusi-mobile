#ifndef __THEME_SELECTION_SCENE_H__
#define __THEME_SELECTION_SCENE_H__

#include "cocos2d.h"
#include "../Helpers/CCScrollLayer.h"
#include "cocos-ext.h"

using namespace cocos2d;

class ThemeSelectionScene : public cocos2d::CCScene, public cocos2d::CCScrollLayerDelegate
{
public:
    ThemeSelectionScene();
	~ThemeSelectionScene();
    
	virtual bool init();
    void pageUpClicked(CCObject* pSender);
    void pageDownClicked(CCObject* pSender);
	CREATE_FUNC(ThemeSelectionScene);
private:
    void finishLoading();
    void scrollLayerScrolledToPageNumber(cocos2d::CCScrollLayer* sender, unsigned int page);
    void categorySelected(CCObject* pSender);
    void menuClicked(CCObject* pSender);
    CCScrollLayer *m_pScrollLayer;
    CCMenuItemImage *m_pUpButton;
    CCMenuItemImage *m_pDownButton;
};

#endif // __THEME_SELECTION_SCENE_H__
