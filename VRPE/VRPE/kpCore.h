#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#ifndef API_EXPORTS
#define JFE_API __declspec(dllexport) 
#else
#define JFE_API __declspec(dllimport)
#endif

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "data\kpLua\lua.hpp"
namespace JackFruitEngine{
	class JFE_API kpCore
	{
	public:
		kpCore(void);
		~kpCore(void);
	};
}
#endif