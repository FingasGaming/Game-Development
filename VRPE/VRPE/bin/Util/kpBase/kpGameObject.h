#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H 

#include "kpBlueprint.h"
#include "../kpMath/kpTransform.h"
#include "kpComponent.h"

#include "../kpMath/camera.h"
#include "kpCamera.h"

namespace JackFruitEngine
{

	class JFE_API kpGameObject : public kpBlueprint
	{
	public:
		kpGameObject();
		~kpGameObject();
		virtual bool init(lua_State* l = NULL);
		virtual bool onStart(bool exe = true);
		virtual void onDestroy();
		virtual void update(float delta = 1);
		virtual void render(kpShader* shader, kpRenderEngine* eng);	
		bool addChild(kpGameObject* child);
		inline kpTransform& getTransform() { return transform; }
		bool addComponent(kpComponent* component)
		{
			if(component != nullptr)
			{
				component->setParent(this);
				components.push_back(component);
				return true;
			}
			return false;
		}
	private:	 
		std::vector<kpGameObject* > children;
		std::vector<kpComponent* > components;	
		kpTransform transform;
	};

}
#endif