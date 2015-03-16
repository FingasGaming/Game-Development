#include "kpGame.h"


JackFruitEngine::kpGame::kpGame(void)
{
}


JackFruitEngine::kpGame::~kpGame(void)
{
}
bool JackFruitEngine::kpGame::init(lua_State* l){ return true; }
bool JackFruitEngine::kpGame::onStart(bool exe){ return true; }
void JackFruitEngine::kpGame::onEvent(SDL_Event _event){}
void JackFruitEngine::kpGame::onDestroy(){}
void JackFruitEngine::kpGame::update(float delta){}
void JackFruitEngine::kpGame::render(kpRenderEngine* eng){}
void JackFruitEngine::kpGame::Execute(){}