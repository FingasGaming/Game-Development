#include "game.h"


Game::Game(void): kpGame()
{
}


Game::~Game(void)
{
}
bool Game::init(lua_State* l, kpWindow* parent)
{
	if(parent)
	{
		_parent = parent;
		test = new kpSprite();
		test->init(_parent->getRenderer(), "bin/resources/image.png");
		test->setOrigin(96/2, 128/2);
		test->setFrame(0,0, 96, 128);

		obj = new kpGameObject();
		kpCamera* cam = new kpCamera(50, _parent->getWidth()/_parent->getHeight(), 1, 1000);

		obj->getTransform().setTranslation(kpVector3f(0,0,0));
		//cam->setAsMain();
	}

	return true;
}
bool Game::onStart(bool exe)
{
	return true;
}
void Game::onEvent(SDL_Event _event)
{}
void Game::onDestroy()
{
	delete obj;
}
void Game::update(float delta)
{}
void Game::render()
{
	test->onDraw((_parent->getRenderer()));

	obj->render(_parent->uber, kpEngine::getRenderer());
}
void Game::Execute()
{}