#ifndef _MyGame_H
#define _MyGame_H

#include "GameApplication.h"

class MyGame:public GameApplication
{
public:
	MyGame();
	~MyGame();

	void render();
	void update();
	void initScene();
	void destroyScene();
private:


	//matrices
	mat4 m_ViewMatrix;
	mat4 m_ProjMatrix;

	GameObject *m_TestObject;

};
#endif
