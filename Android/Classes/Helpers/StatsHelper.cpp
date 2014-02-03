//
//  StatsHelper.cpp
//  ikasikusi
//
//  Created by Asier Fernandez on 17/10/13.
//
//

#include "StatsHelper.h"

StatsHelper* StatsHelper::m_pInstance = NULL;

StatsHelper* StatsHelper::SharedInstance()
{
    if (!m_pInstance)
    {
        // Only allow one instance of class to be generated.
        m_pInstance = new StatsHelper();
        m_pInstance->m_Points = 0;
        m_pInstance->m_LevelsDone = 0;
        m_pInstance->m_Difficulty = 0;
        m_pInstance->m_CurrentLevel = 0;
    }
    
    return m_pInstance;
}

StatsHelper::StatsHelper() // Constructor
{
    
}

StatsHelper::~StatsHelper() // Destructor
{

}

long StatsHelper::getPoints(float percentage)
{
    switch (m_Difficulty) {
        case 1:
            m_Points = (long)(pow((double)(percentage * m_LevelsDone), 1.5));
            return m_Points;
            break;
        case 2:
            m_Points = (long)(pow((double)(percentage * m_LevelsDone), 2.0) / 10);
            return m_Points;
            break;
        case 3:
            m_Points = (long)(pow((double)(percentage * m_LevelsDone), 2.5) / 100);
            return m_Points;
            break;
        default:
            break;
    }
    return 0;
}

long StatsHelper::getPoints()
{
    return m_Points;
}

void StatsHelper::resetStats()
{
    m_Points = 0;
    m_LevelsDone = 0;
}

void StatsHelper::setDifficulty(int var)
{
    m_Difficulty = var;
}

int StatsHelper::getDifficulty()
{
    return m_Difficulty;
}

void StatsHelper::setCurrentLevel(int level)
{
    m_CurrentLevel = level;
}

int StatsHelper::getCurrentLevel()
{
    return m_CurrentLevel;
}

int StatsHelper::getNumberOfLevelsDone()
{
   return m_LevelsDone;
}

void StatsHelper::setOneMoreLevelDone()
{
    m_LevelsDone++;
}