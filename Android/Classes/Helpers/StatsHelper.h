//
//  StatsHelper.h
//  ikasikusi
//
//  Created by Asier Fernandez on 17/10/13.
//
//

#ifndef __ikasikusi__StatsHelper__
#define __ikasikusi__StatsHelper__

#include "cocos2d.h"

using namespace cocos2d;

class StatsHelper
{
public:
    int getNumberOfLevelsDone();
    void setOneMoreLevelDone();
    void setDifficulty(int var);
    int getDifficulty();
    long getPoints(float percentage);
    long getPoints();
    void resetStats();
    void setCurrentLevel(int level);
    int getCurrentLevel();
    static StatsHelper* SharedInstance();
private:
    StatsHelper();  // Private so that it can  not be called
    StatsHelper(StatsHelper const&){};             // copy constructor is private
    StatsHelper& operator=(StatsHelper const&){};  // assignment operator is private
    static StatsHelper* m_pInstance;
    
    ~StatsHelper();
    long m_Points;
    int m_LevelsDone;
    int m_Difficulty;
    int m_CurrentLevel;
};

#endif /* defined(__ikasikusi__StatsHelper__) */
