#pragma once

#ifndef SANDBOX_GAME_H
#define SANDBOX_GAME_H

#include <kpCore.h>

using namespace JackFruitEngine;


class Game : public kpGame
{
public:
	Game(void);
	~Game(void);

	bool init(lua_State* l, kpWindow* parent);
	bool onStart(bool exe = true);
	void onEvent(SDL_Event _event);
	void onDestroy();
	void update(float delta = 1);
	void render();
	void Execute();
	
	kpSprite* test;
	kpGameObject* obj;
	kpWindow* _parent;
	camera* cam;
};

#endif