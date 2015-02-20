#pragma once
#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H

#ifndef API_EXPORTS
#define JFE_API __declspec(dllexport) 
#else
#define JFE_API __declspec(dllimport)
#endif

namespace JackFruitEngine{
	class JFE_API kpComponent
	{
	public:
		kpComponent(void);
		~kpComponent(void);
	};
}
#endif