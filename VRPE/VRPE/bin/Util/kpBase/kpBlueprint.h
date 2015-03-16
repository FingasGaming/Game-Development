#pragma once
#ifndef KPBLUEPRINT_H
#define KPBLUEPRINT_H

#include <vector>
#include <map>
#include "kpScript.h"
#include "../kpSystem/kpStructure.h"

namespace JackFruitEngine
{
	class JFE_API kpBlueprint
	{
	protected:
	public:
		kpBlueprint(void);
		~kpBlueprint(void);
		virtual bool init(lua_State* l = NULL);
		virtual bool onStart(bool exe = true);
		virtual void onDestroy();
		virtual void update(float delta = 1);
	};
}
#endif