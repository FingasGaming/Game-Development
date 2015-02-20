#include "kpEngine.h"
JackFruitEngine::kpEngine* JackFruitEngine::kpEngine::engine = nullptr;

JackFruitEngine::kpEngine::kpEngine(void)
{
}


JackFruitEngine::kpEngine::~kpEngine(void)
{
}
//Function: retrieve engine
JackFruitEngine::kpEngine* JackFruitEngine::kpEngine::getEngine()
{
	if(!engine)
	{
		engine = new kpEngine();
	}
	return engine;
}
//Function: init engine
bool JackFruitEngine::kpEngine::initialise()
{
	return true;
}
//Function: initialise graphics
bool JackFruitEngine::kpEngine::initialiseGraphics()
{
	return true;
}
//Function: initialise physics
bool JackFruitEngine::kpEngine::initialisePhysics()
{
	return true;
}
//Function: update engine
void JackFruitEngine::kpEngine::update()
{

}
//Function: render game world
void JackFruitEngine::kpEngine::draw()
{}