require("./bin/scripts/core/windowflags")
Window = {}
local wflag = winFlags()
function Window:Create(name, x, y, w, h)

	Window.x = x
	Window.y = y
	Window.w = w
	Window.h = h
	Window.refreshRate = 60
	Window.name = name
	Window.win = SDL_Window:new()
	Window.render = SDL_Renderer:new()
	Window.context = nil
	Window.event = SDL_Event:new()
	function Window:onInit()
	Window.win = createWindow(Window.name, Window.x, Window.y, Window.w, Window.h, wflag.SDL_WINDOW_SHOWN)
	Window.render = createRenderer(Window.win)
	return Window
	end

	function Window:begin()		
	Window.render:clear()
	end

	function Window:flip()
	Window.render:flip()
	end


return Window
end