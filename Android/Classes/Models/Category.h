//
//  Category.h
//  ikasikusi
//
//  Created by Asier Fernandez on 08/10/13.
//
//

#ifndef Ikasikusi_Category_h
#define Ikasikusi_Category_h

#include "cocos2d.h"

USING_NS_CC;

class Category : public CCObject {
public:
    
    Category(){};
    ~Category()
    {
        CC_SAFE_FREE(m_Name);
        CC_SAFE_RELEASE(m_Responses);
    };
    
    CC_SYNTHESIZE(int, m_ID, ID);
    CC_SYNTHESIZE(char*, m_Name, Name);
    //CC_SYNTHESIZE_RETAIN(CCArray*, m_Responses, Responses);
    CCArray* m_Responses;
    virtual void setResponses(CCArray* var){ m_Responses = var; m_Responses->retain(); }
    virtual CCArray* getResponses(){ return m_Responses; }
};


#endif