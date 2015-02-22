#include "bin\Util\kpBindLua.h"
#include "bin\Util\kpMath\kpTransform.h"
#include "bin\Util\kpEngine.h"
#include "bin\Util\kpSystem\kpLog.h"

using namespace JackFruitEngine;
//SDL to LUA bindings
int LUA_INITGL(lua_State* l)
{
	//kpBindLua binder(l);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_CULL_FACE);
	glEnable(GL_FRONT_FACE);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return 0;
}
int LUA_regulateFPS(lua_State* l)
{
	kpBindLua binder(l);
	float rate = (float)binder.checknumber(1); 
	int ticks = binder.checkinteger(2);

	if(1000/rate > SDL_GetTicks() - ticks)
	{
		SDL_Delay((Uint32)(1000/rate - ticks));
	}
	return 0;
}
int LUA_GETCURSOR(lua_State* l)
{
	kpBindLua binder(l);
	int x, y;
	SDL_GetMouseState(&x, &y);
	kpVector3f* vec = new kpVector3f((float)x, (float)y);
	binder.pushusertype(vec, "kpVector3f");
	return 1;
}
int LUA_GETTICK(lua_State* l)
{
	kpBindLua binder(l);
	int tick = SDL_GetTicks();

	binder.pushinterger(tick);
	return 1;
}
int LUA_SHOWCURSOR(lua_State* l)
{
	kpBindLua binder(l);
	bool num = binder.checkbool(1);
	if(num == true)
	{
		SDL_ShowCursor(SDL_ENABLE);
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
	}
	return 0;
}
int LUA_QSDL(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Event* e = (SDL_Event*)binder.checkusertype(1, "SDL_Event");
	if(e->type == SDL_QUIT)
	{
		binder.pushboolean(true);
	}
	else
	{
		binder.pushboolean(false);
	}
	return 1;
}
int LUA_SDL_PollEvent(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PollEvent((SDL_Event*)binder.checkusertype(1, "SDL_Event"));
	return 0;
}
int LUA_SDL_checkKeyDown(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Event *h = ((SDL_Event*)binder.checkusertype(1, "SDL_Event"));

	if( h->type == SDL_KEYDOWN )
	{
		if( h->key.keysym.sym == binder.checkinteger(2) )
		{
			binder.pushboolean(1);
		}
		else
		{
			binder.pushboolean(0);
		}
	}

	return 1;
}
int LUA_SDL_checkKeyUP(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Event *h = ((SDL_Event*)binder.checkusertype(1, "SDL_Event"));

	if( h->type == SDL_KEYUP )
	{
		if( h->key.keysym.sym == binder.checkinteger(2) )
		{
			binder.pushboolean(1);
		}
		else
		{
			binder.pushboolean(0);
		}
	}

	return 1;
}
int LUA_SDL_checkButtonDown(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Event *h = ((SDL_Event*)binder.checkusertype(1, "SDL_Event"));

	if( h->type == SDL_MOUSEBUTTONDOWN )
	{
		if( h->button.button == binder.checkinteger(2) )
		{
			binder.pushboolean(1);
		}
		else
		{
			binder.pushboolean(0);
		}
	}

	return 1;
}
int LUA_SDL_checkButtonUP(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Event *h = ((SDL_Event*)binder.checkusertype(1, "SDL_Event"));

	if( h->type == SDL_MOUSEBUTTONUP )
	{
		if( h->button.button == binder.checkinteger(2) )
		{
			binder.pushboolean(1);
		}
		else
		{
			binder.pushboolean(0);
		}
	}

	return 1;
}
int LUA_SDL_checkKeyState(lua_State* l)
{
	kpBindLua binder(l);
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if( keyState[binder.checkinteger(1)])
	{
		binder.pushboolean(1);
	}
	else
	{
		binder.pushboolean(0);
	}

	return 1;
}
int LUA_SDL_QueryTexture(lua_State* l)
{
	kpBindLua binder(l);
	int w = 0;
	int h = 0;
	SDL_QueryTexture((SDL_Texture*)binder.checkusertype(1, "SDL_Texture"), NULL, NULL, &w, &h);
	//need to send back vec2
	binder.pushusertype(new kpVector3f((float)w,(float)h), "kpVector3f");
	return 1;
}
int LUA_SDL_RenderCopy(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect r;
	r.x = binder.checkinteger(3);
	r.y = binder.checkinteger(4);
	r.w = binder.checkinteger(5);
	r.h = binder.checkinteger(6);
	SDL_RenderCopy((SDL_Renderer*)binder.checkusertype(1, "SDL_Renderer"), (SDL_Texture*)binder.checkusertype(2, "SDL_Texture"), NULL, &r);
	return 0;
}
int LUA_SDL_RenderCrop(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect r;
	r.x = binder.checkinteger(3);
	r.y = binder.checkinteger(4);
	r.w = binder.checkinteger(5);
	r.h = binder.checkinteger(6);
	SDL_RenderCopy((SDL_Renderer*)binder.checkusertype(1, "SDL_Renderer"), (SDL_Texture*)binder.checkusertype(2, "SDL_Texture"), &r, NULL);
	return 0;
}
int LUA_SDL_RenderCopyCrop(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect c;
	c.x = binder.checkinteger(3);
	c.y = binder.checkinteger(4);
	c.w = binder.checkinteger(5);
	c.h = binder.checkinteger(6);
	SDL_Rect r;
	r.x = binder.checkinteger(7);
	r.y = binder.checkinteger(8);
	r.w = binder.checkinteger(9);
	r.h = binder.checkinteger(10);
	SDL_RenderCopy((SDL_Renderer*)binder.checkusertype(1, "SDL_Renderer"), (SDL_Texture*)binder.checkusertype(2, "SDL_Texture"), &c, &r);
	return 0;
}
int LUA_IMG_LoadTexture(lua_State* l)
{
	kpBindLua binder(l);
	binder.pushusertype(IMG_LoadTexture((SDL_Renderer*)binder.checkusertype(1, "SDL_Renderer"), binder.checkstring(2)),"SDL_Texture");
	return 1;
}
int LUA_CreateWindow(lua_State* l)
{
	kpBindLua binder(l);
	binder.pushusertype(SDL_CreateWindow(binder.checkstring(1), binder.checkinteger(2), binder.checkinteger(3), binder.checkinteger(4), binder.checkinteger(5), SDL_WINDOW_OPENGL | (Uint32)binder.checkinteger(6)), "SDL_Window");
	return 1;
}
int LUA_CreateGLContext(lua_State* l)
{
	kpBindLua binder(l);
	binder.pushusertype(SDL_GL_CreateContext((SDL_Window*)binder.checkusertype(1, "SDL_Window")), "SDL_GLContext");
	return 1;
}
int LUA_CreateRenderer(lua_State* l)
{
	kpBindLua binder(l);
	binder.pushusertype(SDL_CreateRenderer((SDL_Window*)binder.checkusertype(1, "SDL_Window"), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), "SDL_Renderer");
	return 1;
}
int LUA_CreateTargetRenderer(lua_State* l)
{
	kpBindLua binder(l);
	binder.pushusertype(SDL_CreateRenderer((SDL_Window*)binder.checkusertype(1, "SDL_Window"), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE), "SDL_Renderer");
	return 1;
}
int LUA_ClearRender(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Renderer* num = (SDL_Renderer*)binder.checkusertype(1, "SDL_Renderer");	
	SDL_RenderClear(num);
	return 0;
}
int LUA_FlipRender(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Renderer* num = (SDL_Renderer*)binder.checkusertype(1, "SDL_Renderer");	
	SDL_RenderPresent(num);
	return 0;
}
int LUA_SDL_Renderer(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Renderer* h;
	binder.pushusertype(&h, "SDL_Renderer");
	return 1;
}
int LUA_SDL_Renderer_KILL(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Renderer* h = (SDL_Renderer*) binder.checkusertype(1,"SDL_Renderer");
	SDL_DestroyRenderer(h);
	return 0;
}
int LUA_SDL_Renderer_Flip(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Renderer* h = (SDL_Renderer*) binder.checkusertype(1,"SDL_Renderer");
	SDL_RenderPresent(h);
	return 0;
}
int LUA_SDL_Renderer_DrawRect(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Renderer* h = (SDL_Renderer*) binder.checkusertype(1,"SDL_Renderer");	
	SDL_Rect r;
	r.x = binder.checkinteger(2);
	r.y = binder.checkinteger(3);
	r.w = binder.checkinteger(4);
	r.h = binder.checkinteger(5);
	SDL_RenderDrawRect(h, &r);
	return 0;
}
int LUA_SDL_Renderer_Copy(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect r;
	r.x = binder.checkinteger(3);
	r.y = binder.checkinteger(4);
	r.w = binder.checkinteger(5);
	r.h = binder.checkinteger(6);
	SDL_RenderCopy((SDL_Renderer*)binder.checkusertype(1, "SDL_Renderer"), (SDL_Texture*)binder.checkusertype(2, "SDL_Texture"), NULL, &r);
	return 0;
}
int LUA_SDL_Renderer_Crop(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect r;
	r.x = binder.checkinteger(3);
	r.y = binder.checkinteger(4);
	r.w = binder.checkinteger(5);
	r.h = binder.checkinteger(6);
	SDL_RenderCopy((SDL_Renderer*)binder.checkusertype(1, "SDL_Renderer"), (SDL_Texture*)binder.checkusertype(2, "SDL_Texture"), &r, NULL);
	return 0;
}
int LUA_SDL_Renderer_CopyCrop(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect c;
	c.x = binder.checkinteger(3);
	c.y = binder.checkinteger(4);
	c.w = binder.checkinteger(5);
	c.h = binder.checkinteger(6);
	SDL_Rect r;
	r.x = binder.checkinteger(7);
	r.y = binder.checkinteger(8);
	r.w = binder.checkinteger(9);
	r.h = binder.checkinteger(10);
	SDL_RenderCopy((SDL_Renderer*)binder.checkusertype(1, "SDL_Renderer"), (SDL_Texture*)binder.checkusertype(2, "SDL_Texture"), &c, &r);
	return 0;
}
int LUA_SDL_Renderer_DrawColor(lua_State* l)
{
	kpBindLua binder(l);
	SDL_SetRenderDrawColor((SDL_Renderer*)binder.checkusertype(1, "SDL_Renderer"), binder.checkinteger(2),binder.checkinteger(3), binder.checkinteger(4), binder.checkinteger(5));
	return 0;
}
int LUA_SDL_Renderer_Clear(lua_State* l)
{
	kpBindLua binder(l);
	SDL_RenderClear((SDL_Renderer*)binder.checkusertype(1, "SDL_Renderer"));
	return 0;
}
static const luaL_Reg SDL_Renderer_lib[] = {
	{"new", LUA_SDL_Renderer},
	{"kill", LUA_SDL_Renderer_KILL},
	{"flip", LUA_SDL_Renderer_Flip},
	{"drawRect", LUA_SDL_Renderer_DrawRect},
	{"copy", LUA_SDL_Renderer_Copy},
	{"crop", LUA_SDL_Renderer_Crop},
	{"copyCrop", LUA_SDL_Renderer_CopyCrop},
	{"setDrawColor", LUA_SDL_Renderer_DrawColor},
	{"clear", LUA_SDL_Renderer_Clear},
	{NULL, NULL}
};
//
int SDL_Renderer_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("SDL_Renderer", "", SDL_Renderer_lib, LUA_SDL_Renderer_KILL);
	return 1;
}
int LUA_SDL_GLContext(lua_State* l)
{
	kpBindLua binder(l);
	SDL_GLContext* h;
	binder.pushusertype(&h, "SDL_GLContext");
	return 1;
}
int LUA_SDL_GLContext_KILL(lua_State* l)
{
	kpBindLua binder(l);
	SDL_GLContext* h = (SDL_GLContext*) binder.checkusertype(1,"SDL_GLContext");
	SDL_GL_DeleteContext(h);
	return 0;
}
static const luaL_Reg SDL_GLContext_lib[] = {
	{"new", LUA_SDL_GLContext},
	{"kill", LUA_SDL_GLContext_KILL},
	{NULL, NULL}
};
//
int SDL_GLContext_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("SDL_GLContext", "", SDL_GLContext_lib, LUA_SDL_GLContext_KILL);
	return 1;
}
int LUA_SDL_Window(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Window* h;
	binder.pushusertype(&h, "SDL_Window");
	return 1;
}
int LUA_SDL_Window_KILL(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Window* h = (SDL_Window*) binder.checkusertype(1,"SDL_Window");
	SDL_DestroyWindow(h);
	return 0;
}
int LUA_SDL_Window_clearRect(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Window* h = (SDL_Window*) binder.checkusertype(1,"SDL_Window");
	SDL_FillRect(SDL_GetWindowSurface(h), NULL, 0);
	return 0;
}
int LUA_SDL_Window_UpdateWindow(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Window* h = (SDL_Window*) binder.checkusertype(1,"SDL_Window");
	SDL_UpdateWindowSurface(h);
	return 0;
}
int LUA_SDL_Window_Surface(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Window* h = (SDL_Window*) binder.checkusertype(1,"SDL_Window");
	binder.pushusertype(SDL_GetWindowSurface(h), "SDL_Surface");
	return 0;
}
static const luaL_Reg SDL_Window_lib[] = {
	{"new", LUA_SDL_Window},
	{"kill", LUA_SDL_Window_KILL},
	{"clearRect", LUA_SDL_Window_clearRect},
	{"getSurface", LUA_SDL_Window_Surface},
	{"updateWindow", LUA_SDL_Window_UpdateWindow},
	{NULL, NULL}
};
//
int SDL_Window_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("SDL_Window", "", SDL_Window_lib, LUA_SDL_Window_KILL);
	return 1;
}
int LUA_SDL_Event(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Event* h = new SDL_Event();
	binder.pushusertype(h, "SDL_Event");
	return 1;
}
int LUA_SDL_Event_KILL(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Event* h = (SDL_Event*) binder.checkusertype(1,"SDL_Event");
	delete h;
	return 0;
}
int LUA_SDL_Event_type(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Event* h = new SDL_Event();
	binder.pushusertype(&h->type, "Uinit32");
	return 1;
}
int LUA_SDL_Event_key(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Event* h = new SDL_Event();
	binder.pushusertype(&h->key.keysym.sym, "Sint32");
	return 1;
}
int LUA_SDL_Event_button(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Event* h = new SDL_Event();
	binder.pushusertype(&h->button.button, "Uint8");
	return 1;
}
static const luaL_Reg SDL_Event_lib[] = {
	{"new", LUA_SDL_Event},
	{"kill", LUA_SDL_Event_KILL},
	{"eType", LUA_SDL_Event_type},
	{"key", LUA_SDL_Event_key},
	{"button", LUA_SDL_Event_button},
	{NULL, NULL}
};
//
int SDL_Event_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("SDL_Event", "", SDL_Event_lib, LUA_SDL_Event_KILL);
	return 1;
}
int LUA_SDL_Texture(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Texture* h;
	binder.pushusertype(&h, "SDL_Texture");
	return 1;
}
int LUA_SDL_Texture_KILL(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Texture* h = (SDL_Texture*) binder.checkusertype(1,"SDL_Texture");
	SDL_DestroyTexture(h);
	return 0;
}
static const luaL_Reg SDL_Texture_lib[] = {
	{"new", LUA_SDL_Texture},
	{"kill", LUA_SDL_Texture_KILL},
	{NULL, NULL}
};
//
int SDL_Texture_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("SDL_Texture", "", SDL_Texture_lib, LUA_SDL_Texture_KILL);
	return 1;
}
int LUA_SDL_RECT(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect* h = new SDL_Rect();
	binder.pushusertype(h, "SDL_Rect");
	return 1;
}
int LUA_SDL_RECT_KILL(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect* h =  (SDL_Rect*) binder.checkusertype(1,"SDL_Rect");
	delete h;
	return 0;
}
int LUA_SDL_RECT_x(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect* h =  (SDL_Rect*) binder.checkusertype(1,"SDL_Rect");
	Sint16 x = h->x;
	binder.pushusertype(&x, "Sint16");
	return 1;
}
int LUA_SDL_RECT_y(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect* h =  (SDL_Rect*) binder.checkusertype(1,"SDL_Rect");
	Sint16 x = h->y;
	binder.pushusertype(&x, "Sint16");
	return 1;
}
int LUA_SDL_RECT_w(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect* h =  (SDL_Rect*) binder.checkusertype(1,"SDL_Rect");
	Uint16 x = h->w;
	binder.pushusertype(&x, "Uint16");
	return 1;
}
int LUA_SDL_RECT_h(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect* h =  (SDL_Rect*) binder.checkusertype(1,"SDL_Rect");
	Uint16 x = h->h;
	binder.pushusertype(&x, "Uint16");
	return 1;
}
int LUA_SDL_RECT_setx(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect* h =  (SDL_Rect*) binder.checkusertype(1,"SDL_Rect");
	//h->x = *(Sint16*)binder.checkusertype(2, "Sint16");
	Sint16* x = new Sint16((Sint16)binder.checknumber(2));
	h->w = *x;
	return 0;
}
int LUA_SDL_RECT_sety(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect* h =  (SDL_Rect*) binder.checkusertype(1,"SDL_Rect");
	//h->y = *(Sint16*)binder.checkusertype(2, "Sint16");
	Sint16* x = new Sint16((Sint16)binder.checknumber(2));
	h->w = *x;
	return 0;
}
int LUA_SDL_RECT_setw(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect* h =  (SDL_Rect*) binder.checkusertype(1,"SDL_Rect");
	Uint16* x = new Uint16((Uint16)binder.checknumber(2));
	h->w = *x;
	return 0;
}
int LUA_SDL_RECT_seth(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Rect* h =  (SDL_Rect*) binder.checkusertype(1,"SDL_Rect");
	//h->h = *(Uint16*)binder.checkusertype(2, "Uint16");
	Uint16* x = new Uint16((Uint16)binder.checknumber(2));
	h->w = *x;
	return 0;
}
static const luaL_Reg SDL_RECT_lib[] = {
	{"new", LUA_SDL_RECT},
	{"kill", LUA_SDL_RECT_KILL},
	{"x", LUA_SDL_RECT_x},
	{"y", LUA_SDL_RECT_y},
	{"w", LUA_SDL_RECT_w},
	{"h", LUA_SDL_RECT_h},
	{"setX", LUA_SDL_RECT_setx},
	{"setY", LUA_SDL_RECT_sety},
	{"setW", LUA_SDL_RECT_setw},
	{"setH", LUA_SDL_RECT_seth},
	{NULL, NULL}
};
//
int SDL_RECT_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("SDL_Rect", "", SDL_RECT_lib, LUA_SDL_RECT_KILL);
	return 1;
}
int LUA_SDL_COLOR(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Color* h = new SDL_Color();
	binder.pushusertype(h, "SDL_Color");
	return 1;
}
int LUA_SDL_COLOR_KILL(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Color* h = (SDL_Color*) binder.checkusertype(1,"SDL_Color");
	delete h;
	return 0;
}
int LUA_SDL_COLOR_r(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Color* h =  (SDL_Color*) binder.checkusertype(1,"SDL_Color");
	Uint8 x = h->r;
	binder.pushusertype(&x, "Uint8");
	return 1;
}
int LUA_SDL_COLOR_g(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Color* h =  (SDL_Color*) binder.checkusertype(1,"SDL_Color");
	Uint8 x = h->g;
	binder.pushusertype(&x, "Uint8");
	return 1;
}
int LUA_SDL_COLOR_b(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Color* h =  (SDL_Color*) binder.checkusertype(1,"SDL_Color");
	Uint8 x = h->b;
	binder.pushusertype(&x, "Uint8");
	return 1;
}
static const luaL_Reg SDL_COLOR_lib[] = {
	{"new", LUA_SDL_COLOR},
	{"kill", LUA_SDL_COLOR_KILL},
	{"r", LUA_SDL_COLOR_r},
	{"g", LUA_SDL_COLOR_g},
	{"b", LUA_SDL_COLOR_b},
	{NULL, NULL}
};
//
int SDL_COLOR_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("SDL_Color", "", SDL_COLOR_lib, LUA_SDL_COLOR_KILL);
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_KILL(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*) binder.checkusertype(1,"SDL_PixelFormat");
	delete h;
	return 0;
}
int LUA_SDL_PIXEL_FORMAT(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = new SDL_PixelFormat();
	binder.pushusertype(h, "SDL_PixelFormat");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_Amask(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint32 a = h->Amask;
	binder.pushusertype(&a, "Uint32");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_Ashift(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint8 a = h->Ashift;
	binder.pushusertype(&a, "Uint8");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_Aloss(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint8 a = h->Aloss;
	binder.pushusertype(&a, "Uint8");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_Bmask(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint32 a = h->Bmask;
	binder.pushusertype(&a, "Uint32");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_Bshift(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint8 a = h->Bshift;
	binder.pushusertype(&a, "Uint8");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_Bloss(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint8 a = h->Bloss;
	binder.pushusertype(&a, "Uint8");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_Gmask(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint32 a = h->Gmask;
	binder.pushusertype(&a, "Uint32");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_Gshift(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint8 a = h->Gshift;
	binder.pushusertype(&a, "Uint8");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_Gloss(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint8 a = h->Gloss;
	binder.pushusertype(&a, "Uint8");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_Rmask(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint32 a = h->Rmask;
	binder.pushusertype(&a, "Uint32");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_Rshift(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint8 a = h->Rshift;
	binder.pushusertype(&a, "Uint8");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_Rloss(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint8 a = h->Rloss;
	binder.pushusertype(&a, "Uint8");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_BitsPerPixel(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint8 a = h->BitsPerPixel;
	binder.pushusertype(&a, "Uint8");
	return 1;
}
int LUA_SDL_PIXEL_FORMAT_BytesPerPixel(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* h = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint8 a = h->BytesPerPixel;
	binder.pushusertype(&a, "Uint8");
	return 1;
}
static const luaL_Reg SDL_PIXEL_FORMAT_lib[] = {
	{"new", LUA_SDL_PIXEL_FORMAT},
	{"kill", LUA_SDL_PIXEL_FORMAT_KILL},
	{"Amask", LUA_SDL_PIXEL_FORMAT_Amask},
	{"Ashift", LUA_SDL_PIXEL_FORMAT_Ashift},
	{"Aloss", LUA_SDL_PIXEL_FORMAT_Aloss},
	{"Bmask", LUA_SDL_PIXEL_FORMAT_Bmask},
	{"Bshift", LUA_SDL_PIXEL_FORMAT_Bshift},
	{"Bloss", LUA_SDL_PIXEL_FORMAT_Bloss},
	{"Gmask", LUA_SDL_PIXEL_FORMAT_Gmask},
	{"Gshift", LUA_SDL_PIXEL_FORMAT_Gshift},
	{"Gloss", LUA_SDL_PIXEL_FORMAT_Gloss},
	{"Rmask", LUA_SDL_PIXEL_FORMAT_Rmask},
	{"Rshift", LUA_SDL_PIXEL_FORMAT_Rshift},
	{"Rloss", LUA_SDL_PIXEL_FORMAT_Rloss},
	{"BitsPerPixel", LUA_SDL_PIXEL_FORMAT_BitsPerPixel},
	{"BytesPerPixel", LUA_SDL_PIXEL_FORMAT_BytesPerPixel},
	{NULL, NULL}
};
//
int SDL_PIXEL_FORMAT_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("SDL_PixelFormat", "", SDL_PIXEL_FORMAT_lib, LUA_SDL_PIXEL_FORMAT_KILL);
	return 1;
}
int LUA_SDL_SURFACE(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* h = new SDL_Surface();
	binder.pushusertype(h, "SDL_Surface");
	return 1;
}
int LUA_SDL_SURFACE_KILL(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* h = (SDL_Surface*) binder.checkusertype(1,"SDL_Surface");
	SDL_FreeSurface(h);
	/*if(h)
	{
		delete h;
	}*/
	return 0;
}
int LUA_SDL_SURFACE_format(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* h = (SDL_Surface*)binder.checkusertype(1, "SDL_Surface");
	SDL_PixelFormat *f = h->format;
	binder.pushusertype(f, "SDL_PixelFormat");
	return 1;
}
int LUA_SDL_SURFACE_flags(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* h = (SDL_Surface*)binder.checkusertype(1,"SDL_Surface");
	Uint32 a = h->flags;
	binder.pushusertype(&a, "Uint32");
	return 1;
}
int LUA_SDL_SURFACE_w(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* h = (SDL_Surface*)binder.checkusertype(1,"SDL_Surface");
	int a = h->w;
	binder.pushinterger(a);
	return 1;
}
int LUA_SDL_SURFACE_h(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* h = (SDL_Surface*)binder.checkusertype(1,"SDL_Surface");
	int a = h->h;
	binder.pushinterger(a);
	return 1;
}
int LUA_SDL_SURFACE_pitch(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* h = (SDL_Surface*)binder.checkusertype(1,"SDL_Surface");
	Uint16 a = h->pitch;
	binder.pushusertype(&a, "Uint16");
	return 1;
}
int LUA_SDL_SURFACE_pixels(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* h = (SDL_Surface*)binder.checkusertype(1,"SDL_Surface");
	void* a = h->pixels;
	//binder.pushusertype(&a, "Uint32");
	return 0;
}
int LUA_SDL_SURFACE_clip_rect(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* h = (SDL_Surface*)binder.checkusertype(1,"SDL_Surface");
	SDL_Rect a = h->clip_rect;
	binder.pushusertype(&a, "SDL_Rect");
	return 1;
}
static const luaL_Reg SDL_SURFACE_lib[] = {
	{"new", LUA_SDL_SURFACE},
	{"kill", LUA_SDL_SURFACE_KILL},
	{"format", LUA_SDL_SURFACE_format},
	{"flags", LUA_SDL_SURFACE_flags},
	{"w", LUA_SDL_SURFACE_w},
	{"h", LUA_SDL_SURFACE_h},
	{"pitch", LUA_SDL_SURFACE_pitch},
	{"clip_rect", LUA_SDL_SURFACE_clip_rect},
	{NULL, NULL}
};
//
int SDL_SURFACE_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("SDL_Surface", "", SDL_SURFACE_lib, LUA_SDL_SURFACE_KILL);
	return 1;
}
int LUA_SDL_MAPRGB(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* format = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint8 *r = new Uint8(binder.checkinteger(2));
	Uint8 *g = new Uint8(binder.checkinteger(3));
	Uint8 *b = new Uint8(binder.checkinteger(4));
	Uint32 h = SDL_MapRGB(format, *r, *g, *b);
	binder.pushusertype(&h, "Uint32");
	return 1;
}
int LUA_SDL_MAPRGBA(lua_State* l)
{
	kpBindLua binder(l);
	SDL_PixelFormat* format = (SDL_PixelFormat*)binder.checkusertype(1,"SDL_PixelFormat");
	Uint8 *r = new Uint8(binder.checkinteger(2));
	Uint8 *g = new Uint8(binder.checkinteger(3));
	Uint8 *b = new Uint8(binder.checkinteger(4));
	Uint8 *a = new Uint8(binder.checkinteger(5));
	Uint32 h = SDL_MapRGBA(format, *r, *g, *b, *a);
	binder.pushusertype(&h, "Uint32");
	return 1;
}
int LUA_SDL_FREESURFACE(lua_State* l)
{
	kpBindLua binder(l);
	SDL_FreeSurface((SDL_Surface*)binder.checkusertype(1, "SDL_Surface"));
	return 0;
}
int LUA_SDL_FILLRECT(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* dst = (SDL_Surface*)binder.checkusertype(1, "SDL_Surface");
	//SDL_Rect* h = (SDL_Rect*)binder.checkusertype(2, "SDL_Rect");
	Uint32* c = (Uint32*)binder.checkusertype(2, "Uint32");
	
	SDL_Rect dstR;
	int x = binder.checkinteger(3);
	int y = binder.checkinteger(4);
	int w = binder.checkinteger(5);
	int h = binder.checkinteger(6);
	dstR.x = x;
	dstR.y = y;
	dstR.w = w;
	dstR.h = h;
	
	SDL_FillRect(dst, &dstR, *c);
	return 0;
}
int LUA_SDL_FILLRECTALPHA(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* dst = (SDL_Surface*)binder.checkusertype(1, "SDL_Surface");
	//SDL_Rect* h = (SDL_Rect*)binder.checkusertype(2, "SDL_Rect");
	//Uint32* c = (Uint32*)binder.checkusertype(2, "Uint32");
	
	SDL_Rect dstR;
	int x = binder.checkinteger(2);
	int y = binder.checkinteger(3);
	int w = binder.checkinteger(4);
	int h = binder.checkinteger(5);
	dstR.x = x;
	dstR.y = y;
	dstR.w = w;
	dstR.h = h;
	Uint8 *r = new Uint8(binder.checkinteger(6));
	Uint8 *g = new Uint8(binder.checkinteger(7));
	Uint8 *b = new Uint8(binder.checkinteger(8));
	Uint8 *a = new Uint8(binder.checkinteger(9));
	SDL_Surface* screen = (SDL_Surface*)binder.checkusertype(10, "SDL_Surface");
	SDL_FillRect(dst, &dstR, SDL_MapRGBA(screen->format,
		         *r, *g, *b, *a));
	//SDL_SetAlpha(dst, SDL_SRCALPHA, 129);
	SDL_BlitSurface(dst, NULL, screen, NULL);
	return 0;
}
int LUA_SDL_BLITSURFACE(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* src = (SDL_Surface*)binder.checkusertype(1, "SDL_Surface");
	SDL_Rect* srcR = (SDL_Rect*)binder.checkusertype(2, "SDL_Rect");
	SDL_Surface* dst = (SDL_Surface*)binder.checkusertype(3, "SDL_Surface");
	SDL_Rect* dstR = (SDL_Rect*)binder.checkusertype(4, "SDL_Rect");
	SDL_BlitSurface(src, srcR, dst, dstR);
	return 0;
}
int LUA_SDL_BLITAPPLY(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* src = (SDL_Surface*)binder.checkusertype(1, "SDL_Surface");
	//SDL_Rect* srcR = (SDL_Rect*)binder.checkusertype(2, "SDL_Rect");
	SDL_Surface* dst = (SDL_Surface*)binder.checkusertype(2, "SDL_Surface");
	SDL_Rect* dstR = (SDL_Rect*)binder.checkusertype(3, "SDL_Rect");
	SDL_BlitSurface(src, NULL, dst, dstR);
	return 0;
}
int LUA_SDL_BLITAPPLYf(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Surface* src = (SDL_Surface*)binder.checkusertype(1, "SDL_Surface");
	//SDL_Rect* srcR = (SDL_Rect*)binder.checkusertype(2, "SDL_Rect");
	SDL_Surface* dst = (SDL_Surface*)binder.checkusertype(2, "SDL_Surface");
	SDL_Rect dstR;
	int x = binder.checkinteger(3);
	int y = binder.checkinteger(4);
	int w = binder.checkinteger(5);
	int h = binder.checkinteger(6);
	dstR.x = x;
	dstR.y = y;
	dstR.w = w;
	dstR.h = h;
	SDL_BlitSurface(src, NULL, dst, &dstR);
	return 0;
}

//native to LUA bindings
int LUA_Uint8(lua_State* l)
{
	kpBindLua binder(l);
	Uint8* h = new Uint8(binder.checkinteger(1));
	binder.pushusertype(h, "Uint8");
	return 1;
}
int LUA_Uint8_KILL(lua_State* l)
{
	kpBindLua binder(l);
	Uint8* h = (Uint8*)binder.checkusertype(1,"Uint8");
	delete h;
	return 0;
}
static const luaL_Reg Uint8_lib[] = {
	{"new", LUA_Uint8},
	{"kill", LUA_Uint8_KILL},
	{NULL, NULL}
};
//
int UINT8_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("Uint8", "", Uint8_lib, LUA_Uint8_KILL);
	return 1;
}
int LUA_Uint16(lua_State* l)
{
	kpBindLua binder(l);
	Uint16* h = new Uint16(binder.checkinteger(1));
	binder.pushusertype(h, "Uint16");
	return 1;
}
int LUA_Uint16_KILL(lua_State* l)
{
	kpBindLua binder(l);
	Uint16* h = (Uint16*)binder.checkusertype(1,"Uint16");
	delete h;
	return 0;
}
static const luaL_Reg Uint16_lib[] = {
	{"new", LUA_Uint16},
	{"kill", LUA_Uint16_KILL},
	{NULL, NULL}
};
//
int UINT16_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("Uint16", "", Uint16_lib, LUA_Uint16_KILL);
	return 1;
}
int LUA_Sint16(lua_State* l)
{
	kpBindLua binder(l);
	Sint16* h = new Sint16(binder.checkinteger(1));
	binder.pushusertype(h, "Sint16");
	return 1;
}
int LUA_Sint16_KILL(lua_State* l)
{
	kpBindLua binder(l);
	Sint16* h = (Sint16*)binder.checkusertype(1,"Sint16");
	delete h;
	return 0;
}
static const luaL_Reg Sint16_lib[] = {
	{"new", LUA_Sint16},
	{"kill", LUA_Sint16_KILL},
	{NULL, NULL}
};
//
int SINT16_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("Sint16", "", Sint16_lib, LUA_Uint16_KILL);
	return 1;
}
int LUA_Uint32(lua_State* l)
{
	kpBindLua binder(l);
	Uint32* h = new Uint32(binder.checkinteger(1));
	binder.pushusertype(h, "Uint32");
	return 1;
}
int LUA_Uint32_KILL(lua_State* l)
{
	kpBindLua binder(l);
	Uint32* h = (Uint32*)binder.checkusertype(1,"Uint32");
	delete h;
	return 0;
}
static const luaL_Reg Uint32_lib[] = {
	{"new", LUA_Uint32},
	{"kill", LUA_Uint32_KILL},
	{NULL, NULL}
};
//
int UINT32_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("Uint32", "", Uint32_lib, LUA_Uint32_KILL);
	return 1;
}
int LUA_Sint32(lua_State* l)
{
	kpBindLua binder(l);
	Sint32* h = new Sint32(binder.checkinteger(1));
	binder.pushusertype(h, "Sint32");
	return 1;
}
int LUA_Sint32_KILL(lua_State* l)
{
	kpBindLua binder(l);
	Sint32* h = (Sint32*)binder.checkusertype(1,"Sint32");
	delete h;
	return 0;
}
static const luaL_Reg Sint32_lib[] = {
	{"new", LUA_Sint32},
	{"kill", LUA_Sint32_KILL},
	{NULL, NULL}
};
//
int SINT32_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("Sint32", "", Sint32_lib, LUA_Sint32_KILL);
	return 1;
}
int LUA_unsignedint(lua_State* l)
{
	kpBindLua binder(l);
	unsigned int* h = new unsigned int();
	binder.pushusertype(h, "unsignedint");
	return 1;
}
int LUA_unsignedint_KILL(lua_State* l)
{
	kpBindLua binder(l);
	unsigned int* h = (unsigned int*)binder.checkusertype(1,"unsignedint");
	delete h;
	return 0;
}
static const luaL_Reg unsignedint_lib[] = {
	{"new", LUA_Sint32},
	{"kill", LUA_Sint32_KILL},
	{NULL, NULL}
};
//
int unsignedint_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("unsignedint", "", unsignedint_lib, LUA_unsignedint_KILL);
	return 1;
}
//kpClass to LUA bindings
int LUA_INI(lua_State* l)
{
	kpBindLua binder(l);
	INIReader* h = new INIReader(binder.checkstring(2));
	binder.pushusertype(h, "INIReader");
	return 1;
}
int LUA_INI_KILL(lua_State* l)
{
	kpBindLua binder(l);
	INIReader* h = (INIReader*) binder.checkusertype(1,"INIReader");
	//delete h;
	h = NULL;
	return 0;
}
int LUA_INI_getString(lua_State* l)
{
	kpBindLua binder(l);
	INIReader* h = (INIReader*)binder.checkusertype(1, "INIReader");
	binder.pushstring(h->Get(binder.checkstring(2), binder.checkstring(3),binder.checkstring(4)).c_str());
	return 1;
}
int LUA_INI_getInt(lua_State* l)
{
	kpBindLua binder(l);
	INIReader* h = (INIReader*)binder.checkusertype(1, "INIReader");
	binder.pushinterger(h->GetInteger(binder.checkstring(2), binder.checkstring(3),binder.checkinteger(4)));
	return 1;
}
int LUA_INI_getReal(lua_State* l)
{
	kpBindLua binder(l);
	INIReader* h = (INIReader*)binder.checkusertype(1, "INIReader");
	binder.pushnumber(h->GetReal(binder.checkstring(2), binder.checkstring(3),binder.checknumber(4)));
	return 1;
}
int LUA_INI_getBool(lua_State* l)
{
	kpBindLua binder(l);
	INIReader* h = (INIReader*)binder.checkusertype(1, "INIReader");
	bool b = 0;
	b = (int)h->GetBoolean(binder.checkstring(2), binder.checkstring(3),binder.checkbool(4));
	binder.pushboolean(b);
	return 1;
}
static const luaL_Reg INI_lib[] = {
	{"new", LUA_INI},
	{"kill", LUA_INI_KILL},
	{"getString", LUA_INI_getString},
	{"getInteger", LUA_INI_getInt},
	{"getFloat", LUA_INI_getReal},
	{"getBool", LUA_INI_getBool},
	{NULL, NULL}
};
//
int LUA_INI_LIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("INIReader", "", INI_lib, LUA_INI_KILL);
	return 1;
}
//kpC++ to LUA API bindings
static int bnd_Create_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = new kpVector3f();
    binder.pushusertype(h,"kpVector3f");
    return 1;
}
static int bnd_Create_V2_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	float x;
	x = (float)binder.checknumber(2);
	float y;
	y = (float)binder.checknumber(3);
	kpVector3f* h = new kpVector3f(x, y);
    binder.pushusertype(h,"kpVector3f");
    return 1;
}
static int bnd_Create_V3_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = new kpVector3f((float)binder.checknumber(2), (float)binder.checknumber(3), (float)binder.checknumber(4));
    binder.pushusertype(h,"kpVector3f");
    return 1;
}
static int bnd_Destroy_vector3 (lua_State* L)
{
    kpBindLua binder(L);
    kpVector3f* hero = (kpVector3f*) binder.checkusertype(1,"kpVector3f");
    delete hero;
    return 0;
}
static int bnd_max_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	binder.pushnumber(h->Max());
    return 1;
}
static int bnd_dotProduct_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	binder.pushnumber(h->dotProduct(*(kpVector3f*)binder.checkusertype(2, "kpVector3f")));
    return 1;
}
static int bnd_crossProduct_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	kpVector3f c = h->crossProduct(*(kpVector3f*)binder.checkusertype(2, "kpVector3f"));
	binder.pushusertype(&c, "kpVector3f");
    return 1;
}
static int bnd_length_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	binder.pushnumber(h->length());
    return 1;
}
static int bnd_normalize_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->normalize();
    return 0;
}
static int bnd_scalar_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	kpVector3f c = h->scalar((float)binder.checknumber(2));
	binder.pushusertype(&c, "kpVector3f");
    return 1;
}
static int bnd_lerp_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	kpVector3f c = h->lerp(*(kpVector3f*)binder.checkusertype(2, "kpVector3f"), (float)binder.checknumber(3));
	binder.pushusertype(&c, "kpVector3f");
    return 1;
}
static int bnd_change_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->change(*(kpVector3f*)binder.checkusertype(1, "kpVector3f"));
    return 0;
}
static int bnd_change3f_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->change((float)binder.checknumber(2), (float)binder.checknumber(3), (float)binder.checknumber(4));
    return 0;
}
static int bnd_changeX_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->changeX((float)binder.checknumber(2));
    return 0;
}
static int bnd_changeY_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->changeY((float)binder.checknumber(2));
    return 0;
}
static int bnd_changeZ_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->changeZ((float)binder.checknumber(2));
    return 0;
}
static int bnd_x_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	binder.pushnumber(h->x);
    return 1;
}
static int bnd_y_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	binder.pushnumber(h->y);
    return 1;
}
static int bnd_z_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	binder.pushnumber(h->z);
    return 1;
}
static int bnd_setx_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->x = (float)binder.checknumber(2);
    return 0;
}
static int bnd_sety_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->y = (float)binder.checknumber(2);
    return 0;
}
static int bnd_setz_vector3 (lua_State* L)
{
    kpBindLua binder(L);
	kpVector3f* h = (kpVector3f*)binder.checkusertype(1, "kpVector3f");
	h->z = (float)binder.checknumber(2);
    return 0;
}
static const luaL_Reg kpVector3flib[] = {
	{"new", bnd_Create_vector3},
	{"newV2", bnd_Create_V2_vector3},
	{"newV3", bnd_Create_V3_vector3},
	{"kill", bnd_Destroy_vector3},
	{"max", bnd_max_vector3},
	{"dotProduct", bnd_dotProduct_vector3},
	{"crossProduct", bnd_crossProduct_vector3},
	{"length", bnd_length_vector3},
	{"normalize", bnd_normalize_vector3},
	{"scalar", bnd_scalar_vector3},
	{"lerp", bnd_lerp_vector3},
	{"change", bnd_change_vector3},
	{"change3f", bnd_change3f_vector3},
	{"changeX", bnd_changeX_vector3},
	{"changeY", bnd_changeY_vector3},
	{"changeZ", bnd_changeZ_vector3},
	{"x", bnd_x_vector3},
	{"y", bnd_y_vector3},
	{"z", bnd_z_vector3},	
	{"setX", bnd_setx_vector3},
	{"setY", bnd_sety_vector3},
	{"setZ", bnd_setz_vector3},
	{NULL, NULL}
};
//
static int bnd_Create_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* h = new kpMatrix4f();
    binder.pushusertype(h,"kpMatrix4f");
    return 1;
}
static int bnd_Destroy_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
    delete hero;
    return 0;
}
static int bnd_transpose_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->transpose(), "kpMatrix4f");
    return 1;
}
static int bnd_tranform_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->transform(*(kpVector3f*) binder.checkusertype(2,"kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_identity_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->identity(), "kpMatrix4f");
    return 1;
}
static int bnd_initTranslation3f_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initTranslation((float)binder.checknumber(2), (float)binder.checknumber(3), (float)binder.checknumber(4)), "kpMatrix4f");
    return 1;
}
static int bnd_initTranslation_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initTranslation(*(kpVector3f*)binder.checkusertype(2, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_initRotation3f_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initRotation((float)binder.checknumber(2), (float)binder.checknumber(3), (float)binder.checknumber(4)), "kpMatrix4f");
    return 1;
}
static int bnd_initRotation_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initRotation(*(kpVector3f*)binder.checkusertype(2, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_initScale3f_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initScale((float)binder.checknumber(2), (float)binder.checknumber(3), (float)binder.checknumber(4)), "kpMatrix4f");
    return 1;
}
static int bnd_initScale_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initScale(*(kpVector3f*)binder.checkusertype(2, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_projection_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->projection((float)binder.checknumber(2), (float)binder.checknumber(3), (float)binder.checknumber(4), (float)binder.checknumber(5), (float)binder.checknumber(6)), "kpMatrix4f");
    return 1;
}
static int bnd_ortho_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->ortho((float)binder.checknumber(2), (float)binder.checknumber(3), (float)binder.checknumber(4), (float)binder.checknumber(5), (float)binder.checknumber(6), (float)binder.checknumber(7)), "kpMatrix4f");
    return 1;
}
static int bnd_frustum_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->frustum((float)binder.checknumber(2), (float)binder.checknumber(3), (float)binder.checknumber(4), (float)binder.checknumber(5), (float)binder.checknumber(6), (float)binder.checknumber(7)), "kpMatrix4f");
    return 1;
}
static int bnd_view_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->View(*(kpVector3f*)binder.checkusertype(2, "kpVector3f"), *(kpVector3f*)binder.checkusertype(3, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_initRot_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initRot(*(kpVector3f*)binder.checkusertype(2, "kpVector3f"), *(kpVector3f*)binder.checkusertype(3, "kpVector3f"), *(kpVector3f*)binder.checkusertype(4, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_initRotationFromVectors_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initRotationFromVectors(*(kpVector3f*)binder.checkusertype(2, "kpVector3f"), *(kpVector3f*)binder.checkusertype(3, "kpVector3f"), *(kpVector3f*)binder.checkusertype(4, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_initRotationFromDirection_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initRotationFromDirection(*(kpVector3f*)binder.checkusertype(2, "kpVector3f"), *(kpVector3f*)binder.checkusertype(3, "kpVector3f")), "kpMatrix4f");
    return 1;
}
static int bnd_initPerspective_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->initPerspective((float)binder.checknumber(2), (float)binder.checknumber(3), (float)binder.checknumber(4), (float)binder.checknumber(5)), "kpMatrix4f");
    return 1;
}
static int bnd_mul_matrix4 (lua_State* L)
{
    kpBindLua binder(L);
    kpMatrix4f* hero = (kpMatrix4f*) binder.checkusertype(1,"kpMatrix4f");
	binder.pushusertype(&hero->mul(*(kpMatrix4f*)binder.checkusertype(2, "kpMatrix4f")), "kpMatrix4f");
    return 1;
}
static const luaL_Reg kpMatrix4flib[] = {
	{"new", bnd_Create_matrix4},
	{"kill", bnd_Destroy_matrix4},
	{"transpose", bnd_transpose_matrix4},
	{"transform", bnd_tranform_matrix4},
	{"identity", bnd_identity_matrix4},
	{"initTranslation3f", bnd_initTranslation3f_matrix4},
	{"initTranslation", bnd_initTranslation_matrix4},
	{"initRotation3f", bnd_initRotation3f_matrix4},
	{"initRotation", bnd_initRotation_matrix4},
	{"initScale3f", bnd_initScale3f_matrix4},
	{"initScale", bnd_initScale_matrix4},
	{"initRot", bnd_initRot_matrix4},
	{"initRotationFromVectors", bnd_initRotationFromVectors_matrix4},
	{"initRotationFromDirection", bnd_initRotationFromDirection_matrix4},
	{"initPerspective", bnd_initPerspective_matrix4},
	{"projection", bnd_projection_matrix4},
	{"ortho", bnd_ortho_matrix4},
	{"frustum", bnd_frustum_matrix4},
	{"view", bnd_view_matrix4},
	{"mul", bnd_mul_matrix4},
	{NULL, NULL}
};
//kpQuaternion function bindings
static int bnd_Create_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* h = new kpQuaternion();
    binder.pushusertype(h,"kpQuaternion");
    return 1;
}
static int bnd_Create_4f_quaternion (lua_State* L)
{
    kpBindLua binder(L);
	kpQuaternion* h = new kpQuaternion((float)binder.checknumber(1), (float)binder.checknumber(2), (float)binder.checknumber(3), (float)binder.checknumber(4));
    binder.pushusertype(h,"kpQuaternion");
    return 1;
}
static int bnd_Create_matrix_quaternion (lua_State* L)
{
    kpBindLua binder(L);
	kpQuaternion* h = new kpQuaternion(*(kpMatrix4f*)binder.checkusertype(1, "kpMatrix4f"));
    binder.pushusertype(h,"kpQuaternion");
    return 1;
}
static int bnd_Destroy_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
    delete hero;
    return 0;
}
static int bnd_length_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushnumber(hero->length());
    return 1;
}
static int bnd_normalise_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->normalise(), "kpQuaternion");
    return 1;
}
static int bnd_conjugate_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->conjugate(), "kpQuaternion");
    return 1;
}
static int bnd_mul_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->mul(*(kpQuaternion*) binder.checkusertype(2,"kpQuaternion")), "kpQuaternion");
    return 1;
}
static int bnd_mul_vec_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->mul(*(kpVector3f*) binder.checkusertype(2,"kpVector3f")), "kpQuaternion");
    return 1;
}
static int bnd_mul_f_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->mul((float)binder.checknumber(2)), "kpQuaternion");
    return 1;
}
static int bnd_dot_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushnumber(hero->dot(*(kpQuaternion*) binder.checkusertype(2,"kpQuaternion")));
    return 1;
}
static int bnd_initRotation_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->initRotation(*(kpVector3f*) binder.checkusertype(2,"kpVector3f"), (float)binder.checknumber(3)), "kpQuaternion");
    return 1;
}
static int bnd_toRotationMatrix_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->toRotationMatrix(), "kpMatrix4f");
    return 1;
}
static int bnd_lerp_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->lerp(*(kpQuaternion*) binder.checkusertype(2,"kpQuaternion"), (float)binder.checknumber(3)), "kpQuaternion");
    return 1;
}
static int bnd_NLerp_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->NLerp(*(kpQuaternion*) binder.checkusertype(2,"kpQuaternion"), (float)binder.checknumber(3), binder.checkbool(4)), "kpQuaternion");
    return 1;
}
static int bnd_getForward_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->getForward(), "kpVector3f");
    return 1;
}
static int bnd_getBack_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->getBack(), "kpVector3f");
    return 1;
}
static int bnd_getUp_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->getUp(), "kpVector3f");
    return 1;
}
static int bnd_getDown_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->getDown(), "kpVector3f");
    return 1;
}
static int bnd_getLeft_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->getLeft(), "kpVector3f");
    return 1;
}
static int bnd_getRight_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushusertype(&hero->getRight(), "kpVector3f");
    return 1;
}
static int bnd_getX_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushnumber(hero->getX());
    return 1;
}
static int bnd_getY_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushnumber(hero->getY());
    return 1;
}
static int bnd_getZ_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushnumber(hero->getZ());
    return 1;
}
static int bnd_getW_quaternion (lua_State* L)
{
    kpBindLua binder(L);
    kpQuaternion* hero = (kpQuaternion*) binder.checkusertype(1,"kpQuaternion");
	binder.pushnumber(hero->getW());
    return 1;
}
static const luaL_Reg kpQuaternionlib[] = {
	{"new", bnd_Create_quaternion},
	{"new4f", bnd_Create_4f_quaternion},
	{"newFromMatrix", bnd_Create_matrix_quaternion},
	{"kill", bnd_Destroy_quaternion},
	{"length", bnd_length_quaternion},
	{"normalise", bnd_normalise_quaternion},
	{"conjugate", bnd_conjugate_quaternion},
	{"mul", bnd_mul_quaternion},
	{"mulVec", bnd_mul_vec_quaternion},
	{"mulF", bnd_mul_f_quaternion},
	{"dot", bnd_dot_quaternion},
	{"initRotation", bnd_initRotation_quaternion},
	{"toRotationMatrix", bnd_toRotationMatrix_quaternion},
	{"lerp", bnd_lerp_quaternion},
	{"NLerp", bnd_NLerp_quaternion},
	{"getForward", bnd_getForward_quaternion},
	{"getBack", bnd_getBack_quaternion},
	{"getUp", bnd_getUp_quaternion},
	{"getDown", bnd_getDown_quaternion},
	{"getLeft", bnd_getLeft_quaternion},
	{"getRight", bnd_getRight_quaternion},
	{"getX", bnd_getX_quaternion},
	{"getY", bnd_getY_quaternion},
	{"getZ", bnd_getZ_quaternion},
	{"getW", bnd_getW_quaternion},
	{NULL, NULL}
};
//
static int bnd_Create_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* h = new kpTransform();
    binder.pushusertype(h,"kpTransform");
    return 1;
}
static int bnd_Create_pos_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* h = new kpTransform(*(kpVector3f*) binder.checkusertype(1,"kpVector3f"));
    binder.pushusertype(h,"kpTransform");
    return 1;
}
static int bnd_Create_pos_rot_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* h = new kpTransform(*(kpVector3f*) binder.checkusertype(1,"kpVector3f"), *(kpVector3f*) binder.checkusertype(2,"kpVector3f"));
    binder.pushusertype(h,"kpTransform");
    return 1;
}
static int bnd_Create_pos_rot_scl_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* h = new kpTransform(*(kpVector3f*) binder.checkusertype(1,"kpVector3f"), *(kpVector3f*) binder.checkusertype(2,"kpVector3f"), *(kpVector3f*) binder.checkusertype(3,"kpVector3f"));
    binder.pushusertype(h,"kpTransform");
    return 1;
}
static int bnd_Destroy_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
    delete hero;
    return 0;
}
static int bnd_Process_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->Process();
    return 0;
}
static int bnd_setParent_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->setParent((kpTransform*) binder.checkusertype(2,"kpTransform"));
    return 0;
}
static int bnd_setTranslation_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->setTranslation(*(kpVector3f*) binder.checkusertype(2,"kpVector3f"));
    return 0;
}
static int bnd_setRotation_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->setRotation(*(kpVector3f*) binder.checkusertype(2,"kpVector3f"));
    return 0;
}
static int bnd_rotate_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->rotate(*(kpQuaternion*) binder.checkusertype(2,"kpQuaternion"));
    return 0;
}
static int bnd_setScale_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->setScale(*(kpVector3f*) binder.checkusertype(2,"kpVector3f"));
    return 0;
}
static int bnd_getLookAtRotation_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getLookAtRotation(*(kpVector3f*) binder.checkusertype(2,"kpVector3f"), *(kpVector3f*) binder.checkusertype(3,"kpVector3f")), "kpQuaternion");
    return 1;
}
static int bnd_lookAt_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	hero->lookAt(*(kpVector3f*) binder.checkusertype(2,"kpVector3f"), *(kpVector3f*) binder.checkusertype(3,"kpVector3f"));
    return 0;
}
static int bnd_hasChanged_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushinterger(hero->hasChanged());
    return 1;
}
static int bnd_getTransformation_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getTransformation(), "kpMatrix4f");
    return 1;
}
static int bnd_getProjectedTransFormation_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getProjectedTransFormation(), "kpMatrix4f");
    return 1;
}
static int bnd_getTransformedRot_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getTransformedRot(),"kpQuaternion");
    return 1;
}
static int bnd_getRot_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getRot(),"kpQuaternion");
    return 1;
}
static int bnd_getOrigin_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getOrigin(), "kpVector3f");
    return 1;
}
static int bnd_getPostion_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getPostion(), "kpVector3f");
    return 1;
}
static int bnd_getRotation_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getRotation(), "kpVector3f");
    return 1;
}
static int bnd_getScale_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getScale(), "kpVector3f");
    return 1;
}
static int bnd_getUpVector_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getUpVector(), "kpVector3f");
    return 1;
}
static int bnd_getTransformedPos_transform (lua_State* L)
{
    kpBindLua binder(L);
    kpTransform* hero = (kpTransform*) binder.checkusertype(1,"kpTransform");
	binder.pushusertype(&hero->getTransformedPos(), "kpVector3f");
    return 1;
}
static const luaL_Reg kpTransformlib[] = {
	{"new", bnd_Create_transform},
	{"newP", bnd_Create_pos_transform},
	{"newPR", bnd_Create_pos_rot_transform},
	{"newPRS", bnd_Create_pos_rot_scl_transform},
	{"kill", bnd_Destroy_transform},
	{"update", bnd_Process_transform},
	{"setParent", bnd_setParent_transform},
	{"setTranslation", bnd_setTranslation_transform},
	{"setRotation", bnd_setRotation_transform},
	{"rotate", bnd_rotate_transform},
	{"setScale", bnd_setScale_transform},
	{"getLookAtRotation", bnd_getLookAtRotation_transform},
	{"lookAt", bnd_lookAt_transform},
	{"hasChanged", bnd_hasChanged_transform},
	{"getTransformation", bnd_getTransformation_transform},
	{"getProjectedTransFormation", bnd_getProjectedTransFormation_transform},
	{"getTransformedRot", bnd_getTransformedRot_transform},
	{"getRot", bnd_getRot_transform},
	{"getOrigin", bnd_getOrigin_transform},
	{"getPostion", bnd_getPostion_transform},
	{"getRotation", bnd_getRotation_transform},
	{"getScale", bnd_getScale_transform},
	{"getUpVector", bnd_getUpVector_transform},
	{"getTransformedPos", bnd_getTransformedPos_transform},
	{NULL, NULL}
};
//kpGameObject function bindings

static int bnd_Create_timer (lua_State* L)
{
    kpBindLua binder(L);
    kpTimer* h = new kpTimer();
    binder.pushusertype(h,"kpTimer");
    return 1;
}
static int bnd_Destroy_timer (lua_State* L)
{
    kpBindLua binder(L);
    kpTimer* hero = (kpTimer*) binder.checkusertype(1,"kpTimer");
    delete hero;
    return 0;
}
static int bnd_Start_timer (lua_State* L)
{
    kpBindLua binder(L);
    kpTimer* hero = (kpTimer*) binder.checkusertype(1,"kpTimer");
	hero->start();
    return 0;
}
static int bnd_Stop_timer (lua_State* L)
{
    kpBindLua binder(L);
    kpTimer* hero = (kpTimer*) binder.checkusertype(1,"kpTimer");
	hero->stop();
    return 0;
}
static int bnd_Pause_timer (lua_State* L)
{
    kpBindLua binder(L);
    kpTimer* hero = (kpTimer*) binder.checkusertype(1,"kpTimer");
	hero->pause();
    return 0;
}
static int bnd_Unpause_timer (lua_State* L)
{
    kpBindLua binder(L);
    kpTimer* hero = (kpTimer*) binder.checkusertype(1,"kpTimer");
	hero->unpause();
    return 0;
}
static int bnd_Restart_timer (lua_State* L)
{
    kpBindLua binder(L);
    kpTimer* hero = (kpTimer*) binder.checkusertype(1,"kpTimer");
	binder.pushinterger(hero->restart());
    return 1;
}
static int bnd_Ticks_timer (lua_State* L)
{
    kpBindLua binder(L);
    kpTimer* hero = (kpTimer*) binder.checkusertype(1,"kpTimer");
	binder.pushinterger(hero->ticks());
    return 1;
}
static int bnd_Started_timer (lua_State* L)
{
    kpBindLua binder(L);
    kpTimer* hero = (kpTimer*) binder.checkusertype(1,"kpTimer");
	binder.pushboolean(hero->started());
    return 1;
}
static int bnd_Paused_timer (lua_State* L)
{
    kpBindLua binder(L);
    kpTimer* hero = (kpTimer*) binder.checkusertype(1,"kpTimer");
	binder.pushboolean(hero->paused());
    return 1;
}
static const luaL_Reg kpTimerlib[] = {
    {"new", bnd_Create_timer},
    {"kill", bnd_Destroy_timer},
	{"start", bnd_Start_timer},
    {"stop", bnd_Stop_timer},
	{"pause", bnd_Pause_timer},
	{"unpause", bnd_Unpause_timer},
	{"restart", bnd_Restart_timer},
	{"ticks", bnd_Ticks_timer},
	{"started", bnd_Started_timer},
	{"paused", bnd_Paused_timer},
    {NULL, NULL}
};
//
static int bnd_Create_log (lua_State* L)
{
    kpBindLua binder(L);
    kpLog* h = new kpLog();
    binder.pushusertype(h,"kpLog");
    return 1;
}
static int bnd_Destroy_log (lua_State* L)
{
    kpBindLua binder(L);
    kpLog* hero = (kpLog*) binder.checkusertype(1,"kpLog");
    delete hero;
    return 0;
}
static int bnd_i_log (lua_State* L)
{
    kpBindLua binder(L);
    kpLog* hero = (kpLog*) binder.checkusertype(1,"kpLog");
	hero->i(binder.checkstring(2));
    return 0;
}
static int bnd_ie_log (lua_State* L)
{
    kpBindLua binder(L);
    kpLog* hero = (kpLog*) binder.checkusertype(1,"kpLog");
	binder.pushstring(hero->ie(binder.checkstring(2)).c_str());
    return 1;
}
static int bnd_i2_log (lua_State* L)
{
    kpBindLua binder(L);
    kpLog* hero = (kpLog*) binder.checkusertype(1,"kpLog");
	hero->i(binder.checkstring(2), binder.checkstring(3));
    return 0;
}
static int bnd_ie2_log (lua_State* L)
{
    kpBindLua binder(L);
    kpLog* hero = (kpLog*) binder.checkusertype(1,"kpLog");
	binder.pushstring(hero->ie(binder.checkstring(2), binder.checkstring(3)).c_str());
    return 1;
}
static int bnd_i3_log (lua_State* L)
{
    kpBindLua binder(L);
    kpLog* hero = (kpLog*) binder.checkusertype(1,"kpLog");
	hero->i(binder.checkstring(2), binder.checkstring(3), binder.checkstring(4));
    return 0;
}
static int bnd_ie3_log (lua_State* L)
{
    kpBindLua binder(L);
    kpLog* hero = (kpLog*) binder.checkusertype(1,"kpLog");
	binder.pushstring(hero->ie(binder.checkstring(2), binder.checkstring(3), binder.checkstring(4)).c_str());
    return 1;
}
static const luaL_Reg kpLoglib[] = {
	{"new", bnd_Create_log},
	{"kill", bnd_Destroy_log},
	{"iTag", bnd_i_log},
	{"ieTag", bnd_ie_log},
	{"iMsg", bnd_i2_log},
	{"ieMsg", bnd_ie2_log},
	{"iFunc", bnd_i3_log},
	{"ieFunc", bnd_ie3_log},
	{NULL, NULL}
};
//kpText function bindings
int kpLOGLIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("kpLog", "", kpLoglib, bnd_Destroy_log);
	return 1;
}
int kpTIMERLIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("kpTimer", "", kpTimerlib, bnd_Destroy_timer);
	return 1;
}
int kpVECTOR3FLIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("kpVector3f", "", kpVector3flib, bnd_Destroy_vector3);
	return 1;
}
int kpMATRIX4FLIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("kpMatrix4f", "", kpMatrix4flib, bnd_Destroy_matrix4);
	return 1;
}
int kpQUATERNIONLIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("kpQuaternion", "", kpQuaternionlib, bnd_Destroy_quaternion);
	return 1;
}
int kpTRANSFROMLIB(lua_State* l)
{	
	kpBindLua binder(l);
	binder.init("kpTransform", "", kpTransformlib, bnd_Destroy_transform);
	return 1;
}
/////////////////////////////////////

int LUA_ENGINE(lua_State* l)
{
	kpBindLua binder(l);
	binder.pushusertype((kpEngine*)kpEngine::getEngine(), "kpEngine");
	return 1;
}
int LUA_ENG_WIN(lua_State* l)
{
	kpBindLua binder(l);
	SDL_Window* h = kpEngine::getMainWindow();
	binder.pushusertype(h, "SDL_Window");
	return 1;
}
int LUA_ENG_SETWIN(lua_State* l)
{
	kpBindLua binder(l);
	kpEngine::setMainWindow((SDL_Window*)binder.checkusertype(1,"SDL_Window"));
	return 0;
}
int LUA_ENG_RUN(lua_State* l)
{
	kpBindLua binder(l);
	int h = kpEngine::getRun();
	binder.pushinterger(h);
	return 1;
}
int LUA_ENG_Event(lua_State* l)
{
	kpBindLua binder(l);
	//SDL_Evetn* h = kpEngine::getEvent();
	//binder.pushusertype(h, "SDL_Event");
	return 1;
}
int LUA_ENG_SETRUN(lua_State* l)
{
	kpBindLua binder(l);
	kpEngine::setRun(binder.checkinteger(1));
	return 0;
}
//API
int kpAPILIBS(lua_State* l)
{
	//Register functions
	UINT8_LIB(l);
	UINT16_LIB(l);
	SINT16_LIB(l);
	UINT32_LIB(l);
	SINT32_LIB(l);
	unsignedint_LIB(l);
	//gl functions
	lua_register(l, "getEngine", LUA_ENGINE);
	lua_register(l, "getMainWindow", LUA_ENG_WIN);
	lua_register(l, "setMainWindow", LUA_ENG_WIN);	
	lua_register(l, "getMainEvent", LUA_ENG_WIN);
	lua_register(l, "getRun", LUA_ENG_WIN);
	lua_register(l, "setRun", LUA_ENG_WIN);
	lua_register(l, "initGL", LUA_INITGL);
	//SDL functions
	lua_register(l, "regulateFPS", LUA_regulateFPS);
	lua_register(l, "SDL_GetTicks", LUA_GETTICK);
	lua_register(l, "getCursor", LUA_GETCURSOR);
	lua_register(l, "showCursor", LUA_SHOWCURSOR);
	lua_register(l, "QSDL", LUA_QSDL);
	lua_register(l, "pollEvent", LUA_SDL_PollEvent);
	lua_register(l, "renderCopy", LUA_SDL_RenderCopy);
	lua_register(l, "renderCrop", LUA_SDL_RenderCrop);
	lua_register(l, "renderCopyCrop", LUA_SDL_RenderCopyCrop);
	lua_register(l, "loadTexture", LUA_IMG_LoadTexture);
	lua_register(l, "createWindow", LUA_CreateWindow);
	lua_register(l, "createGLContext", LUA_CreateGLContext);
	lua_register(l, "createRenderer", LUA_CreateRenderer);
	lua_register(l, "createTargetRenderer", LUA_CreateTargetRenderer);
	lua_register(l, "clearRender", LUA_ClearRender);
	lua_register(l, "flipRender", LUA_FlipRender);
	lua_register(l, "checkKeyState", LUA_SDL_checkKeyState);
	lua_register(l, "checkKeyDown", LUA_SDL_checkKeyDown);
	lua_register(l, "checkKeyUP", LUA_SDL_checkKeyUP);
	lua_register(l, "checkButtonDown", LUA_SDL_checkButtonDown);
	lua_register(l, "checkButtonUP", LUA_SDL_checkButtonUP);
	lua_register(l, "SDL_MapRGB", LUA_SDL_MAPRGB);
	lua_register(l, "SDL_MapRGBA", LUA_SDL_MAPRGBA);
	lua_register(l, "SDL_FillRect", LUA_SDL_FILLRECT);
	lua_register(l, "SDL_FillRectAlpha", LUA_SDL_FILLRECTALPHA);
	lua_register(l, "SDL_FreeSurface", LUA_SDL_FREESURFACE);
	lua_register(l, "SDL_BlitSurface", LUA_SDL_BLITSURFACE);
	lua_register(l, "SDL_ApplyBlit", LUA_SDL_BLITAPPLY);
	lua_register(l, "SDL_ApplyBlitF", LUA_SDL_BLITAPPLYf);	
	lua_register(l, "SDL_MapRGB", LUA_SDL_MAPRGB);
	lua_register(l, "SDL_MapRGBA", LUA_SDL_MAPRGBA);
	lua_register(l, "queryTexture", LUA_SDL_QueryTexture);
	//-------------------------------------------------------------
	SDL_Window_LIB(l);
	SDL_Renderer_LIB(l);
	SDL_RECT_LIB(l);
	SDL_COLOR_LIB(l);
	SDL_Event_LIB(l);
	SDL_Texture_LIB(l);
	SDL_GLContext_LIB(l);
	SDL_PIXEL_FORMAT_LIB(l);
	SDL_SURFACE_LIB(l);
	//Custom classes and functions
	LUA_INI_LIB(l);	
	kpVECTOR3FLIB(l);
	kpMATRIX4FLIB(l);
	kpQUATERNIONLIB(l);
	kpTRANSFROMLIB(l);
	kpLOGLIB(l);
	kpTIMERLIB(l);
	return 0;
}