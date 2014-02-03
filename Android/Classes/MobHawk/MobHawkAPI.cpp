//
//  DataFileHelper.cpp
//  ikasikusi
//
//  Created by Asier Fernandez on 09/10/13.
//
//

#include "MobHawkAPI.h"

using namespace cocos2d::extension;

MobHawkAPI* MobHawkAPI::m_pInstance = NULL;

MobHawkAPI* MobHawkAPI::SharedInstance()
{
    if (!m_pInstance)
    {   // Only allow one instance of class to be generated.
        m_pInstance = new MobHawkAPI();
        m_pInstance->m_isBloqued = false;
    }
    
    return m_pInstance;
}

MobHawkAPI::MobHawkAPI() // Constructor
{
}

MobHawkAPI::~MobHawkAPI() // Destructor
{
}

CCHttpRequest* MobHawkAPI::createRequest()
{
    const char* postData = "app=ikasikusi&version=2";
    
    CCHttpRequest* pRequest = new CCHttpRequest();
    pRequest->setUrl("https://mob-hawk.irontec.com/check");
    pRequest->setRequestType(CCHttpRequest::kHttpPost);
    pRequest->setResponseCallback(this, httpresponse_selector(MobHawkAPI::RequestCompleted));
    pRequest->setRequestData(postData, strlen(postData));
    return pRequest;
}

void MobHawkAPI::call()
{
    CCHttpRequest *pRequest = createRequest();
    CCHttpClient::getInstance()->send(pRequest);
    pRequest->release();
}

void MobHawkAPI::RequestCompleted(CCHttpClient* client, CCHttpResponse* response)
{
    std::string data = checkResponse(response).c_str();
    CCLog("%s", data.c_str());
    if (!data.empty() && response->isSucceed()) {
        bool silence, update, mustBlock;
        std::string es, eu, en, ca;
        
        cJSON *pRoot = cJSON_Parse(data.c_str());
        cJSON *jsonUpdate = cJSON_GetObjectItem(pRoot, "update");
        if (jsonUpdate != NULL) {
            update = jsonUpdate->valueint;
        }
        cJSON *jsonSilence = cJSON_GetObjectItem(pRoot, "silence");
        if (jsonSilence != NULL) {
            silence = jsonSilence->valueint;
        }
        cJSON *jsonMustBlock = cJSON_GetObjectItem(pRoot, "mustBlock");
        if (jsonMustBlock != NULL) {
            mustBlock = jsonMustBlock->valueint;
        }
        
        cJSON *messages = cJSON_GetObjectItem(pRoot, "messages");
        if (messages != NULL) {
            es = strdup(cJSON_GetObjectItem(messages, "es")->valuestring);
            eu = strdup(cJSON_GetObjectItem(messages, "eu")->valuestring);
            en = strdup(cJSON_GetObjectItem(messages, "en")->valuestring);
            ca = strdup(cJSON_GetObjectItem(messages, "ca")->valuestring);
        }
        
        if (!silence) {
            if (update && mustBlock) {
                CCMessageBox("", es.c_str());
            } else if (update) {
                CCMessageBox("", es.c_str());
                if (m_scene != NULL) {
                    m_scene->schedule(schedule_selector(LogoScene::finishLoading), 2);
                }
            } else {
                if (m_scene != NULL) {
                    m_scene->schedule(schedule_selector(LogoScene::finishLoading), 2);
                }
            }
        } else {
            if (m_scene != NULL) {
                m_scene->schedule(schedule_selector(LogoScene::finishLoading), 2);
            }
        }
    } else {
        if (m_scene != NULL) {
            m_scene->schedule(schedule_selector(LogoScene::finishLoading), 2);
        }
    }
}

bool MobHawkAPI::isBloqued()
{
    return m_isBloqued;
}

void MobHawkAPI::setScene(CCScene *scene) {
    m_scene = scene;
}

std::string MobHawkAPI::checkResponse(CCHttpResponse *response)
{
    if (!response)
        return NULL;
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        CCLog("HTTP Status Code: %d", response->getResponseCode());
        
        std::vector<char> *buffer = response->getResponseData();
        
        printf("Http Test, dump data: ");
        for (unsigned int i = 0; i < buffer->size(); i++)
        {
            printf("%c", (*buffer)[i]);
        }
        printf("\n");
    }
    
    std::vector<char> *buffer = response->getResponseData();
    std::string data(buffer->begin(), buffer->end());
    
    return data;
}