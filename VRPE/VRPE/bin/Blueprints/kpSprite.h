#pragma once
#ifndef KPSPRITE_H
#define KPSPRITE_H

#include "../Util/kpBase/kpBlueprint.h"
#include "../Util/kpMath/kpVector3f.h"

namespace JackFruitEngine
{
	class JFE_API kpSprite : public kpBlueprint
	{
	protected:
		SDL_Texture* image;
		float x,y,w,h,imgW,imgH, fX, fY, fW,fH,originX,originY;
	public:
		kpSprite(void);
		~kpSprite(void);
		bool init(SDL_Renderer* render, const char* path);
		void setOrigin(float x, float y);
		void onDraw(SDL_Renderer* render);
		void setDemensions(float x, float y, float w, float h);
		void setFrame(float x, float y, float w, float h);

		void setX(float x);
		void setY(float y);
		float getX();
		float getY();
		void setXY(float x, float y);
		void setXY(kpVector3f vec);
		void setFrameXY(float x, float y);
	};
}
#endif