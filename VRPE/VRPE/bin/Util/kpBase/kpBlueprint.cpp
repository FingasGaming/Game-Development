#include "kpBlueprint.h"


JackFruitEngine::kpBlueprint::kpBlueprint(void)
{
}
JackFruitEngine::kpBlueprint::~kpBlueprint(void)
{
	this->onDestroy();
}
bool JackFruitEngine::kpBlueprint::init(lua_State* l) 
{ 
	if(l != NULL)
	{
		return true;
	}
	return false;
}
bool JackFruitEngine::kpBlueprint::onStart(bool exe)
{
	if(exe)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void JackFruitEngine::kpBlueprint::onDestroy()
{
	
}
void JackFruitEngine::kpBlueprint::update(float delta)
{
}
