#include "kpSprite.h"



JackFruitEngine::kpSprite::kpSprite(void): image(NULL), x(0), y(0),w(0),h(0),imgW(0),imgH(0), fX(0), fY(0), fW(0),fH(0), originX(0), originY(0)
{
}


JackFruitEngine::kpSprite::~kpSprite(void)
{
	if(image)
	{
		SDL_DestroyTexture(image);
	}
}

bool JackFruitEngine::kpSprite::init(SDL_Renderer* render, const char* path)
{
	if(render)
	{
		
		image = IMG_LoadTexture(render, path);
		if(image)
		{
			int _w = 0;
			int _h = 0;
			SDL_QueryTexture(image, NULL, NULL, &_w, &_h);
			imgW = _w;
			imgH = _h;
		}

		return true;
	}
	return false;
}

void JackFruitEngine::kpSprite::setOrigin(float x, float y)
{
	originX = x;
	originY = y;
}

void JackFruitEngine::kpSprite::onDraw(SDL_Renderer* render)
{
	SDL_Rect c; SDL_Rect r;
	r.x = x; r.y = y; r.w = w; r.h = h;	
	c.x = fX; c.y = fY; c.w = fW; c.h = fH;
	SDL_RenderCopy(render, image, &c,&r);
}

void JackFruitEngine::kpSprite::setDemensions(float _x, float _y, float _w, float _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	imgW = _w;
	fW = _w;
	imgH = _h;
	fH = _h;
}
void JackFruitEngine::kpSprite::setFrame(float _x, float _y, float _w, float _h)
{
		fX = _x - originX;
		fY = _y - originY;
		w = _w + originX;
		fW = _w + originX;
		h = _h + originY;
		fH = _h + originY;
}
void JackFruitEngine::kpSprite::setX(float x)
{
		x = x - originX;
}
void JackFruitEngine::kpSprite::setY(float y)
{
	y = y - originY;
}
float JackFruitEngine::kpSprite::getX()
{
		return x - originX;
}
float JackFruitEngine::kpSprite::getY()
{
		return y - originY;
}
void JackFruitEngine::kpSprite::setXY(float x, float y)
{
	setX(x);
	setY(y);
}
void JackFruitEngine::kpSprite::setXY(kpVector3f vec)
{
	setX(vec.x);
	setY(vec.y);
}
void JackFruitEngine::kpSprite::setFrameXY(float x, float y)
{
		fX = x - originX;
		fY = y - originY;
}