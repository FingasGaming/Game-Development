#include "MainWindow.h"

#include "game.h"


MainWindow::MainWindow(void) : JackFruitEngine::kpWindow()
{
}


MainWindow::~MainWindow(void)
{
}
bool MainWindow::init(lua_State* l)
{
	//JackFruitEngine::kpWindow().init(l);
	//window = loadWindowSettings("bin/config/settings.ini");
	//setupWindowInfo(window);
	this->myWindowSettings("bin/config/settings.ini");
	this->uber = new kpShader("bin/resources/shaders/basic.vs","bin/resources/shaders/basic.fs");

	if(uber == NULL)
	{			
		std::cout << "Unable to create shader" <<"\n";
	}
	Game* game = new Game();
	game->init(l, this);
	JackFruitEngine::kpEngine::setGame(game);
	return true;
}
void MainWindow::onDestroy()
{}
void MainWindow::update(float delta)
{}