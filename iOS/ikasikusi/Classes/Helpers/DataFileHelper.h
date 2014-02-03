//
//  DataFileHelper.h
//  ikasikusi
//
//  Created by Asier Fernandez on 09/10/13.
//
//

#ifndef __ikasikusi__DataFileHelper__
#define __ikasikusi__DataFileHelper__

#include "cocos2d.h"
#include "cJSON.h"

using namespace cocos2d;

class DataFileHelper
{
public:
    CCArray* getCategories();
    static DataFileHelper* SharedInstance();
private:
    DataFileHelper();  // Private so that it can  not be called
    DataFileHelper(DataFileHelper const&){};             // copy constructor is private
    DataFileHelper& operator=(DataFileHelper const&){};  // assignment operator is private
    static DataFileHelper* m_pInstance;

    ~DataFileHelper();
    CCArray *m_Categories;
    void parseDataFile();
};

#endif /* defined(__ikasikusi__DataFileHelper__) */


