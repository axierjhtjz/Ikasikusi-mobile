#include "../Scenes/ThemeSelectionScene.h"
#include "../Helpers/CCScrollLayer.h"
#include "../Helpers/VisibleRect.h"
#include "SimpleAudioEngine.h"
#include "../Helpers/SpriteButton.h"
#include "../Helpers/DataFileHelper.h"
#include "../Models/Category.h"
#include "../Models/Response.h"
#include "../Helpers/SpriteButton.h"
#include "../Scenes/DifficultyScene.h"
#include "../Helpers/StatsHelper.h"
#include "../Scenes/PreferenceScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

ThemeSelectionScene::~ThemeSelectionScene()
{
    /*CC_SAFE_DELETE(m_pScrollLayer);
    CC_SAFE_DELETE(m_pUpButton);
    CC_SAFE_DELETE(m_pDownButton);*/
}

ThemeSelectionScene::ThemeSelectionScene()
{
    m_pUpButton = CCMenuItemImage::create("up_arrow.png","up_arrow.png",this, menu_selector(ThemeSelectionScene::pageUpClicked));
    m_pDownButton = CCMenuItemImage::create("down_arrow.png","down_arrow.png",this, menu_selector(ThemeSelectionScene::pageDownClicked));
}

bool ThemeSelectionScene::init()
{
    
    if ( !CCScene::init() )
    {
        return false;
    }
    
    CCArray *categories = DataFileHelper::SharedInstance()->getCategories();
    
    //CCSize iSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLayer *layer = CCLayer::create();
    layer->setContentSize(ccp(VisibleRect::right().x, VisibleRect::top().y));
    layer->setPosition( VisibleRect::center() );
    layer->setAnchorPoint(ccp(0.5f, 0.5f));
    layer->ignoreAnchorPointForPosition(false);
    
    CCSprite *pBackground = CCSprite::create("fondo_azul.jpg");
    pBackground->setPosition(VisibleRect::center());
    layer->addChild(pBackground);
    
    int numLevels = categories->count();
    
    int numberPages = numLevels / 3;
    
    if (numLevels % 3 > 0) {
        numberPages++;
    }

    int cont = 0;
    CCArray *pLayers = CCArray::create();
    CCSize diffContainerSize;
    
    for (int i = 1; i <= numberPages; i++) {
        
        CCLayer *pContainer = CCLayer::create();
        pContainer->setAnchorPoint(ccp(0.5f, 0.5f));
        pContainer->ignoreAnchorPointForPosition(false);
        
        CCSprite *pBlueSprite = CCSprite::create("difficulty_container.png");
        pBlueSprite->setPosition(ccp(VisibleRect::right().x/2, VisibleRect::top().y/2));
        diffContainerSize = pBlueSprite->getContentSize();
        pContainer->addChild(pBlueSprite);
        
        float rowHeight = ((VisibleRect::top().y - 160) / 3); // Max 3 items per page
        float rowWidth = VisibleRect::right().x - 160;
        CCSize contentSize = CCSizeMake(rowWidth, rowHeight);
        
        CCSprite *pBox = CCSprite::create("caja.png");
        
        CCPoint layerPosition[] = {
            ccp(VisibleRect::right().x/2, (VisibleRect::top().y/2) + pBox->getContentSize().height + 10),  // top row
            ccp(VisibleRect::right().x/2, VisibleRect::top().y/2),               // middle row
            ccp(VisibleRect::right().x/2, (VisibleRect::top().y/2) - pBox->getContentSize().height - 10) // bottom row
        };
        
        int numberRows = numLevels - (3 * (i-1));
        
        if (numberRows > 3)
            numberRows = 3;
        
        for(int j = 1; j <= numberRows; j++) {
            
            Category *cat = (Category*)categories->objectAtIndex(cont);
            
            CCLayer *pContentLayer = CCLayer::create();
            pContentLayer->setContentSize(contentSize);
            pContentLayer->setPosition(layerPosition[j-1]);
            pContentLayer->setAnchorPoint(ccp(0.5f,0.5f));
            pContentLayer->ignoreAnchorPointForPosition(false);
            
            CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("caja.png");
            SpriteButton *pBox2 = SpriteButton::create(pTexture ,this, callfuncO_selector(ThemeSelectionScene::categorySelected), 1.0f);
            pBox2->setPosition(ccp(pContentLayer->getContentSize().width/2, pContentLayer->getContentSize().height/2));
            pBox2->setTag(cat->getID());
            pContentLayer->addChild(pBox2);
            
            std::string layout = cat->getName();
            std::ostringstream s;
            s << layout;
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                CCLabelTTF *pLabel = CCLabelTTF::create(s.str().c_str(), "IndieFlower", 40.0);
            #else
                CCLabelTTF *pLabel = CCLabelTTF::create(s.str().c_str(), "fonts/IndieFlower.ttf", 40.0);
            #endif
            CCSize parentSize = pContentLayer->getContentSize();
            pLabel->setPosition(ccp(parentSize.width/2, parentSize.height/2));
            pLabel->setColor(ccc3(3, 72, 140));
            pContentLayer->addChild(pLabel);
            
            pContainer->addChild(pContentLayer);
            cont++;
        }
        
        pLayers->addObject(pContainer);
    }

    m_pScrollLayer = CCScrollLayer::nodeWithLayers(pLayers, 0);
    m_pScrollLayer->setPagesIndicatorPosition(VisibleRect::leftBottom());
    m_pScrollLayer->setDelegate(this);
    m_pScrollLayer->moveToPage(0);
    layer->addChild(m_pScrollLayer);

    CCSprite *pLogo = CCSprite::create("logo_theme_selection.png");
    float pLogoX = (VisibleRect::center().x - diffContainerSize.width/2) + pLogo->getContentSize().width / 2;
    float pLogoY = ((VisibleRect::top().y /2) + diffContainerSize.height / 2) + (pLogo->getContentSize().height / 2) - 50;
    pLogo->setPosition(ccp(pLogoX, pLogoY));
    pLogo->setAnchorPoint(ccp(0.5,0.5));
    pLogo->ignoreAnchorPointForPosition(false);
    layer->addChild(pLogo);
    
    m_pUpButton->setPosition(ccp(0, VisibleRect::top().y - 160 - m_pUpButton->getContentSize().height));
    m_pDownButton->setPosition(ccp(0, 160 + m_pUpButton->getContentSize().height));
    
    CCMenu* pLayerMenu = CCMenu::create(m_pUpButton, m_pDownButton, NULL);
    pLayerMenu->setContentSize(ccp(m_pUpButton->getContentSize().width, VisibleRect::rightTop().y));
    pLayerMenu->setPosition(ccp(VisibleRect::rightBottom().x - pLayerMenu->getContentSize().width, 0));
    
    layer->addChild(pLayerMenu);

    this->addChild(layer, 0);
    CCTexture2D *pTexture2 = CCTextureCache::sharedTextureCache()->addImage("options.png");
    SpriteButton *pBackButton = SpriteButton::create(pTexture2, this, callfuncO_selector(ThemeSelectionScene::menuClicked));
    CCPoint bottomLeft = VisibleRect::leftBottom();
    pBackButton->setPosition(ccp(bottomLeft.x + 70, bottomLeft.y + 60));
    addChild(pBackButton);

    return true;
}

void ThemeSelectionScene::menuClicked(CCObject* pSender)
{
    PreferenceScene *scene = PreferenceScene::create();
    scene->setSceneReturnType(kPopScene);
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCTransitionFade *tscene = CCTransitionFade::create(0.5, scene);
    pDirector->pushScene(tscene);
}

void ThemeSelectionScene::categorySelected(CCObject* pSender)
{
    SpriteButton *button = (SpriteButton*)pSender;
    StatsHelper::SharedInstance()->setCurrentLevel(button->getTag());
    CCTransitionFade *tscene = CCTransitionFade::create(0.5, DifficultyScene::create());
    CCDirector::sharedDirector()->replaceScene(tscene);
}

void ThemeSelectionScene::pageUpClicked(CCObject* pSender)
{
    m_pUpButton->setEnabled(false);
    if (m_pScrollLayer->getTotalScreens() - 1 > m_pScrollLayer->getCurrentScreen()) {
        m_pScrollLayer->moveToPage(m_pScrollLayer->getCurrentScreen() + 1);
    }
}

void ThemeSelectionScene::pageDownClicked(CCObject* pSender)
{
    m_pDownButton->setEnabled(false);
    if (m_pScrollLayer->getCurrentScreen() > 0) {
        m_pScrollLayer->moveToPage(m_pScrollLayer->getCurrentScreen() - 1);
    }
}

void ThemeSelectionScene::scrollLayerScrolledToPageNumber(CCScrollLayer* sender, unsigned int page)
{
    m_pUpButton->setEnabled(true);
    m_pDownButton->setEnabled(true);
}

void ThemeSelectionScene::finishLoading(){
    
}