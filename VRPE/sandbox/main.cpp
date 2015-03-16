
#include <kpCore.h>
#include "game\assets\src\MainWindow.h"

using namespace JackFruitEngine;

int main(int args, char** argv)
{
	kpApplication app;

	//testing lua game files
	//return app.run("main.lua", LUA_DEFAULT);
	//return app.run("bin/scripts/main.lua", LUA_CUSTUM);
	//testing kpGame class

	//kpGame* game = new kpGame();
	//return app.run(game, CPP_DEFAULT);
	//kpWindow *win = new kpWindow();
	kpWindow* win = new MainWindow();
	return app.run(win);
}