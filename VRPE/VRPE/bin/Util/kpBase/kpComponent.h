#pragma once
#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H

#ifndef API_EXPORTS
#define JFE_API __declspec(dllexport) 
#else
#define JFE_API __declspec(dllimport)
#endif

#include "../kpSystem/kpLua/lua.hpp"
#include "../kpMath/kpTransform.h"

namespace JackFruitEngine
{
	class JFE_API kpBlueprint;
	class JFE_API kpGameObject;
	class JFE_API kpRenderEngine;
	class JFE_API kpShader;	
	class JFE_API kpTransform;

	class JFE_API kpComponent
	{
	private:
		kpGameObject* parent;
		kpTransform trans;
	public:
		kpComponent(void);
		~kpComponent(void);
		friend class kpGameObject;
		friend class kpBlueprint;		
		virtual bool onStart(bool exe = true)
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
		virtual bool init()
		{
			return true;
		}
		virtual bool init(lua_State* L)
		{
			if(L != NULL)
			{
				return true;
			}
			return false;
		}
		void setParent(kpGameObject* parent = NULL)
		{
			this->parent = parent;
		}
		void setTransform(kpTransform _parent)
		{
			this->trans = _parent;
		}
		virtual void onDestroy(){}
		kpTransform& getTransform(){ return trans;}
		bool exec(bool exe = true)
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
		virtual void update(float delta){}
		virtual void render(kpShader* shader, kpRenderEngine* eng){}
	};
}
#endif