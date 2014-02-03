//
//  Response.h
//  ikasikusi
//
//  Created by Asier Fernandez on 08/10/13.
//
//

#ifndef Ikasikusi_Response_h
#define Ikasikusi_Response_h

#include "cocos2d.h"

USING_NS_CC;

class Response : public CCObject {
public:
    
    Response(){};
    ~Response()
    {
        CC_SAFE_FREE(m_Name);
        CC_SAFE_FREE(m_Option1);
        CC_SAFE_FREE(m_Option2);
        CC_SAFE_FREE(m_Option3);
        CC_SAFE_FREE(m_Option4);
    };
    
    CC_SYNTHESIZE(int, m_ID, ID);
    CC_SYNTHESIZE(char*, m_Name, Name);
    CC_SYNTHESIZE(int, m_Valid, Valid);
    CC_SYNTHESIZE(char*, m_Option1, Option1);
    CC_SYNTHESIZE(char*, m_Option2, Option2);
    CC_SYNTHESIZE(char*, m_Option3, Option3);
    CC_SYNTHESIZE(char*, m_Option4, Option4);    
};


#endif