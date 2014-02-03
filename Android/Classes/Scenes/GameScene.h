#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameScene : public cocos2d::CCScene
{
public:
    GameScene();
	~GameScene();
    
	virtual bool init();
    void setColumns(int columns) { m_columns = columns; }
	void setRows(int rows) { m_rows = rows; }
    int getColumns() const { return m_columns; }
	int getRows() const { return m_rows; }
	CREATE_FUNC(GameScene);
private:
    int m_columns;
    int m_rows;
    int m_time;
    int m_responseNumber;
};

#endif // __GAME_SCENE_H__