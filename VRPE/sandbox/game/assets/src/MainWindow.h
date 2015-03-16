#pragma once

#include <kpCore.h>
using namespace JackFruitEngine;

class MainWindow : public kpWindow
{
public:
	MainWindow(void);
	~MainWindow(void);
	bool init(lua_State* l = NULL);
	void onDestroy();
	void update(float delta = 1);
};

