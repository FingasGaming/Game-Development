#include "kpGameObject.h"


JackFruitEngine::kpGameObject::kpGameObject() : kpBlueprint()
{

}
JackFruitEngine::kpGameObject::~kpGameObject()
{
	for(unsigned int i = 0; i < children.size(); i++)
		if(children[i])
			delete children[i];
}
void JackFruitEngine::kpGameObject::render(kpShader* shader, kpRenderEngine* eng)
{
	for(int i = 0; i < components.size(); i++)
	{
		components[i]->render(shader, eng);
	}
	for(int i = 0; i < children.size(); i++)
	{
		children[i]->render(shader, eng);
	}
}
bool JackFruitEngine::kpGameObject::addChild(kpGameObject* child)
{
	if(child != nullptr)
	{
		children.push_back(child);
		child->getTransform().setParent(&transform);
		return true;
	}
	return false;
}
bool JackFruitEngine::kpGameObject::init(lua_State* l) 
{ 
	if(l != NULL)
	{
		return true;
	}
	return false;
}
bool JackFruitEngine::kpGameObject::onStart(bool exe)
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
void JackFruitEngine::kpGameObject::onDestroy()
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		delete components[i];
	}
}
void JackFruitEngine::kpGameObject::update(float delta)
{
}
