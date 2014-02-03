//
//  DataFileHelper.h
//  ikasikusi
//
//  Created by Asier Fernandez on 09/10/13.
//
//

#ifndef __MobHawkAPI__
#define __MobHawkAPI__

#include "cocos2d.h"
#include "cJSON.h"
#include "HttpClient.h"
#include "HttpRequest.h"
#include "../Scenes/LogoScene.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MobHawkAPI : public CCObject
{
public:
    void call();
    static MobHawkAPI* SharedInstance();
    bool isBloqued();
    void setScene(CCScene *scene);
private:
    MobHawkAPI();  // Private so that it can  not be called
    MobHawkAPI(MobHawkAPI const&){};             // copy constructor is private
    MobHawkAPI& operator=(MobHawkAPI const&){};  // assignment operator is private
    static MobHawkAPI* m_pInstance;
    
    ~MobHawkAPI();
    bool m_isBloqued;
    CCScene *m_scene;
    CCHttpRequest* createRequest();
    void RequestCompleted(CCHttpClient* client, CCHttpResponse* response);
    std::string checkResponse(CCHttpResponse *response);
};

#endif /* defined(__MobHawkAPI__) */


