#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#ifndef API_EXPORTS
#define JFE_API __declspec(dllexport) 
#else
#define JFE_API __declspec(dllimport)
#endif
namespace JackFruitEngine{
	class kpCore
	{
	public:
		kpCore(void);
		~kpCore(void);
	};
}
#endif