--require("./bin/scripts/core/windowflags")
--require("./bin/scripts/core/SDLEvent")
--require("./bin/scripts/core/game")
require("./bin/scripts/core/core")
require("./bin/scripts/core/kernel")
--local wflag = winFlags()
--local etype = eventType()
--local eKey = keyCode()
--local FSM = kpFSM:Create()
--local win = SDL_Window:new()
--win = createWindow("DanceHall Kombat 1.0", 100, 100, 600, 400, wflag.SDL_WINDOW_SHOWN)
--local render = SDL_Renderer:new()
--render = createRenderer(win)
--run = true
--local mainEvent = SDL_Event:new()
-----------------------------------------------
--local img = SDL_Texture:new()
--img = loadTexture(render, "bin/resources/nvidia_1.png")
--local img1 = SDL_Texture:new()
--img1 = loadTexture(render, "bin/resources/test.jpg")
-----------------------------------------------
local k = Kernel:Create()
k:onInit()
k:onExecute(true)
k:onDestroy()
-----------------------------------------------
--while run and QSDL(mainEvent) == false do
--	pollEvent(mainEvent)
	--handle events here	
	
	--update here
--	clearRender(render)
--	if checkKeyDown(mainEvent, eKey.SDLK_1) == true then
--			print("key was pressed")		
--	end
	--render here
--	renderCopy(render, img1, 100, -25, 500, 432)
--	renderCopy(render, img, 10, 50, 50, 50)
--	flipRender(render)
--end

----------------------------------------------------
--json test
-------------------------------------------------------
--[[
local JSON = package("json")

local m = {}
m.x = 10
m.y = 10
m.offX = 5
m.offY = 5
m.w = 20
m.h = 20

print(m.x)

local raw_json_text = JSON:encode(m)

print(m)
print(raw_json_text)
local p = "bin/save/"
local fie = "file.json"
--writeToFile(p, fie, raw_json_text)

local f = readFile(p .. fie)

local s = f:read("*a")
print(s)
f:close()]]