//
//  DataFileHelper.cpp
//  ikasikusi
//
//  Created by Asier Fernandez on 09/10/13.
//
//

#include "DataFileHelper.h"
#include "../Models/Category.h"
#include "../Models/Response.h"

DataFileHelper* DataFileHelper::m_pInstance = NULL;

DataFileHelper* DataFileHelper::SharedInstance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new DataFileHelper();
    
    return m_pInstance;
}

DataFileHelper::DataFileHelper() // Constructor
{
    parseDataFile();
}

DataFileHelper::~DataFileHelper() // Destructor
{
    CC_SAFE_RELEASE(m_Categories);
}

CCArray* DataFileHelper::getCategories()
{
    return m_Categories;
}

void DataFileHelper::parseDataFile()
{
    
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("data.json");
    unsigned char* fileContent = NULL;
    unsigned long bufferSize = 0;
    fileContent = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &bufferSize);
    cocos2d::CCString *ccStr = cocos2d::CCString::createWithData( fileContent, bufferSize );
    //printf("%s\n",ccStr->getCString());
    free(fileContent);
    
    cJSON *pRoot = cJSON_Parse(ccStr->getCString());
    int numItems = cJSON_GetArraySize(pRoot);
    
    m_Categories = new CCArray();
    m_Categories->initWithCapacity(numItems);
    
    for (int i = 0; i < numItems; i++)
    {
        Category *pCat = new Category();
        
        cJSON * item = cJSON_GetArrayItem(pRoot, i);
        pCat->setID(cJSON_GetObjectItem(item, "id")->valueint);
        pCat->setName(strdup(cJSON_GetObjectItem(item, "name")->valuestring));
        
        cJSON *pResponses = cJSON_GetObjectItem(item, "answers");
        
        CCArray *responses = CCArray::create();
        
        int numResponses = cJSON_GetArraySize(pResponses);
        for (int j = 0; j < numResponses; j++) {
            cJSON * response = cJSON_GetArrayItem(pResponses, j);
            Response *pRes = new Response();
            pRes->setID(cJSON_GetObjectItem(response, "id")->valueint);
            pRes->setName(strdup(cJSON_GetObjectItem(response, "name")->valuestring));
            pRes->setValid(cJSON_GetObjectItem(response, "valid")->valueint);
            pRes->setOption1(strdup(cJSON_GetObjectItem(response, "option1")->valuestring));
            pRes->setOption2(strdup(cJSON_GetObjectItem(response, "option2")->valuestring));
            pRes->setOption3(strdup(cJSON_GetObjectItem(response, "option3")->valuestring));
            pRes->setOption4(strdup(cJSON_GetObjectItem(response, "option4")->valuestring));
            responses->addObject(pRes);
            pRes->release();
        }
        
        pCat->setResponses(responses);
        m_Categories->addObject(pCat);
        pCat->release();
    }
    
    cJSON_Delete(pRoot);
    
}